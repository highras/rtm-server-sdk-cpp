# RTM Server C++ SDK API Docs: Users

[TOC]

### Users api



#### GetOnlineUsers

	//-- Sync Method
	int32_t getOnlineUsers(set<int64_t>& onlineUserIds, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Async Method
	void getOnlineUsers(const set<int64_t>& userIds, std::function<void (set<int64_t> onlineUserIds, int32_t errorCode)> callback, int32_t timeout = 0);

获取在线用户

参数:

+ `userIds` 

  用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  *  输出参数onlineUserIds,  在线的用户id集合
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数onlineUserIds,  在线的用户id集合



#### AddProjectBlack

	//-- Sync Method
	int32_t addProjectBlack(int64_t userId, int32_t blackTime, int32_t timeout = 0);
	
	//-- Async Method
	void addProjectBlack(int64_t userId, int32_t blackTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

添加项目黑名单

参数:

+ `userId` 

  用户id

+ `blackTime` 

  封禁时间

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### RemoveProjectBlack

	//-- Sync Method
	int32_t removeProjectBlack(int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void removeProjectBlack(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

移除项目黑名单

参数:

+ `userId` 

  群组id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### IsProjectBlack

	//-- Sync Method
	int32_t isProjectBlack(bool& isBlack, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void isProjectBlack(int64_t userId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout = 0);

判断是否添加了项目黑名单

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数isBlack,  是否在黑名单
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数isBlack,  是否在黑名单



#### SetUserInfo

	//-- Sync Method
	int32_t setUserInfo(int64_t userId, string* oinfo, string* pinfo, int32_t timeout = 0);
	
	//-- Async Method
	void setUserInfo(int64_t userId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

设置用户信息

参数:

+ `userId` 

  用户id

+ `oinfo` 

  公有信息

+ `pinfo` 

  私有信息

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况



#### GetUserInfo

	//-- Sync Method
	int32_t getUserInfo(string& oinfo, string& pinfo, int64_t userId, int32_t timeout = 0);
	
	//-- Async Method
	void getUserInfo(int64_t userId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);

获取用户信息

参数:

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数oinfo,  用户的公有信息
  * 输出参数pinfo,  用户的私有信息
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数oinfo,  用户的公有信息
  * 参数pinfo,  用户的私有信息



#### GetUserOpenInfo

	//-- Sync Method
	int32_t getUserOpenInfo(map<string, string>& info, const set<int64_t>& userIds, int32_t timeout = 0);
	
	//-- Async Method
	void getUserOpenInfo(const set<int64_t>& userIds, std::function<void (map<string, string> info, int32_t errorCode)> callback, int32_t timeout = 0);

获取用户的公有信息

参数:

+ `userIds` 

  用户id集合

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数info,  用户的公有信息表
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数info,  用户的公有信息表
