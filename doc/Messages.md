# RTM Server C++ SDK API Docs: Message

[TOC]

### Message api



#### sendMessage

	//-- Sync Method
	int32_t sendMessage(int32_t& modifyTime, int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendMessage(int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送P2P消息

参数:

+ `fromUid` 

  发送者用户id

+ `toUid` 

  接收者用户id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

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



#### sendMessages

	//-- Sync Method
	int32_t sendMessages(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendMessages(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送多人P2P消息

参数:

+ `fromUid` 

  发送者用户id

+ `toUids` 

  接收者用户id集合

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

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
	int32_t sendGroupMessage(int32_t& modifyTime, int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupMessage(int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送群组消息

参数:

+ `fromUid` 

  发送者用户id

+ `groupId` 

  群组id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

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



#### sendRoomMessage

	//-- Sync Method
	int32_t sendRoomMessage(int32_t& modifyTime, int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomMessage(int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送房间消息

参数:

+ `fromUid` 

  发送者用户id

+ `roomId` 

  房间id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

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



#### broadcastMessage

	//-- Sync Method
	int32_t broadcastMessage(int32_t& modifyTime, int64_t fromUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastMessage(int64_t fromUid, int8_t mtype, const string& message, const string& attrs, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送广播消息

参数:

+ `fromUid` 

  发送者用户id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

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



#### getGroupMessage

	//-- Sync Method
	int32_t getGroupMessage(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupMessage(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取群组历史消息

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

+ `mtypes` 

  获取哪些mtype的集合

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



#### getRoomMessage

	//-- Sync Method
	int32_t getRoomMessage(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getRoomMessage(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取房间历史消息

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

+ `mtypes` 

  获取哪些mtype的集合

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



#### getBroadcastMessage

	//-- Sync Method
	int32_t getBroadcastMessage(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getBroadcastMessage(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取广播历史消息

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

+ `mtypes` 

  获取哪些mtype的集合

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



#### getP2PMessage

	//-- Sync Method
	int32_t getP2PMessage(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int32_t timeout = 0);
	
	//-- Async Method
	void getP2PMessage(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

获取P2P历史消息

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

+ `mtypes` 

  获取哪些mtype的集合

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



#### getMessage

	//-- Sync Method
	int32_t getMessage(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void getMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout = 0);

获取消息

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



#### deleteMessage

	//-- Sync Method
	int32_t deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除消息

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

