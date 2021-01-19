#include "RTMServerClient.h"

using namespace rtm;

int32_t RTMServerClient::sendChat(int64_t& mid, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, TextChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendChat(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, TextChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendCmd(int64_t& mid, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, CmdChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendCmd(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendMessageQuest(fromUid, toUid, CmdChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendChats(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, TextChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendChats(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, TextChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendCmds(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, CmdChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendCmds(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendMessagesQuest(fromUid, toUids, CmdChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendGroupChat(int64_t& mid, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, TextChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendGroupChat(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, TextChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendGroupCmd(int64_t& mid, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, CmdChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendGroupCmd(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendGroupMessageQuest(fromUid, groupId, CmdChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendRoomChat(int64_t& mid, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, TextChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendRoomChat(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, TextChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::sendRoomCmd(int64_t& mid, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, CmdChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::sendRoomCmd(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getSendRoomMessageQuest(fromUid, roomId, CmdChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::broadcastChat(int64_t& mid, int64_t fromUid, const string& message, const string& attrs,int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, TextChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    !_checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::broadcastChat(int64_t fromUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, TextChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
    }, timeout);

    if (!status)
        callback(0, FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::broadcastCmd(int64_t& mid, int64_t fromUid, const string& message, const string& attrs, int32_t timeout)
{
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, CmdChatMType, message, attrs, mid);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult result;
    _checkAnswerError(answer, result);
    return result.errorCode;
}

void RTMServerClient::broadcastCmd(int64_t fromUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout)
{
    int64_t mid = 0;
    FPQuestPtr quest = _getBroadcastMessageQuest(fromUid, CmdChatMType, message, attrs, mid);
    bool status = _client->sendQuest(quest, [this, mid, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        _checkAnswerError(answer, result, errorCode);
        callback(mid, result.errorCode);
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

FPQuestPtr RTMServerClient::_getSpeechToTextQuest(const string& audio, int32_t audioType, const string& language, const string& codec, int32_t sampleRate, int64_t userId)
{
    int32_t size = 10;
    if (codec.empty())
        size -= 1;
    if (sampleRate <= 0)
        size -= 1;
    if (userId <= 0)
        size -= 1;

    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "speech2text", sign, salt);

    FPQWriter qw(size, "speech2text");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("audio", audio);
    qw.param("type", audioType);
    qw.param("lang", language);
    if (!codec.empty())
        qw.param("codec", codec);
    if (sampleRate > 0)
        qw.param("srate", sampleRate);
    if (userId > 0)
        qw.param("uid", userId);
 
    return qw.take();
}

FPQuestPtr RTMServerClient::_getTextCheckQuest(const string& text, int64_t userId)
{
    int32_t size = 6;
    if (userId <= 0)
        size -= 1;

    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "tcheck", sign, salt);

    FPQWriter qw(size, "tcheck");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("text", text);
    if (userId > 0)
        qw.param("uid", userId);
 
    return qw.take();
}

FPQuestPtr RTMServerClient::_getImageCheckQuest(const string& image, int32_t imageType, int64_t userId)
{
    int32_t size = 7;
    if (userId <= 0)
        size -= 1;

    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "icheck", sign, salt);

    FPQWriter qw(size, "icheck");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("image", image);
    qw.param("type", imageType);
    if (userId > 0)
        qw.param("uid", userId);
 
    return qw.take();
}

FPQuestPtr RTMServerClient::_getAudioCheckQuest(const string& audio, int32_t audioType, const string& language, const string& codec, int32_t sampleRate, int64_t userId)
{
    int32_t size = 10;
    if (codec.empty())
        size -= 1;
    if (sampleRate <= 0)
        size -= 1;
    if (userId <= 0)
        size -= 1;

    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "acheck", sign, salt);

    FPQWriter qw(size, "acheck");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("audio", audio);
    qw.param("type", audioType);
    qw.param("lang", language);
    if (!codec.empty())
        qw.param("codec", codec);
    if (sampleRate > 0)
        qw.param("srate", sampleRate);
    if (userId > 0)
        qw.param("uid", userId);
 
    return qw.take();
}

FPQuestPtr RTMServerClient::_getVideoCheckQuest(const string& video, int32_t videoType, const string& videoName, int64_t userId)
{
    int32_t size = 8;
    if (userId <= 0)
        size -= 1;

    int32_t ts = slack_real_sec(); 
    string sign;
    int64_t salt;
    _makeSignAndSalt(ts, "vcheck", sign, salt);

    FPQWriter qw(size, "vcheck");
    qw.param("pid", _pid);
    qw.param("sign", sign);
    qw.param("salt", salt);
    qw.param("ts", ts);
    qw.param("video", video);
    qw.param("type", videoType);
    qw.param("videoName", videoName);
    if (userId > 0)
        qw.param("uid", userId);
 
    return qw.take();
}

bool RTMServerClient::_checkCheckType(int32_t type)
{
    if (type >= 1 || type <= 2)
        return true;
    return false;
}

int32_t RTMServerClient::speechToText(string& resultText, string& resultLanguage, const string& audio, int32_t audioType, const string& language, const string codec, int32_t sampleRate, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(audioType))
        return RTM_EC_INVALID_PARAMETER;

    FPQuestPtr quest = _getSpeechToTextQuest(audio, audioType, language, codec, sampleRate, userId);
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

void RTMServerClient::speechToText(const string& audio, int32_t audioType, const string& language, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, const string codec, int32_t sampleRate, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(audioType))
    {
        callback("", "", RTM_EC_INVALID_PARAMETER);
        return;
    }
    FPQuestPtr quest = _getSpeechToTextQuest(audio, audioType, language, codec, sampleRate, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult result;
        string resultText;
        string resultLanguage;
        if (!_checkAnswerError(answer, result, errorCode))
        {
            FPAReader ar(answer);
            resultText = ar.getString("text");
            resultLanguage = ar.getString("lang");
        }
        callback(resultText, resultLanguage, errorCode);
    }, timeout);

    if (!status)
        callback("", "", FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::textCheck(TextCheckResult& result, const string& text, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getTextCheckQuest(text, userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
    {
        FPAReader ar(answer);
        result.result = ar.wantInt("result");
        result.text = ar.getString("text");
        result.tags = ar.get("tags", vector<int32_t>());
        result.wlist = ar.get("wlist", vector<string>());
    }
    return questResult.errorCode;
}

void RTMServerClient::textCheck(const string& text, std::function<void (TextCheckResult result, int32_t errorCode)> callback, int64_t userId, int32_t timeout)
{
    FPQuestPtr quest = _getTextCheckQuest(text, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        TextCheckResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
        {
            FPAReader ar(answer);
            result.result = ar.wantInt("result");
            result.text = ar.getString("text");
            result.tags = ar.get("tags", vector<int32_t>());
            result.wlist = ar.get("wlist", vector<string>());
        }
        callback(result, errorCode);
    }, timeout);

    if (!status)
        callback(TextCheckResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::imageCheck(CheckResult& result, const string& image, int32_t imageType, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(imageType))
        return RTM_EC_INVALID_PARAMETER;

    FPQuestPtr quest = _getImageCheckQuest(image, imageType, userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
    {
        FPAReader ar(answer);
        result.result = ar.wantInt("result");
        result.tags = ar.get("tags", vector<int32_t>());
    }
    return questResult.errorCode;
}

void RTMServerClient::imageCheck(const string& image, int32_t imageType, std::function<void (CheckResult result, int32_t errorCode)> callback, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(imageType))
    {
        callback(CheckResult(), RTM_EC_INVALID_PARAMETER);
        return;
    }

    FPQuestPtr quest = _getImageCheckQuest(image, imageType, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        CheckResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
        {
            FPAReader ar(answer);
            result.result = ar.wantInt("result");
            result.tags = ar.get("tags", vector<int32_t>());
        }
        callback(result, errorCode);
    }, timeout);

    if (!status)
        callback(CheckResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::audioCheck(CheckResult& result, const string& audio, int32_t audioType, const string& language, const string codec, int32_t sampleRate, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(audioType))
        return RTM_EC_INVALID_PARAMETER;

    FPQuestPtr quest = _getAudioCheckQuest(audio, audioType, language, codec, sampleRate, userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
    {
        FPAReader ar(answer);
        result.result = ar.wantInt("result");
        result.tags = ar.get("tags", vector<int32_t>());
    }
    return questResult.errorCode;
}

void RTMServerClient::audioCheck(const string& audio, int32_t audioType, const string& language, std::function<void (CheckResult result, int32_t errorCode)> callback, const string codec, int32_t sampleRate, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(audioType))
    {
        callback(CheckResult(), RTM_EC_INVALID_PARAMETER);
        return;
    }

    FPQuestPtr quest = _getAudioCheckQuest(audio, audioType, language, codec, sampleRate, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        CheckResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
        {
            FPAReader ar(answer);
            result.result = ar.wantInt("result");
            result.tags = ar.get("tags", vector<int32_t>());
        }
        callback(result, errorCode);
    }, timeout);

    if (!status)
        callback(CheckResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

int32_t RTMServerClient::videoCheck(CheckResult& result, const string& video, int32_t videoType, const string& videoName, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(videoType))
        return RTM_EC_INVALID_PARAMETER;

    FPQuestPtr quest = _getVideoCheckQuest(video, videoType, videoName, userId);
    FPAnswerPtr answer = _client->sendQuest(quest, timeout);

    QuestResult questResult;
    if (!_checkAnswerError(answer, questResult))
    {
        FPAReader ar(answer);
        result.result = ar.wantInt("result");
        result.tags = ar.get("tags", vector<int32_t>());
    }
    return questResult.errorCode;
}

void RTMServerClient::videoCheck(const string& video, int32_t videoType, const string& videoName, std::function<void (CheckResult result, int32_t errorCode)> callback, int64_t userId, int32_t timeout)
{
    if (!_checkCheckType(videoType))
    {
        callback(CheckResult(), RTM_EC_INVALID_PARAMETER);
        return;
    }

    FPQuestPtr quest = _getVideoCheckQuest(video, videoType, videoName, userId);
    bool status = _client->sendQuest(quest, [this, callback](FPAnswerPtr answer, int32_t errorCode) {
        QuestResult questResult;
        CheckResult result;
        if (!_checkAnswerError(answer, questResult, errorCode))
        {
            FPAReader ar(answer);
            result.result = ar.wantInt("result");
            result.tags = ar.get("tags", vector<int32_t>());
        }
        callback(result, errorCode);
    }, timeout);

    if (!status)
        callback(CheckResult(), FPNN_EC_CORE_INVALID_CONNECTION);
}

