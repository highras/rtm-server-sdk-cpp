#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getSendMessageQuest(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "sendmsg", sign, salt);

    FPQWriter qw(10, "sendmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("to", to);
    qw.param("mid", MidGenerator::genMid());
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

int32_t RTMServerClient::sendMessage(int32_t& modifyTime, int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, mtype, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendMessage(int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, mtype, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getSendMessagesQuest(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "sendmsgs", sign, salt);

    FPQWriter qw(10, "sendmsgs");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("tos", tos);
    qw.param("mid", MidGenerator::genMid());
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

int32_t RTMServerClient::sendMessages(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, mtype, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendMessages(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, mtype, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getSendGroupMessageQuest(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "sendgroupmsg", sign, salt);

    FPQWriter qw(10, "sendgroupmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("gid", gid);
    qw.param("mid", MidGenerator::genMid());
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

int32_t RTMServerClient::sendGroupMessage(int32_t& modifyTime, int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, mtype, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendGroupMessage(int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, mtype, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getSendRoomMessageQuest(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "sendroommsg", sign, salt);

    FPQWriter qw(10, "sendroommsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("rid", rid);
    qw.param("mid", MidGenerator::genMid());
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

int32_t RTMServerClient::sendRoomMessage(int32_t& modifyTime, int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, mtype, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendRoomMessage(int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, mtype, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getBroadcastMessageQuest(int64_t from, int8_t mtype, const string& message, const string& attrs)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "broadcastmsg", sign, salt);

    FPQWriter qw(9, "broadcastmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("mid", MidGenerator::genMid());
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

int32_t RTMServerClient::broadcastMessage(int32_t& modifyTime, int64_t fromUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, mtype, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::broadcastMessage(int64_t fromUid, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, mtype, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetGroupMessageQuest(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes, int64_t uid) {
    int32_t ts = slack_real_sec(); 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(ts, "getgroupmsg", sign, salt); 

    FPQWriter qw(12, "getgroupmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    qw.param("mtypes", mtypes);
    qw.param("uid", uid);
    return qw.take();
}

void RTMServerClient::_getCommonMessage(vector<struct CommonMessage>& messageList, FPAReader& reader, bool isP2P)
{
    if (!isP2P)
        messageList = reader.get("msgs", messageList);
    else {
        vector<struct P2PMessage> msgs;
        msgs = reader.get("msgs", msgs);
        
        for (auto& msg: msgs) {
            if (msg.deleted)
                continue;
            CommonMessage commonMessage;
            commonMessage.id = msg.id;
            commonMessage.from = msg.direction;
            commonMessage.mtype = msg.mtype;
            commonMessage.mid = msg.mid;
            commonMessage.msg = msg.msg;
            commonMessage.attrs = msg.attrs;
            commonMessage.mtime = msg.mtime;
            messageList.push_back(commonMessage);
        }
    }
}

HistoryMessageResult RTMServerClient::_buildHistoryMessageResult(int64_t toId, FPAnswerPtr answer, bool isP2P)
{
    HistoryMessageResult result;
    FPAReader ar(answer);
    result.count = ar.getInt("num");
    result.lastCursorId = ar.getInt("lastid");
    result.beginMsec = ar.getInt("begin");
    result.endMsec = ar.getInt("end");
    result.messages = vector<HistoryMessage>();

    vector<struct CommonMessage> msgs;
    _getCommonMessage(msgs, ar, isP2P);

    for (auto& msg: msgs) {
        HistoryMessage historyMsg;
        historyMsg.cursorId = msg.id;
        historyMsg.fromUid = msg.from;
        historyMsg.toId = toId;
        historyMsg.messageType = msg.mtype;
        historyMsg.messageId = msg.mid;
        historyMsg.message = msg.msg;
        historyMsg.attrs = msg.attrs;
        historyMsg.modifiedTime = msg.mtime;

        if (historyMsg.messageType == AudioChatMType) {
            historyMsg.audioInfo = buildAudioInfo(historyMsg.message);

            if (historyMsg.audioInfo != nullptr)
                historyMsg.message = historyMsg.audioInfo->recognizedText;
        }

        result.messages.push_back(historyMsg);
    }
    return result;
}

void RTMServerClient::_adjustHistoryMessageResultForP2PMessage(HistoryMessageResult& result, int64_t selfUid, int64_t peerUserUid)
{
    for (auto& msg: result.messages) {
        if (msg.fromUid == 1) {
            msg.fromUid = selfUid;
            msg.toId = peerUserUid;
        } else if (msg.fromUid == 2) {
            msg.fromUid = peerUserUid;
            msg.toId = selfUid;
        }
    }
}

int32_t RTMServerClient::getGroupMessage(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMessageQuest(groupId, desc, count, beginMsec, endMsec, lastId, mtypes, uid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
        result = _buildHistoryMessageResult(groupId, answer, false);
    return questResult.errorCode;
}

void RTMServerClient::getGroupMessage(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMessageQuest(groupId, desc, count, beginMsec, endMsec, lastId, mtypes, uid);
    bool status = _client->sendQuest(quest, [this, groupId, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        HistoryMessageResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
            result = _buildHistoryMessageResult(groupId, answer, false);
        callback(result, questResult.errorCode);
    }, timeout);

    if (!status)
        callback(HistoryMessageResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetRoomMessageQuest(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes, int64_t uid) { 
    int32_t ts = slack_real_sec(); 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(ts, "getroommsg", sign, salt); 
    
    FPQWriter qw(12, "getroommsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    qw.param("mtypes", mtypes);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getRoomMessage(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomMessageQuest(roomId, desc, count, beginMsec, endMsec, lastId, mtypes, uid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
        result = _buildHistoryMessageResult(roomId, answer, false);
    return questResult.errorCode;
}

void RTMServerClient::getRoomMessage(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomMessageQuest(roomId, desc, count, beginMsec, endMsec, lastId, mtypes, uid);
    bool status = _client->sendQuest(quest, [this, roomId, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        HistoryMessageResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
            result = _buildHistoryMessageResult(roomId, answer, false);
        callback(result, questResult.errorCode);
    }, timeout);

    if (!status)
        callback(HistoryMessageResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetBroadcastMessageQuest(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes, int64_t uid) { 
    int32_t ts = slack_real_sec(); 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(ts, "getbroadcastmsg", sign, salt); 
    
    FPQWriter qw(11, "getbroadcastmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    qw.param("mtypes", mtypes);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getBroadcastMessage(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getGetBroadcastMessageQuest(desc, count, beginMsec, endMsec, lastId, mtypes, uid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
        result = _buildHistoryMessageResult(0, answer, false);
    return questResult.errorCode;
}

void RTMServerClient::getBroadcastMessage(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetBroadcastMessageQuest(desc, count, beginMsec, endMsec, lastId, mtypes, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        HistoryMessageResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
            result = _buildHistoryMessageResult(0, answer, false);
        callback(result, questResult.errorCode);
    }, timeout);

    if (!status)
        callback(HistoryMessageResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetP2PMessageQuest(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes) { 
    int32_t ts = slack_real_sec(); 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(ts, "getp2pmsg", sign, salt); 
    
    FPQWriter qw(12, "getp2pmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("ouid", ouid);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    qw.param("mtypes", mtypes);
    return qw.take();
}

int32_t RTMServerClient::getP2PMessage(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int32_t timeout)
{
    FPQuestPtr quest = _getGetP2PMessageQuest(userId, otherUserId, desc, count, beginMsec, endMsec, lastId, mtypes);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult)) {
        result = _buildHistoryMessageResult(0, answer, true);
        _adjustHistoryMessageResultForP2PMessage(result, userId, otherUserId);
    }
    return questResult.errorCode;
}

void RTMServerClient::getP2PMessage(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetP2PMessageQuest(userId, otherUserId, desc, count, beginMsec, endMsec, lastId, mtypes);
    bool status = _client->sendQuest(quest, [this, userId, otherUserId, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        HistoryMessageResult result;
        if (!_checkAnswerError(answer, questResult, errorCode)) {
            result = _buildHistoryMessageResult(0, answer, true);
            _adjustHistoryMessageResultForP2PMessage(result, userId, otherUserId);
        }
        callback(result, questResult.errorCode);
    }, timeout);

    if (!status)
        callback(HistoryMessageResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetMessageQuest(int64_t mid, int64_t from, int64_t xid, int8_t type)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getmsg", sign, salt);

    FPQWriter qw(8, "getmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mid", mid);
    qw.param("from", from);
    qw.param("xid", xid);
    qw.param("type", type);
    return qw.take();
}

RetrievedMessage RTMServerClient::_buildRetrievedMessage(FPAnswerPtr answer)
{
    RetrievedMessage retrievedMessage;
    FPAReader ar(answer);
    retrievedMessage.cursorId = ar.getInt("id");
    retrievedMessage.messageType = ar.getInt("mtype");
    retrievedMessage.message = ar.getString("msg");
    retrievedMessage.attrs = ar.getString("attrs");
    retrievedMessage.modifiedTime = ar.getInt("mtime");
    return retrievedMessage;
}

int32_t RTMServerClient::getMessage(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout)
{
    FPQuestPtr quest = _getGetMessageQuest(mid, fromUid, toId, (int8_t)messageCategory);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
        retrievedMessage = _buildRetrievedMessage(answer);
    return result.errorCode;
}

void RTMServerClient::getMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetMessageQuest(mid, fromUid, toId, (int8_t)messageCategory);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        RetrievedMessage retrievedMessage;
        if (!_checkAnswerError(answer, result, errorCode))
            retrievedMessage = _buildRetrievedMessage(answer);
        callback(retrievedMessage, result.errorCode);
    }, timeout);

    if (!status)
        callback(RetrievedMessage(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDeleteMessageQuest(int64_t mid, int64_t from, int64_t xid, int8_t type)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "delmsg", sign, salt);

    FPQWriter qw(8, "delmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("mid", mid);
    qw.param("from", from);
    qw.param("xid", xid);
    qw.param("type", type);
    return qw.take();
}

int32_t RTMServerClient::deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteMessageQuest(mid, fromUid, toId, (int8_t)messageCategory);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteMessageQuest(mid, fromUid, toId, (int8_t)messageCategory);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}