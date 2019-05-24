#ifndef RTM_PROCESSOR_H
#define RTM_PROCESSOR_H
#include <mutex>
#include "fpnn.h"
#include "LruHashMap.h"
#include "RTMServerMonitor.h"

using namespace std;
using namespace fpnn;

namespace rtm 
{

    enum MessageType {
        P2PMessage = 0,
        GroupMessage = 1,
        RoomMessage = 2,
    };

    struct MessageDuplicateKey
    {
        int64_t from;
        int64_t to;
        int64_t mid;
        int64_t type;

        MessageDuplicateKey(int64_t f, int64_t t, int64_t m, MessageType mt): from(f), to(t), mid(m) 
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

        shared_ptr<RTMServerMonitor> _serverMonitor;
        mutex _duplicateCacheLock;
        MessageDuplicateCacheMap* _duplicateCache;

        bool _checkDuplicate(MessageType msgType, int64_t from, int64_t to, int64_t mid);

    public:
        void setServerMonitor(shared_ptr<RTMServerMonitor> serverMonitor) { _serverMonitor = serverMonitor; }

        virtual void connected(const ConnectionInfo& connInfo);
        virtual void connectionWillClose(const ConnectionInfo& connInfo, bool closeByError);
        FPAnswerPtr  pushP2PMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pushGroupMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pushRoommMessageAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pushEventAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);
        FPAnswerPtr pingAction(const FPReaderPtr args, const FPQuestPtr quest, const ConnectionInfo& ci);

        RTMProcessor(int32_t duplicateCacheSize)
        {
            _serverMonitor = nullptr;
            _duplicateCache = new MessageDuplicateCacheMap(duplicateCacheSize); 

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
