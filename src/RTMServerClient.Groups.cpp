#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getAddGroupMembersQuest(int64_t gid, const set<int64_t>& uids)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addgroupmembers", sign, salt);

    FPQWriter qw(6, "addgroupmembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    qw.param("uids", uids);
    return qw.take();
}

int32_t RTMServerClient::addGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupMembersQuest(groupId, userIds);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupMembersQuest(groupId, userIds);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDeleteGroupMembersQuest(int64_t gid, const set<int64_t>& uids)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "delgroupmembers", sign, salt);

    FPQWriter qw(6, "delgroupmembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    qw.param("uids", uids);
    return qw.take();
}

int32_t RTMServerClient::deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupMembersQuest(groupId, userIds);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupMembersQuest(groupId, userIds);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getDeleteGroupQuest(int64_t gid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "delgroup", sign, salt);

    FPQWriter qw(5, "delgroup");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    return qw.take();
}

int32_t RTMServerClient::deleteGroup(int64_t groupId, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupQuest(groupId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::deleteGroup(int64_t groupId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getDeleteGroupQuest(groupId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetGroupMembersQuest(int64_t gid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getgroupmembers", sign, salt);

    FPQWriter qw(5, "getgroupmembers");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    return qw.take();
}

int32_t RTMServerClient::getGroupMembers(set<int64_t>& members, int64_t groupId, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMembersQuest(groupId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        members = ar.get("uids", members);
    }
    return result.errorCode;
}

void RTMServerClient::getGroupMembers(int64_t groupId, std::function<void (set<int64_t> members, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupMembersQuest(groupId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> members;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            members = ar.get("uids", members);
        }
        callback(members, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsGroupMemberQuest(int64_t gid, int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isgroupmember", sign, salt);

    FPQWriter qw(6, "isgroupmember");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::isGroupMember(bool& isMember, int64_t groupId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getIsGroupMemberQuest(groupId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        isMember = ar.getBool("ok");
    }
    return result.errorCode;
}

void RTMServerClient::isGroupMember(int64_t groupId, int64_t userId, std::function<void (bool isMember, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsGroupMemberQuest(groupId, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        bool isMember = false;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            isMember = ar.getBool("ok");
        }
        callback(isMember, result.errorCode);
    }, timeout);

    if (!status)
        callback(false, FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetUserGroupsQuest(int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getusergroups", sign, salt);

    FPQWriter qw(5, "getusergroups");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::getUserGroups(set<int64_t>& groupIds, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserGroupsQuest(userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        groupIds = ar.get("gids", groupIds);
    }
    return result.errorCode;
}

void RTMServerClient::getUserGroups(int64_t userId, std::function<void (set<int64_t> groupIds, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetUserGroupsQuest(userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        set<int64_t> groupIds;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            groupIds = ar.get("gids", groupIds);
        }
        callback(groupIds, result.errorCode);
    }, timeout);

    if (!status)
        callback(set<int64_t>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getAddGroupBanQuest(int64_t gid, int64_t uid, int32_t btime)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addgroupban", sign, salt);

    int32_t paramSize = gid == 0 ? 6 : 7;
    FPQWriter qw(paramSize, "addgroupban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    if (gid != 0)
        qw.param("gid", gid);
    qw.param("uid", uid);
    qw.param("btime", btime);
    return qw.take();
}

int32_t RTMServerClient::addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupBanQuest(groupId, userId, banTime);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddGroupBanQuest(groupId, userId, banTime);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveGroupBanQuest(int64_t gid, int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removegroupban", sign, salt);

    int32_t paramSize = gid == 0 ? 5 : 6;
    FPQWriter qw(paramSize, "removegroupban");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    if (gid != 0)
        qw.param("gid", gid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::removeGroupBan(int64_t groupId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveGroupBanQuest(groupId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::removeGroupBan(int64_t groupId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveGroupBanQuest(groupId, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode); 
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getIsBanOfGroupQuest(int64_t gid, int64_t uid)
{
    int32_t ts = slack_real_sec();
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "isbanofgroup", sign, salt);

    FPQWriter qw(6, "isbanofgroup");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::isBanOfGroup(bool& isBan, int64_t groupId, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfGroupQuest(groupId, userId);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        isBan = ar.getBool("ok");
    }
    return result.errorCode;
}

void RTMServerClient::isBanOfGroup(int64_t groupId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getIsBanOfGroupQuest(groupId, userId);
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

FPQuestPtr RTMServerClient::_getSetGroupInfoQuest(int64_t gid, string* oinfo, string* pinfo)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setgroupinfo", sign, salt);

    int32_t size = 7;
    if (!oinfo)
        --size;
    if (!pinfo)
        --size;

    FPQWriter qw(size, "setgroupinfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    if (oinfo)
        qw.param("oinfo", *oinfo);
    if (pinfo)
        qw.param("pinfo", *pinfo);
    return qw.take();
}

int32_t RTMServerClient::setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, int32_t timeout)
{
    FPQuestPtr quest = _getSetGroupInfoQuest(groupId, oinfo, pinfo);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetGroupInfoQuest(groupId, oinfo, pinfo);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getGetGroupInfoQuest(int64_t gid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "getgroupinfo", sign, salt);

    FPQWriter qw(5, "getgroupinfo");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gid", gid);
    return qw.take();
}

int32_t RTMServerClient::getGroupInfo(string& oinfo, string& pinfo, int64_t groupId, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupInfoQuest(groupId);
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

void RTMServerClient::getGroupInfo(int64_t groupId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getGetGroupInfoQuest(groupId);
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