#include "RTMServerConfig.h"

using namespace rtm;

const string RTMServerConfig::SDK_VERSION = "2.1.0";
const string RTMServerConfig::INTERFACE_VERSION = "2.6.1";

int32_t RTMServerConfig::globalConnectTimeoutSeconds = 30;
int32_t RTMServerConfig::globalQuestTimeoutSeconds = 30;
int32_t RTMServerConfig::fileGateClientHoldingSeconds = 150;
int32_t RTMServerConfig::globalDuplicateCacheSize = 5000;