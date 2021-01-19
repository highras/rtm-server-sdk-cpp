#include "RTMServerClient.h"
#include "FPJson.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getFileTokenQuest(const SendFileInfo& info)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    string cmd = _getSendFileType(info.type);
    _makeSignAndSalt(ts, "filetoken", sign, salt);

    int32_t size = 7;
    if (info.type == BroadcastFile)
        size = 6;
    FPQWriter qw(size, "filetoken");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("from", info.from);
    qw.param("cmd", cmd);
    if (info.type == P2PFile)
        qw.param("to", info.toId);
    else if (info.type == MultiFiles)
        qw.param("tos", info.toIds);
    else if (info.type == RoomFile)
        qw.param("rid", info.toId);
    else if (info.type == GroupFile)
        qw.param("gid", info.toId);
    return qw.take();
}

string RTMServerClient::_getSendFileType(FileTokenType sendType)
{
    if (sendType == P2PFile)
        return "sendfile";
    if (sendType == MultiFiles)
        return "sendfiles";
    if (sendType == RoomFile)
        return "sendroomfile";
    if (sendType == GroupFile)
        return "GroupFile";
    return "BroadcastFile";
}

int32_t RTMServerClient::_fileTokenAction(string& token, string& endpoint, int64_t from, FileTokenType fileType, int64_t toId, const set<int64_t>& toIds, int32_t timeout)
{
    SendFileInfo info;
    info.type = fileType;
    info.toId = toId;
    info.toIds = toIds;
    info.from = from;
    FPQuestPtr quest = _getFileTokenQuest(info);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    { 
        FPAReader ar(answer);
        token = ar.getString("token");
        endpoint = ar.getString("endpoint");
    }
    return result.errorCode;
}

void RTMServerClient::_fileTokenAction(int64_t from, FileTokenType fileType, int64_t toId, const set<int64_t>& toIds, std::function<void (string token, string endpoint, int32_t errorCode)> callback, int32_t timeout)
{
    SendFileInfo info;
    info.type = fileType;
    info.toId = toId;
    info.toIds = toIds;
    info.from = from;
    FPQuestPtr quest = _getFileTokenQuest(info);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string token, endpoint;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            token = ar.getString("token");
            endpoint = ar.getString("endpoint");
        }
        callback(token, endpoint, result.errorCode);
    }, timeout);

    if (!status)
        callback("", "", FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::fileToken(string& token, string& endpoint, int64_t from, FileTokenType fileType, int64_t toId, int32_t timeout)
{
    return _fileTokenAction(token, endpoint, from, fileType, toId, {}, timeout);
}

int32_t RTMServerClient::fileToken(string& token, string& endpoint, int64_t from, FileTokenType fileType, const set<int64_t>& toIds, int32_t timeout)
{
    return _fileTokenAction(token, endpoint, from, fileType, 0, toIds, timeout);
}

void RTMServerClient::fileToken(int64_t from, FileTokenType fileType, int64_t toId, std::function<void (string token, string endpoint, int32_t errorCode)> callback, int32_t timeout)
{
    _fileTokenAction(from, fileType, toId, {}, callback, timeout);
}

void RTMServerClient::fileToken(int64_t from, FileTokenType fileType, const set<int64_t>& toIds, std::function<void (string token, string endpoint, int32_t errorCode)> callback, int32_t timeout)
{
    _fileTokenAction(from, fileType, 0, toIds, callback, timeout);
}

void RTMServerClient::_activeFileGateClient(string endpoint, TCPClientPtr client)
{
    lock_guard<mutex> lck(_fileClientMapLock);
    auto it = _fileClientMap.find(endpoint);
    if (it != _fileClientMap.end()) {
        it->second[client] = TimeUtil::curr_sec();
    } else {
        _fileClientMap[endpoint] = { {client, TimeUtil::curr_sec()} };
    }
}

TCPClientPtr RTMServerClient::_fecthFileGateClient(string endpoint)
{
    lock_guard<mutex> lck(_fileClientMapLock);
    auto it = _fileClientMap.find(endpoint);
    if (it != _fileClientMap.end()) {
        for (auto& kv: it->second)
            return kv.first;
    }
    return nullptr;
}

void RTMServerClient::_updateTimeout(int32_t& timeout, int64_t& lastActionTimestamp)
{
    int64_t currMsec = TimeUtil::curr_msec();

    timeout -= (int32_t)((currMsec - lastActionTimestamp) / 1000);

    lastActionTimestamp = currMsec;
}

bool RTMServerClient::loadFile(const string& filePath, string& fileData)
{
    std::ifstream file(filePath);
    if (!file)
        return false;
    fileData.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return true;
}

FPQuestPtr RTMServerClient::_getSendFileQuest(const string& token, int64_t from, SendFileInfo info, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int64_t& mid)
{
    string fileMD5 = _calcMD5(fileData);
    transform(fileMD5.begin(), fileMD5.end(), fileMD5.begin(), ::tolower);
    string sign = _calcMD5(fileMD5 + ":" + token);
    transform(sign.begin(), sign.end(), sign.begin(), ::tolower);
    shared_ptr<FPQWriter> qw;
    if (info.type == P2PFile) {
        qw.reset(new FPQWriter(8, "sendfile"));
        qw->param("to", to);
    } else if (info.type == MultiFiles) {
        qw.reset(new FPQWriter(8, "sendfiles"));
        qw->param("tos", tos);
    } else if (info.type == GroupFile) {
        qw.reset(new FPQWriter(8, "sendgroupfile"));
        qw->param("gid", gid);
    } else if (info.type == RoomFile) {
        qw.reset(new FPQWriter(8, "sendroomfile"));
        qw->param("rid", rid);
    } else {
        qw.reset(new FPQWriter(7, "broadcastfile"));
    }

    mid = MidGenerator::genMid();
    qw->param("pid", _pid);
    qw->param("token", token);
    qw->param("mtype", mtype);
    qw->param("from", from);
    qw->param("mid", mid);
    qw->param("file", fileData);
    qw->param("attrs", _buildFileAttrs(sign, fileName, fileExtension, attrs));
    return qw->take();
}

int32_t RTMServerClient::_sendFileProcess(int64_t& mid, FileTokenType tokenType, int64_t from, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    if (!checkFileMessageType(mtype))
        return RTM_EC_INVALID_MTYPE;
    int64_t lastActionTimestamp = TimeUtil::curr_msec();
    if (timeout == 0)
        timeout = _questTimeout;

    SendFileInfo info;
    info.from = from;
    if (tokenType == P2PFile)
        info.toId = to;
    if (tokenType == MultiFiles)
        info.toIds = tos;
    if (tokenType == GroupFile)
        info.toId = gid;
    if (tokenType == RoomFile)
        info.toId = rid;
    info.type = tokenType;

    string token, endpoint;
    int32_t errorCode = _fileTokenAction(token, endpoint, from, tokenType, info.toId, info.toIds, timeout);

    if (errorCode != FPNN_EC_OK)
        return errorCode;

    _updateTimeout(timeout, lastActionTimestamp);
    if (timeout <= 0)
        return FPNN_EC_CORE_TIMEOUT;

    FPQuestPtr quest = _getSendFileQuest(token, from, info, to, tos, gid, rid, mtype, fileData, fileName, fileExtension, attrs, mid);
    TCPClientPtr client = _fecthFileGateClient(endpoint);

    if (!client)
    {
        client = TCPClient::createClient(endpoint, true);
        if (client->connect())
            _activeFileGateClient(endpoint, client);
        else
            return FPNN_EC_CORE_INVALID_CONNECTION;
    }

    _updateTimeout(timeout, lastActionTimestamp);
    if (timeout <= 0)
        return FPNN_EC_CORE_TIMEOUT;

    FPAnswerPtr answer = client->sendQuest(quest, timeout);
    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::_sendFileProcess(FileTokenType tokenType, int64_t from, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, const string& fileName, 
        std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    if (!checkFileMessageType(mtype))
    {
        callback(0, RTM_EC_INVALID_MTYPE);
        return;
    }
    int64_t lastActionTimestamp = TimeUtil::curr_msec();
    if (timeout == 0)
        timeout = _questTimeout;

    SendFileInfo info;
    info.from = from;
    if (tokenType == P2PFile)
        info.toId = to;
    if (tokenType == MultiFiles)
        info.toIds = tos;
    if (tokenType == GroupFile)
        info.toId = gid;
    if (tokenType == RoomFile)
        info.toId = rid;
    info.type = tokenType;

    _fileTokenAction(from, tokenType, info.toId, info.toIds, [this, from, info, to, tos, gid, rid, mtype, fileData, fileName, fileExtension, attrs, timeout, callback, lastActionTimestamp](string token, string endpoint, int32_t errorCode) {
        if (errorCode != FPNN_EC_OK) {
            callback(0, errorCode);
            return;
        }

        int32_t timeout2 = timeout;
        int64_t lastActionTimestamp2 = lastActionTimestamp;

        _updateTimeout(timeout2, lastActionTimestamp2);
        if (timeout2 <= 0) {
            callback(0, FPNN_EC_CORE_TIMEOUT);
            return;
        }

        int64_t mid = 0;
        FPQuestPtr quest = _getSendFileQuest(token, from, info, to, tos, gid, rid, mtype, fileData, fileName, fileExtension, attrs, mid);
        TCPClientPtr client = _fecthFileGateClient(endpoint);

        if (!client) {
            client = TCPClient::createClient(endpoint, true);
            if (client->connect())
                _activeFileGateClient(endpoint, client);
            else {
                callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
                return;
            }
        }

        _updateTimeout(timeout2, lastActionTimestamp2);
        if (timeout2 <= 0) {
            callback(0, FPNN_EC_CORE_TIMEOUT);
            return;
        }

        bool status = client->sendQuest(quest, [this, client, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
            QuestResult result;
            if (!_checkAnswerError(answer, result)) {
                callback(mid, result.errorCode);
            } else
                callback(0, result.errorCode);
        }, timeout2);

        if (!status)
            callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
    }, timeout);
}

int32_t RTMServerClient::sendFile(int64_t& mid, int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    return _sendFileProcess(mid, P2PFile, fromUid, toUid, {}, 0, 0, mtype, fileData, fileName, fileExtension, attrs, timeout); 
}

void RTMServerClient::sendFile(int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    _sendFileProcess(P2PFile, fromUid, toUid, {}, 0, 0, mtype, fileData, fileName, callback, fileExtension, attrs, timeout);
}

int32_t RTMServerClient::sendFiles(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    return _sendFileProcess(mid, MultiFiles, fromUid, 0, toUids, 0, 0, mtype, fileData, fileName, fileExtension, attrs, timeout);
}

void RTMServerClient::sendFiles(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    _sendFileProcess(MultiFiles, fromUid, 0, toUids, 0, 0, mtype, fileData, fileName, callback, fileExtension, attrs, timeout);
}

int32_t RTMServerClient::sendGroupFile(int64_t& mid, int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    return _sendFileProcess(mid, GroupFile, fromUid, 0, {}, groupId, 0, mtype, fileData, fileName, fileExtension, attrs, timeout);
}

void RTMServerClient::sendGroupFile(int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    _sendFileProcess(GroupFile, fromUid, 0, {}, groupId, 0, mtype, fileData, fileName, callback, fileExtension, attrs, timeout);
}

int32_t RTMServerClient::sendRoomFile(int64_t& mid, int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    return _sendFileProcess(mid, RoomFile, fromUid, 0, {}, 0, roomId, mtype, fileData, fileName, fileExtension, attrs, timeout); 
}

void RTMServerClient::sendRoomFile(int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    _sendFileProcess(RoomFile, fromUid, 0, {}, 0, roomId, mtype, fileData, fileName, callback, fileExtension, attrs, timeout);
}

int32_t RTMServerClient::broadcastFile(int64_t& mid, int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    return _sendFileProcess(mid, BroadcastFile, fromUid, 0, {}, 0, 0, mtype, fileData, fileName, fileExtension, attrs, timeout); 
}

void RTMServerClient::broadcastFile(int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension, const map<string, string>& attrs, int32_t timeout)
{
    _sendFileProcess(BroadcastFile, fromUid, 0, {}, 0, 0, mtype, fileData, fileName, callback, fileExtension, attrs, timeout);
}

void RTMServerClient::buildFileInfo(RTMMessage& message)
{
    message.fileInfo = make_shared<FileInfo>();
    parseFileMessage(message);
    parseFileAttrs(message);
}

void RTMServerClient::parseFileMessage(RTMMessage& message)
{
    rapidjson::Document document;
    if (document.Parse(message.message.c_str()).HasParseError())
        return;
    if (!document.IsObject())
        return;
    if (document.HasMember("url") && document["url"].IsString())
        message.fileInfo->url = document["url"].GetString();
    if (document.HasMember("size") && document["size"].IsInt())
        message.fileInfo->size = document["size"].GetInt();
    if (message.messageType == ImageFileType)
    {
        if (document.HasMember("surl") && document["surl"].IsString())
            message.fileInfo->surl = document["surl"].GetString();
    }
    message.message = "";
}

void RTMServerClient::parseFileAttrs(RTMMessage& message)
{
    rapidjson::Document document;
    if (document.Parse(message.attrs.c_str()).HasParseError())
        return;
    if (!document.IsObject())
        return;
    if (document.HasMember("rtm"))
    {
        const auto& rtm = document["rtm"];
        auto iter = rtm.FindMember("type");
        if (iter != rtm.MemberEnd() && iter->value.IsString())
        {
            string type = iter->value.GetString();
            if (type == "audiomsg")
                message.fileInfo->isRTMAudio = true;
        }
        if (message.fileInfo->isRTMAudio == true)
        {
            iter = rtm.FindMember("lang");
            if (iter != rtm.MemberEnd() && iter->value.IsString())
                message.fileInfo->language = iter->value.GetString();
            iter = rtm.FindMember("duration");
            if (iter != rtm.MemberEnd() && iter->value.IsInt())
                message.fileInfo->duration = iter->value.GetInt();
        }
    }
    if (document.HasMember("custom"))
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document["custom"].Accept(writer);
        message.attrs = buffer.GetString();
    }
}

bool RTMServerClient::checkFileMessageType(int8_t messageType)
{
    if (messageType >= ImageFileType && messageType <= NormalFileType)
        return true;
    return false;
}

string RTMServerClient::_buildFileAttrs(const string& sign, const string& fileName, const string& fileExtension, const map<string, string>& attrs)
{
    Json attr;
    Json rtm;
    rtm.add("sign", sign);

    if (!fileName.empty()) 
        rtm.add("filename", fileName);
    if (!fileExtension.empty())
        rtm.add("fileExtension", fileExtension);
    if (!attrs.empty())
        attr.add("custom", attrs);
    else
        attr.add("custom", "");
    return attr.str();
}
