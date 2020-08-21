#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getAddFriendsQuest(int64_t uid, const set<int64_t>& friends)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addfriends", sign, salt);

    FPQWriter qw(6, "addfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("friends", friends);
    return qw.take();
}

int32_t RTMServerClient::addFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout)
{
    FPQuestPtr quest = _getAddFriendsQuest(userId, friends);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddFriendsQuest(userId, friends);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getAddBlacksQuest(int64_t uid, const set<int64_t>& blacks)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addblacks", sign, salt);

    FPQWriter qw(6, "addblacks");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("blacks", blacks);
    return qw.take();
}

int32_t RTMServerClient::addBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout)
{
    FPQuestPtr quest = _getAddBlacksQuest(userId, blacks);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddBlacksQuest(userId, blacks);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDeleteFriendsQuest(int64_t uid, const set<int64_t>& friends)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "delfriends", sign, salt);

    FPQWriter qw(6, "delfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("friends", friends);
    return qw.take();
}

int32_t RTMServerClient::deleteFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteFriendsQuest(userId, friends);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::deleteFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteFriendsQuest(userId, friends);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDeleteBlacksQuest(int64_t uid, const set<int64_t>& blacks)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "delblacks", sign, salt);

    FPQWriter qw(6, "delblacks");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("blacks", blacks);
    return qw.take();
}

int32_t RTMServerClient::deleteBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteBlacksQuest(userId, blacks);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::deleteBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteBlacksQuest(userId, blacks);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsFriendQuest(int64_t uid, int64_t fuid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isfriend", sign, salt);

    FPQWriter qw(6, "isfriend");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("fuid", fuid);
    return qw.take();
}

int32_t RTMServerClient::isFriend(bool& isFriend, int64_t userId, int64_t otherUserId, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendQuest(userId, otherUserId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        isFriend = ar.getBool("ok");
    }
    return result.errorCode;
}

void RTMServerClient::isFriend(int64_t userId, int64_t otherUserId, std::function<void (bool isFriend, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendQuest(userId, otherUserId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        bool isFriend = false;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            isFriend = ar.getBool("ok");
        }
        callback(isFriend, result.errorCode);
    }, timeout);

    if (!status)
        callback(false, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsFriendsQuest(int64_t uid, const set<int64_t>& fuids)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isfriends", sign, salt);

    FPQWriter qw(6, "isfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("fuids", fuids);
    return qw.take();
}

int32_t RTMServerClient::isFriends(set<int64_t>& friendUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendsQuest(userId, otherUserIds);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        friendUserIds = ar.get("fuids", friendUserIds);
    }
    return result.errorCode;
}

void RTMServerClient::isFriends(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsFriendsQuest(userId, otherUserIds);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> friendUserIds;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            friendUserIds = ar.get("fuids", friendUserIds);
        }
        callback(friendUserIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetFriendsQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getfriends", sign, salt);

    FPQWriter qw(5, "getfriends");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getFriends(set<int64_t>& friendUserIds, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getGetFriendsQuest(userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        friendUserIds = ar.get("uids", friendUserIds);
    }
    return result.errorCode;
}

void RTMServerClient::getFriends(int64_t userId, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetFriendsQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> friendUserIds;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            friendUserIds = ar.get("uids", friendUserIds);
        }
        callback(friendUserIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetBlacksQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getblacks", sign, salt);

    FPQWriter qw(5, "getblacks");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getBlacks(set<int64_t>& blackUserIds, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getGetBlacksQuest(userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        blackUserIds = ar.get("uids", blackUserIds);
    }
    return result.errorCode;
}

void RTMServerClient::getBlacks(int64_t userId, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetBlacksQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> blackUserIds;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            blackUserIds = ar.get("uids", blackUserIds);
        }
        callback(blackUserIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsBlackQuest(int64_t uid, int64_t buid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isblack", sign, salt);

    FPQWriter qw(6, "isblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("buid", buid);
    return qw.take();
}

int32_t RTMServerClient::isBlack(bool& isBlack, int64_t userId, int64_t otherUserId, int32_t timeout)
{
    FPQuestPtr quest = _getIsBlackQuest(userId, otherUserId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        isBlack = ar.getBool("ok");
    }
    return result.errorCode;
}

void RTMServerClient::isBlack(int64_t userId, int64_t otherUserId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsBlackQuest(userId, otherUserId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        bool isBlack = false;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            isBlack = ar.getBool("ok");
        }
        callback(isBlack, result.errorCode);
    }, timeout);

    if (!status)
        callback(false, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsBlacksQuest(int64_t uid, const set<int64_t>& buids)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isblacks", sign, salt);

    FPQWriter qw(6, "isblacks");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("buids", buids);
    return qw.take();
}

int32_t RTMServerClient::isBlacks(set<int64_t>& blackUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout)
{
    FPQuestPtr quest = _getIsBlacksQuest(userId, otherUserIds);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        blackUserIds = ar.get("buids", blackUserIds);
    }
    return result.errorCode;
}

void RTMServerClient::isBlacks(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsBlacksQuest(userId, otherUserIds);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> blackUserIds;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            blackUserIds = ar.get("buids", blackUserIds);
        }
        callback(blackUserIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}