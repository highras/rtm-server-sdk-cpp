# RTM Server C++ SDK API Docs: Groups

[TOC]

### Groups api



#### AddGroupMembers

	//-- Sync Method
	int32_t addGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Sync Method
	void addGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Add Members Into the Group

Parameters:

+ `groupId` 

  group id

+ `userIds` 

  member user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### DeleteFriends

	//-- Sync Method
	int32_t deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Async Method
	void deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Delete Friends

Parameters:

+ `groupId` 

  group id

+ `userIds` 

  member user id set 

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### DeleteGroup

	//-- Sync Method
	int32_t deleteGroup(int64_t groupId, int32_t timeout = 0);
	
	//-- Async Method
	void deleteGroup(int64_t groupId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Delete Group

Parameters:

+ `groupId` 

  group id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### GetGroupMembers

	//-- Sync Method
	int32_t getGroupMembers(set<int64_t>& members, int64_t groupId, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupMembers(int64_t groupId, std::function<void (set<int64_t> members, int32_t errorCode)> callback, int32_t timeout = 0);

Get Group Members

Parameters:

+ `groupId` 

  group id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter members,  member user id set
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter members,  member user id set



#### IsGroupMember

	//-- Sync Method
	int32_t isGroupMember(bool& isMember, int64_t groupId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isGroupMember(int64_t groupId, int64_t userId, std::function<void (bool isMember, int32_t errorCode)> callback, int32_t timeout = 0);

Is Groupt Member

Parameters:

+ `groupId` 

  group id

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter isMember, is group member
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter isMember, is group member



#### GetUserGroups

	//-- Sync Method
	int32_t getUserGroups(set<int64_t>& groupIds, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getUserGroups(int64_t userId, std::function<void (set<int64_t> groupIds, int32_t errorCode)> callback, int32_t timeout = 0);

Get Groups The User In

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter groupIds,  joined group id set
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter groupIds,  joined group id set



#### AddGroupBan

	//-- Sync Method
	int32_t addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, int32_t timeout = 0);
	
	//-- Async Method
	void addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Ban The Group Member 

Parameters:

+ `groupId` 

  group id, if 0 is setted, all the groups will be banned for this user

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



#### RemoveGroupBan

	//-- Sync Method
	int32_t removeGroupBan(int64_t groupId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeGroupBan(int64_t groupId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Unban The Group Member

Parameters:

+ `groupId` 

  group id, if 0 is setted, all the groups will remove ban for this user

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  
    



#### IsBanOfGroup

	//-- Sync Method
	int32_t isBanOfGroup(bool& isBan, int64_t groupId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isBanOfGroup(int64_t groupId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout = 0);

Is The Member Banned In The Group

Parameters:

+ `groupId` 

  group id

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter isBan,  is banned
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter isBan,  is banned



#### SetGroupInfo

	//-- Sync Method
	int32_t setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, int32_t timeout = 0);
	
	//-- Async Method
	void setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Set Group Info

Parameters:

+ `groupId` 

  group id

+ `oinfo` 

  group open information

+ `pinfo` 

  group private information

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### GetGroupInfo

	//-- Sync Method
	int32_t getGroupInfo(string& oinfo, string& pinfo, int64_t groupId, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupInfo(int64_t groupId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);

 Get Group Information

Parameters:

+ `groupId` 

  group id

+ `oinfo` 

  group open information

+ `pinfo` 

  group private information

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter oinfo,  open information
  * output parameter pinfo,  private information
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter oinfo,  open information
  * output parameter pinfo,  private information
