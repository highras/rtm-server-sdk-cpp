# RTM Server C++ SDK API Docs: Friends

[TOC]

### Friends api



#### AddFriends

	//-- Sync Method
	int32_t addFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout = 0);
	
	//-- Async Method
	void addFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Add Friends

Parameters:

+ `userId` 

  user id

+ `friends` 

  friend user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### DeleteFriends

	//-- Sync Method
	int32_t deleteFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout = 0);
	
	//-- Async Method
	void deleteFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Delete Friends

Parameters:

+ `userId` 

  user id

+ `friends` 

  friend user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### GetFriends

	//-- Sync Method
	int32_t getFriends(set<int64_t>& friendUserIds, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getFriends(int64_t userId, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

Get Friend Ids

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter friendUserIds, friend user id set
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter friendUserIds, friend user id set



#### IsFriend

	//-- Sync Method
	int32_t isFriend(bool& isFriend, int64_t userId, int64_t otherUserId, int32_t timeout = 0);
	
	//-- Async Method
	void isFriend(int64_t userId, int64_t otherUserId, std::function<void (bool isFriend, int32_t errorCode)> callback, int32_t timeout = 0);

Check Is Firend

Parameters:

+ `userId` 

  user id

+ `otherUserId` 

  target user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output patameter isFriend,  is friend
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output patameter isFriend,  is friend



#### IsFriends

	//-- Sync Method
	int32_t isFriends(set<int64_t>& friendUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout = 0);
	
	//-- Async Method
	void isFriends(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

Check Is Firends

Parameters:

+ `userId` 

  user id

+ `otherUserIds` 

  target user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter friendUserIds,  friend user id set
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter friendUserIds,  friend user id set



#### AddBlacks

	//-- Sync Method
	int32_t addBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout = 0);
	
	//-- Async Method
	void addBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Add Blacklist

Parameters:

+ `userId` 

  user id

+ `blacks` 

  target user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### DeleteBlacks

	//-- Sync Method
	int32_t deleteBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout = 0);
	
	//-- Async Method
	void deleteBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Delete Blacklist

Parameters:

+ `userId` 

  user id

+ `blacks` 

  target user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### IsBlack

	//-- Sync Method
	int32_t isBlack(bool& isBlack, int64_t userId, int64_t otherUserId, int32_t timeout = 0);
	
	//-- Async Method
	void isBlack(int64_t userId, int64_t otherUserId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout = 0);

Is In Blacklist

Parameters:

+ `userId` 

  user id

+ `otherUserId` 

  target user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter isBlack,  is in blacklist
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter isBlack,  is in blacklist



#### IsBlacks

	//-- Sync Method
	int32_t isBlacks(set<int64_t>& blackUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout = 0);
	
	//-- Async Method
	void isBlacks(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

Is In Blacklist

Parameters:

+ `userId` 

  user id

+ `otherUserIds` 

  target user id set

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter blackUserIds,  user id set in blacklist
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter blackUserIds,  user id set in blacklist



#### GetBlacks

	//-- Sync Method
	int32_t getBlacks(set<int64_t>& blackUserIds, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getBlacks(int64_t userId, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

Get Blacklist

Parameters:

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter blackUserIds,  user id set in blacklist
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter blackUserIds,  user id set in blacklist