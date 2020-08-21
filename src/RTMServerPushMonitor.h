#ifndef RTM_SERVER_MONITOR_H
#define RTM_SERVER_MONITOR_H
#include "fpnn.h"
#include "RTMStructures.h"

namespace rtm 
{
    using namespace std;
    using namespace fpnn;

    class RTMServerPushMonitor
    {
        public:
            
            virtual void connected(const string& endpoint, bool connected, bool isReconnect) {}
            virtual void closed(const string& endpoint, bool causedByError, bool isReconnect) {}

            virtual void pushP2PMessage(RTMMessage message) {}
            virtual void pushGroupMessage(RTMMessage message) {}
            virtual void pushRoomMessage(RTMMessage message) {}
            virtual void pushP2PFile(RTMMessage message) {}
            virtual void pushGroupFile(RTMMessage message) {}
            virtual void pushRoomFile(RTMMessage message) {}
            virtual void pushP2PChat(RTMMessage message) {}
            virtual void pushP2PAudio(RTMMessage message) {}
            virtual void pushP2PCmd(RTMMessage message) {}
            virtual void pushGroupChat(RTMMessage message) {}
            virtual void pushGroupAudio(RTMMessage message) {}
            virtual void pushGroupCmd(RTMMessage message) {}
            virtual void pushRoomChat(RTMMessage message) {}
            virtual void pushRoomAudio(RTMMessage message) {}
            virtual void pushRoomCmd(RTMMessage message) {}
            virtual void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data) {}
            virtual void ping() {}
            virtual ~RTMServerPushMonitor() {}
    };
}

#endif
