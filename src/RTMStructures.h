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
        RealAudioType = 35,
        RealVideoType = 36,
        ImageFileType = 40,
        AudioFileType = 41,
        VideoFileType = 42,
        NormalFileType = 50
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

    struct TranslatedInfo
    {
        string sourceLanguage;
        string targetLanguage;
        string sourceText;
        string targetText;
    };

    struct FileInfo
    {
        FileInfo(): url(""), surl(""), language(""), size(0), duration(0), isRTMAudio(false){}
        string url;
        string surl;
        string language;
        int32_t size;
        int32_t duration;
        bool isRTMAudio;
    };

    struct CheckResult
    {
        CheckResult() : result(0) {}
        int32_t result;
        vector<int32_t> tags;
    };

    struct TextCheckResult
    {
        TextCheckResult() : result(0) {}
        string text;
        int32_t result;
        vector<string> wlist;
        vector<int32_t> tags;
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
        shared_ptr<TranslatedInfo> translatedInfo;
        shared_ptr<FileInfo> fileInfo;
    };

    struct HistoryMessage : RTMMessage
    {
        int64_t cursorId;
    };

    struct RetrievedMessage : RTMMessage
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

    enum AdministratorCommand
    {
        AppointAdministrator    = 0, //赋予管理员权限
        DismissAdministrator    = 1, //剥夺管理员权限
        ForbidSendingAudio      = 2, //禁止发送音频数据
        AllowSendingAudio       = 3, //允许发送视频数据
        ForbidSendingVideo      = 4, //禁止发送视频数据
        AllowSendingVideo       = 5, //允许发送视频数据
        CloseOthersMicroPhone   = 6, //关闭他人麦克风
        CloseOthersMicroCamera  = 7, //关闭他人摄像头
    };
}

#endif