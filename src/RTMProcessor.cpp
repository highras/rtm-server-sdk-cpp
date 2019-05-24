#include "RTMProcessor.h"

using namespace rtm;

bool RTMProcessor::_checkDuplicate(MessageType msgType, int64_t from, int64_t to, int64_t mid)
{
    MessageDuplicateKey key(from, to, mid, msgType);
    lock_guard<mutex> lck(_duplicateCacheLock);
    MessageDuplicateCacheMap::node_type* node = _duplicateCache->find(key);
    if (node)
        return true;
    _duplicateCache->replace(key, true);
    return false;
}

void RTMProcessor::connected(const ConnectionInfo& connInfo) 
{
    if (_serverMonitor)
        _serverMonitor->connected(connInfo);
}

void RTMProcessor::connectionWillClose(const ConnectionInfo& connInfo, bool closeByError)
{
    if (_serverMonitor)
        _serverMonitor->connectionWillClose(connInfo, closeByError);
}

FPAnswerPtr RTMProcessor::pushP2PMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));

    int64_t from = args->wantInt("from");
    int64_t to = args->wantInt("to");
    int8_t mtype = args->wantInt("mtype");
    int64_t mid = args->wantInt("mid");
    string msg = args->wantString("msg");
    string attrs = args->wantString("attrs");
    int64_t mtime = args->wantInt("mtime");

    if (!_checkDuplicate(P2PMessage, from, to, mid) && _serverMonitor)
        _serverMonitor->pushP2PMessage(from, to, mtype, mid, msg, attrs, mtime);

    return nullptr;
}

FPAnswerPtr RTMProcessor::pushGroupMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));
    
    int64_t from = args->wantInt("from");
    int64_t gid = args->wantInt("gid");
    int8_t mtype = args->wantInt("mtype");
    int64_t mid = args->wantInt("mid");
    string msg = args->wantString("msg");
    string attrs = args->wantString("attrs");
    int64_t mtime = args->wantInt("mtime");

    if (!_checkDuplicate(GroupMessage, from, gid, mid) && _serverMonitor)
        _serverMonitor->pushGroupMessage(from, gid, mtype, mid, msg, attrs, mtime);

    return nullptr;
}

FPAnswerPtr RTMProcessor::pushRoommMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));

    int64_t from = args->wantInt("from");
    int64_t rid = args->wantInt("rid");
    int8_t mtype = args->wantInt("mtype");
    int64_t mid = args->wantInt("mid");
    string msg = args->wantString("msg");
    string attrs = args->wantString("attrs");
    int64_t mtime = args->wantInt("mtime");

    if (!_checkDuplicate(RoomMessage, from, rid, mid) && _serverMonitor)
         _serverMonitor->pushRoomMessage(from, rid, mtype, mid, msg, attrs, mtime);

    return nullptr;
}

FPAnswerPtr RTMProcessor::pushEventAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));

    int32_t pid = args->wantInt("pid");
    string event = args->wantString("event");
    int64_t uid = args->wantInt("uid");
    int32_t time = args->wantInt("time");
    string endpoint = args->wantString("endpoint");
    string data = args->getString("data", string());

    if (_serverMonitor)
        _serverMonitor->pushEvent(pid, event, uid, time, endpoint, data);

    return nullptr;
}

FPAnswerPtr RTMProcessor::pingAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));
    return nullptr;
}

