#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getGetOnlineUsersQuest(const set<int64_t>& uids)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getonlineusers", sign, salt);

    FPQWriter qw(5, "getonlineusers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uids", uids);
    return qw.take();
}

int32_t RTMServerClient::getOnlineUsers(set<int64_t>& onlineUserIds, const set<int64_t>& userIds, int32_t timeout)
{
    FPQuestPtr quest = _getGetOnlineUsersQuest(userIds);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        onlineUserIds = ar.get("uids", onlineUserIds);
    }
    return result.errorCode;
}

void RTMServerClient::getOnlineUsers(const set<int64_t>& userIds, std::function<void (set<int64_t> onlineUserIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetOnlineUsersQuest(userIds);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> onlineUserIds;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            onlineUserIds = ar.get("uids", onlineUserIds);
        }
        callback(onlineUserIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getAddProjectBlackQuest(int64_t uid, int32_t btime)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addprojectblack", sign, salt);

    FPQWriter qw(6, "addprojectblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("btime", btime);
    return qw.take();
}

int32_t RTMServerClient::addProjectBlack(int64_t userId, int32_t blackTime, int32_t timeout)
{
    FPQuestPtr quest = _getAddProjectBlackQuest(userId, blackTime);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addProjectBlack(int64_t userId, int32_t blackTime, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddProjectBlackQuest(userId, blackTime);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveProjectBlackQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removeprojectblack", sign, salt);

    FPQWriter qw(5, "removeprojectblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::removeProjectBlack(int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveProjectBlackQuest(userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::removeProjectBlack(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveProjectBlackQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsProjectBlackQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isprojectblack", sign, salt);

    FPQWriter qw(5, "isprojectblack");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::isProjectBlack(bool& isBlack, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getIsProjectBlackQuest(userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        isBlack = ar.getBool("ok");
    }
    return result.errorCode;
}

void RTMServerClient::isProjectBlack(int64_t userId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsProjectBlackQuest(userId);
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

FPQuestPtr RTMServerClient::_getSetUserInfoQuest(int64_t uid, string* oinfo, string* pinfo)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setuserinfo", sign, salt);

    int32_t size = 7;
    if (!oinfo)
        --size;
    if (!pinfo)
        --size;

    FPQWriter qw(size, "setuserinfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    if (oinfo)
        qw.param("oinfo", *oinfo);
    if (pinfo)
        qw.param("pinfo", *pinfo);
    return qw.take();
}

int32_t RTMServerClient::setUserInfo(int64_t userId, string* oinfo, string* pinfo, int32_t timeout)
{
    FPQuestPtr quest = _getSetUserInfoQuest(userId, oinfo, pinfo);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::setUserInfo(int64_t userId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetUserInfoQuest(userId, oinfo, pinfo);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetUserInfoQuest(int64_t uid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getuserinfo", sign, salt);

    FPQWriter qw(5, "getuserinfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getUserInfo(string& oinfo, string& pinfo, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserInfoQuest(userId);
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

void RTMServerClient::getUserInfo(int64_t userId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserInfoQuest(userId);
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

FPQuestPtr RTMServerClient::_getGetUserOpenInfoQuest(const set<int64_t>& uids)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getuseropeninfo", sign, salt);

    FPQWriter qw(5, "getuseropeninfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uids", uids);
    return qw.take();
}

int32_t RTMServerClient::getUserOpenInfo(map<string, string>& info, const set<int64_t>& userIds, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserOpenInfoQuest(userIds);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        info = ar.get("info", info);
    }
    return result.errorCode;
}

void RTMServerClient::getUserOpenInfo(const set<int64_t>& userIds, std::function<void (map<string, string> info, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserOpenInfoQuest(userIds);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        map<string, string> info;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            info = ar.get("info", info);
        } 
        callback(info, result.errorCode);
    }, timeout);

    if (!status)
        callback(map<string, string>(), FPNN_EC_CORE_INVALID_CONNECTION);
}