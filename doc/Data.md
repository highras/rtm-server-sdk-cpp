# RTM Server C++ SDK API Docs: Data

[TOC]

### Data api



#### DataSet

	//-- Sync Method
	int32_t dataSet(int64_t userId, const string& key, const string& value, int32_t timeout = 0);
	
	//-- Async Method
	void dataSet(int64_t userId, const string& key, const string& value, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

数据添加

参数:

+ `userId` 

  用户id

+ `key` 

  数据的key

+ `value` 

  数据的value

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### DataDelete

	//-- Sync Method
	int32_t dataDelete(int64_t userId, const string& key, int32_t timeout = 0);
	
	//-- Async Method
	void dataDelete(int64_t userId, const string& key, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

数据删除

参数:

+ `userId` 

  用户id

+ `key` 

  数据的key

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### DataGet

	//-- Sync Method
	int32_t dataGet(string& value, int64_t userId, const string& key, int32_t timeout = 0);
	
	//-- Async Method
	void dataGet(int64_t userId, const string& key, std::function<void (string value, int32_t errorCode)> callback, int32_t timeout = 0);

获取数据

参数:

+ `userId` 

  群组id

+ `key` 

  数据的key

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数value: 数据的值
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数value: 数据的值


