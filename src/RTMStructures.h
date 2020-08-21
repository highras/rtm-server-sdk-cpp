#ifndef RTM_STRUCTURES_H
#define RTM_STRUCTURES_H
#include <vector>
#include "fpnn.h"
#include "FPJson.h"

namespace rtm 
{
    using namespace std;
    using namespace fpnn;

    struct QuestResult
    {
        int32_t errorCode;
        string errorInfo;

        QuestResult()
        {
            errorCode = 0;
            errorInfo = "";
        }

        bool isError()
        {
            return errorCode > 0 || !errorInfo.empty();
        }
    };

    struct CommonMessage
    {
        int64_t id;
        int64_t from;
        int8_t mtype;
        int64_t mid;
        bool deleted;
        string msg;
        string attrs;
        int64_t mtime;
        MSGPACK_DEFINE(id, from, mtype, mid, deleted, msg, attrs, mtime);
    };

    struct P2PMessage
    {
        int64_t id;
        int8_t direction;
        int8_t mtype;
        int64_t mid;
        bool deleted;
        string msg;
        string attrs;
        int64_t mtime;
        MSGPACK_DEFINE(id, direction, mtype, mid, deleted, msg, attrs, mtime);
    };
    
    enum ChatMessageType 
    {
        TextChatMType = 30,
        AudioChatMType = 31,
        CmdChatMType = 32,
    };

    enum FileTokenType
    {
        P2PFile = 1,
        MultiFiles,
        RoomFile,
        GroupFile,
        BroadcastFile
    };

    enum MessageCategory
    {
        P2PMessage = 1,
        GroupMessage = 2,
        RoomMessage = 3,
        BroadcastMessage = 4
    };


    struct SendFileInfo
    {
        FileTokenType type;
        int64_t from;
        int64_t toId;
        set<int64_t> toIds;
    };

    struct RetrievedMessage
    {
        int64_t cursorId;
        int8_t messageType;
        string message;
        string attrs;
        int64_t modifiedTime;
    };

    struct AudioInfo
    {
        string sourceLanguage;
        string recognizedLanguage;
        string recognizedText;
        int32_t duration;
    };

    struct TranslatedInfo
    {
        string sourceLanguage;
        string targetLanguage;
        string sourceText;
        string targetText;
    };

    struct RTMMessage
    {
        int64_t fromUid;
        int64_t toId;                   //-- xid
        int8_t messageType;
        int64_t messageId;
        string message;
        string attrs;
        int64_t modifiedTime;
        shared_ptr<AudioInfo> audioInfo;
        shared_ptr<TranslatedInfo> translatedInfo;
    };

    struct HistoryMessage : RTMMessage
    {
        int64_t cursorId;
    };

    struct HistoryMessageResult
    {
        int32_t count;
        int64_t lastCursorId;
        int64_t beginMsec;
        int64_t endMsec;
        vector<HistoryMessage> messages;
    };

    enum TranslateType
    {
        Chat,
        Mail
    };

    enum ProfanityType
    {
        Off,
        Censor
    };

    enum TranslateLanguage
    {
        ar,             //阿拉伯语
        nl,             //荷兰语
        en,             //英语
        fr,             //法语
        de,             //德语
        el,             //希腊语
        id,             //印度尼西亚语
        it,             //意大利语
        ja,             //日语
        ko,             //韩语
        no,             //挪威语
        pl,             //波兰语
        pt,             //葡萄牙语
        ru,             //俄语
        es,             //西班牙语
        sv,             //瑞典语
        tl,             //塔加路语（菲律宾语）
        th,             //泰语
        tr,             //土耳其语
        vi,             //越南语
        zh_cn,       //中文（简体）
        zh_tw,       //中文（繁体）
        None
    };

    inline string getTranslatedLanguage(TranslateLanguage language)
    {
        switch (language)
        {
            case ar:   return "ar";
            case nl:   return "nl";
            case en:   return "en";
            case fr:   return "fr";
            case de:   return "de";
            case el:   return "el";
            case id:   return "id";
            case it:   return "it";
            case ja:   return "ja";
            case ko:   return "ko";
            case no:   return "no";
            case pl:   return "pl";
            case pt:   return "pt";
            case ru:   return "ru";
            case es:   return "es";
            case sv:   return "sv";
            case tl:   return "tl";
            case th:   return "th";
            case tr:   return "tr";
            case vi:   return "vi";
            case zh_cn:   return "zh-CN";
            case zh_tw:   return "zh-TW";
            default:      return "";
        }
    }

    inline shared_ptr<AudioInfo> buildAudioInfo(const string& message)
    {
        try {
            shared_ptr<AudioInfo> audioInfo(new AudioInfo);
            JsonPtr json = Json::parse(message.c_str());
            audioInfo->sourceLanguage = json->wantString("sl");
            audioInfo->recognizedLanguage = json->wantString("rl");
            audioInfo->recognizedText = json->wantString("rt");
            audioInfo->duration = json->wantInt("du");
            return audioInfo;
        } catch (...) {
            return nullptr;
        }
    }

}

#endif