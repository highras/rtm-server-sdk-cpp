#include "RTMServerConfig.h"

using namespace rtm;

const string RTMServerConfig::SDK_VERSION = "2.2.0";
const string RTMServerConfig::INTERFACE_VERSION = "2.7.0";

int32_t RTMServerConfig::globalConnectTimeoutSeconds = 30;
int32_t RTMServerConfig::globalQuestTimeoutSeconds = 30;
int32_t RTMServerConfig::fileGateClientHoldingSeconds = 150;
int32_t RTMServerConfig::globalDuplicateCacheSize = 5000;