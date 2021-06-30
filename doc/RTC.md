# RTM Server C++ SDK API Docs: RTC

[TOC]

### RTC api



#### InviteUserIntoRTCRoom

	//-- Sync Method
	int32_t inviteUserIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, int32_t timeout = 0);
	
	//-- Async Method
	void inviteUserIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int64_t fromUid, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Invite User Into RTC Room

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

#### CloseRTCRoom

	//-- Sync Method
	int32_t closeRTCRoom(int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
	void closeRTCRoom(int64_t roomId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Close RTC Room

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

#### KickoutFromRTCRoom

	//-- Sync Method
	int32_t kickoutFromRTCRoom(int64_t uid, int64_t roomId, int64_t fromUid, int32_t timeout = 0);
	
	//-- Async Method
	void closeRTCRoom(int64_t roomId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Kickout User from the RTC Room

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

#### GetRTCRoomList

	//-- Sync Method
    int32_t getRTCRoomList(set<int64_t>& roomIds, int32_t timeout = 0);
	
	//-- Async Method
    void getRTCRoomList(std::function<void (set<int64_t> roomIds, int32_t errorCode)> callback, int32_t timeout = 0);

Get List of the RTC Rooms 

Parameters:

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter roomIds, set of the roomId
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter roomIds, set of the roomId

#### GetRTCRoomMembers

	//-- Sync Method
    int32_t getRTCRoomMembers(set<int64_t>& uids, set<int64_t>& administartors, int64_t roomId, int64_t owner, int32_t timeout = 0);
	
	//-- Async Method
    void getRTCRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, set<int64_t> administartors, int64_t owner, int32_t errorCode)> callback, int32_t timeout = 0);

Get Members of the RTC Room 

Parameters:

+ `roomId` 

  room id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter uids, set of the members 
  * output parameter administartors, set of the administartors 
  * output parameter owner, owner of the room
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter uids, set of the members 
  * output parameter administartors, set of the administartors 
  * output parameter owner, owner of the room

#### GetRTCRoomMemberCount

	//-- Sync Method
    int32_t getRTCRoomMemberCount(int32_t& count, int64_t roomId, int32_t timeout = 0);
	
	//-- Async Method
    void getRTCRoomMemberCount(int64_t roomId, std::function<void (int32_t count, int32_t errorCode)> callback, int32_t timeout = 0);

Get Member Count of the RTC Room 

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

#### SetRTCRoomMicStatus

	//-- Sync Method
    int32_t setRTCRoomMicStatus(int64_t roomId, bool status, int32_t timeout = 0);
	
	//-- Async Method
    void setRTCRoomMicStatus(int64_t roomId, bool status, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Set the Default Microphone Status of the RTC Room 

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

#### PullIntoRTCRoom

	//-- Sync Method
    int32_t pullIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int32_t type, int32_t timeout = 0);
	
	//-- Async Method
    void pullIntoRTCRoom(int64_t roomId, const set<int64_t>& toUids, int32_t type, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Pull User Into the RTC Room

Parameters:

+ `roomId` 

  room id

+ `toUids`

  set of the pulled uids

+ `type`

  1 for voice room, 2 for video room

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

#### AdminCommand

	//-- Sync Method
    int32_t adminCommand(int64_t roomId, const set<int64_t>& uids, int32_t command, int32_t timeout = 0);
	
	//-- Async Method
    void adminCommand(int64_t roomId, const set<int64_t>& uids, int32_t command, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Administrator Command Operation

Parameters:

+ `roomId` 

  room id

+ `toUids`

  set of the pulled uids

+ `command`

  type of administrator command
  Please refer [RTM Structures](doc/Structures.md)

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

