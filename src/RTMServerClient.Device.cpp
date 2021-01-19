#include "RTMServerClient.h"

using namespace rtm;

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

FPQuestPtr RTMServerClient::_getAddOptionQuest(int64_t uid, int8_t type, int64_t xid, const set<int8_t>& mtype)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addoption", sign, salt);

    int32_t paramSize = 7;
    if (!mtype.empty())
        paramSize += 1;
    FPQWriter qw(paramSize, "addoption");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("type", type);
    qw.param("xid", xid);
    if (!mtype.empty())
        qw.param("mtype", mtype);
    return qw.take();
}

int32_t RTMServerClient::addDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, int32_t timeout)
{
    switch (type)
    {
    case P2PMessage:
        type = 0;
        break;
    case GroupMessage:
        type = 1;
        break;
    default:
        return RTM_EC_INVALID_PARAMETER;
    }

    FPQuestPtr quest = _getAddOptionQuest(userId, type, xid, mtype);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    switch (type)
    {
    case P2PMessage:
        type = 0;
        break;
    case GroupMessage:
        type = 1;
        break;
    default:
        callback(RTM_EC_INVALID_PARAMETER);
        return;
    }
    FPQuestPtr quest = _getAddOptionQuest(userId, type, xid, mtype);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
            QuestResult result;
            _checkAnswerError(answer, result, errorCode);
            callback(result.errorCode);
        }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveOptionQuest(int64_t uid, int8_t type, int64_t xid, const set<int8_t>& mtype)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removeoption", sign, salt);

    int32_t paramSize = 7;
    if (!mtype.empty())
        paramSize += 1;
    FPQWriter qw(paramSize, "removeoption");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    qw.param("type", type);
    qw.param("xid", xid);
    if (!mtype.empty())
        qw.param("mtype", mtype);
    return qw.take();
}

int32_t RTMServerClient::removeDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, int32_t timeout)
{
    switch (type)
    {
    case P2PMessage:
        type = 0;
        break;
    case GroupMessage:
        type = 1;
        break;
    default:
        return RTM_EC_INVALID_PARAMETER;
    }

    FPQuestPtr quest = _getRemoveOptionQuest(userId, type, xid, mtype);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode; 
}

void RTMServerClient::removeDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    switch (type)
    {
    case P2PMessage:
        type = 0;
        break;
    case GroupMessage:
        type = 1;
        break;
    default:
        callback(RTM_EC_INVALID_PARAMETER);
        return;
    }

    FPQuestPtr quest = _getRemoveOptionQuest(userId, type, xid, mtype);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
            QuestResult result;
            _checkAnswerError(answer, result, errorCode);
            callback(result.errorCode);
        }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetOptionQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getoption", sign, salt);

    FPQWriter qw(5, "getoption");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getDevicePushOption(map<string, set<int8_t>>& p2p, map<string, set<int8_t>>& group, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getGetOptionQuest(userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if(!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        p2p = ar.get("p2p", p2p);
        group = ar.get("group", group);
    }
    return result.errorCode; 
}

void RTMServerClient::getDevicePushOption(int64_t userId, std::function<void (map<string, set<int8_t>> p2p, map<string, set<int8_t>> group, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetOptionQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        map<string, set<int8_t>> p2p;
        map<string, set<int8_t>> group;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            p2p = ar.get("p2p", p2p);
            group = ar.get("group", group);
        }
        callback(p2p, group, result.errorCode);
    }, timeout);

    if (!status)
        callback(map<string, set<int8_t>>(), map<string, set<int8_t>>(), FPNN_EC_CORE_INVALID_CONNECTION);
}