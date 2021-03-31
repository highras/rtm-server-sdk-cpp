# RTM Server C++ SDK API Docs: RTC

[TOC]

### RTC api



#### InviteUserIntoVoiceRoom

	//-- Sync Method
	int32_t inviteUserIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, int32_t timeout = 0);
	
	//-- Async Method
	void inviteUserIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Invite User Into Voice Room

Parameters:

+ `roomId` 

  room id

+ `toUids` 

  set of the invited uids

+ `fromUid` 

  uid of the inviter

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

#### CloseVoiceRoom

	//-- Sync Method
	int32_t closeVoiceRoom(int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
	void closeVoiceRoom(int64_t roomId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Close Voice Room

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

#### KickoutFromVoiceRoom

	//-- Sync Method
	int32_t kickoutFromVoiceRoom(int64_t uid, int64_t roomId, int64_t fromUid, int32_t timeout = 0);
	
	//-- Async Method
	void closeVoiceRoom(int64_t roomId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Kickout User from the Voice Room

Parameters:

+ `uid`

  kicked uid

+ `roomId` 

  room id

+ `fromUid`

  kicker uid

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

#### GetVoiceRoomList

	//-- Sync Method
    int32_t getVoiceRoomList(set<int64_t>& roomIds, int32_t timeout = 0);
	
	//-- Async Method
    void getVoiceRoomList(std::function<void (set<int64_t> roomIds, int32_t errorCode)> callback, int32_t timeout = 0);

Get List of the Voice Rooms 

Parameters:

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter roomIds, set of the roomId
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter roomIds, set of the roomId

#### GetVoiceRoomMembers

	//-- Sync Method
    int32_t getVoiceRoomMembers(set<int64_t>& uids, set<int64_t>& managers, int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
    void getVoiceRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, set<int64_t> managers, int32_t errorCode)> callback, int32_t timeout = 0);

Get Members of the Voice Room 

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter uids, set of the members 
  * output parameter managers, set of the managers 
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter uids, set of the members 
  * output parameter managers, set of the managers 

#### GetVoiceRoomMemberCount

	//-- Sync Method
    int32_t getVoiceRoomMemberCount(int32_t& count, int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
    void getVoiceRoomMemberCount(int64_t roomId, std::function<void (int32_t count, int32_t errorCode)> callback, int32_t timeout = 0);

Get Member Count of the Voice Room 

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter count, count of the members 
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter count, count of the members 

#### SetVoiceRoomMicStatus

	//-- Sync Method
    int32_t setVoiceRoomMicStatus(int64_t roomId, bool status, int32_t timeout = 0);
	
	//-- Async Method
    void setVoiceRoomMicStatus(int64_t roomId, bool status, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Set the Default Microphone Status of the Voice Room 

Parameters:

+ `roomId` 

  room id

+ `status`

  default status, false for close, true for open

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

#### PullIntoVoiceRoom

	//-- Sync Method
    int32_t pullIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, int32_t timeout = 0);
	
	//-- Async Method
    void pullIntoVoiceRoom(int64_t roomId, const set<int64_t>& toUids, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Pull User Into the Voice Room

Parameters:

+ `roomId` 

  room id

+ `toUids`

  set of the pulled uids

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

