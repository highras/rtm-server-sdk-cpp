# RTM Server C++ SDK API Docs: Rooms

[TOC]

### Rooms api



#### AddRoomBan

	//-- Sync Method
	int32_t addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, int32_t timeout = 0);
	
	//-- Async Method
	void addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Ban Room Member

Parameters:

+ `roomId` 

  room id, if 0 is setted, all the rooms will be banned for this user

+ `userId` 

  user id

+ `banTime` 

  ban time

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### RemoveRoomBan

	//-- Sync Method
	int32_t removeRoomBan(int64_t roomId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeRoomBan(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Unban Room Member

Parameters:

+ `roomId` 

  room id, if 0 is setted, all the rooms will remove ban for this user

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### IsBanOfRoom

	//-- Sync Method
	int32_t isBanOfRoom(bool& isBan, int64_t roomId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isBanOfRoom(int64_t roomId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout = 0);

Is Member Baned In The Room

Parameters:

+ `roomId` 

  room id

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter isBan，is banned
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter isBan，is banned



#### SetRoomInfo

	//-- Sync Method
	int32_t setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, int32_t timeout = 0);
	
	//-- Async Method
	void setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Set Room Information

Parameters:

+ `roomId` 

  room id

+ `oinfo` 

  open infomation

+ `pinfo` 

  private infomation

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### GetRoomInfo

	//-- Sync Method
	int32_t getRoomInfo(string& oinfo, string& pinfo, int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
	void getRoomInfo(int64_t roomId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);

Get Room Information

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter oinfo,  open infomation
  * private parameter pinfo, private information 
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter oinfo,  open infomation
  * private parameter pinfo, private information 

#### GetRoomMembers

	//-- Sync Method
  int32_t getRoomMembers(set<int64_t>& uids, int64_t roomid, int32_t timeout = 0);
	
	//-- Async Method
  void getRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, int32_t errorCode)> callback, int32_t timeout = 0);

Get Members of the Room 

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * uids uids of the room members
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * uids uids of the room members

#### GetRoomMember

	//-- Sync Method
  int32_t getRoomCount(map<string ,int32_t>& count, int64_t roomid, int32_t timeout = 0);
	
	//-- Async Method
  void getRoomCount(int64_t roomId, std::function<void (map<string, int32_t> count, int32_t errorCode)> callback, int32_t timeout = 0);

Get Member Count of the Room 

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter count, key for room id, value for count of the room members
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter count, key for room id, value for count of the room members
