#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getAddRoomBanQuest(int64_t rid, int64_t uid, int32_t btime)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addroomban", sign, salt);

    FPQWriter qw(7, "addroomban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
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

    FPQWriter qw(6, "removeroomban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
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