#include <fstream>
#include <streambuf>
#include "md5.h"
#include "hex.h"
#include "MidGenerator.h"
#include "RTMServerClient.h"
#include "FPLog.h"

using namespace rtm;

RTMServerClient::RTMServerClient(int32_t pid, const string& secret, const string& endpoint, bool reconnect, int32_t timeout, 
        int32_t duplicateCacheSize): _pid(pid), _secret(secret)
{
    MidGenerator::init(slack_real_msec());
    _client = TCPClient::createClient(endpoint, reconnect);
    _processor.reset(new RTMProcessor(duplicateCacheSize));
    if (_client) {
        _client->setQuestTimeout(timeout);
        _client->setQuestProcessor(_processor);
    }
}

RTMServerClient::~RTMServerClient()
{

}

void RTMServerClient::setServerMonitor(shared_ptr<RTMServerMonitor> serverMonitor)
{
    _processor->setServerMonitor(serverMonitor);
}

bool RTMServerClient::connected()
{
    return _client->connected();
}

const string& RTMServerClient::endpoint()
{
    return _client->endpoint();
}

void RTMServerClient::setQuestTimeout(int seconds)
{
    _client->setQuestTimeout(seconds);
}

void RTMServerClient::setAutoReconnect(bool autoReconnect)
{
    _client->setAutoReconnect(autoReconnect);
}

bool RTMServerClient::enableEncryptorByDerData(const string &derData, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByDerData(derData, packageMode, reinforce);
}

bool RTMServerClient::enableEncryptorByPemData(const string &PemData, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByPemData(PemData, packageMode, reinforce);
}

bool RTMServerClient::enableEncryptorByDerFile(const char *derFilePath, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByDerFile(derFilePath, packageMode, reinforce);
}

bool RTMServerClient::enableEncryptorByPemFile(const char *pemFilePath, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByPemFile(pemFilePath, packageMode, reinforce);
}

void RTMServerClient::enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode, bool reinforce)
{
    _client->enableEncryptor(curve, peerPublicKey, packageMode, reinforce);
}

string RTMServerClient::_calcMD5(const string& content)
{
    unsigned char digest[16];
    md5_checksum(digest, content.c_str(), content.size());
    char hexstr[32 + 1];
    Hexlify(hexstr, digest, sizeof(digest));
    return string(hexstr);
}

void RTMServerClient::_makeSignAndSalt(string& sign, int64_t& salt)
{
    salt = MidGenerator::genMid();
    string content = to_string(_pid) + ":" + _secret + ":" + to_string(salt);
    sign = _calcMD5(content); 
}

FPQuestPtr RTMServerClient::_getSendMessageQuest(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, int64_t& mid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(9, "sendmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("to", to);
    if (mid == 0)
        mid = MidGenerator::genMid();
    qw.param("mid", mid);
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

bool RTMServerClient::_checkAnswerError(FPAnswerPtr answer, QuestResult& result, int32_t errorCode)
{
    if (!answer) 
    {
        result.errorCode = -1;
        result.errorInfo = "answer is null";
        return true;
    }
    if (errorCode > 0 || answer->status()) 
    {
        FPAReader ar(answer);
        result.errorCode = ar.getInt("code");
        result.errorInfo = ar.getString("ex");
        return true; 
    }
    return false;
}

SendMessageResult RTMServerClient::sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(from, to, mtype, message, attrs, mid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    SendMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.mtime = ar.getInt("mtime");
        result.mid = mid;
    }
    return result;
}

void RTMServerClient::sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(from, to, mtype, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        SendMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.mtime = ar.getInt("mtime");
            result.mid = mid;
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        SendMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getSendMessagesQuest(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, int64_t& mid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(9, "sendmsgs");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("tos", tos);
    if (mid == 0)
        mid = MidGenerator::genMid();
    qw.param("mid", mid);
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

SendMessageResult RTMServerClient::sendMessages(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(from, tos, mtype, message, attrs, mid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    SendMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.mtime = ar.getInt("mtime");
        result.mid = mid;
    }
    return result;
}

void RTMServerClient::sendMessages(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(from, tos, mtype, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        SendMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.mtime = ar.getInt("mtime");
            result.mid = mid;
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        SendMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getSendGroupMessageQuest(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, int64_t& mid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(9, "sendgroupmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("gid", gid);
    if (mid == 0)
        mid = MidGenerator::genMid();
    qw.param("mid", mid);
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

SendMessageResult RTMServerClient::sendGroupMessage(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(from, gid, mtype, message, attrs, mid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    SendMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.mtime = ar.getInt("mtime");
        result.mid = mid;
    }
    return result;
}

void RTMServerClient::sendGroupMessage(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(from, gid, mtype, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        SendMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.mtime = ar.getInt("mtime");
            result.mid = mid;
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        SendMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getSendRoomMessageQuest(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, int64_t& mid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(9, "sendroommsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("mtype", mtype);
    qw.param("from", from);
    qw.param("rid", rid);
    if (mid == 0)
        mid = MidGenerator::genMid();
    qw.param("mid", mid);
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

SendMessageResult RTMServerClient::sendRoomMessage(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(from, rid, mtype, message, attrs, mid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    SendMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.mtime = ar.getInt("mtime");
        result.mid = mid;
    }
    return result;
}

void RTMServerClient::sendRoomMessage(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(from, rid, mtype, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        SendMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.mtime = ar.getInt("mtime");
            result.mid = mid;
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        SendMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getBroadcastMessageQuest(int64_t from, int8_t mtype, const string& message, const string& attrs, int64_t& mid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(8, "broadcastmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("mtype", mtype);
    qw.param("from", from);
    if (mid == 0)
        mid = MidGenerator::genMid();
    qw.param("mid", mid);
    qw.param("msg", message);
    qw.param("attrs", attrs);
    return qw.take();
}

SendMessageResult RTMServerClient::broadcastMessage(int64_t from, int8_t mtype, const string& message, const string& attrs, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(from, mtype, message, attrs, mid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    SendMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.mtime = ar.getInt("mtime");
        result.mid = mid;
    }
    return result;
}

void RTMServerClient::broadcastMessage(int64_t from, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(from, mtype, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        SendMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.mtime = ar.getInt("mtime");
            result.mid = mid;
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        SendMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddFriendsQuest(int64_t uid, const set<int64_t>& friends)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "addfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("friends", friends);
    return qw.take();
}

QuestResult RTMServerClient::addFriends(int64_t uid, const set<int64_t>& friends, int32_t timeout)
{
    FPQuestPtr quest = _getAddFriendsQuest(uid, friends);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddFriendsQuest(uid, friends);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getDeleteFriendsQuest(int64_t uid, const set<int64_t>& friends)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "delfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("friends", friends);
    return qw.take();
}

QuestResult RTMServerClient::deleteFriends(int64_t uid, const set<int64_t>& friends, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteFriendsQuest(uid, friends);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::deleteFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteFriendsQuest(uid, friends);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetFriendsQuest(int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "getfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    return qw.take();
}

GetFriendsResult RTMServerClient::getFriends(int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getGetFriendsQuest(uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetFriendsResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.uids = ar.get("uids", result.uids);
    }
    return result;
}

void RTMServerClient::getFriends(int64_t uid, std::function<void (GetFriendsResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetFriendsQuest(uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetFriendsResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.uids = ar.get("uids", result.uids);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetFriendsResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getIsFriendQuest(int64_t uid, int64_t fuid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "isfriend");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("fuid", fuid);
    return qw.take();
}

IsFriendResult RTMServerClient::isFriend(int64_t uid, int64_t fuid, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendQuest(uid, fuid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    IsFriendResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.ok = ar.getBool("ok");
    }
    return result;
}

void RTMServerClient::isFriend(int64_t uid, int64_t fuid, std::function<void (IsFriendResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendQuest(uid, fuid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        IsFriendResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.ok = ar.getBool("ok");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        IsFriendResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getIsFriendsQuest(int64_t uid, const set<int64_t>& fuids)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "isfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("fuids", fuids);
    return qw.take();
}

IsFriendsResult RTMServerClient::isFriends(int64_t uid, const set<int64_t>& fuids, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendsQuest(uid, fuids);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    IsFriendsResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.fuids = ar.get("fuids", result.fuids);
    }
    return result;
}

void RTMServerClient::isFriends(int64_t uid, const set<int64_t>& fuids, std::function<void (IsFriendsResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendsQuest(uid, fuids);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        IsFriendsResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.fuids = ar.get("fuids", result.fuids);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        IsFriendsResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddGroupMembersQuest(int64_t gid, const set<int64_t>& uids)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "addgroupmembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("uids", uids);
    return qw.take();
}

QuestResult RTMServerClient::addGroupMembers(int64_t gid, const set<int64_t>& uids, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupMembersQuest(gid, uids);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addGroupMembers(int64_t gid, const set<int64_t>& uids, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupMembersQuest(gid, uids);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getDeleteGroupMembersQuest(int64_t gid, const set<int64_t>& uids)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "delgroupmembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("uids", uids);
    return qw.take();
}

QuestResult RTMServerClient::deleteGroupMembers(int64_t gid, const set<int64_t>& uids, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupMembersQuest(gid, uids);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::deleteGroupMembers(int64_t gid, const set<int64_t>& uids, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupMembersQuest(gid, uids);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getDeleteGroupQuest(int64_t gid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "delgroup");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    return qw.take();
}

QuestResult RTMServerClient::deleteGroup(int64_t gid, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupQuest(gid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::deleteGroup(int64_t gid, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupQuest(gid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetGroupMembersQuest(int64_t gid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "getgroupmembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    return qw.take();
}

GetGroupMembersResult RTMServerClient::getGroupMembers(int64_t gid, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMembersQuest(gid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetGroupMembersResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.uids = ar.get("uids", result.uids);
    }
    return result;
}

void RTMServerClient::getGroupMembers(int64_t gid, std::function<void (GetGroupMembersResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMembersQuest(gid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetGroupMembersResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.uids = ar.get("uids", result.uids);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetGroupMembersResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getIsGroupMemberQuest(int64_t gid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "isgroupmember");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("uid", uid);
    return qw.take();
}

IsGroupMemberResult RTMServerClient::isGroupMember(int64_t gid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getIsGroupMemberQuest(gid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    IsGroupMemberResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.ok = ar.getBool("ok");
    }
    return result;
}

void RTMServerClient::isGroupMember(int64_t gid, int64_t uid, std::function<void (IsGroupMemberResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsGroupMemberQuest(gid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        IsGroupMemberResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.ok = ar.getBool("ok");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        IsGroupMemberResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetUserGroupsQuest(int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "getusergroups");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    return qw.take();
}

GetUserGroupsResult RTMServerClient::getUserGroups(int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserGroupsQuest(uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetUserGroupsResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.gids = ar.get("gids", result.gids);
    }
    return result;
}

void RTMServerClient::getUserGroups(int64_t uid, std::function<void (GetUserGroupsResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserGroupsQuest(uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetUserGroupsResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.gids = ar.get("gids", result.gids);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetUserGroupsResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetTokenQuest(int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "gettoken");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    return qw.take();
}

GetTokenResult RTMServerClient::getToken(int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getGetTokenQuest(uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetTokenResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.token = ar.getString("token");
    }
    return result;
}

void RTMServerClient::getToken(int64_t uid, std::function<void (GetTokenResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetTokenQuest(uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetTokenResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.token = ar.getString("token");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetTokenResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetOnlineUsersQuest(const set<int64_t>& uids)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "getonlineusers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uids", uids);
    return qw.take();
}

GetOnlineUsersResult RTMServerClient::getOnlineUsers(const set<int64_t>& uids, int32_t timeout)
{
    FPQuestPtr quest = _getGetOnlineUsersQuest(uids);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetOnlineUsersResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.uids = ar.get("uids", result.uids);
    }
    return result;
}

void RTMServerClient::getOnlineUsers(const set<int64_t>& uids, std::function<void (GetOnlineUsersResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetOnlineUsersQuest(uids);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetOnlineUsersResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.uids = ar.get("uids", result.uids);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetOnlineUsersResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddGroupBanQuest(int64_t gid, int64_t uid, int32_t btime)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(6, "addgroupban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("uid", uid);
    qw.param("btime", btime);
    return qw.take();
}

QuestResult RTMServerClient::addGroupBan(int64_t gid, int64_t uid, int32_t btime, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupBanQuest(gid, uid, btime);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addGroupBan(int64_t gid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupBanQuest(gid, uid, btime);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getRemoveGroupBanQuest(int64_t gid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "removegroupban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("uid", uid);
    return qw.take();
}

QuestResult RTMServerClient::removeGroupBan(int64_t gid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveGroupBanQuest(gid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::removeGroupBan(int64_t gid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveGroupBanQuest(gid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddRoomBanQuest(int64_t rid, int64_t uid, int32_t btime)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(6, "addroomban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("rid", rid);
    qw.param("uid", uid);
    qw.param("btime", btime);
    return qw.take();
}

QuestResult RTMServerClient::addRoomBan(int64_t rid, int64_t uid, int32_t btime, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomBanQuest(rid, uid, btime);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addRoomBan(int64_t rid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomBanQuest(rid, uid, btime);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getRemoveRoomBanQuest(int64_t rid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "removeroomban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

QuestResult RTMServerClient::removeRoomBan(int64_t rid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveRoomBanQuest(rid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::removeRoomBan(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveRoomBanQuest(rid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddProjectBlackQuest(int64_t uid, int32_t btime)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "addprojectblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("btime", btime);
    return qw.take();
}

QuestResult RTMServerClient::addProjectBlack(int64_t uid, int32_t btime, int32_t timeout)
{
    FPQuestPtr quest = _getAddProjectBlackQuest(uid, btime);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addProjectBlack(int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddProjectBlackQuest(uid, btime);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getRemoveProjectBlackQuest(int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "removeprojectblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    return qw.take();
}

QuestResult RTMServerClient::removeProjectBlack(int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveProjectBlackQuest(uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::removeProjectBlack(int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveProjectBlackQuest(uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getIsBanOfGroupQuest(int64_t gid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "isbanofgroup");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("uid", uid);
    return qw.take();
}

IsBanOfGroupResult RTMServerClient::isBanOfGroup(int64_t gid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfGroupQuest(gid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    IsBanOfGroupResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.ok = ar.getBool("ok");
    }
    return result;
}

void RTMServerClient::isBanOfGroup(int64_t gid, int64_t uid, std::function<void (IsBanOfGroupResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfGroupQuest(gid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        IsBanOfGroupResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.ok = ar.getBool("ok");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        IsBanOfGroupResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getIsBanOfRoomQuest(int64_t rid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "isbanofroom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

IsBanOfRoomResult RTMServerClient::isBanOfRoom(int64_t rid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfRoomQuest(rid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    IsBanOfRoomResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.ok = ar.getBool("ok");
    }
    return result;
}

void RTMServerClient::isBanOfRoom(int64_t rid, int64_t uid, std::function<void (IsBanOfRoomResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfRoomQuest(rid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        IsBanOfRoomResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.ok = ar.getBool("ok");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        IsBanOfRoomResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getIsProjectBlackQuest(int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(4, "isprojectblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    return qw.take();
}

IsProjectBlackResult RTMServerClient::isProjectBlack(int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getIsProjectBlackQuest(uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    IsProjectBlackResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.ok = ar.getBool("ok");
    }
    return result;
}

void RTMServerClient::isProjectBlack(int64_t uid, std::function<void (IsProjectBlackResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsProjectBlackQuest(uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        IsProjectBlackResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.ok = ar.getBool("ok");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        IsProjectBlackResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getFileTokenQuest(int64_t from, const string& cmd, const FileTokenInfo& info)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    int32_t size = 6;
    if (cmd == "broadcastfile")
        size = 5;
    FPQWriter qw(size, "filetoken");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("from", from);
    qw.param("cmd", cmd);
    if (cmd == "sendfile")
        qw.param("to", info.toUid);
    else if (cmd == "sendfiles")
        qw.param("tos", info.toUids);
    else if (cmd == "sendroomfile")
        qw.param("rid", info.roomId);
    else if (cmd == "sendgroupfile")
        qw.param("gid", info.groupId);
    return qw.take();
}

FileTokenResult RTMServerClient::fileToken(int64_t from, const string& cmd, const FileTokenInfo& info, int32_t timeout)
{
    FPQuestPtr quest = _getFileTokenQuest(from, cmd, info);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    FileTokenResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.token = ar.getString("token");
        result.endpoint = ar.getString("endpoint");
    }
    return result;
}

void RTMServerClient::fileToken(int64_t from, const string& cmd, const FileTokenInfo& info, std::function<void (FileTokenResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getFileTokenQuest(from, cmd, info);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        FileTokenResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.token = ar.getString("token");
            result.endpoint = ar.getString("endpoint");
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        FileTokenResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetGroupMessageQuest(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId) { string sign; int64_t salt; _makeSignAndSalt(sign, salt); 
    FPQWriter qw(9, "getgroupmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gid", gid);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    return qw.take();
}

GetGroupMessageResult RTMServerClient::getGroupMessage(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMessageQuest(gid, desc, num, begin, end, lastId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetGroupMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.num = ar.getInt("num");
        result.lastId = ar.getInt("lastid");
        result.begin = ar.getInt("begin");
        result.end = ar.getInt("end");
        result.msgs = ar.get("msgs", result.msgs);
    }
    return result;
}

void RTMServerClient::getGroupMessage(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetGroupMessageResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMessageQuest(gid, desc, num, begin, end, lastId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetGroupMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.num = ar.getInt("num");
            result.lastId = ar.getInt("lastid");
            result.begin = ar.getInt("begin");
            result.end = ar.getInt("end");
            result.msgs = ar.get("msgs", result.msgs);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetGroupMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetRoomMessageQuest(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId) { 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(sign, salt); 
    
    FPQWriter qw(9, "getroommsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("rid", rid);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    return qw.take();
}

GetRoomMessageResult RTMServerClient::getRoomMessage(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomMessageQuest(rid, desc, num, begin, end, lastId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetRoomMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.num = ar.getInt("num");
        result.lastId = ar.getInt("lastid");
        result.begin = ar.getInt("begin");
        result.end = ar.getInt("end");
        result.msgs = ar.get("msgs", result.msgs);
    }
    return result;
}

void RTMServerClient::getRoomMessage(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetRoomMessageResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomMessageQuest(rid, desc, num, begin, end, lastId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetRoomMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.num = ar.getInt("num");
            result.lastId = ar.getInt("lastid");
            result.begin = ar.getInt("begin");
            result.end = ar.getInt("end");
            result.msgs = ar.get("msgs", result.msgs);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetRoomMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetBroadcastMessageQuest(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId) { 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(sign, salt); 
    
    FPQWriter qw(8, "getbroadcastmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    return qw.take();
}

GetBroadcastMessageResult RTMServerClient::getBroadcastMessage(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout)
{
    FPQuestPtr quest = _getGetBroadcastMessageQuest(desc, num, begin, end, lastId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetBroadcastMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.num = ar.getInt("num");
        result.lastId = ar.getInt("lastid");
        result.begin = ar.getInt("begin");
        result.end = ar.getInt("end");
        result.msgs = ar.get("msgs", result.msgs);
    }
    return result;
}

void RTMServerClient::getBroadcastMessage(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetBroadcastMessageResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetBroadcastMessageQuest(desc, num, begin, end, lastId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetBroadcastMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.num = ar.getInt("num");
            result.lastId = ar.getInt("lastid");
            result.begin = ar.getInt("begin");
            result.end = ar.getInt("end");
            result.msgs = ar.get("msgs", result.msgs);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetBroadcastMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getGetP2PMessageQuest(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId) { 
    string sign; 
    int64_t salt; 
    _makeSignAndSalt(sign, salt); 
    
    FPQWriter qw(10, "getp2pmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("ouid", ouid);
    qw.param("desc", desc);
    qw.param("num", num);
    qw.param("begin", begin);
    qw.param("end", end);
    qw.param("lastid", lastId);
    return qw.take();
}

GetP2PMessageResult RTMServerClient::getP2PMessage(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout)
{
    FPQuestPtr quest = _getGetP2PMessageQuest(uid, ouid, desc, num, begin, end, lastId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    GetP2PMessageResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.num = ar.getInt("num");
        result.lastId = ar.getInt("lastid");
        result.begin = ar.getInt("begin");
        result.end = ar.getInt("end");
        result.msgs = ar.get("msgs", result.msgs);
    }
    return result;
}

void RTMServerClient::getP2PMessage(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetP2PMessageResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetP2PMessageQuest(uid, ouid, desc, num, begin, end, lastId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        GetP2PMessageResult result;
        if (errorCode == FPNN_EC_OK) {
            FPAReader ar(answer);
            result.num = ar.getInt("num");
            result.lastId = ar.getInt("lastid");
            result.begin = ar.getInt("begin");
            result.end = ar.getInt("end");
            result.msgs = ar.get("msgs", result.msgs);
        } else
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        GetP2PMessageResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddRoomMemberQuest(int64_t rid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "addroommember");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

QuestResult RTMServerClient::addRoomMember(int64_t rid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomMemberQuest(rid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addRoomMember(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomMemberQuest(rid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getDeleteRoomMemberQuest(int64_t rid, int64_t uid)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "delroommember");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

QuestResult RTMServerClient::deleteRoomMember(int64_t rid, int64_t uid, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteRoomMemberQuest(rid, uid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::deleteRoomMember(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteRoomMemberQuest(rid, uid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(7, "addlisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gids", gids);
    qw.param("rids", rids);
    qw.param("p2p", p2p);
    qw.param("events", events);
    return qw.take();
}

QuestResult RTMServerClient::addListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, int32_t timeout)
{
    FPQuestPtr quest = _getAddListenQuest(gids, rids, p2p, events);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddListenQuest(gids, rids, p2p, events);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getRemoveListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(7, "removelisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gids", gids);
    qw.param("rids", rids);
    qw.param("p2p", p2p);
    qw.param("events", events);
    return qw.take();
}

QuestResult RTMServerClient::removeListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveListenQuest(gids, rids, p2p, events);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::removeListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddListenQuest(gids, rids, p2p, events);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getSetListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(8, "setlisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("gids", gids);
    qw.param("rids", rids);
    qw.param("p2p", p2p);
    qw.param("events", events);
    qw.param("all", all);
    return qw.take();
}

QuestResult RTMServerClient::setListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all, int32_t timeout)
{
    FPQuestPtr quest = _getSetListenQuest(gids, rids, p2p, events, all);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::setListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetListenQuest(gids, rids, p2p, events, all);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getAddDeviceQuest(int64_t uid, const string& appType, const string& deviceToken)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(6, "adddevice");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("appType", appType);
    qw.param("deviceToken", deviceToken);
    return qw.take();
}

QuestResult RTMServerClient::addDevice(int64_t uid, const string& appType, const string& deviceToken, int32_t timeout)
{
    FPQuestPtr quest = _getAddDeviceQuest(uid, appType, deviceToken);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::addDevice(int64_t uid, const string& appType, const string& deviceToken, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddDeviceQuest(uid, appType, deviceToken);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getRemoveDeviceQuest(int64_t uid, const string& deviceToken)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "removedevice");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("deviceToken", deviceToken);
    return qw.take();
}

QuestResult RTMServerClient::removeDevice(int64_t uid, const string& deviceToken, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveDeviceQuest(uid, deviceToken);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::removeDevice(int64_t uid, const string& deviceToken, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveDeviceQuest(uid, deviceToken);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getDeleteMessageQuest(int64_t mid, int64_t from, int64_t xid, int8_t type)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(7, "delmsg");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("mid", mid);
    qw.param("from", from);
    qw.param("xid", xid);
    qw.param("type", type);
    return qw.take();
}

QuestResult RTMServerClient::deleteMessage(int64_t mid, int64_t from, int64_t xid, int8_t type, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteMessageQuest(mid, from, xid, type);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::deleteMessage(int64_t mid, int64_t from, int64_t xid, int8_t type, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteMessageQuest(mid, from, xid, type);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

FPQuestPtr RTMServerClient::_getKickoutQuest(int64_t uid, const string& ce)
{
    string sign;
    int64_t salt;
    _makeSignAndSalt(sign, salt);

    FPQWriter qw(5, "kickout");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("uid", uid);
    qw.param("ce", ce);
    return qw.take();
}

QuestResult RTMServerClient::kickout(int64_t uid, const string& ce, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutQuest(uid, ce);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result;
}

void RTMServerClient::kickout(int64_t uid, const string& ce, std::function<void (QuestResult result)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutQuest(uid, ce);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (errorCode != FPNN_EC_OK)
            _checkAnswerError(answer, result); 
        callback(result);
    }, timeout);

    if (!status)
    {
        QuestResult result;
        result.errorCode = -1;
        result.errorInfo = "socket maybe closed";
        callback(result);
    }
}

bool RTMServerClient::loadFile(const string& filePath, string& fileData)
{
    std::ifstream file(filePath);
    if (!file)
        return false;
    fileData.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return true;
}

FPQuestPtr RTMServerClient::_getSendFileQuest(const string& token, int64_t from, const string& cmd, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, int64_t mid)
{
    string fileMD5 = _calcMD5(fileData);
    transform(fileMD5.begin(), fileMD5.end(), fileMD5.begin(), ::tolower);
    string sign = _calcMD5(fileMD5 + ":" + token);
    transform(sign.begin(), sign.end(), sign.begin(), ::tolower);
    string attrs = "{\"sign\":\"" + sign + "\"}";

    if (cmd == "sendfile") {
        FPQWriter qw(8, "sendfile");
        qw.param("pid", _pid);
        qw.param("token", token);
        qw.param("mtype", mtype);
        qw.param("from", from);
        qw.param("to", to);
        qw.param("mid", mid);
        qw.param("file", fileData);
        qw.param("attrs", attrs);
        return qw.take();
    } else if (cmd == "sendfiles") {
        FPQWriter qw(8, "sendfiles");
        qw.param("pid", _pid);
        qw.param("token", token);
        qw.param("mtype", mtype);
        qw.param("from", from);
        qw.param("tos", tos);
        qw.param("mid", mid);
        qw.param("file", fileData);
        qw.param("attrs", attrs);
        return qw.take();
    } else if (cmd == "sendgroupfile") {
        FPQWriter qw(8, "sendgroupfile");
        qw.param("pid", _pid);
        qw.param("token", token);
        qw.param("mtype", mtype);
        qw.param("from", from);
        qw.param("gid", gid);
        qw.param("mid", mid);
        qw.param("file", fileData);
        qw.param("attrs", attrs);
        return qw.take();
    } else if (cmd == "sendroomfile") {
        FPQWriter qw(8, "sendroomfile");
        qw.param("pid", _pid);
        qw.param("token", token);
        qw.param("mtype", mtype);
        qw.param("from", from);
        qw.param("rid", rid);
        qw.param("mid", mid);
        qw.param("file", fileData);
        qw.param("attrs", attrs);
        return qw.take();
    } else {
        FPQWriter qw(7, "broadcastfile");
        qw.param("pid", _pid);
        qw.param("token", token);
        qw.param("mtype", mtype);
        qw.param("from", from);
        qw.param("mid", mid);
        qw.param("file", fileData);
        qw.param("attrs", attrs);
        return qw.take();
    }
}

SendFileResult RTMServerClient::_sendFileProcess(int64_t from, const string& cmd, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, int64_t& mid, int32_t timeout)
{
    if (fileData.empty()) {
        SendFileResult result;
        result.errorCode = -1;
        result.errorInfo = "file data is empty";
        return result;
    }
    
    if (mid == 0)
        mid = MidGenerator::genMid();

    FileTokenInfo info;
    info.toUid = to;
    info.toUids = tos;
    info.groupId = gid;
    info.roomId = rid;

    SendFileResult result;
    FileTokenResult tokenResult = fileToken(from, cmd, info, timeout);
    if (tokenResult.isError())
    {
        result.errorCode = tokenResult.errorCode;
        result.errorInfo = tokenResult.errorInfo;
        return result;
    }

    FPQuestPtr quest = _getSendFileQuest(tokenResult.token, from, cmd, to, tos, gid, rid, mtype, fileData, mid);
    
    TCPClientPtr fileClient = TCPClient::createClient(tokenResult.endpoint, true);
    FPAnswerPtr answer = fileClient->sendQuest(quest, timeout);

    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        result.mtime = ar.getInt("mtime");
        result.mid = mid;
    }
    return result;
}

void RTMServerClient::_sendFileProcess(int64_t from, const string& cmd, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, 
        std::function<void (SendFileResult result)> callback, int64_t& mid, int32_t timeout)
{
    if (fileData.empty()) {
        SendFileResult result;
        result.errorCode = -1;
        result.errorInfo = "file data is empty";
        callback(result);
        return;
    }

    if (mid == 0)
        mid = MidGenerator::genMid();

    FileTokenInfo info;
    info.toUid = to;
    info.toUids = tos;
    info.groupId = gid;
    info.roomId = rid;

    fileToken(from, cmd, info, [this, from, cmd, to, tos, gid, rid, mtype, fileData, mid, timeout, callback](FileTokenResult tokenResult) {
        if (tokenResult.isError()) {
            SendFileResult result;
            result.errorCode = tokenResult.errorCode;
            result.errorInfo = tokenResult.errorInfo;
            callback(result);
            return;
        }
        FPQuestPtr quest = _getSendFileQuest(tokenResult.token, from, cmd, to, tos, gid, rid, mtype, fileData, mid);

        TCPClientPtr fileClient = TCPClient::createClient(tokenResult.endpoint, true);
        bool status = fileClient->sendQuest(quest, [this, fileClient, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
            SendFileResult result;
            if (errorCode == FPNN_EC_OK) {
                FPAReader ar(answer);
                result.mtime = ar.getInt("mtime");
                result.mid = mid;
            } else
                _checkAnswerError(answer, result); 
            callback(result);
        }, timeout);

        if (!status)
        {
            SendFileResult result;
            result.errorCode = -1;
            result.errorInfo = "socket maybe closed";
            callback(result);
        }
    }, timeout);
}

SendFileResult RTMServerClient::sendFile(int64_t from, int64_t to, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout)
{
    return _sendFileProcess(from, "sendfile", to, {}, 0, 0, mtype, fileData, mid, timeout); 
}

void RTMServerClient::sendFile(int64_t from, int64_t to, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid, int32_t timeout)
{
    _sendFileProcess(from, "sendfile", to, {}, 0, 0, mtype, fileData, [callback](SendFileResult result) {
        callback(result); 
    }, mid, timeout);
}

SendFileResult RTMServerClient::sendFiles(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout)
{
    return _sendFileProcess(from, "sendfiles", 0, tos, 0, 0, mtype, fileData, mid, timeout); 
}

void RTMServerClient::sendFiles(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid, int32_t timeout)
{
    _sendFileProcess(from, "sendfiles", 0, tos, 0, 0, mtype, fileData, [callback](SendFileResult result) {
        callback(result); 
    }, mid, timeout);
}

SendFileResult RTMServerClient::sendGroupFile(int64_t from, int64_t gid, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout)
{
    return _sendFileProcess(from, "sendgroupfile", 0, {}, gid, 0, mtype, fileData, mid, timeout); 
}

void RTMServerClient::sendGroupFile(int64_t from, int64_t gid, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid, int32_t timeout)
{
    _sendFileProcess(from, "sendgroupfile", 0, {}, gid, 0, mtype, fileData, [callback](SendFileResult result) {
        callback(result); 
    }, mid, timeout);
}

SendFileResult RTMServerClient::sendRoomFile(int64_t from, int64_t rid, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout)
{
    return _sendFileProcess(from, "sendroomfile", 0, {}, 0, rid, mtype, fileData, mid, timeout); 
}

void RTMServerClient::sendRoomFile(int64_t from, int64_t rid, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid, int32_t timeout)
{
    _sendFileProcess(from, "sendroomfile", 0, {}, 0, rid, mtype, fileData, [callback](SendFileResult result) {
        callback(result); 
    }, mid, timeout);
}

SendFileResult RTMServerClient::broadcastFile(int64_t from, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout)
{
    return _sendFileProcess(from, "broadcastfile", 0, {}, 0, 0, mtype, fileData, mid, timeout); 
}

void RTMServerClient::broadcastFile(int64_t from, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid, int32_t timeout)
{
    _sendFileProcess(from, "sendroomfile", 0, {}, 0, 0, mtype, fileData, [callback](SendFileResult result) {
        callback(result); 
    }, mid, timeout);
}

