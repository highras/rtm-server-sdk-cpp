# RTM Server C++ SDK API Docs: Structures

[TOC]

### TranslatedInfo

```
struct TranslatedInfo
{
    string sourceLanguage;   // source language
    string targetLanguage;   // target language
    string sourceText;       // source text
    string targetText;       // target text
};
```


### FileInfo

```
struct FileInfo
{
    string url;
    string surl;
    string language;
    int32_t size;
    int32_t duration;
    bool isRTMAudio;
};


### CheckResult

```
struct CheckResult
{
    int32_t result;
    vector<int32_t> tags;
};
```


### TextCheckResult

```
struct TextCheckResult
{
    string text;
    int32_t result;
    vector<string> wlist;
    vector<int32_t> tags;
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
    RealAudioType = 35,
    RealVideoType = 36,
    ImageFileType = 40,
    AudioFileType = 41,
    VideoFileType = 42,
    NormalFileType = 50,
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
    ar,             //Arabic
    nl,             //Dutch
    en,             //English
    fr,             //French
    de,             //German
    el,             //Greek
    id,             //Indonesian
    it,             //Italian
    ja,             //Japanese
    ko,             //Korean
    no,             //Norwegian
    pl,             //Polish
    pt,             //Portuguese
    ru,             //Russian
    es,             //Spanish
    sv,             //Swedish
    tl,             //Tagalog(Filipino)
    th,             //Thai
    tr,             //Turkish
    vi,             //Vietnamese
    zh_cn,       //Chinese(Simplified)
    zh_tw,       //Chinese(Traditional)
    None
};
```

