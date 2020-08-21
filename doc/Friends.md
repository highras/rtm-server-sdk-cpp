# RTM Server C++ SDK API Docs: Friends

[TOC]

### Friends api



#### AddFriends

	//-- Sync Method
	int32_t addFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout = 0);
	
	//-- Async Method
	void addFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加好友

参数:

+ `userId` 

  用户id

+ `friends` 

  好友用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### DeleteFriends

	//-- Sync Method
	int32_t deleteFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout = 0);
	
	//-- Async Method
	void deleteFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除好友

参数:

+ `userId` 

  用户id

+ `friends` 

  好友用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### GetFriends

	//-- Sync Method
	int32_t getFriends(set<int64_t>& friendUserIds, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getFriends(int64_t userId, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

获取好友

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数friendUserIds,  好友集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数friendUserIds,  好友集合



#### IsFriend

	//-- Sync Method
	int32_t isFriend(bool& isFriend, int64_t userId, int64_t otherUserId, int32_t timeout = 0);
	
	//-- Async Method
	void isFriend(int64_t userId, int64_t otherUserId, std::function<void (bool isFriend, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否好友

参数:

+ `userId` 

  用户id

+ `otherUserId` 

  对方用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数isFriend,  是否为好友
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数isFriend,  是否为好友



#### IsFriends

	//-- Sync Method
	int32_t isFriends(set<int64_t>& friendUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout = 0);
	
	//-- Async Method
	void isFriends(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

发送广播消息

参数:

+ `userId` 

  用户id

+ `otherUserIds` 

  对方用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数friendUserIds,  好友的用户id集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数friendUserIds,  好友的用户id集合



#### AddBlacks

	//-- Sync Method
	int32_t addBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout = 0);
	
	//-- Async Method
	void addBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加黑名单

参数:

+ `userId` 

  用户id

+ `blacks` 

  对方用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### DeleteBlacks

	//-- Sync Method
	int32_t deleteBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout = 0);
	
	//-- Async Method
	void deleteBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加黑名单

参数:

+ `userId` 

  用户id

+ `blacks` 

  对方用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### IsBlack

	//-- Sync Method
	int32_t isBlack(bool& isBlack, int64_t userId, int64_t otherUserId, int32_t timeout = 0);
	
	//-- Async Method
	void isBlack(int64_t userId, int64_t otherUserId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否为黑名单

参数:

+ `userId` 

  用户id

+ `otherUserId` 

  对方用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数isBlack,  是否为黑名单
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数isBlack,  是否为黑名单



#### IsBlacks

	//-- Sync Method
	int32_t isBlacks(set<int64_t>& blackUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout = 0);
	
	//-- Async Method
	void isBlacks(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否为黑名单

参数:

+ `userId` 

  用户id

+ `otherUserIds` 

  对方用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数blackUserIds,  黑名单用户id集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数blackUserIds,  黑名单用户id集合



#### GetBlacks

	//-- Sync Method
	int32_t getBlacks(set<int64_t>& blackUserIds, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getBlacks(int64_t userId, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否为黑名单

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数blackUserIds,  黑名单用户id集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数blackUserIds,  黑名单用户id集合