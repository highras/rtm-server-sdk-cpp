#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getAddRoomBanQuest(int64_t rid, int64_t uid, int32_t btime)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addroomban", sign, salt);

    int32_t paramSize = rid == 0 ? 6: 7;

    FPQWriter qw(paramSize, "addroomban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    if (rid != 0)
        qw.param("rid", rid);
    qw.param("uid", uid);
    qw.param("btime", btime);
    return qw.take();
}

int32_t RTMServerClient::addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomBanQuest(roomId, userId, banTime);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomBanQuest(roomId, userId, banTime);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveRoomBanQuest(int64_t rid, int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removeroomban", sign, salt);

    int32_t paramSize = rid == 0 ? 5 : 6;
    FPQWriter qw(paramSize, "removeroomban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    if (rid != 0)
        qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::removeRoomBan(int64_t roomId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveRoomBanQuest(roomId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::removeRoomBan(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveRoomBanQuest(roomId, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsBanOfRoomQuest(int64_t rid, int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isbanofroom", sign, salt);

    FPQWriter qw(6, "isbanofroom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::isBanOfRoom(bool& isBan, int64_t roomId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfRoomQuest(roomId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        isBan = ar.getBool("ok");
    }
    return result.errorCode;
}

void RTMServerClient::isBanOfRoom(int64_t roomId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfRoomQuest(roomId, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        bool isBan = false;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            isBan = ar.getBool("ok");
        } 
        callback(isBan, result.errorCode);
    }, timeout);

    if (!status)
        callback(false, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getAddRoomMemberQuest(int64_t rid, int64_t uid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addroommember", sign, salt);

    FPQWriter qw(6, "addroommember");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::addRoomMember(int64_t roomId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomMemberQuest(roomId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addRoomMember(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddRoomMemberQuest(roomId, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDeleteRoomMemberQuest(int64_t rid, int64_t uid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "delroommember", sign, salt);

    FPQWriter qw(6, "delroommember");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::deleteRoomMember(int64_t roomId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteRoomMemberQuest(roomId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::deleteRoomMember(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteRoomMemberQuest(roomId, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getSetRoomInfoQuest(int64_t rid, string* oinfo, string* pinfo)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setroominfo", sign, salt);

    int32_t size = 7;
    if (!oinfo)
        --size;
    if (!pinfo)
        --size;

    FPQWriter qw(size, "setroominfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    if (oinfo)
        qw.param("oinfo", *oinfo);
    if (pinfo)
        qw.param("pinfo", *pinfo);
    return qw.take();
}

int32_t RTMServerClient::setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, int32_t timeout)
{
    FPQuestPtr quest = _getSetRoomInfoQuest(roomId, oinfo, pinfo);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetRoomInfoQuest(roomId, oinfo, pinfo);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetRoomInfoQuest(int64_t rid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getroominfo", sign, salt);

    FPQWriter qw(5, "getroominfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    return qw.take();
}

FPQuestPtr RTMServerClient::_getGetRoomMembersQuest(int64_t rid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getroommembers", sign, salt);

    FPQWriter qw(5, "getroommembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    return qw.take();
}

FPQuestPtr RTMServerClient::_getGetRoomCountQuest(int64_t rid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getroomcount", sign, salt);

    FPQWriter qw(5, "getroomcount");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", rid);
    return qw.take();
}

int32_t RTMServerClient::getRoomInfo(string& oinfo, string& pinfo, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomInfoQuest(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        oinfo = ar.getString("oinfo");
        pinfo = ar.getString("pinfo");
    }
    return result.errorCode;
}

void RTMServerClient::getRoomInfo(int64_t roomId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomInfoQuest(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string oinfo, pinfo;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            oinfo = ar.getString("oinfo");
            pinfo = ar.getString("pinfo");
        }
        callback(oinfo, pinfo, result.errorCode);
    }, timeout);

    if (!status)
        callback("", "", FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::getRoomMembers(set<int64_t>& uids, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomMembersQuest(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        uids = ar.get("uids", uids);
    }
    return result.errorCode;
}

void RTMServerClient::getRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomMembersQuest(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> uids;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            uids = ar.get("uids", uids);
        }
        callback(uids, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::getRoomCount(map<string, int32_t>& count, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomCountQuest(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        count = ar.get("cn", count);
    }
    return result.errorCode;
}

void RTMServerClient::getRoomCount(int64_t roomId, std::function<void (map<string, int32_t> count, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRoomCountQuest(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        map<string, int32_t> count;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            count = ar.get("cn" ,count);
        }
        callback(count, result.errorCode);
    }, timeout);

    if (!status)
        callback(map<string, int32_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}