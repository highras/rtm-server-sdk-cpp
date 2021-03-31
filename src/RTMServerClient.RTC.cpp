#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getInviteUserIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "inviteUserIntoVoiceRoom", sign, salt);

    FPQWriter qw(7, "inviteUserIntoVoiceRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("toUids", toUids);
    qw.param("fromUid", fromUid);
    return qw.take();
}

int32_t RTMServerClient::inviteUserIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, int32_t timeout)
{
    FPQuestPtr quest = _getInviteUserIntoVoiceRoom(roomId, toUids, fromUid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::inviteUserIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getInviteUserIntoVoiceRoom(roomId, toUids, fromUid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getCloseVoiceRoom(int64_t roomId)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "closeVoiceRoom", sign, salt);

    FPQWriter qw(5, "closeVoiceRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    return qw.take();
}

int32_t RTMServerClient::closeVoiceRoom(int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getCloseVoiceRoom(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::closeVoiceRoom(int64_t roomId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getCloseVoiceRoom(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getKickoutFromVoiceRoom(int64_t uid, int64_t roomId, int64_t fromUid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "kickoutFromVoiceRoom", sign, salt);

    FPQWriter qw(7, "kickoutFromVoiceRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("rid", roomId);
    qw.param("fromUid", fromUid);
    return qw.take();
}

int32_t RTMServerClient::kickoutFromVoiceRoom(int64_t uid, int64_t roomId, int64_t fromUid, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutFromVoiceRoom(uid, roomId, fromUid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::kickoutFromVoiceRoom(int64_t uid, int64_t roomId, int64_t fromUid, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutFromVoiceRoom(uid, roomId, fromUid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetVoiceRoomList()
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getVoiceRoomList", sign, salt);

    FPQWriter qw(4, "getVoiceRoomList");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    return qw.take();
}

int32_t RTMServerClient::getVoiceRoomList(set<int64_t>& roomIds, int32_t timeout)
{
    FPQuestPtr quest = _getGetVoiceRoomList();
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        roomIds = ar.get("rids", roomIds);
    }
    return result.errorCode;
}

void RTMServerClient::getVoiceRoomList(std::function<void (set<int64_t> roomIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetVoiceRoomList();
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> roomIds;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            roomIds = ar.get("rids", roomIds);
        }
        callback(roomIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetVoiceRoomMembers(int64_t roomId)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getVoiceRoomMembers", sign, salt);

    FPQWriter qw(5, "getVoiceRoomMembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    return qw.take();
}

int32_t RTMServerClient::getVoiceRoomMembers(set<int64_t>& uids, set<int64_t>& managers, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetVoiceRoomMembers(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        uids = ar.get("uids", uids);
        managers = ar.get("managers", managers);
    }
    return result.errorCode;
}

void RTMServerClient::getVoiceRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, set<int64_t> managers, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetVoiceRoomMembers(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> uids;
        set<int64_t> managers;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            uids = ar.get("uids", uids);
            managers = ar.get("managers", managers);
        }
        callback(uids, managers, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetVoiceRoomMemberCount(int64_t roomId)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getVoiceRoomMemberCount", sign, salt);

    FPQWriter qw(5, "getVoiceRoomMemberCount");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    return qw.take();
}

int32_t RTMServerClient::getVoiceRoomMemberCount(int32_t& count, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetVoiceRoomMemberCount(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        count = ar.getInt("count");
    }
    return result.errorCode;
}

void RTMServerClient::getVoiceRoomMemberCount(int64_t roomId, std::function<void (int32_t count, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetVoiceRoomMemberCount(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t count = 0;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            count = ar.getInt("count");
        }
        callback(count, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getSetVoiceRoomMicStatus(int64_t roomId, bool status)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setVoiceRoomMicStatus", sign, salt);

    FPQWriter qw(6, "setVoiceRoomMicStatus");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("status", status);
    return qw.take();
}

int32_t RTMServerClient::setVoiceRoomMicStatus(int64_t roomId, bool status, int32_t timeout)
{
    FPQuestPtr quest = _getSetVoiceRoomMicStatus(roomId, status);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::setVoiceRoomMicStatus(int64_t roomId, bool status, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetVoiceRoomMicStatus(roomId, status);
    bool questStatus = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!questStatus)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getPullIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "pullIntoVoiceRoom", sign, salt);

    FPQWriter qw(6, "pullIntoVoiceRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("toUids", toUids);
    return qw.take();
}

int32_t RTMServerClient::pullIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int32_t timeout)
{
    FPQuestPtr quest = _getPullIntoVoiceRoom(roomId, toUids);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::pullIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getPullIntoVoiceRoom(roomId, toUids);
    bool questStatus = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!questStatus)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}
