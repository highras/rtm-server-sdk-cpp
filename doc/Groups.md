# RTM Server C++ SDK API Docs: Groups

[TOC]

### Groups api



#### AddGroupMembers

	//-- Sync Method
	int32_t addGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Sync Method
	void addGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加群组成员

参数:

+ `groupId` 

  群组id

+ `userIds` 

  成员用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### DeleteFriends

	//-- Sync Method
	int32_t deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Async Method
	void deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除好友

参数:

+ `groupId` 

  群组id

+ `userIds` 

  成员用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### DeleteGroup

	//-- Sync Method
	int32_t deleteGroup(int64_t groupId, int32_t timeout = 0);
	
	//-- Async Method
	void deleteGroup(int64_t groupId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

删除群组

参数:

+ `groupId` 

  群组id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### GetGroupMembers

	//-- Sync Method
	int32_t getGroupMembers(set<int64_t>& members, int64_t groupId, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupMembers(int64_t groupId, std::function<void (set<int64_t> members, int32_t errorCode)> callback, int32_t timeout = 0);

获取群组成员

参数:

+ `groupId` 

  群组id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数members,  成员用户id集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数members,  成员用户id集合



#### IsGroupMember

	//-- Sync Method
	int32_t isGroupMember(bool& isMember, int64_t groupId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isGroupMember(int64_t groupId, int64_t userId, std::function<void (bool isMember, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否为群组成员

参数:

+ `groupId` 

  群组id

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数isMember,  是否群组成员
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数isMember,  是否群组成员



#### GetUserGroups

	//-- Sync Method
	int32_t getUserGroups(set<int64_t>& groupIds, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getUserGroups(int64_t userId, std::function<void (set<int64_t> groupIds, int32_t errorCode)> callback, int32_t timeout = 0);

获取用户加入了哪些群组

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数groupIds,  加入的群组id集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数groupIds,  加入的群组id集合



#### AddGroupBan

	//-- Sync Method
	int32_t addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, int32_t timeout = 0);
	
	//-- Async Method
	void addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加群组封禁

参数:

+ `groupId` 

  群组id

+ `userId` 

  用户id

+ `banTime` 

  封禁时间

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### RemoveGroupBan

	//-- Sync Method
	int32_t removeGroupBan(int64_t groupId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeGroupBan(int64_t groupId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

解除群组封禁

参数:

+ `groupId` 

  群组id

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  
    



#### IsBanOfGroup

	//-- Sync Method
	int32_t isBanOfGroup(bool& isBan, int64_t groupId, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isBanOfGroup(int64_t groupId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否为群组封禁

参数:

+ `groupId` 

  群组id

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数isBan,  是否封禁
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数isBan,  是否封禁



#### SetGroupInfo

	//-- Sync Method
	int32_t setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, int32_t timeout = 0);
	
	//-- Async Method
	void setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

设置群组信息 

参数:

+ `groupId` 

  群组id

+ `oinfo` 

  群组公开信息

+ `pinfo` 

  群组私有信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### GetGroupInfo

	//-- Sync Method
	int32_t getGroupInfo(string& oinfo, string& pinfo, int64_t groupId, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupInfo(int64_t groupId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);

获取群组信息 

参数:

+ `groupId` 

  群组id

+ `oinfo` 

  群组公开信息

+ `pinfo` 

  群组私有信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数oinfo,  公有信息
  * 参数pinfo,  私有信息

