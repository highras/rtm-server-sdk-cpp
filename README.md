# RTM Server C++ SDK

[TOC]

### Install

* Dependency [FPNN C++ SDK](https://github.com/highras/fpnn-sdk-cpp)
* Default header file path **../fpnn-sdk-cpp/release/include** 
* Or you can modify the value in Makefile **FPNN_RELEASE_INCLUDE_PATH**

1. Compile 

		cd <rtm-C++-SDK-folder>
		make

2. Release

		sh release.sh
    
    
### Notice

* Please make sure the server time is correct, or the signature will be incorrect



### Usage

```
#include "rtm.h"
using namespace rtm;

// optional, global configuration
RTMServerConfig config;
RTMServerConfigCenter::init(config);

// create RTMServerClient
RTMServerClientPtr client(new RTMServerClient(11000001, "xxx-xxx-xxx-xxx-xxx", "161.189.171.91:13315"));
```



#### RTMServerClient structure function

* RTMServerClient(int32_t pid, const string& secret, const string& endpoint)
  * `pid`: project id, provided by RTM
  * `secret`: secret key, provided by RTM
  * `endpoint`: server gate endpoint



#### RTMServerClient configuration function list

```
void setQuestTimeout(int seconds);
void setAutoReconnect(bool autoReconnect);
void setServerPushMonitor(shared_ptr<RTMServerPushMonitor> serverMonitor);
void setRegressiveConnectStrategy(RegressiveStrategy strategy);
bool enableEncryptorByDerData(const string &derData, bool packageMode = true, bool reinforce = false);
bool enableEncryptorByPemData(const string &PemData, bool packageMode = true, bool reinforce = false);
bool enableEncryptorByDerFile(const char *derFilePath, bool packageMode = true, bool reinforce = false);
bool enableEncryptorByPemFile(const char *pemFilePath, bool packageMode = true, bool reinforce = false);
void enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode = true, bool reinforce = false);
```



* setQuestTimeout

  ```
  public void setQuestTimeout(int seconds)
  ```

  Set the global timeout time, if don't specify in sendQuest function， will use this as the default timeout time.



- setServerPushMonitor

  ```
  void setServerPushMonitor(shared_ptr<RTMServerPushMonitor> serverMonitor);
  ```

  Set Server Push Monitor. please refer [Server Push Monitor](doc/ServerPushMonitor.md)

  

- setAutoReconnect

  ```
  void setAutoReconnect(bool autoReconnect);
  ```

  Auto Reconnection , default on.

  

- setRegressiveConnectStrategy

  ```
  void setRegressiveConnectStrategy(RegressiveStrategy strategy);
  ```

  Set the gegressive connect strategy when auto reconnection.

  

- enableEncryptor*

  ```
  bool enableEncryptorByDerData(const string &derData, bool packageMode = true, bool reinforce = false);
  bool enableEncryptorByPemData(const string &PemData, bool packageMode = true, bool reinforce = false);
  bool enableEncryptorByDerFile(const char *derFilePath, bool packageMode = true, bool reinforce = false);
  bool enableEncryptorByPemFile(const char *pemFilePath, bool packageMode = true, bool reinforce = false);
  void enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode = true, bool reinforce = false);
  ```

  Encrypte the connection，please refer : [FPNN Client Advanced Tutorial](https://github.com/highras/fpnn/blob/master/doc/zh-cn/fpnn-client-advanced-tutorial.md#-%E5%8A%A0%E5%AF%86%E9%93%BE%E6%8E%A5)



### SDK Version

	RTMServerConfig::SDK_VERSION  // current sdk version
	RTMServerConfig::INTERFACE_VERSION   // rtm server api version



### API and Structures Docs



#### RTM Error Code

Please refer [RTM Error Code](src/RTMErrorCode.h)




#### Structures

Please refer [RTM Structures](doc/Structures.md)



#### Listening & Server Push Monitor

Please refer [Server Push Monitor](doc/ServerPushMonitor.md)



#### Token Functions

Please refer [Token Functions](doc/Token.md)



#### Chat Functions

Please refer [Chat Functions](doc/Chat.md)



#### Messages Functions

Please refer [Messages Functions](doc/Messages.md)



#### Files Functions

Please refer [Files Functions](doc/Files.md)



#### Friends Functions

Please refer [Friends Functions](doc/Friends.md)



#### Groups Functions

Please refer [Groups Functions](doc/Groups.md)



#### Rooms Functions

Please refer [Rooms Functions](doc/Rooms.md)



#### Users Functions

Please refer [Users Functions](doc/Users.md)



#### Data Functions

Please refer [Data Functions](doc/Data.md)



#### ValueAdded Functions

Please refer [ValueAdded Functions](doc/ValueAdded.md)



#### Device Functions

Please refer [Device Functions](doc/Device.md)



#### RealTimeVoice Functions

Please refer [RealTimeVoice Functions](doc/RTC.md)