#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getInviteUserIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "inviteUserIntoRTCRoom", sign, salt);

    FPQWriter qw(7, "inviteUserIntoRTCRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("toUids", toUids);
    qw.param("fromUid", fromUid);
    return qw.take();
}

int32_t RTMServerClient::inviteUserIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, int32_t timeout)
{
    FPQuestPtr quest = _getInviteUserIntoRTCRoom(roomId, toUids, fromUid);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::inviteUserIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getInviteUserIntoRTCRoom(roomId, toUids, fromUid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getCloseRTCRoom(int64_t roomId)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "closeRTCRoom", sign, salt);

    FPQWriter qw(5, "closeRTCRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    return qw.take();
}

int32_t RTMServerClient::closeRTCRoom(int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getCloseRTCRoom(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::closeRTCRoom(int64_t roomId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getCloseRTCRoom(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getKickoutFromRTCRoom(int64_t uid, int64_t roomId, int64_t fromUid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "kickoutFromRTCRoom", sign, salt);

    FPQWriter qw(7, "kickoutFromRTCRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("rid", roomId);
    qw.param("fromUid", fromUid);
    return qw.take();
}

int32_t RTMServerClient::kickoutFromRTCRoom(int64_t uid, int64_t roomId, int64_t fromUid, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutFromRTCRoom(uid, roomId, fromUid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::kickoutFromRTCRoom(int64_t uid, int64_t roomId, int64_t fromUid, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutFromRTCRoom(uid, roomId, fromUid);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetRTCRoomList()
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getRTCRoomList", sign, salt);

    FPQWriter qw(4, "getRTCRoomList");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    return qw.take();
}

int32_t RTMServerClient::getRTCRoomList(set<int64_t>& roomIds, int32_t timeout)
{
    FPQuestPtr quest = _getGetRTCRoomList();
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        roomIds = ar.get("rids", roomIds);
    }
    return result.errorCode;
}

void RTMServerClient::getRTCRoomList(std::function<void (set<int64_t> roomIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRTCRoomList();
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

FPQuestPtr RTMServerClient::_getGetRTCRoomMembers(int64_t roomId)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getRTCRoomMembers", sign, salt);

    FPQWriter qw(5, "getRTCRoomMembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    return qw.take();
}

int32_t RTMServerClient::getRTCRoomMembers(set<int64_t>& uids, set<int64_t>& administartors, int64_t& owner, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetRTCRoomMembers(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        uids = ar.get("uids", uids);
        administartors = ar.get("administartors", administartors);
        owner = ar.getInt("owner");
    }
    return result.errorCode;
}

void RTMServerClient::getRTCRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, set<int64_t> administartors, int64_t owner, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRTCRoomMembers(roomId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> uids;
        set<int64_t> administartors;
        int64_t owner = -1;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            uids = ar.get("uids", uids);
            administartors = ar.get("administrators", administartors);
            owner = ar.getInt("owner");
        }
        callback(uids, administartors, owner, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), set<int64_t>(), -1, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetRTCRoomMemberCount(int64_t roomId)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getRTCRoomMemberCount", sign, salt);

    FPQWriter qw(5, "getRTCRoomMemberCount");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    return qw.take();
}

int32_t RTMServerClient::getRTCRoomMemberCount(int32_t& count, int64_t roomId, int32_t timeout)
{
    FPQuestPtr quest = _getGetRTCRoomMemberCount(roomId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        count = ar.getInt("count");
    }
    return result.errorCode;
}

void RTMServerClient::getRTCRoomMemberCount(int64_t roomId, std::function<void (int32_t count, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetRTCRoomMemberCount(roomId);
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

FPQuestPtr RTMServerClient::_getSetRTCRoomMicStatus(int64_t roomId, bool status)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setRTCRoomMicStatus", sign, salt);

    FPQWriter qw(6, "setRTCRoomMicStatus");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("status", status);
    return qw.take();
}

int32_t RTMServerClient::setRTCRoomMicStatus(int64_t roomId, bool status, int32_t timeout)
{
    FPQuestPtr quest = _getSetRTCRoomMicStatus(roomId, status);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::setRTCRoomMicStatus(int64_t roomId, bool status, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetRTCRoomMicStatus(roomId, status);
    bool questStatus = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!questStatus)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getPullIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int32_t type)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "pullIntoRTCRoom", sign, salt);

    FPQWriter qw(7, "pullIntoRTCRoom");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("toUids", toUids);
    qw.param("type", type);
    return qw.take();
}

int32_t RTMServerClient::pullIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int32_t type, int32_t timeout)
{
    FPQuestPtr quest = _getPullIntoRTCRoom(roomId, toUids, type);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::pullIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int32_t type, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getPullIntoRTCRoom(roomId, toUids, type);
    bool questStatus = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!questStatus)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getAdminCommand(int64_t roomId, const set<int64_t>& uids, int32_t command)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "adminCommand", sign, salt);

    FPQWriter qw(7, "adminCommand");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("rid", roomId);
    qw.param("uids", uids);
    qw.param("command", command);
    return qw.take();
}

int32_t RTMServerClient::adminCommand(int64_t roomId, const set<int64_t>& uids, int32_t command, int32_t timeout)
{
    FPQuestPtr quest = _getAdminCommand(roomId, uids, command);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::adminCommand(int64_t roomId, const set<int64_t>& uids, int32_t command, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAdminCommand(roomId, uids, command);
    bool questStatus = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    },timeout);

    if (!questStatus)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}
