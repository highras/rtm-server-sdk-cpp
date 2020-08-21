# RTM Server C++ SDK API Docs: Token

[TOC]

### Token api



#### GetToken

	//-- Sync Method
	int32_t getToken(string& token, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getToken(int64_t userId, std::function<void (string token, int32_t errorCode)> callback, int32_t timeout = 0);

获取用户登录token

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数token, 为用户登录token
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数token, 为用户登录token



#### RemoveToken

	//-- Sync Method
	int32_t removeToken(int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeToken(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除用户登录token

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况





#### AddDevice

	//-- Sync Method
	int32_t addDevice(int64_t userId, const string& appType, const string& deviceToken, int32_t timeout = 0);
	
	//-- Async Method
	void addDevice(int64_t userId, const string& appType, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加设备推送Token

参数:

+ `userId` 

  用户id

+ `appType` 

  推送app平台类型，apns 或 pcm

+ `deviceToken` 

  用来推送的device token

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### RemoveDevice

	//-- Sync Method
	int32_t removeDevice(int64_t userId, const string& deviceToken, int32_t timeout = 0);
	
	//-- Async Method
	void removeDevice(int64_t userId, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加设备推送Token

参数:

+ `userId` 

  用户id

+ `deviceToken` 

  用来推送的device token

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### Kickout

	//-- Sync Method
	int32_t kickout(int64_t userId, const string& ce, int32_t timeout = 0);
	
	//-- Async Method
	void kickout(int64_t userId, const string& ce, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

踢出用户

参数:

+ `userId` 

  用户id

+ `ce` 

  用户登录的endpoint

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况

