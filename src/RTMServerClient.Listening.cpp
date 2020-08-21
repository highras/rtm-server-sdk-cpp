#include "RTMServerClient.h"

using namespace rtm;

FPQuestPtr RTMServerClient::_getAddListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, const set<int64_t>& uids, const set<string>& events)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "addlisten", sign, salt);

    FPQWriter qw(8, "addlisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gids", gids);
    qw.param("rids", rids);
    qw.param("uids", uids);
    qw.param("events", events);
    return qw.take();
}

int32_t RTMServerClient::addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout)
{
    FPQuestPtr quest = _getAddListenQuest(groupIds, roomIds, userIds, events);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result)) {
        lock_guard<mutex> lck(_opLock);
        if (groupIds.size())
            _listenStatusInfo.groupIds.insert(groupIds.begin(), groupIds.end());
        if (roomIds.size())
            _listenStatusInfo.roomIds.insert(roomIds.begin(), roomIds.end());
        if (userIds.size())
            _listenStatusInfo.userIds.insert(userIds.begin(), userIds.end());
        if (events.size())
            _listenStatusInfo.events.insert(events.begin(), events.end());
    }
    return result.errorCode;
}

void RTMServerClient::addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddListenQuest(groupIds, roomIds, userIds, events);
    bool status = _client->sendQuest(quest, [this, groupIds, roomIds, userIds, events, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (!_checkAnswerError(answer, result, errorCode)) {
            lock_guard<mutex> lck(_opLock);
            if (groupIds.size())
                _listenStatusInfo.groupIds.insert(groupIds.begin(), groupIds.end());
            if (roomIds.size())
                _listenStatusInfo.roomIds.insert(roomIds.begin(), roomIds.end());
            if (userIds.size())
                _listenStatusInfo.userIds.insert(userIds.begin(), userIds.end());
            if (events.size())
                _listenStatusInfo.events.insert(events.begin(), events.end());
        }
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getRemoveListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, const set<int64_t>& uids, const set<string>& events)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "removelisten", sign, salt);

    FPQWriter qw(8, "removelisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("gids", gids);
    qw.param("rids", rids);
    qw.param("uids", uids);
    qw.param("events", events);
    return qw.take();
}

int32_t RTMServerClient::removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout)
{
    FPQuestPtr quest = _getRemoveListenQuest(groupIds, roomIds, userIds, events);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result)) {
        lock_guard<mutex> lck(_opLock);
        if (groupIds.size())
            for (auto& id: groupIds)
                _listenStatusInfo.groupIds.erase(id);
        if (roomIds.size())
            for (auto& id: roomIds)
                _listenStatusInfo.roomIds.erase(id);
        if (userIds.size())
            for (auto& id: userIds)
                _listenStatusInfo.userIds.erase(id);
        if (events.size())
            for (auto& id: events)
                _listenStatusInfo.events.erase(id);
    }
    return result.errorCode;
}

void RTMServerClient::removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getAddListenQuest(groupIds, roomIds, userIds, events);
    bool status = _client->sendQuest(quest, [this, groupIds, roomIds, userIds, events, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (!_checkAnswerError(answer, result, errorCode)) {
            lock_guard<mutex> lck(_opLock);
            if (groupIds.size())
                for (auto& id: groupIds)
                    _listenStatusInfo.groupIds.erase(id);
            if (roomIds.size())
                for (auto& id: roomIds)
                    _listenStatusInfo.roomIds.erase(id);
            if (userIds.size())
                for (auto& id: userIds)
                    _listenStatusInfo.userIds.erase(id);
            if (events.size())
                for (auto& id: events)
                    _listenStatusInfo.events.erase(id);
        }
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getSetListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, const set<int64_t>& uids, const set<string>& events)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setlisten", sign, salt);

    int32_t size = 4;
    if (gids.size())
        ++size;
    if (rids.size())
        ++size;
    if (uids.size())
        ++size;
    if (events.size())
        ++size;

    FPQWriter qw(size, "setlisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);

    if (gids.size())
        qw.param("gids", gids);
    if (rids.size())
        qw.param("rids", rids);
    if (uids.size())
        qw.param("uids", uids);
    if (events.size())
        qw.param("events", events);

    return qw.take();
}

FPQuestPtr RTMServerClient::_getSetListenQuest(bool allGroup, bool allRoom, bool allP2P, bool allEvent)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "setlisten", sign, salt);

    FPQWriter qw(8, "setlisten");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("group", allGroup);
    qw.param("room", allRoom);
    qw.param("p2p", allP2P);
    qw.param("ev", allEvent);
    return qw.take();
}

int32_t RTMServerClient::setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout)
{
    FPQuestPtr quest = _getSetListenQuest(groupIds, roomIds, userIds, events);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result)) {
        lock_guard<mutex> lck(_opLock);
        _listenStatusInfo.groupIds = groupIds;
        _listenStatusInfo.roomIds = roomIds;
        _listenStatusInfo.userIds = userIds;
        _listenStatusInfo.events = events;
    }
    return result.errorCode;
}

int32_t RTMServerClient::setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, int32_t timeout)
{
    FPQuestPtr quest = _getSetListenQuest(allGroup, allRoom, allP2P, allEvent);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result)) {
        lock_guard<mutex> lck(_opLock);
        _listenStatusInfo.allGroups = allGroup;
        _listenStatusInfo.allRooms = allRoom;
        _listenStatusInfo.allP2P = allP2P;
        _listenStatusInfo.allEvents = allEvent;
    }
    return result.errorCode;
}

void RTMServerClient::setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetListenQuest(groupIds, roomIds, userIds, events);
    bool status = _client->sendQuest(quest, [this, groupIds, roomIds, userIds, events, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (!_checkAnswerError(answer, result, errorCode)) {
            lock_guard<mutex> lck(_opLock);
            _listenStatusInfo.groupIds = groupIds;
            _listenStatusInfo.roomIds = roomIds;
            _listenStatusInfo.userIds = userIds;
            _listenStatusInfo.events = events;
        }
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

void RTMServerClient::setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSetListenQuest(allGroup, allRoom, allP2P, allEvent);
    bool status = _client->sendQuest(quest, [this, allGroup, allRoom, allP2P, allEvent, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        if (!_checkAnswerError(answer, result, errorCode)) {
            lock_guard<mutex> lck(_opLock);
            _listenStatusInfo.allGroups = allGroup;
            _listenStatusInfo.allRooms = allRoom;
            _listenStatusInfo.allP2P = allP2P;
            _listenStatusInfo.allEvents = allEvent;
        }
        callback(result.errorCode);
    }, timeout);

    if (!status)
        callback(FPNN_EC_CORE_INVALID_CONNECTION);
}

void RTMServerClient::_listenStatusRestoration()
{
    if (_listenStatusInfo.allP2P || _listenStatusInfo.allGroups || _listenStatusInfo.allRooms || _listenStatusInfo.allEvents) {
        setListen(_listenStatusInfo.allGroups, _listenStatusInfo.allRooms, _listenStatusInfo.allP2P, _listenStatusInfo.allEvents, [](int32_t errorCode) {});
    }

    if (_listenStatusInfo.userIds.size() || _listenStatusInfo.groupIds.size() || _listenStatusInfo.roomIds.size() || _listenStatusInfo.events.size()) {
        setListen(_listenStatusInfo.groupIds, _listenStatusInfo.roomIds, _listenStatusInfo.userIds, _listenStatusInfo.events, [](int32_t errorCode) {});
    }
}
