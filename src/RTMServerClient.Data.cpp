#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getDataSetQuest(int64_t uid, const string& key, const string& value)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "dataset", sign, salt);

    FPQWriter qw(7, "dataset");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("key", key);
    qw.param("val", value);
    return qw.take();
}

int32_t RTMServerClient::dataSet(int64_t userId, const string& key, const string& value, int32_t timeout)
{
    FPQuestPtr quest = _getDataSetQuest(userId, key, value);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::dataSet(int64_t userId, const string& key, const string& value, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDataSetQuest(userId, key, value);  
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDataDeleteQuest(int64_t uid, const string& key)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "datadel", sign, salt);

    FPQWriter qw(6, "datadel");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("key", key);
    return qw.take();
}

int32_t RTMServerClient::dataDelete(int64_t userId, const string& key, int32_t timeout)
{
    FPQuestPtr quest = _getDataDeleteQuest(userId, key);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::dataDelete(int64_t userId, const string& key, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDataDeleteQuest(userId, key);  
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDataGetQuest(int64_t uid, const string& key)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "dataget", sign, salt);

    FPQWriter qw(6, "dataget");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("key", key);
    return qw.take();
}

int32_t RTMServerClient::dataGet(string& value, int64_t userId, const string& key, int32_t timeout)
{
    FPQuestPtr quest = _getDataGetQuest(userId, key);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result)) {
        FPAReader ar(answer);
        value = ar.getString("val");
    }
    return result.errorCode;
}

void RTMServerClient::dataGet(int64_t userId, const string& key, std::function<void (string value, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDataGetQuest(userId, key);  
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string value;
        if (_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            value = ar.getString("val");
        }
        callback(value, result.errorCode);
    }, timeout);

    if (!status)
        callback("", FPNN_EC_CORE_INVALID_CONNECTION);
}