# RTM Server C++ SDK API Docs: Rooms

[TOC]

### Rooms api



#### AddRoomBan

	//-- Sync Method
	int32_t addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, int32_t timeout = 0);
	
	//-- Async Method
	void addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加房间封禁

参数:

+ `roomId` 

  房间id

+ `userId` 

  用户id

+ `banTime` 

  封禁时间

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### RemoveRoomBan

	//-- Sync Method
	int32_t removeRoomBan(int64_t roomId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeRoomBan(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除房间封禁

参数:

+ `roomId` 

  群组id

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### IsBanOfRoom

	//-- Sync Method
	int32_t isBanOfRoom(bool& isBan, int64_t roomId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isBanOfRoom(int64_t roomId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否房间封禁

参数:

+ `roomId` 

  房间id

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数isBan，是否封禁
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数isBan，是否封禁



#### SetRoomInfo

	//-- Sync Method
	int32_t setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, int32_t timeout = 0);
	
	//-- Async Method
	void setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

设置房间信息

参数:

+ `roomId` 

  房间id

+ `oinfo` 

  共有信息

+ `pinfo` 

  私有信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### GetRoomInfo

	//-- Sync Method
	int32_t getRoomInfo(string& oinfo, string& pinfo, int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
	void getRoomInfo(int64_t roomId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);

获取房间信息

参数:

+ `roomId` 

  群组id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数oinfo,  公有信息
  * 输出参数pinfo,  私有信息
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数oinfo,  公有信息
  * 参数pinfo,  私有信息
