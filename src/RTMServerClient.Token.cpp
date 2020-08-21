#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getGetTokenQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "gettoken", sign, salt);

    FPQWriter qw(5, "gettoken");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getToken(string& token, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getGetTokenQuest(userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        token = ar.getString("token");
    }
    return result.errorCode;
}

void RTMServerClient::getToken(int64_t userId, std::function<void (string token, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetTokenQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string token = "";
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            token = ar.getString("token");
        }
        callback(token, result.errorCode);
    }, timeout);

    if (!status)
        callback("", FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveTokenQuest(int64_t uid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removetoken", sign, salt);

    FPQWriter qw(5, "removetoken");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::removeToken(int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveTokenQuest(userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::removeToken(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveTokenQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getAddDeviceQuest(int64_t uid, const string& appType, const string& deviceToken)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "adddevice", sign, salt);

    FPQWriter qw(7, "adddevice");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("apptype", appType);
    qw.param("devicetoken", deviceToken);
    return qw.take();
}

int32_t RTMServerClient::addDevice(int64_t userId, const string& appType, const string& deviceToken, int32_t timeout)
{
    FPQuestPtr quest = _getAddDeviceQuest(userId, appType, deviceToken);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addDevice(int64_t userId, const string& appType, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddDeviceQuest(userId, appType, deviceToken);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveDeviceQuest(int64_t uid, const string& deviceToken)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removedevice", sign, salt);

    FPQWriter qw(6, "removedevice");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("devicetoken", deviceToken);
    return qw.take();
}

int32_t RTMServerClient::removeDevice(int64_t userId, const string& deviceToken, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveDeviceQuest(userId, deviceToken);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::removeDevice(int64_t userId, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveDeviceQuest(userId, deviceToken);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getKickoutQuest(int64_t uid, const string& ce)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "kickout", sign, salt);

    FPQWriter qw(6, "kickout");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("ce", ce);
    return qw.take();
}

int32_t RTMServerClient::kickout(int64_t userId, const string& ce, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutQuest(userId, ce);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::kickout(int64_t userId, const string& ce, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getKickoutQuest(userId, ce);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}