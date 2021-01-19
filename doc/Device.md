# RTM Server C++ SDK API Docs: Device

[TOC]

### Device api



#### AddDevice

	//-- Sync Method
	int32_t addDevice(int64_t userId, const string& appType, const string& deviceToken, int32_t timeout = 0);
	
	//-- Async Method
	void addDevice(int64_t userId, const string& appType, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Add Device For Mobile Notifications

Parameters:

+ `userId` 

  user id

+ `appType` 

  push type, apns or pcm

+ `deviceToken` 

  push device token

+ `timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### RemoveDevice

	//-- Sync Method
	int32_t removeDevice(int64_t userId, const string& deviceToken, int32_t timeout = 0);
	
	//-- Async Method
	void removeDevice(int64_t userId, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Remove Device For Mobile Notifications

Parameters:

+ `userId` 

  user id

+ `deviceToken` 

  push device token

+ `timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### AddDevicePushOption

	//-- Sync Method
    int32_t addDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, int32_t timeout = 0);
	//-- Async Method
    void addDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
 
Add Chat or Group Message Not To Push

Parameters:

+ `userId` 

  user id

+ `type` 

  option type, only P2PMessage or GroupMessage can be used

+ `xid`

  uid for P2PMessage, group id for GroupMessage

+ `mtype`

  message types, if mtype is empty, all the messages types will be disabled for push.
  
+ `timeout`

  timeout in second，default 0(global configuration)

Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### RemoveDevicePushOption

	//-- Sync Method
    int32_t removeDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, int32_t timeout = 0);
	//-- Async Method
    void removeDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
 
Remove Chat or Group Message Not To Push

Parameters:

+ `userId` 

  user id

+ `type` 

  option type, only P2PMessage or GroupMessage can be used

+ `xid`

  uid for P2PMessage, group id for GroupMessage

+ `mtype`

  message types, if mtype is empty, all the messages types will be abled for push.

+ `timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success


#### GetDevicePushOption

	//-- Sync Method
     int32_t getDevicePushOption(map<string, set<int8_t>>& p2p, map<string, set<int8_t>>& group, int64_t userId, int32_t timeout = 0);
	//-- Async Method
    void getDevicePushOption(int64_t userId, std::function<void (map<string, set<int8_t>> p2p, map<string, set<int8_t>> group, int32_t errorCode)> callback, int32_t timeout = 0);
 
Get Options of Chat or Group Message Not To Push 

Parameters:

+ `userId` 

  user id

Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter p2p, options of chat message not to push
  * output parameter group, options of group message not to push
+ Async method return nothing：
  * output parameter p2p, options of chat message not to push 
  * output parameter group, options of group message not to push
  * output parameter errorCode, FPNN_EC_OK for success

