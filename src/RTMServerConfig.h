#ifndef RTM_SERVER_CONFIG_H
#define RTM_SERVER_CONFIG_H
#include "fpnn.h"

namespace rtm 
{
    using namespace std;
    using namespace fpnn;

    class RTMServerConfig
    {
    public:
        static const string SDK_VERSION;
        static const string INTERFACE_VERSION;

        static int32_t globalConnectTimeoutSeconds;
        static int32_t globalQuestTimeoutSeconds;
        static int32_t fileGateClientHoldingSeconds;
        static int32_t globalDuplicateCacheSize;

        int32_t globalConnectTimeout;
        int32_t globalQuestTimeout;
        int32_t fileClientHoldingSeconds;
        int32_t duplicateCacheSize;

        RTMServerConfig()
        {
            globalConnectTimeout = globalConnectTimeoutSeconds;
            globalQuestTimeout = globalQuestTimeoutSeconds;
            fileClientHoldingSeconds = fileGateClientHoldingSeconds;
            duplicateCacheSize = globalDuplicateCacheSize;
        }

        static void config(RTMServerConfig config)
        {
            globalConnectTimeoutSeconds = config.globalConnectTimeout;
            globalQuestTimeoutSeconds = config.globalQuestTimeoutSeconds;
            fileGateClientHoldingSeconds = config.fileClientHoldingSeconds;
            globalDuplicateCacheSize = config.duplicateCacheSize;
        }
    };

    class RTMServerConfigCenter
    {
    public:
        static void init()
        {
        }

        static void init(RTMServerConfig config)
        {
            RTMServerConfig::config(config);
        }
    };
}

#endif