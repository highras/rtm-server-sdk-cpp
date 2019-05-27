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
		
#### 是否group成员(同步)
* `IsGroupMemberResult isGroupMember(int64_t gid, int64_t uid, int32_t timeout = 0)`
    * `gid`: 组id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetGroupMembersResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否group成员
    
#### 是否group成员(异步)
* `void isGroupMember(int64_t gid, int64_t uid, std::function<void (IsGroupMemberResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetGroupMembersResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否group成员
		
#### 获取用户的group(同步)
* `GetUserGroupsResult getUserGroups(int64_t uid, int32_t timeout = 0)`
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetUserGroupsResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.gids`: **(set<int64_t>)** group列表
    
#### 获取用户的group(异步)
* `void getUserGroups(int64_t uid, std::function<void (GetUserGroupsResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetUserGroupsResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.gids`: **(set<int64_t>)** group列表	
		
#### 获取auth token(同步)
* `GetTokenResult getToken(int64_t uid, int32_t timeout = 0)`
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetTokenResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.token`: **(set<string>)** token
    
#### 获取auth token(异步)
* `void getToken(int64_t uid, std::function<void (GetTokenResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `GetTokenResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.token`: **(set<string>)** token
	
#### 获取在线用户, 每次最多获取200个(同步)
* `GetOnlineUsersResult getOnlineUsers(const set<int64_t>& uids, int32_t timeout = 0)`
    * `uids`: 用户id列表
    * `timeout`: 超时时间(s)
    * `GetOnlineUsersResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.uids`: **(set<int64_t>)** 在线用户列表

#### 获取在线用户, 每次最多获取200个(异步)
* `void getOnlineUsers(const set<int64_t>& uids, std::function<void (GetOnlineUsersResult result)> callback, int32_t timeout = 0)`   
    * `uids`: 用户id列表
    * `timeout`: 超时时间(s)
    * `GetOnlineUsersResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.uids`: **(set<int64_t>)** 在线用户列表
		
#### 阻止用户组消息(同步)
* `QuestResult addGroupBan(int64_t gid, int64_t uid, int32_t btime, int32_t timeout = 0)`
    * `gid`: 组id
    * `uid`: 用户id
    * `btime`: 阻止时间
    * `timeout`: 超时时间(s)

#### 阻止用户组消息(异步)
* `void addGroupBan(int64_t gid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `uid`: 用户id
    * `btime`: 阻止时间
    * `timeout`: 超时时间(s)
    
#### 取消阻止用户组消息(同步)
* `QuestResult removeGroupBan(int64_t gid, int64_t uid, int32_t timeout = 0)`
    * `gid`: 组id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)

#### 取消阻止用户组消息(异步)
* `void removeGroupBan(int64_t gid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    
#### 阻止用户房间消息(同步)
* `QuestResult addRoomBan(int64_t rid, int64_t uid, int32_t btime, int32_t timeout = 0)`
    * `rid`: 房间id
    * `uid`: 用户id
    * `btime`: 阻止时间
    * `timeout`: 超时时间(s)

#### 阻止用户房间消息(异步)
* `void addRoomBan(int64_t rid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `rid`: 房间id
    * `uid`: 用户id
    * `btime`: 阻止时间
    * `timeout`: 超时时间(s)
    
#### 取消阻止用户房间消息(同步)
* `QuestResult removeRoomBan(int64_t rid, int64_t uid, int32_t timeout = 0)`
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)

#### 取消阻止用户房间消息(异步)
* `void removeRoomBan(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    
#### 阻止用户消息(project)(同步)
* `QuestResult addProjectBlack(int64_t uid, int32_t btime, int32_t timeout = 0)`
    * `rid`: 房间id
    * `btime`: 阻止时间
    * `timeout`: 超时时间(s)

#### 阻止用户消息(project)(异步)
* `void addRoomBan(int64_t rid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `rid`: 房间id
    * `btime`: 阻止时间
    * `timeout`: 超时时间(s)
    
#### 取消阻止用户消息(project)(同步)
* `QuestResult removeProjectBlack(int64_t uid, int32_t timeout = 0)`
    * `rid`: 房间id
    * `timeout`: 超时时间(s)

#### 取消阻止用户消息(project)(异步)
* `void removeProjectBlack(int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `rid`: 房间id
    * `timeout`: 超时时间(s)
    
#### 检查阻止(group)(同步)
* `IsBanOfGroupResult isBanOfGroup(int64_t gid, int64_t uid, int32_t timeout = 0)`
    * `gid`: 组id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsBanOfGroupResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止

#### 检查阻止(group)(异步)
* `void isBanOfGroup(int64_t gid, int64_t uid, std::function<void (IsBanOfGroupResult result)> callback, int32_t timeout = 0)`   
    * `gid`: 组id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsBanOfGroupResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止
    
#### 检查阻止(room)(同步)
* `IsBanOfRoomResult isBanOfRoom(int64_t rid, int64_t uid, int32_t timeout = 0)`
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsBanOfRoomResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止

#### 检查阻止(room)(异步)
* `void isBanOfRoom(int64_t rid, int64_t uid, std::function<void (IsBanOfRoomResult result)> callback, int32_t timeout = 0)`   
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsBanOfRoomResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止
		
#### 检查阻止(project)(同步)
* `IsProjectBlackResult isProjectBlack(int64_t uid, int32_t timeout = 0)`
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsProjectBlackResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止

#### 检查阻止(project)(异步)
* `void isProjectBlack(int64_t uid, std::function<void (IsProjectBlackResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsProjectBlackResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止
		
#### 检查阻止(project)(同步)
* `IsProjectBlackResult isProjectBlack(int64_t uid, int32_t timeout = 0)`
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsProjectBlackResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止

#### 检查阻止(project)(异步)
* `void isProjectBlack(int64_t uid, std::function<void (IsProjectBlackResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    * `IsProjectBlackResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.ok`: **(bool)** 是否阻止
		
#### 获取发送文件的token(同步)
* `FileTokenResult fileToken(int64_t from, const string& cmd, const FileTokenInfo& info, int32_t timeout = 0)`
    * `from`:  发送方 id
    * `cmd`: 文件发送方式`sendfile | sendfiles | sendroomfile | sendgroupfile | broadcastfile`
    * `tos`: 接收方 uids
    * `to`: 接收方 uid
    * `rid`:  Room id
    * `gid`:  Group id
    * `timeout`: 超时时间(s)
    * `FileTokenResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.token`: **(string)** 发送token
		* `result.endpoint`: **(string)** 发送服务器地址

#### 获取发送文件的token(异步)
* `void fileToken(int64_t from, const string& cmd, const FileTokenInfo& info, std::function<void (FileTokenResult result)> callback, int32_t timeout = 0)`   
    * `from`:  发送方 id
    * `cmd`: 文件发送方式`sendfile | sendfiles | sendroomfile | sendgroupfile | broadcastfile`
    * `tos`: 接收方 uids
    * `to`: 接收方 uid
    * `rid`:  Room id
    * `gid`:  Group id
    * `timeout`: 超时时间(s)
    * `FileTokenResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.token`: **(string)** 发送token
		* `result.endpoint`: **(string)** 发送服务器地址

#### 获取Group历史消息(同步)
* `GetGroupMessageResult getGroupMessage(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0)`
    * `gid`: Group id
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetGroupMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of GroupMessage)** 
			* GroupMessage.id: **(int64_t)** 
			* GroupMessage.from: **(int64_t)** 
			* GroupMessage.mtype: **(int8_t)** 
			* GroupMessage.mid: **(int64_t)** 
			* GroupMessage.deleted: **(bool)** 
			* GroupMessage.msg: **(string)** 
			* GroupMessage.attrs: **(string)** 
			* GroupMessage.mtime: **(int64_t)** 

#### 获取Group历史消息(异步)
* `void getGroupMessage(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetGroupMessageResult result)> callback, int32_t timeout = 0)`   
    * `gid`: Group id
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetGroupMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of GroupMessage)** 
			* GroupMessage.id: **(int64_t)** 
			* GroupMessage.from: **(int64_t)** 
			* GroupMessage.mtype: **(int8_t)** 
			* GroupMessage.mid: **(int64_t)** 
			* GroupMessage.deleted: **(bool)** 
			* GroupMessage.msg: **(string)** 
			* GroupMessage.attrs: **(string)** 
			* GroupMessage.mtime: **(int64_t)** 

#### 获取Room历史消息(同步)
* `GetRoomMessageResult getRoomMessage(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0)`
    * `rid`: Room id
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetRoomMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of RoomMessage)** 
			* RoomMessage.id: **(int64_t)** 
			* RoomMessage.from: **(int64_t)** 
			* RoomMessage.mtype: **(int8_t)** 
			* RoomMessage.mid: **(int64_t)** 
			* RoomMessage.deleted: **(bool)** 
			* RoomMessage.msg: **(string)** 
			* RoomMessage.attrs: **(string)** 
			* RoomMessage.mtime: **(int64_t)** 

#### 获取Room历史消息(异步)
* `void getRoomMessage(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetRoomMessageResult result)> callback, int32_t timeout = 0)`   
    * `rid`: Room id
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetRoomMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of RoomMessage)** 
			* RoomMessage.id: **(int64_t)** 
			* RoomMessage.from: **(int64_t)** 
			* RoomMessage.mtype: **(int8_t)** 
			* RoomMessage.mid: **(int64_t)** 
			* RoomMessage.deleted: **(bool)** 
			* RoomMessage.msg: **(string)** 
			* RoomMessage.attrs: **(string)** 
			* RoomMessage.mtime: **(int64_t)** 
			
#### 获取Broadcast历史消息(同步)
* `GetBroadcastMessageResult getBroadcastMessage(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0)`
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetBroadcastMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of BroadcastMessage)** 
			* BroadcastMessage.id: **(int64_t)** 
			* BroadcastMessage.from: **(int64_t)** 
			* BroadcastMessage.mtype: **(int8_t)** 
			* BroadcastMessage.mid: **(int64_t)** 
			* BroadcastMessage.deleted: **(bool)** 
			* BroadcastMessage.msg: **(string)** 
			* BroadcastMessage.attrs: **(string)** 
			* BroadcastMessage.mtime: **(int64_t)** 

#### 获取Broadcast历史消息(异步)
* `void getBroadcastMessage(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetBroadcastMessageResult result)> callback, int32_t timeout = 0)`   
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetBroadcastMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of BroadcastMessage)** 
			* BroadcastMessage.id: **(int64_t)** 
			* BroadcastMessage.from: **(int64_t)** 
			* BroadcastMessage.mtype: **(int8_t)** 
			* BroadcastMessage.mid: **(int64_t)** 
			* BroadcastMessage.deleted: **(bool)** 
			* BroadcastMessage.msg: **(string)** 
			* BroadcastMessage.attrs: **(string)** 
			* BroadcastMessage.mtime: **(int64_t)** 
			
#### 获取P2P历史消息(同步)
* `GetP2PMessageResult getP2PMessage(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0)`
    * `uid`: 用户id
    * `ouid`: 对方用户id
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetP2PMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of P2PMessage)** 
			* P2PMessage.id: **(int64_t)** 
			* P2PMessage.direction: **(int8_t)** 
			* P2PMessage.mtype: **(int8_t)** 
			* P2PMessage.mid: **(int64_t)** 
			* P2PMessage.deleted: **(bool)** 
			* P2PMessage.msg: **(string)** 
			* P2PMessage.attrs: **(string)** 
			* P2PMessage.mtime: **(int64_t)** 

#### 获取P2P历史消息(异步)
* `void getP2PMessage(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetP2PMessageResult result)> callback, int32_t timeout = 0)`   
    * `uid`: 用户id
    * `ouid`: 对方用户id
    * `desc`: `true`: 则从`end`的时间戳开始倒序翻页, `false`: 则从`begin`的时间戳顺序翻页
    * `num`: 一次最多获取20条, 建议10条**
    * `begin`: 开始时间戳, 毫秒, 默认`0`, 条件：`>=`
    * `end`:  结束时间戳, 毫秒, 默认`0`, 条件：`<=`
    * `lastId`:  最后一条消息的id, 第一次默认传`0`, 条件：`> or <`
    * `timeout`: 超时时间(s)
    * `GetP2PMessageResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.num`: **(int16_t)** 总数
		* `result.lastId`: **(int64_t)** lastId
		* `result.begin`: **(int64_t)** 
		* `result.end`: **(int64_t)** 
		* `result.msgs`: **(vector of P2PMessage)** 
			* P2PMessage.id: **(int64_t)** 
			* P2PMessage.direction: **(int8_t)** 
			* P2PMessage.mtype: **(int8_t)** 
			* P2PMessage.mid: **(int64_t)** 
			* P2PMessage.deleted: **(bool)** 
			* P2PMessage.msg: **(string)** 
			* P2PMessage.attrs: **(string)** 
			* P2PMessage.mtime: **(int64_t)** 
			
#### 添加Room成员(同步)
* `QuestResult addRoomMember(int64_t rid, int64_t uid, int32_t timeout = 0)`
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)

#### 添加Room成员(异步)
* `void addRoomMember(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0)`   
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    
#### 删除Room成员(同步)
* `QuestResult deleteRoomMember(int64_t rid, int64_t uid, int32_t timeout = 0)`
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)

#### 删除Room成员(异步)
* `void deleteRoomMember(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `rid`: 房间id
    * `uid`: 用户id
    * `timeout`: 超时时间(s)
    
####  添加事件/消息监听(同步)
* `QuestResult addListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, int32_t timeout = 0)`
    * `gids`: 多个Group id
    * `rids`:  多个Room id
    * `p2p`:  P2P消息
    * `events`: 多个事件名称, 请参考 `RTMConfig.SERVER_EVENT` 成员
    * `timeout`: 超时时间(s)

#### 添加事件/消息监听(异步)
* `void addListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `gids`: 多个Group id
    * `rids`:  多个Room id
    * `p2p`:  P2P消息
    * `events`: 多个事件名称, 请参考 `RTMConfig.SERVER_EVENT` 成员
    * `timeout`: 超时时间(s)
    
####  删除事件/消息监听(同步)
* `QuestResult removeListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, int32_t timeout = 0)`
    * `gids`: 多个Group id
    * `rids`:  多个Room id
    * `p2p`:  P2P消息
    * `events`: 多个事件名称, 请参考 `RTMConfig.SERVER_EVENT` 成员
    * `timeout`: 超时时间(s)

#### 删除事件/消息监听(异步)
* `void removeListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `gids`: 多个Group id
    * `rids`:  多个Room id
    * `p2p`:  P2P消息
    * `events`: 多个事件名称, 请参考 `RTMConfig.SERVER_EVENT` 成员
    * `timeout`: 超时时间(s)
    
#### 更新事件/消息监听(同步)
* `QuestResult setListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all, int32_t timeout = 0)`
    * `gids`: 多个Group id
    * `rids`:  多个Room id
    * `p2p`:  P2P消息
    * `events`: 多个事件名称, 请参考 `RTMConfig.SERVER_EVENT` 成员
    * `all`: `true`: 监听所有 `事件` / `消息`, `false`: 取消所有 `事件` / `消息` 监听
    * `timeout`: 超时时间(s)

#### 更新事件/消息监听(异步)
* `void setListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `gids`: 多个Group id
    * `rids`:  多个Room id
    * `p2p`:  P2P消息
    * `events`: 多个事件名称, 请参考 `RTMConfig.SERVER_EVENT` 成员
    * `all`: `true`: 监听所有 `事件` / `消息`, `false`: 取消所有 `事件` / `消息` 监听
    * `timeout`: 超时时间(s)
    
#### 添加设备, 应用信息(同步)
* `QuestResult addDevice(int64_t uid, const string& appType, const string& deviceToken, int32_t timeout = 0)`
    * `uid`: 用户id
    * `appType`: 应用信息
    * `deviceToken`:  设备token
    * `timeout`: 超时时间(s)

#### 添加设备, 应用信息(异步)
* `void addDevice(int64_t uid, const string& appType, const string& deviceToken, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `uid`: 用户id
    * `appType`: 应用信息
    * `deviceToken`:  设备token
    * `timeout`: 超时时间(s)
    
#### 移除设备(同步)
* `QuestResult removeDevice(int64_t uid, const string& deviceToken, int32_t timeout = 0)`
    * `uid`: 用户id
    * `deviceToken`:  设备token
    * `timeout`: 超时时间(s)

#### 移除设备(异步)
* `void removeDevice(int64_t uid, const string& deviceToken, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `uid`: 用户id
    * `deviceToken`:  设备token
    * `timeout`: 超时时间(s)
    
#### 删除消息(同步)
* `QuestResult deleteMessage(int64_t mid, int64_t from, int64_t xid, int8_t type, int32_t timeout = 0)`
    * `mid`: 消息id
    * `from`: 发送方id
    * `xid`: 接收放id, `rid/gid/to`
    * `type`: 消息发送分类 `1:P2P, 2:Group, 3:Room, 4:Broadcast`
    * `timeout`: 超时时间(s)

#### 删除消息(异步)
* `void deleteMessage(int64_t mid, int64_t from, int64_t xid, int8_t type, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `mid`: 消息id
    * `from`: 发送方id
    * `xid`: 接收放id, `rid/gid/to`
    * `type`: 消息发送分类 `1:P2P, 2:Group, 3:Room, 4:Broadcast`
    * `timeout`: 超时时间(s)
    
#### 踢掉一个用户或者一个链接(同步)
* `QuestResult kickout(int64_t uid, const string& ce, int32_t timeout = 0)`
    * `uid`: 用户 id
    * `ce`: 踢掉`ce`对应链接, 多用户登录情况
    * `timeout`: 超时时间(s)

#### 踢掉一个用户或者一个链接(异步)
* `void kickout(int64_t uid, const string& ce, std::function<void (QuestResult result)> callback, int32_t timeout = 0)` 
    * `uid`: 用户 id
    * `ce`: 踢掉`ce`对应链接, 多用户登录情况
    * `timeout`: 超时时间(s)
    
#### 读取文件到string
* `bool loadFile(const string& filePath, string& fileData)`
    * `filePath`: 文件path

#### 发送文件(同步)
* `SendFileResult sendFile(int64_t from, int64_t to, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0)`
    * `from`: 发送方 id
    * `to`: 接收方 uid
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

#### 发送文件(异步)
* `void sendFile(int64_t from, int64_t to, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0)` 
    * `from`: 发送方 id
    * `to`: 接收方 uid
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

#### 给多人发送文件(同步)
* `SendFileResult sendFiles(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0)`
    * `from`: 发送方 id
    * `tos`: 接收方uid list
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

#### 给多人发送文件(异步)
* `void sendFiles(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0)` 
    * `from`: 发送方 id
    * `tos`: 接收方uid list
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效
		
#### 给Group发送文件(同步)
* `SendFileResult sendGroupFile(int64_t from, int64_t gid, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0)`
    * `from`: 发送方 id
    * `gid`: 组id
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

#### 给Group发送文件(异步)
* `void sendGroupFile(int64_t from, int64_t gid, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0)` 
    * `from`: 发送方 id
    * `gid`: 组id
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效
		
#### 给Room发送文件(同步)
* `SendFileResult sendRoomFile(int64_t from, int64_t rid, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout = 0)`
    * `from`: 发送方 id
    * `rid`: 房间id
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

#### 给Room发送文件(异步)
* `void sendRoomFile(int64_t from, int64_t rid, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0)` 
    * `from`: 发送方 id
    * `rid`: 组id
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效
		
#### 广播文件(同步)
* `SendFileResult broadcastFile(int64_t from, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0)`
    * `from`: 发送方 id
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

#### 广播文件(异步)
* `void broadcastFile(int64_t from, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0)` 
    * `from`: 发送方 id
    * `mtype`: 文件类型
    * `fileData`: 文件内容
    * `mid`: 消息 id, 用于过滤重复消息, 非重发时为`0`
    * `timeout`: 超时时间(s)
    * `SendFileResult`: 返回值
		* `result.isError()`: **(bool)** 是否为错误
		* `result.errorCode`: **(int32_t)** 错误码，当为错误时有效
		* `result.errorInfo`: **(string)** 错误描述，当为错误时有效
		* `result.mid`: **(int64_t)** 消息id，当为正常时有效
		* `result.mtime`: **(int64_t)** 毫秒时间戳，当为正常时有效

