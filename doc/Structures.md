# RTM Server C++ SDK API Docs: Structures

[TOC]

### AudioInfo

```
struct AudioInfo
{
    string sourceLanguage;   // 源语言类型
    string recognizedLanguage;  // 识别的语言类型
    string recognizedText;   // 识别的文字
    int32_t duration;   // 语音时长（ms）
};
```



### TranslatedInfo

```
struct TranslatedInfo
{
    string sourceLanguage;   // 源语言类型
    string targetLanguage;   // 目标语言类型
    string sourceText;       // 原始文字内容
    string targetText;       // 目标文字内容
};
```



### RTMMessage

```
struct RTMMessage
{
    int64_t fromUid;
    int64_t toId;                   
    int8_t messageType;
    int64_t messageId;
    string message;
    string attrs;
    int64_t modifiedTime;
    shared_ptr<AudioInfo> audioInfo;
    shared_ptr<TranslatedInfo> translatedInfo;
};
```

When messageType == (int8_t)AudioChatMType, the audioInfo  will be assigned, and the message may be the recognized message, or empty string;  



### ChatMessageType

```
enum ChatMessageType 
{
    TextChatMType = 30,
    AudioChatMType = 31,
    CmdChatMType = 32,
};
```



### FileTokenType

```
enum FileTokenType
{
    P2PFile = 1,
    MultiFiles,
    RoomFile,
    GroupFile,
    BroadcastFile
};
```



### MessageCategory

```
enum MessageCategory
{
    P2PMessage = 1,
    GroupMessage = 2,
    RoomMessage = 3,
    BroadcastMessage = 4
};
```



### RetrievedMessage

```
struct RetrievedMessage
{
    int64_t cursorId;
    int8_t messageType;
    string message;
    string attrs;
    int64_t modifiedTime;
};
```



### HistoryMessage & HistoryMessageResult

```
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
```



### Translate & ProfanityType

```
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
```

