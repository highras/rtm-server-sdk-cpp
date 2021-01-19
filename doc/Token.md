# RTM Server C++ SDK API Docs: Token

[TOC]

### Token api



#### GetToken

	//-- Sync Method
	int32_t getToken(string& token, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getToken(int64_t userId, std::function<void (string token, int32_t errorCode)> callback, int32_t timeout = 0);

Get Login Token

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter token, user login token
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter token, user login token



#### RemoveToken

	//-- Sync Method
	int32_t removeToken(int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeToken(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Remove Login Token

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### Kickout

	//-- Sync Method
	int32_t kickout(int64_t userId, const string& ce, int32_t timeout = 0);
	
	//-- Async Method
	void kickout(int64_t userId, const string& ce, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Kickout User

Parameters:

+ `userId` 

  user id

+ `ce` 

  user login endpoint

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

