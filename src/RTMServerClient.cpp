#include "RTMServerClient.h"
#include "RTMMidGenerator.h"

using namespace rtm;

RTMServerClient::RTMServerClient(int32_t pid, const string& secret, const string& endpoint): 
_stop(false), _pid(pid), _secret(secret)
{
    _autoReconnect = true;
    _isReconnect = false;
    _canReconnect = false;
    _requireClose = false;
    RTMMidGenerator::init();
    _regressiveStatus.connectFailedCount = 0;
    _regressiveStatus.regressiveConnectInterval = _regressiveStrategy.firstIntervalSeconds;
    _client = TCPClient::createClient(endpoint);
    _processor.reset(new RTMProcessor(RTMServerConfig::globalDuplicateCacheSize, [this](const ConnectionInfo& connInfo, bool connected) {
        _client->setAutoReconnect(false);
        _connectedCallback(connInfo, connected);
    }, [this](const ConnectionInfo& connInfo, bool closeByError) {
        _closedCallback(connInfo, closeByError);
    }));
    _questTimeout = RTMServerConfig::globalQuestTimeoutSeconds;
    if (_client) {
        _client->setQuestTimeout(RTMServerConfig::globalQuestTimeoutSeconds);
        _client->setQuestProcessor(_processor);
    }
    {
        lock_guard<mutex> lck(_opLock);
        _routineStart = false;
    }
}

RTMServerClient::~RTMServerClient()
{
    _stop = true;
    {
        lock_guard<mutex> lck(_opLock);
        if (_routineStart)
            _routineThread.join();
    }
}

void RTMServerClient::_connectedCallback(const ConnectionInfo& connInfo, bool connected)
{
    lock_guard<mutex> lck(_opLock);
    _canReconnect = true;
    _lastConnectTime = TimeUtil::curr_msec();
    _processor->rtmConnectedCallback(connInfo.endpoint(), true, _isReconnect);
}

void RTMServerClient::_closedCallback(const ConnectionInfo& connInfo, bool closeByError)
{
    lock_guard<mutex> lck(_opLock);
    _lastCloseTime = TimeUtil::curr_msec();
    _processor->rtmClosedCallback(connInfo.endpoint(), closeByError, _isReconnect);

    if (!_requireClose && _autoReconnect) {
        _isReconnect = true;
        if (_lastCloseTime - _lastConnectTime > _regressiveStrategy.connectFailedMaxIntervalMilliseconds) {
            _regressiveStatus.connectFailedCount = 0;
            _regressiveStatus.regressiveConnectInterval = _regressiveStrategy.firstIntervalSeconds;
        }
        _tryReconnect();
    }
}

void RTMServerClient::_tryReconnect()
{
    if (_regressiveStatus.connectFailedCount < _regressiveStrategy.startConnectFailedCount) {
        _regressiveStatus.connectFailedCount++;
        if (!_client->reconnect()) {
            _processor->rtmConnectedCallback("", false, _isReconnect);
            _tryReconnect();
        } else if (_isReconnect)
            _listenStatusRestoration();
    } else
        thread(&RTMServerClient::_regressiveReconnect, this).detach();
}

void RTMServerClient::_regressiveReconnect()
{
    int sleepInterval = 0;
    {
        lock_guard<mutex> lck(_opLock);
        sleepInterval = _regressiveStatus.regressiveConnectInterval;
        _regressiveStatus.regressiveConnectInterval += (_regressiveStrategy.maxIntervalSeconds - _regressiveStrategy.firstIntervalSeconds) / _regressiveStrategy.linearRegressiveCount;
    }
    sleep(sleepInterval);
    {
        lock_guard<mutex> lck(_opLock);
        _regressiveStatus.connectFailedCount++;
    }
    if (!_client->reconnect()) {
        _processor->rtmConnectedCallback("", false, _isReconnect);
        _tryReconnect();
    } else if (_isReconnect)
        _listenStatusRestoration();
}

void RTMServerClient::setServerPushMonitor(shared_ptr<RTMServerPushMonitor> serverMonitor)
{
    _processor->setServerMonitor(serverMonitor);
}

bool RTMServerClient::connected()
{
    return _client->connected();
}

bool RTMServerClient::connect()
{
    return _client->connect();
}

void RTMServerClient::close()
{
    {
        lock_guard<mutex> lck(_opLock);
        _requireClose = true;
    }
    _client->close();
}

const string& RTMServerClient::endpoint()
{
    return _client->endpoint();
}

void RTMServerClient::setQuestTimeout(int seconds)
{
    _questTimeout = seconds;
    _client->setQuestTimeout(seconds);
}

void RTMServerClient::setAutoReconnect(bool autoReconnect)
{
    _autoReconnect = autoReconnect;
}

void RTMServerClient::setRegressiveConnectStrategy(RegressiveStrategy strategy)
{
    _regressiveStrategy = strategy;
}

bool RTMServerClient::enableEncryptorByDerData(const string &derData, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByDerData(derData, packageMode, reinforce);
}

bool RTMServerClient::enableEncryptorByPemData(const string &PemData, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByPemData(PemData, packageMode, reinforce);
}

bool RTMServerClient::enableEncryptorByDerFile(const char *derFilePath, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByDerFile(derFilePath, packageMode, reinforce);
}

bool RTMServerClient::enableEncryptorByPemFile(const char *pemFilePath, bool packageMode, bool reinforce)
{
    return _client->enableEncryptorByPemFile(pemFilePath, packageMode, reinforce);
}

void RTMServerClient::enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode, bool reinforce)
{
    _client->enableEncryptor(curve, peerPublicKey, packageMode, reinforce);
}

string RTMServerClient::_calcMD5(const string& content)
{
    unsigned char digest[16];
    md5_checksum(digest, content.c_str(), content.size());
    char hexstr[32 + 1];
    Hexlify(hexstr, digest, sizeof(digest));
    return string(hexstr);
}

void RTMServerClient::_makeSignAndSalt(int32_t ts, const string& cmd, string& sign, int64_t& salt)
{
    salt = RTMMidGenerator::genMid();
    string content = to_string(_pid) + ":" + _secret + ":" + to_string(salt) + ":" + cmd + ":" + to_string(ts);
    sign = _calcMD5(content); 
}

bool RTMServerClient::_checkAnswerError(FPAnswerPtr answer, QuestResult& result, int32_t errorCode)
{
    if (!answer) 
    {
        result.errorCode = FPNN_EC_CORE_UNKNOWN_ERROR;
        result.errorInfo = "Unknown Error";
        return true;
    }
    if (errorCode > 0 || answer->status()) 
    {
        FPAReader ar(answer);
        result.errorCode = ar.getInt("code");
        result.errorInfo = ar.getString("ex");
        return true; 
    }
    else
    {
        result.errorCode = FPNN_EC_OK;
        result.errorInfo = "";
    }
    return false;
}

void RTMServerClient::_checkRoutine()
{
    lock_guard<mutex> lck(_opLock);
    if (!_routineStart) {
        _routineThread = thread(&RTMServerClient::_routine, this);
        _routineStart = true;
    }
}

void RTMServerClient::_routine()
{
    while (!_stop)
    {
        int cyc = 1 * 10;
        while (!_stop && cyc--)
        	usleep(100000);

        _checkFileGateClients();
    }
}

void RTMServerClient::_checkFileGateClients()
{
    set<string> emptyEndpoints;
    int32_t threshold = TimeUtil::curr_sec() - RTMServerConfig::fileGateClientHoldingSeconds;
    {
        lock_guard<mutex> lck(_fileClientMapLock);
        for (auto& kvEndpoint: _fileClientMap) {
            set<TCPClientPtr> unactivedClients;
            for (auto& kvClient: kvEndpoint.second) {
                if (kvClient.second < threshold)
                    unactivedClients.insert(kvClient.first);
            }

            for (auto& client: unactivedClients)
                kvEndpoint.second.erase(client);

            if (kvEndpoint.second.size() == 0)
                emptyEndpoints.insert(kvEndpoint.first);
        }

        for (auto& key: emptyEndpoints)
            _fileClientMap.erase(key);
    }
}
