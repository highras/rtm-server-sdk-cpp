#ifndef RTM_PROCESSOR_H
#define RTM_PROCESSOR_H
#include <mutex>
#include "fpnn.h"
#include "LruHashMap.h"
#include "RTMServerPushMonitor.h"
#include "RTMStructures.h"

namespace rtm 
{
    using namespace std;
    using namespace fpnn;

    enum PushMessageType {
        PT_P2PMessage = 0,
        PT_GroupMessage = 1,
        PT_RoomMessage = 2,
        PT_P2PFile = 3,
        PT_GroupFile = 4,
        PT_RoomFile = 5,
        PT_P2PChat = 6,
        PT_GroupChat = 7,
        PT_RoomChat = 8,
        PT_P2PAudio = 9,
        PT_GroupAudio = 10,
        PT_RoomAudio = 11,
        PT_P2PCmd = 12,
        PT_GroupCmd = 13,
        PT_RoomCmd = 14,
    };

    struct MessageDuplicateKey
    {
        int64_t from;
        int64_t to;
        int64_t mid;
        int64_t type;

        MessageDuplicateKey(int64_t f, int64_t t, int64_t m, PushMessageType mt): from(f), to(t), mid(m) 
        {
            type = int64_t(mt);  
        }

        bool operator==(const struct MessageDuplicateKey& key) const 
        {
            return type == key.type && from == key.from && to == key.to && mid == key.mid;
        }

        bool operator<(const struct MessageDuplicateKey& key) const
        {
            if (from != key.from)
                return from < key.from;
            else if (to != key.to)
                return to < key.to;
            else if (mid != key.mid)
                return mid < key.mid;
            else
                return type < key.type;
        }

        unsigned int hash() const
        {
            return jenkins_hash(this, sizeof(*this), 0);
        }
    };

    typedef LruHashMap<struct MessageDuplicateKey, bool> MessageDuplicateCacheMap;
    
    class RTMProcessor: public IQuestProcessor
    {
        QuestProcessorClassPrivateFields(RTMProcessor)

        shared_ptr<RTMServerPushMonitor> _serverMonitor;
        mutex _duplicateCacheLock;
        MessageDuplicateCacheMap* _duplicateCache;
        std::function<void (const ConnectionInfo& connInfo, bool connected)> _connectedCallback;
        std::function<void (const ConnectionInfo& connInfo, bool closeByError)> _willCloseCallback;

        bool _checkDuplicate(PushMessageType msgType, int64_t from, int64_t to, int64_t mid);
        RTMMessage _buildRTMMessage(const FPReaderPtr args);
        shared_ptr<TranslatedInfo> ProcessChatMessage(const FPReaderPtr args);
    public:
        void setServerMonitor(shared_ptr<RTMServerPushMonitor> serverMonitor) { _serverMonitor = serverMonitor; }

        virtual void connected(const ConnectionInfo& connInfo, bool connected);
        virtual void connectionWillClose(const ConnectionInfo& connInfo, bool closeByError);
        FPAnswerPtr  pushP2PMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pushGroupMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pushRoommMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pushEventAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pingAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        
        void rtmConnectedCallback(const string& endpoint, bool connected, bool isReconnect);
        void rtmClosedCallback(const string& endpoint, bool causedByError, bool isReconnect);
        
        RTMProcessor(int32_t duplicateCacheSize, std::function<void (const ConnectionInfo& connInfo, bool connected)> connectedCallback, std::function<void (const ConnectionInfo& connInfo, bool closeByError)> willCloseCallback)
        {
            _serverMonitor = nullptr;
            _duplicateCache = new MessageDuplicateCacheMap(duplicateCacheSize);
            _connectedCallback = connectedCallback;
            _willCloseCallback = willCloseCallback;

            registerMethod("pushmsg", &RTMProcessor::pushP2PMessageAction);
            registerMethod("pushgroupmsg", &RTMProcessor::pushGroupMessageAction);
            registerMethod("pushroommsg", &RTMProcessor::pushRoommMessageAction);
            registerMethod("pushevent", &RTMProcessor::pushEventAction);
            registerMethod("ping", &RTMProcessor::pingAction);
        }

        ~RTMProcessor()
        {
            delete _duplicateCache;
        }

        QuestProcessorClassBasicPublicFuncs
    };
}

#endif
