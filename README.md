# RTM Server C++ SDK

### 安装

* 本SDK依赖 [FPNN C++ SDK](https://github.com/highras/fpnn-sdk-cpp)
* 头文件默认搜索路径为 **../fpnn-sdk-cpp/release/include** 
* 如在其他位置可自行修改Makefile中 **FPNN_RELEASE_INCLUDE_PATH**

1. 编译

		cd <rtm-C++-SDK-folder>
		make

1. release

		sh release.sh
    
### 开发
```
  #include "rtm.h"
  using namespace rtm;
  
  // 定义服务端监听类
  class MyMonitor: public RTMServerMonitor
  {
      // 链接建立事件
      virtual void connected(const ConnectionInfo& connInfo);
    
      // 链接关闭事件
      virtual void connectionWillClose(const ConnectionInfo& connInfo, bool closeByError);
    
      // P2P消息监听事件
      virtual void pushP2PMessage(int64_t from, int64_t to, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime);
    
      // Group消息监听事件
      virtual void pushGroupMessage(int64_t from, int64_t gid, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime);
    
      // Room消息监听事件
      virtual void pushRoomMessage(int64_t from, int64_t rid, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime);
    
      // 主动推送事件 (目前仅支持2个event: login和logout)
      virtual void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data);
  };
  
  RTMServerClientPtr client(new RTMServerClient(11000001, "xxx-xxx-xxx-xxx-xxx", "52.83.245.22:13315", true, 5000));
  
  // 设置服务端监听
  client->setServerMonitor(make_shared<MyMonitor>());
  
  // 添加监听类型  
  QuestResult result = client->addListen({}, {}, true, {"login"});
  if (addListenResult.isError()) {
      cout << result.errorCode << " " << result.errorInfo << endl;
  } else {
      cout << "ok" << endl;
  }
  
  // 发送P2P消息（同步）
  SendMessageResult result = client->sendMessage(1, 123, 51, "test", "");
  if (result.isError()) {
      cout << result.errorCode << " " << result.errorInfo << endl;
  } else {
      cout << result.mid << endl;
      cout << result.mtime << endl;
  }
  
  // 发送P2P消息（异步）
  client->sendMessage(1, 123, 51, "test", "", [](SendMessageResult result) {
      if (result.isError()) {
          cout << result.errorCode << " " << result.errorInfo << endl;
      } else {
          cout << result.mid << endl;
          cout << result.mtime << endl;
      }
  });
  ```

### API

#### RTMServerClient构造函数
* `RTMServerClient(int32_t pid, const string& secret, const string& endpoint, bool reconnect, int32_t timeout, int32_t duplicateCacheSize = 100000)` 
    * `pid`: 应用编号, RTM提供
    * `secret`: 应用密钥, RTM提供
    * `endpoint`: 服务端网关地址
    * `reconnect`: 是否重连
    * `timeout`: 请求超时时间(s)
    * `duplicateCacheSize`: mid去重LRUMAP大小
   
#### 设置全局请求超时时间  
* `void setQuestTimeout(int seconds)`  

#### 设置是否自动重连
* `void setAutoReconnect(bool autoReconnect)` 

#### 设置服务端监听
* `void setServerMonitor(shared_ptr<RTMServerMonitor> serverMonitor)` 

#### 配置链接加密 请参考 [FPNN Client Advanced Tutorial](https://github.com/highras/fpnn/blob/master/doc/zh-cn/fpnn-client-advanced-tutorial.md#-%E5%8A%A0%E5%AF%86%E9%93%BE%E6%8E%A5)
* `bool enableEncryptorByDerData(const string &derData, bool packageMode = true, bool reinforce = false)`
* `bool enableEncryptorByPemData(const string &PemData, bool packageMode = true, bool reinforce = false)`
* `bool enableEncryptorByDerFile(const char *derFilePath, bool packageMode = true, bool reinforce = false)`
* `bool enableEncryptorByPemFile(const char *pemFilePath, bool packageMode = true, bool reinforce = false)`
* `void enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode = true, bool reinforce = false)`

#### 发送P2P消息(同步)
* `SendMessageResult sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0)`
    * `from`: 发送方 id
    * `to`: 接收方uid
    * `mtype`: 消息类型
    * `message`: 消息内容
    * `attrs`: 消息附加信息, 没有可传`""`
    * `mid`: 消息id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendMessageResult`: 返回值
		* `result.isError()`: 是否为错误
		* `result.errorCode`: 错误码，当为错误时有效
		* `result.errorInfo`: 错误描述，当为错误时有效
		* `result.mid`: 消息id，当为正常时有效
		* `result.mtime`: 毫秒时间戳，当为正常时有效
    
#### 发送P2P消息(异步)
* `void sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0)`
    
    
    
    
