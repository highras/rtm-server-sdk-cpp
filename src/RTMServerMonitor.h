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
            virtual ~RTMServerMonitor() {}
    };
}

#endif
