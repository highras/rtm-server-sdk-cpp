# RTM Server C++ SDK API Docs: Users

[TOC]

### Users api



#### GetOnlineUsers

	//-- Sync Method
	int32_t getOnlineUsers(set<int64_t>& onlineUserIds, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Async Method
	void getOnlineUsers(const set<int64_t>& userIds, std::function<void (set<int64_t> onlineUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

Get Online Users

Parameters:

+ `userIds` 

  user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter onlineUserIds,  online user id set
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter onlineUserIds,  online user id set



#### AddProjectBlack

	//-- Sync Method
	int32_t addProjectBlack(int64_t userId, int32_t blackTime, int32_t timeout = 0);
	
	//-- Async Method
	void addProjectBlack(int64_t userId, int32_t blackTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Add User Into The Project Blacklist

Parameters:

+ `userId` 

  user id

+ `blackTime` 

  banned time

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### RemoveProjectBlack

	//-- Sync Method
	int32_t removeProjectBlack(int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeProjectBlack(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Remove User Out Of The Project Blacklist

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### IsProjectBlack

	//-- Sync Method
	int32_t isProjectBlack(bool& isBlack, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isProjectBlack(int64_t userId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout = 0);

Is In The Project Blacklist

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter isBlack,  is in blacklist
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter isBlack,  is in blacklist



#### SetUserInfo

	//-- Sync Method
	int32_t setUserInfo(int64_t userId, string* oinfo, string* pinfo, int32_t timeout = 0);
	
	//-- Async Method
	void setUserInfo(int64_t userId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Set User Information

Parameters:

+ `userId` 

  user id

+ `oinfo` 

  open information

+ `pinfo` 

  private information 

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### GetUserInfo

	//-- Sync Method
	int32_t getUserInfo(string& oinfo, string& pinfo, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getUserInfo(int64_t userId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);

Get User Information

Parameters:

+ `userId` 

  group id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter oinfo,  public information of the user
  * output pinfo,  private information of the user
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter oinfo,  public information of the user
  * output pinfo,  private information of the user




#### GetUserOpenInfo

	//-- Sync Method
	int32_t getUserOpenInfo(map<string, string>& info, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Async Method
	void getUserOpenInfo(const set<int64_t>& userIds, std::function<void (map<string, string> info, int32_t errorCode)> callback, int32_t timeout = 0);

Get User Open Info

Parameters:

+ `userIds` 

  user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter info,  public information of the users
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter info,  public information of the users
