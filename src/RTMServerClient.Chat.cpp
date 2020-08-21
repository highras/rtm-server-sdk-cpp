#include "RTMServerClient.h"

using namespace rtm;

int32_t RTMServerClient::sendChat(int32_t& modifyTime, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, TextChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendChat(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, TextChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendAudio(int32_t& modifyTime, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, AudioChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendAudio(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, AudioChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendCmd(int32_t& modifyTime, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, CmdChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendCmd(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, CmdChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode)) 
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendChats(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, TextChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendChats(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, TextChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendAudios(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, AudioChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendAudios(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, AudioChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode)) 
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendCmds(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, CmdChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendCmds(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, CmdChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendGroupChat(int32_t& modifyTime, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, TextChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendGroupChat(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, TextChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendGroupAudio(int32_t& modifyTime, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, AudioChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendGroupAudio(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, AudioChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendGroupCmd(int32_t& modifyTime, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, CmdChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendGroupCmd(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, CmdChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendRoomChat(int32_t& modifyTime, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, TextChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendRoomChat(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, TextChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendRoomAudio(int32_t& modifyTime, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, AudioChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendRoomAudio(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, AudioChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendRoomCmd(int32_t& modifyTime, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, CmdChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::sendRoomCmd(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, CmdChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::broadcastChat(int32_t& modifyTime, int64_t fromUid, const string& message, const string& attrs,int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, TextChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::broadcastChat(int64_t fromUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, TextChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::broadcastAudio(int32_t& modifyTime, int64_t fromUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, AudioChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::broadcastAudio(int64_t fromUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, AudioChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::broadcastCmd(int32_t& modifyTime, int64_t fromUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, CmdChatMType, message, attrs);  
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        modifyTime = ar.getInt("mtime");
    }
    return result.errorCode;
}

void RTMServerClient::broadcastCmd(int64_t fromUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, CmdChatMType, message, attrs);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        int32_t modifyTime = 0;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            modifyTime = ar.getInt("mtime");
        }
        callback(modifyTime, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::getGroupChat(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout)
{
    return getGroupMessage(result, groupId, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, uid, timeout);
}

void RTMServerClient::getGroupChat(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    getGroupMessage(groupId, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, uid, callback, timeout);
}

int32_t RTMServerClient::getRoomChat(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout)
{
    return getRoomMessage(result, roomId, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, uid, timeout);
}

void RTMServerClient::getRoomChat(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    getRoomMessage(roomId, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, uid, callback, timeout);
}

int32_t RTMServerClient::getBroadcastChat(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout)
{
    return getBroadcastMessage(result, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, uid, timeout);
}

void RTMServerClient::getBroadcastChat(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    getBroadcastMessage(desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, uid, callback, timeout);
}

int32_t RTMServerClient::getP2PChat(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int32_t timeout)
{
    return getP2PMessage(result, userId, otherUserId, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, timeout);
}

void RTMServerClient::getP2PChat(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout)
{
    getP2PMessage(userId, otherUserId, desc, count, beginMsec, endMsec, lastId, {TextChatMType, AudioChatMType, CmdChatMType}, callback, timeout);
}

int32_t RTMServerClient::getChat(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout)
{
    return getMessage(retrievedMessage, mid, fromUid, toId, messageCategory, timeout);
}

void RTMServerClient::getChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout)
{
    getMessage(mid, fromUid, toId, messageCategory, callback, timeout);
}

int32_t RTMServerClient::deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout)
{
    return deleteMessage(mid, fromUid, toId, messageCategory, timeout);
}

void RTMServerClient::deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout)
{
    deleteMessage(mid, fromUid, toId, messageCategory, callback, timeout);
}

FPQuestPtr RTMServerClient::_getTranslateQuest(const string& text, const string& dst, const string& src, const string& type, const string& profanity, int64_t uid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "translate", sign, salt);

    FPQWriter qw(10, "translate");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("text", text);
    qw.param("dst", dst);
    qw.param("src", src);
    qw.param("type", type);
    qw.param("profanity", profanity);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::translate(TranslatedInfo& translatedInfo, const string& text, TranslateLanguage destinationLanguage, TranslateLanguage sourceLanguage, TranslateType type, ProfanityType profanity, int64_t userId, int32_t timeout)
{
    string typeStr = "chat";
    if (type == Mail)
        typeStr = "mail";

    string profanityStr = "off";
    if (profanity == Censor)
        profanityStr = "censor";

    FPQuestPtr quest = _getTranslateQuest(text, getTranslatedLanguage(destinationLanguage), getTranslatedLanguage(sourceLanguage), typeStr, profanityStr, userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        translatedInfo.sourceLanguage = ar.getString("source");
        translatedInfo.targetLanguage = ar.getString("target");
        translatedInfo.sourceText = ar.getString("sourceText");
        translatedInfo.targetText = ar.getString("targetText");
    }
    return result.errorCode;
}

void RTMServerClient::translate(const string& text, TranslateLanguage destinationLanguage, std::function<void (TranslatedInfo translatedInfo, int32_t errorCode)> callback, TranslateLanguage sourceLanguage, TranslateType type, ProfanityType profanity, int64_t userId, int32_t timeout)
{
    string typeStr = "chat";
    if (type == Mail)
        typeStr = "mail";

    string profanityStr = "off";
    if (profanity == Censor)
        profanityStr = "censor";

    FPQuestPtr quest = _getTranslateQuest(text, getTranslatedLanguage(destinationLanguage), getTranslatedLanguage(sourceLanguage), typeStr, profanityStr, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        TranslatedInfo translatedInfo;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            translatedInfo.sourceLanguage = ar.getString("source");
            translatedInfo.targetLanguage = ar.getString("target");
            translatedInfo.sourceText = ar.getString("sourceText");
            translatedInfo.targetText = ar.getString("targetText");
        }
        callback(translatedInfo, result.errorCode);
    }, timeout);

    if (!status)
        callback(TranslatedInfo(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getProfanityQuest(const string& text, bool classify, int64_t uid)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "profanity", sign, salt);

    FPQWriter qw(7, "profanity");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("text", text);
    qw.param("classify", classify);
    qw.param("uid", uid);
    return qw.take();
}

int32_t RTMServerClient::profanity(string& resultText, vector<string>& classification, const string& text, bool classify, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getProfanityQuest(text, classify, userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        resultText = ar.getString("text");
        classification = ar.get("classification", vector<string>());
    }
    return result.errorCode;
}

void RTMServerClient::profanity(const string& text, std::function<void (string resultText, vector<string> classification, int32_t errorCode)> callback, bool classify, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getProfanityQuest(text, classify, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string resultText;
        vector<string> classification;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            resultText = ar.getString("text");
            classification = ar.get("classification", classification);
        } 
        callback(resultText, classification, result.errorCode);
    }, timeout);

    if (!status)
        callback("", vector<string>(), FPNN_EC_CORE_INVALID_CONNECTION);
}

FPQuestPtr RTMServerClient::_getTranscribeQuest(const string& audio, int64_t uid, bool profanityFilter)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "transcribe", sign, salt);

    int32_t size = 6;
    if (uid > 0)
        ++size;

    FPQWriter qw(size, "transcribe");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("audio", audio);
    qw.param("profanityFilter", profanityFilter);

    if (uid > 0)
        qw.param("uid", uid);

    return qw.take();
}

FPQuestPtr RTMServerClient::_getTranscribeMessageQuest(int64_t from, int64_t mid, int64_t toId, int8_t type, bool profanityFilter)
{
    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "stranscribe", sign, salt);

    FPQWriter qw(9, "stranscribe");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("from", from);
    qw.param("mid", mid);
    qw.param("xid", toId);
    qw.param("type", type);
    qw.param("profanityFilter", profanityFilter);
    return qw.take();
}

bool RTMServerClient::_getTranscribeCache(const char* buffer, size_t length, string& text, string& lang) 
{
    if (length < 8)
		return false;
    int8_t infoDataCount = uint8_t(*(buffer + 3));
    if (infoDataCount == 0)
        return false;
    uint32_t sectionLength = uint32_t(*(buffer + 4)) 
                            | (uint32_t(*(buffer + 5)) << 8) 
                            | (uint32_t(*(buffer + 6)) << 16) 
                            | (uint32_t(*(buffer + 7)) << 24);
    if (sectionLength + 8 >= length)
        return false;
    string payload = string(buffer + 8, sectionLength);
    FPReaderPtr reader(new FPReader(payload));
    text = reader->getString("rtext");
    lang = reader->getString("rlang");
    return text.size() && lang.size();
}

int32_t RTMServerClient::transcribe(string& resultText, string& resultLanguage, const string& audio, int64_t userId, bool profanityFilter, int32_t timeout)
{
    if (_getTranscribeCache(audio.c_str(), audio.size(), resultText, resultLanguage)) {
        if (profanityFilter) {
            vector<string> classification;
            int32_t errorCode = profanity(resultText, classification, resultText, false, userId, timeout);
            return errorCode;
        } else
            return FPNN_EC_OK;
    }

    FPQuestPtr quest = _getTranscribeQuest(audio, userId, profanityFilter);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);
    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        resultText = ar.getString("text");
        resultLanguage = ar.getString("lang");
    }
    return result.errorCode;
}

void RTMServerClient::transcribe(const string& audio, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, int64_t userId, bool profanityFilter, int32_t timeout)
{
    string resultText, resultLanguage;
    if (_getTranscribeCache(audio.c_str(), audio.size(), resultText, resultLanguage)) {
        if (profanityFilter) {
            profanity(resultText, [callback, resultLanguage](string resultText, vector<string> classification, int32_t errorCode) {
                if (errorCode == FPNN_EC_OK) {
                    callback(resultText, resultLanguage, FPNN_EC_OK);
                    return;
                } else {
                    callback("", "", errorCode);
                    return;
                }
            }, false, userId, timeout);
            return;
        } else {
            callback(resultText, resultLanguage, FPNN_EC_OK);
            return;
        }
    }

    FPQuestPtr quest = _getTranscribeQuest(audio, userId, profanityFilter);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string resultText, resultLanguage;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            resultText = ar.getString("text");
            resultLanguage = ar.getString("lang");
        }
        callback(resultText, resultLanguage, result.errorCode);
    }, timeout);

    if (!status)
        callback("", "", FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::transcribeMessage(string& resultText, string& resultLanguage, int64_t fromUid, int64_t mid, int64_t toId, MessageCategory messageCategory, bool profanityFilter, int32_t timeout)
{
    FPQuestPtr quest = _getTranscribeMessageQuest(fromUid, mid, toId, (int8_t)messageCategory, profanityFilter);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);
    QuestResult result;
    if (!_checkAnswerError(answer, result))
    {
        FPAReader ar(answer);
        resultText = ar.getString("text");
        resultLanguage = ar.getString("lang");
    }
    return result.errorCode;
}

void RTMServerClient::transcribeMessage(int64_t fromUid, int64_t mid, int64_t toId, MessageCategory messageCategory, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, bool profanityFilter, int32_t timeout)
{
    FPQuestPtr quest = _getTranscribeMessageQuest(fromUid, mid, toId, (int8_t)messageCategory, profanityFilter);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string resultText, resultLanguage;
        if (!_checkAnswerError(answer, result, errorCode)) {
            FPAReader ar(answer);
            resultText = ar.getString("text");
            resultLanguage = ar.getString("lang");
        }
        callback(resultText, resultLanguage, result.errorCode);
    }, timeout);

    if (!status)
        callback("", "", FPNN_EC_CORE_INVALID_CONNECTION);
}