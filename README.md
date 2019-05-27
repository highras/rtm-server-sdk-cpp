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
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效
    
#### 发送P2P消息(异步)
* `void sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0)`

#### 发送多人P2P消息(同步)
* `SendMessageResult sendMessages(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0)`
    * `tos`: 接收方uid列表

#### 发送多人P2P消息(异步)
* `void sendMessages(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0)`
    * `tos`: 接收方uid列表

#### 发送组消息(同步)
* `SendMessageResult sendGroupMessage(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0)`
    * `gid`: 组id

#### 发送组消息(异步)
* `void sendGroupMessage(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0)`
    * `gid`: 组id
    
#### 发送房间消息(同步)
* `SendMessageResult sendRoomMessage(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0)`
    * `rid`: 房间id
    
#### 发送房间消息(异步)
* `void sendRoomMessage(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0)`
    * `rid`: 房间id
    
#### 发送广播消息(同步)
* `SendMessageResult broadcastMessage(int64_t from, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0)`
    
#### 发送广播消息(异步)
* `void broadcastMessage(int64_t from, int8_t mtype, const string& message, const string& attrs, std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0)`
    
#### 添加好友，每次最多添加100人(同步)
* `QuestResult addFriends(int64_t uid, const set<int64_t>& friends, int32_t timeout = 0)`
    * `uid`: 用户id
    * `friends`: 多个好友id
    * `timeout`: 超时时间(s)
    * `QuestResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
    
#### 添加好友，每次最多添加100人(异步)
* `void addFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `friends`: 多个好友id
    * `timeout`: 超时时间(s)
    * `QuestResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
    
#### 删除好友，每次最多100人(同步)
* `QuestResult deleteFriends(int64_t uid, const set<int64_t>& friends, int32_t timeout = 0)`
    * `uid`: 用户id
    * `friends`: 多个好友id
    * `timeout`: 超时时间(s)
    * `QuestResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
    
#### 删除好友，每次最多100人(异步)
* `void deleteFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `friends`: 多个好友id
    * `timeout`: 超时时间(s)
    * `QuestResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		
#### 获取好友(同步)
* `GetFriendsResult getFriends(int64_t uid, int32_t timeout = 0)`
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetFriendsResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.uids`: **(set<int64>)** 好友列表
    
#### 获取好友(异步)
* `void deleteFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `friends`: 多个好友id
    * `timeout`: 超时时间(s)
    * `QuestResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		
#### 判断好友关系(同步)
* `IsFriendResult isFriend(int64_t uid, int64_t fuid, int32_t timeout = 0)`
    * `uid`: 用户id
    * `fuid`: 对方用户id
    * `timeout`: 超时时间(s)
    * `IsFriendResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否为好友关系
    
#### 判断好友关系(异步)
* `void isFriend(int64_t uid, int64_t fuid, std::function<void (IsFriendResult result)> callback, int32_t timeout = 0)`   
* `uid`: 用户id
    * `fuid`: 对方用户id
    * `timeout`: 超时时间(s)
    * `IsFriendResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否为好友关系
		
#### 过滤好友关系, 每次最多过滤100人(同步)
* `IsFriendsResult isFriends(int64_t uid, const set<int64_t>& fuids, int32_t timeout = 0)`
    * `uid`: 用户id
    * `fuids`: 对方用户id列表
    * `timeout`: 超时时间(s)
    * `IsFriendsResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.fuids`: **(set<int64_t>)** 好友列表
    
#### 过滤好友关系, 每次最多过滤100人(异步)
* `void isFriends(int64_t uid, const set<int64_t>& fuids, std::function<void (IsFriendsResult result)> callback, int32_t timeout = 0)`   
* `uid`: 用户id
    * `uid`: 用户id
    * `fuids`: 对方用户id列表
    * `timeout`: 超时时间(s)
    * `IsFriendsResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.fuids`: **(set<int64_t>)** 好友列表
		
#### 添加group成员, 每次最多添加100人(同步)
* `QuestResult addGroupMembers(int64_t gid, const set<int64_t>& uids, int32_t timeout = 0)`
    * `gid`: 组id
    * `uids`: 成员用户id列表
    * `timeout`: 超时时间(s)
    
#### 添加group成员, 每次最多添加100人(异步)
* `void addGroupMembers(int64_t gid, const set<int64_t>& uids, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `uids`: 成员用户id列表
    * `timeout`: 超时时间(s)
    
#### 删除group成员, 每次最多删除100人(同步)
* `QuestResult deleteGroupMembers(int64_t gid, const set<int64_t>& uids, int32_t timeout = 0)`
    * `gid`: 组id
    * `uids`: 成员用户id列表
    * `timeout`: 超时时间(s)
    
#### 删除group成员, 每次最多删除100人(异步)
* `void deleteGroupMembers(int64_t gid, const set<int64_t>& uids, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `uids`: 成员用户id列表
    * `timeout`: 超时时间(s)
    
#### 删除group成员, 每次最多删除100人(同步)
* `QuestResult deleteGroup(int64_t gid, int32_t timeout = 0)`
    * `gid`: 组id
    * `timeout`: 超时时间(s)
    
#### 删除group成员, 每次最多删除100人(异步)
* `void deleteGroup(int64_t gid, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `timeout`: 超时时间(s)
    
#### 获取group成员(同步)
* `GetGroupMembersResult getGroupMembers(int64_t gid, int32_t timeout = 0)`
    * `gid`: 组id
    * `timeout`: 超时时间(s)
    * `GetGroupMembersResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.uids`: **(set<int64_t>)** group成员列表
    
#### 获取group成员(异步)
* `void getGroupMembers(int64_t uid, std::function<void (GetGroupMembersResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `timeout`: 超时时间(s)
    * `GetGroupMembersResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.uids`: **(set<int64_t>)** group成员列表
		
		
		
		
		
