#ifndef RTM_SERVER_MONITOR_H
#define RTM_SERVER_MONITOR_H
#include "fpnn.h"

namespace rtm 
{
    using namespace std;
    using namespace fpnn;

    class RTMServerMonitor
    {
        public:
            virtual void connected(const ConnectionInfo& connInfo) {}
            virtual void connectionWillClose(const ConnectionInfo& connInfo, bool closeByError) {}
            virtual void pushP2PMessage(int64_t from, int64_t to, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime) {}
            virtual void pushGroupMessage(int64_t from, int64_t gid, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime) {}
            virtual void pushRoomMessage(int64_t from, int64_t rid, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime) {}
            virtual void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data) {}
            virtual void pushP2PFile(int64_t from, int64_t to, int8_t mtype, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushGroupFile(int64_t from, int64_t gid, int8_t mtype, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushRoomFile(int64_t from, int64_t rid, int8_t mtype, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushP2PChat(int64_t from, int64_t to, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushP2PAudio(int64_t from, int64_t to, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushP2PCmd(int64_t from, int64_t to, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushGroupChat(int64_t from, int64_t gid, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushGroupAudio(int64_t from, int64_t gid, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushGroupCmd(int64_t from, int64_t gid, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushRoomChat(int64_t from, int64_t rid, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushRoomAudio(int64_t from, int64_t rid, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual void pushRoomCmd(int64_t from, int64_t rid, int64_t mid, const string& msg, const string& attrs, int64_t mtime) {}
            virtual ~RTMServerMonitor() {}
    };
}

#endif
