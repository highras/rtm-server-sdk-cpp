# RTM Server C++ SDK API Docs: Files

[TOC]

### Files api



#### SendFile

	//-- Sync Method
	int32_t sendFile(int32_t& modifyTime, int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendFile(int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送文件

参数:

+ `fromUid` 

  发送者用户id

+ `toUid` 

  接收者用户id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

+ `fileData` 

  文件内容

+ `fileName` 

  文件名字

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



#### SendFiles

	//-- Sync Method
	int32_t sendFiles(int32_t& modifyTime, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendFiles(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送多人文件消息

参数:

+ `fromUid` 

  发送者用户id

+ `toUids` 

  接收者用户id集合

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

+ `fileData` 

  文件内容

+ `fileName` 

  文件名字

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### SendGroupFile

	//-- Sync Method
	int32_t sendGroupFile(int32_t& modifyTime, int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupFile(int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送群组文件消息

参数:

+ `fromUid` 

  发送者用户id

+ `groupId` 

  群组id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

+ `fileData` 

  文件内容

+ `fileName` 

  文件名字

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### SendRoomFile

	//-- Sync Method
	int32_t sendRoomFile(int32_t& modifyTime, int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomFile(int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送房间文件消息

参数:

+ `fromUid` 

  发送者用户id

+ `roomId` 

  房间id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

+ `fileData` 

  文件内容

+ `fileName` 

  文件名字

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳



#### BroadcastFile

	//-- Sync Method
	int32_t broadcastFile(int32_t& modifyTime, int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastFile(int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int32_t modifyTime, int32_t errorCode)> callback, int32_t timeout = 0);

发送广播消息

参数:

+ `fromUid` 

  发送者用户id

+ `mtype` 

  消息类型，mtype <= 50，系统保留使用，一般有特殊含义，业务使用 超过50的mtype

+ `fileData` 

  文件内容

+ `fileName` 

  文件名字

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数modifyTime,  服务器返回的时间戳
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数modifyTime,  服务器返回的时间戳


