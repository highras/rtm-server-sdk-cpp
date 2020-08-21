# RTM Server C++ SDK API Docs: Server Push Monitor

# Index

[TOC]

## 实现自己的RTMServerPushMonitor类

    class MyMonitor: public RTMServerPushMonitor
    {
        // 链接建立事件
        virtual void connected(const string& endpoint, bool connected, bool isReconnect) {}
    
        // 链接关闭事件
        virtual void closed(const string& endpoint, bool causedByError, bool isReconnect) {}
    
        // P2P消息监听事件
        virtual void pushP2PMessage(RTMMessage message) {}
    
        // Group消息监听事件
        virtual void pushGroupMessage(RTMMessage message) {}
    
        // Room消息监听事件
        virtual void pushRoomMessage(RTMMessage message) {}
    
        // P2P文件监听事件
        virtual void pushP2PFile(RTMMessage message) {}
    
        // Group文件监听事件
        virtual void pushGroupFile(RTMMessage message) {}
    
        // Room文件监听事件
        virtual void pushRoomFile(RTMMessage message) {}
    
        // P2P聊天监听事件
        virtual void pushP2PChat(RTMMessage message) {}
    
        // P2P语音监听事件
        virtual void pushP2PAudio(RTMMessage message) {}
    
        // P2P聊天控制命令监听事件
        virtual void pushP2PCmd(RTMMessage message) {}
    
        // Group聊天监听事件
        virtual void pushGroupChat(RTMMessage message) {}
    
        // Group语音监听事件
        virtual void pushGroupAudio(RTMMessage message) {}
    
        // Group聊天控制命令监听事件
        virtual void pushGroupCmd(RTMMessage message) {}
    
        // Room聊天监听事件
        virtual void pushRoomChat(RTMMessage message) {}
    
        // Room语音监听事件
        virtual void pushRoomAudio(RTMMessage message) {}
    
        // Room聊天控制命令监听事件
        virtual void pushRoomCmd(RTMMessage message) {}
    
        // 主动推送事件 (目前仅支持2个event: login和logout)
        virtual void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data) {}
    
        // 服务端心跳检查
        virtual void ping() {}
    };



### Set Server Push Monitor

	client->setServerPushMonitor(make_shared<MyMonitor>());



### SetListen / AddListen api



#### AddListen

	//-- Sync Method
	int32_t addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
	
	//-- Async Method
	void addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加要监听哪些事件，增量添加，仅对当前连接有效

参数:

+ `groupIds` 

		要监听的群组id集合

+ `roomIds`

	要监听的房间id集合

+ `userIds`

   要监听的用户id集合

+ `events`

   要监听的事件集合，目前支持login、logout

+ `int timeout`

	超时时间(秒)，默认0(使用全局设置)



返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
* errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### RemoveListen

	//-- Sync Method
	int32_t removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
	
	//-- Async Method
	void removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

取消添加过的监听，增量取消，仅对当前连接有效

参数:

+ `groupIds` 

  要监听的群组id集合

+ `roomIds`

  要监听的房间id集合

+ `userIds`

  要监听的用户id集合

+ `events`

  要监听的事件集合，目前支持login、logout

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### SetListen

	//-- Sync Method
	int32_t setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
	int32_t setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, int32_t timeout = 0);
	       
	//-- Async Method
	void setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
	void setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

设置要监听哪些内容，全量覆盖，仅对当前连接有效

参数:

+ `groupIds` 

  要监听的群组id集合

+ `roomIds`

  要监听的房间id集合

+ `userIds`

  要监听的用户id集合

+ `events`

  要监听的事件集合，目前支持login、logout

+ `allGroup`

  监听全部group消息

+ `allRoom`

  监听全部room消息

+ `allP2P`

  监听全部p2p消息

+ `allEvent`

  监听全部事件

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况