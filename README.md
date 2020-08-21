# RTM Server C++ SDK

[TOC]

### 安装

* 本SDK依赖 [FPNN C++ SDK](https://github.com/highras/fpnn-sdk-cpp)
* 头文件默认搜索路径为 **../fpnn-sdk-cpp/release/include** 
* 如在其他位置可自行修改Makefile中 **FPNN_RELEASE_INCLUDE_PATH**

1. 编译

		cd <rtm-C++-SDK-folder>
		make

2. release

		sh release.sh
    
    
### 注意

* 使用之前请确保服务器时间校准，否则可能导致签名失败



### 开始使用

```
#include "rtm.h"
using namespace rtm;

// 可选，设置全局配置信息
RTMServerConfig config;
RTMServerConfigCenter::init(config);

// 创建RTMServerClient
RTMServerClientPtr client(new RTMServerClient(11000001, "xxx-xxx-xxx-xxx-xxx", "161.189.171.91:13315"));
```



#### RTMServerClient构造函数

* RTMServerClient(int32_t pid, const string& secret, const string& endpoint)
  * `pid`: 应用编号, RTM提供
  * `secret`: 应用密钥, RTM提供
  * `endpoint`: 服务端网关地址



#### RTMServerClient配置方法列表

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

  设置全局请求超时时间，如果在sendQuest中没有指定超时时间，将使用该值作为请求的默认超时时间。



- setServerPushMonitor

  ```
  void setServerPushMonitor(shared_ptr<RTMServerPushMonitor> serverMonitor);
  ```

  设置处理服务端转发时间的Monitor. 请参考 [Server Push Monitor](doc/ServerPushMonitor.md)

  

- setAutoReconnect

  ```
  void setAutoReconnect(bool autoReconnect);
  ```

  是否开启自动重连，默认开启。

  

- setRegressiveConnectStrategy

  ```
  void setRegressiveConnectStrategy(RegressiveStrategy strategy);
  ```

  设置当发生自动重连时，进行退行性重连的策略。

  

- enableEncryptor*

  ```
  bool enableEncryptorByDerData(const string &derData, bool packageMode = true, bool reinforce = false);
  bool enableEncryptorByPemData(const string &PemData, bool packageMode = true, bool reinforce = false);
  bool enableEncryptorByDerFile(const char *derFilePath, bool packageMode = true, bool reinforce = false);
  bool enableEncryptorByPemFile(const char *pemFilePath, bool packageMode = true, bool reinforce = false);
  void enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode = true, bool reinforce = false);
  ```

  开启加密连接，请参考：[FPNN Client Advanced Tutorial](https://github.com/highras/fpnn/blob/master/doc/zh-cn/fpnn-client-advanced-tutorial.md#-%E5%8A%A0%E5%AF%86%E9%93%BE%E6%8E%A5)



### 打印SDK 版本信息

	RTMServerConfig::SDK_VERSION  // 当前SDK版本号
	RTMServerConfig::INTERFACE_VERSION   // 当前RTM服务端接口版本号



### 接口和基本数据结构文档



#### RTM错误码汇总

请参考 [RTM Error Code](src/RTMErrorCode.h)




#### 基本数据结构

请参考 [RTM Structures](doc/Structures.md)



#### 添加事件监听 & 处理服务端推送事件

请参考 [Server Push Monitor](doc/ServerPushMonitor.md)



#### 登录Token相关

请参考 [Token Functions](doc/Token.md)



#### 聊天相关

请参考 [Chat Functions](doc/Chat.md)



#### 消息相关

请参考 [Messages Functions](doc/Messages.md)



#### 文件相关

请参考 [Files Functions](doc/Files.md)



#### 好友相关

请参考 [Friends Functions](doc/Friends.md)



#### 群组相关

请参考 [Groups Functions](doc/Groups.md)



#### 房间相关

请参考 [Rooms Functions](doc/Rooms.md)



#### 用户相关

请参考 [Users Functions](doc/Users.md)



#### 数据相关

请参考 [Data Functions](doc/Data.md)



#### 增值服务相关

请参考 [ValueAdded Functions](doc/ValueAdded.md)

