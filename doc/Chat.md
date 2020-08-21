# RTM Server C++ SDK API Docs: Chat

[TOC]

### Chat api



#### SendChat

	//-- Sync Method
	int32_t sendChat(int32_t& modifyTime, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendChat(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送P2P聊天

参数:

+ `fromUid` 

  发送者用户id

+ `toUid` 

  接收者用户id

+ `message` 

  聊天内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### SendAudio

	//-- Sync Method
	int32_t sendAudio(int32_t& modifyTime, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendAudio(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送P2P语音消息

参数:

+ `fromUid` 

  发送者用户id

+ `toUid` 

  接收者用户id

+ `message` 

  语音内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳





#### SendCmd

	//-- Sync Method
	int32_t sendCmd(int32_t& modifyTime, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendCmd(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送P2P聊天控制命令

参数:

+ `fromUid` 

  发送者用户id

+ `toUid` 

  接收者用户id

+ `message` 

  内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### SendChats

	//-- Sync Method
	int32_t sendChats(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendChats(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送多人P2P聊天消息

参数:

+ `fromUid` 

  发送者用户id

+ `toUids` 

  接收者用户id集合

+ `message` 

  内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### SendAudios

	//-- Sync Method
	int32_t sendAudios(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendAudios(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送多人P2P语音聊天消息

参数:

+ `fromUid` 

  发送者用户id

+ `toUids` 

  接收者用户id集合

+ `message` 

  语音内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### SendCmds

	//-- Sync Method
	int32_t sendCmds(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendCmds(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送多人P2P聊天控制命令

参数:

+ `fromUid` 

  发送者用户id

+ `toUids` 

  接收者用户id集合

+ `message` 

  内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### sendGroupChat

	//-- Sync Method
	int32_t sendGroupChat(int32_t& modifyTime, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupChat(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送群组聊天

参数:

+ `fromUid` 

  发送者用户id

+ `groupId` 

  群组id

+ `message` 

  聊天内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### sendGroupAudio

	//-- Sync Method
	int32_t sendGroupAudio(int32_t& modifyTime, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupAudio(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送群组语音聊天

参数:

+ `fromUid` 

  发送者用户id

+ `groupId` 

  群组id

+ `message` 

  语音内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### sendGroupCmd

	//-- Sync Method
	int32_t sendGroupCmd(int32_t& modifyTime, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupCmd(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送群组语音控制命令

参数:

+ `fromUid` 

  发送者用户id

+ `groupId` 

  群组id

+ `message` 

  内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### sendRoomChat

	//-- Sync Method
	int32_t sendRoomChat(int32_t& modifyTime, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomChat(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送房间聊天

参数:

+ `fromUid` 

  发送者用户id

+ `roomId` 

  房间id

+ `message` 

  聊天内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### sendRoomAudio

	//-- Sync Method
	int32_t sendRoomAudio(int32_t& modifyTime, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomAudio(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送房间语音聊天

参数:

+ `fromUid` 

  发送者用户id

+ `roomId` 

  房间id

+ `message` 

  语音内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### sendRoomCmd

	//-- Sync Method
	int32_t sendRoomCmd(int32_t& modifyTime, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomCmd(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送房间聊天控制命令

参数:

+ `fromUid` 

  发送者用户id

+ `roomId` 

  房间id

+ `message` 

  内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### broadcastChat

	//-- Sync Method
	int32_t broadcastChat(int32_t& modifyTime, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastChat(int64_t fromUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送广播聊天

参数:

+ `fromUid` 

  发送者用户id

+ `message` 

  聊天内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### broadcastAudio

	//-- Sync Method
	int32_t broadcastAudio(int32_t& modifyTime, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastAudio(int64_t fromUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送广播语音消息

参数:

+ `fromUid` 

  发送者用户id

+ `message` 

  语音内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### broadcastCmd

	//-- Sync Method
	int32_t broadcastCmd(int32_t& modifyTime, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastCmd(int64_t fromUid, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送广播聊天控制命令

参数:

+ `fromUid` 

  发送者用户id

+ `message` 

  内容

+ `attrs` 

  附加信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### getGroupChat

	//-- Sync Method
	int32_t getGroupChat(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupChat(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取群组历史聊天

参数:

+ `groupId` 

  群组id

+ `desc` 

  true:  降序排列， false: 升序排列

+ `count` 

  获取消息的数量

+ `beginMsec` 

  开始的毫秒时间戳

+ `endMsec` 

  结束的毫秒时间戳

+ `lastId` 

  上次调用返回的最后一条消息的cursorId， 第一次获取传0

+ `uid` 

  调用者的用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数HistoryMessageResult,  服务器返回历史消息结果
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数HistoryMessageResult,  服务器返回历史消息结果



#### getRoomChat

	//-- Sync Method
	int32_t getRoomChat(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getRoomChat(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取房间历史聊天

参数:

+ `roomId` 

  房间id

+ `desc` 

  true:  降序排列， false: 升序排列

+ `count` 

  获取消息的数量

+ `beginMsec` 

  开始的毫秒时间戳

+ `endMsec` 

  结束的毫秒时间戳

+ `lastId` 

  上次调用返回的最后一条消息的cursorId， 第一次获取传0

+ `uid` 

  调用者的用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数HistoryMessageResult,  服务器返回历史消息结果
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数HistoryMessageResult,  服务器返回历史消息结果



#### getBroadcastChat

	//-- Sync Method
	int32_t getBroadcastChat(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getBroadcastChat(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取广播历史聊天

参数:

+ `desc` 

  true:  降序排列， false: 升序排列

+ `count` 

  获取消息的数量

+ `beginMsec` 

  开始的毫秒时间戳

+ `endMsec` 

  结束的毫秒时间戳

+ `lastId` 

  上次调用返回的最后一条消息的cursorId， 第一次获取传0

+ `uid` 

  调用者的用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数HistoryMessageResult,  服务器返回历史消息结果
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数HistoryMessageResult,  服务器返回历史消息结果



#### getP2PChat

	//-- Sync Method
	int32_t getP2PChat(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int32_t timeout = 0);
	
	//-- Async Method
	void getP2PChat(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取P2P历史聊天

参数:

+ `userId` 

  用户id

+ `otherUserId` 

  对方用户id

+ `desc` 

  true:  降序排列， false: 升序排列

+ `count` 

  获取消息的数量

+ `beginMsec` 

  开始的毫秒时间戳

+ `endMsec` 

  结束的毫秒时间戳

+ `lastId` 

  上次调用返回的最后一条消息的cursorId， 第一次获取传0

+ `uid` 

  调用者的用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数HistoryMessageResult,  服务器返回历史消息结果
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数HistoryMessageResult,  服务器返回历史消息结果



#### getChat

	//-- Sync Method
	int32_t getChat(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void getChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout = 0);

获取聊天

参数:

+ `mid` 

  消息id

+ `fromUid` 

  发送者用户id

+ `toId` 

  groupId或roomId或userId

+ `messageCategory` 

  消息类型 参考 [RTM Structures](Structures.md)

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数RetrievedMessage,  服务器返回历史消息结果
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数RetrievedMessage,  服务器返回历史消息结果



#### deleteChat

	//-- Sync Method
	int32_t deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除聊天

参数:

+ `mid` 

  消息id

+ `fromUid` 

  发送者用户id

+ `toId` 

  groupId或roomId或userId

+ `messageCategory` 

  消息类型 参考 [RTM Structures](Structures.md)

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况

