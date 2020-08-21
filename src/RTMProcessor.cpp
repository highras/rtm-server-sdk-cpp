#include "RTMProcessor.h"

using namespace rtm;

bool RTMProcessor::_checkDuplicate(PushMessageType msgType, int64_t from, int64_t to, int64_t mid)
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
    _connectedCallback(connInfo);
}

void RTMProcessor::connectionWillClose(const ConnectionInfo& connInfo, bool closeByError)
{
    _willCloseCallback(connInfo, closeByError);
}

void RTMProcessor::rtmConnectedCallback(const string& endpoint, bool connected, bool isReconnect)
{
    if (_serverMonitor)
        _serverMonitor->connected(endpoint, connected, isReconnect);
}

void RTMProcessor::rtmClosedCallback(const string& endpoint, bool causedByError, bool isReconnect)
{
    if (_serverMonitor)
        _serverMonitor->closed(endpoint, causedByError, isReconnect);
}

RTMMessage RTMProcessor::_buildRTMMessage(const FPReaderPtr args)
{
    RTMMessage rtmMessage;
    rtmMessage.fromUid = args->wantInt("from");
    rtmMessage.toId = args->wantInt("to");
    rtmMessage.messageId = args->wantInt("mid");
    rtmMessage.messageType = args->wantInt("mtype");
    rtmMessage.attrs = args->wantString("attrs");
    rtmMessage.modifiedTime = args->wantInt("mtime");
    rtmMessage.message = args->wantInt("msg");

    if (rtmMessage.messageType == (int8_t)AudioChatMType)
    {
        rtmMessage.audioInfo = buildAudioInfo(rtmMessage.message);

        if (rtmMessage.audioInfo != nullptr)
            rtmMessage.message = rtmMessage.audioInfo->recognizedText;
    }
    return rtmMessage;
}

FPAnswerPtr RTMProcessor::pushP2PMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));

    int64_t from = args->wantInt("from");
    int64_t to = args->wantInt("to");
    int64_t mid = args->wantInt("mid");

    if (_checkDuplicate(PT_P2PMessage, from, to, mid) || !_serverMonitor)
        return nullptr;

    RTMMessage rtmMessage = _buildRTMMessage(args);

    if (rtmMessage.messageType == (int8_t)TextChatMType)
        _serverMonitor->pushP2PChat(rtmMessage);
    else if (rtmMessage.messageType == (int8_t)AudioChatMType && rtmMessage.audioInfo != nullptr)
        _serverMonitor->pushP2PAudio(rtmMessage);
    else if (rtmMessage.messageType == (int8_t)CmdChatMType)
        _serverMonitor->pushP2PCmd(rtmMessage);
    else if (rtmMessage.messageType >= 40 && rtmMessage.messageType <= 50)
        _serverMonitor->pushP2PFile(rtmMessage);
    else
        _serverMonitor->pushP2PMessage(rtmMessage);
        
    return nullptr;
}

FPAnswerPtr RTMProcessor::pushGroupMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));
    
    int64_t from = args->wantInt("from");
    int64_t gid = args->wantInt("gid");
    int64_t mid = args->wantInt("mid");

    if (_checkDuplicate(PT_GroupMessage, from, gid, mid) || !_serverMonitor)
        return nullptr;

    RTMMessage rtmMessage = _buildRTMMessage(args);

    if (rtmMessage.messageType == (int8_t)TextChatMType)
        _serverMonitor->pushGroupChat(rtmMessage);
    else if (rtmMessage.messageType == (int8_t)AudioChatMType && rtmMessage.audioInfo != nullptr)
        _serverMonitor->pushGroupAudio(rtmMessage);
    else if (rtmMessage.messageType == (int8_t)CmdChatMType)
        _serverMonitor->pushGroupCmd(rtmMessage);
    else if (rtmMessage.messageType >= 40 && rtmMessage.messageType <= 50)
        _serverMonitor->pushGroupFile(rtmMessage);
    else
        _serverMonitor->pushGroupMessage(rtmMessage);

    return nullptr;
}

FPAnswerPtr RTMProcessor::pushRoommMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci)
{
    sendAnswer(quest, FPAWriter::emptyAnswer(quest));

    int64_t from = args->wantInt("from");
    int64_t rid = args->wantInt("rid");
    int64_t mid = args->wantInt("mid");

    if (_checkDuplicate(PT_RoomMessage, from, rid, mid) || !_serverMonitor)
         return nullptr;

    RTMMessage rtmMessage = _buildRTMMessage(args);

    if (rtmMessage.messageType == (int8_t)TextChatMType)
        _serverMonitor->pushRoomChat(rtmMessage);
    else if (rtmMessage.messageType == (int8_t)AudioChatMType && rtmMessage.audioInfo != nullptr)
        _serverMonitor->pushRoomAudio(rtmMessage);
    else if (rtmMessage.messageType == (int8_t)CmdChatMType)
        _serverMonitor->pushRoomCmd(rtmMessage);
    else if (rtmMessage.messageType >= 40 && rtmMessage.messageType <= 50)
        _serverMonitor->pushRoomFile(rtmMessage);
    else
        _serverMonitor->pushRoomMessage(rtmMessage);

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
    if (_serverMonitor)
        _serverMonitor->ping();
    return nullptr;
}
