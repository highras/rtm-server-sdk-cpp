# RTM Server C++ SDK API Docs: Data

[TOC]

### Data api



#### DataSet

	//-- Sync Method
	int32_t dataSet(int64_t userId, const string& key, const string& value, int32_t timeout = 0);
	
	//-- Async Method
	void dataSet(int64_t userId, const string& key, const string& value, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

DataSet

Parameters:

+ `userId` 

  user id

+ `key` 

  data key

+ `value` 

   data value

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### DataDelete

	//-- Sync Method
	int32_t dataDelete(int64_t userId, const string& key, int32_t timeout = 0);
	
	//-- Async Method
	void dataDelete(int64_t userId, const string& key, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

DataDelete

Parameters:

+ `userId` 

  user id

+ `key` 

  data key

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### DataGet

	//-- Sync Method
	int32_t dataGet(string& value, int64_t userId, const string& key, int32_t timeout = 0);
	
	//-- Async Method
	void dataGet(int64_t userId, const string& key, std::function<void (string value, int32_t errorCode)> callback, int32_t timeout = 0);

DataGet

Parameters:

+ `userId` 

  user id

+ `key` 

  data key

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output message value, data value
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output message value, data value


