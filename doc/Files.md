# RTM Server C++ SDK API Docs: Files

[TOC]

### Files api



#### SendFile

	//-- Sync Method
	int32_t sendFile(int64_t& mid, int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendFile(int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send File

Parameters:

+ `fromUid` 

  sender user id

+ `toUid` 

  receiver user id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

+ `fileData` 

  file content

+ `fileName` 

  file name

+ `attrs` 

  additional information

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter mid, message id
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter mid, message id



#### SendFiles

	//-- Sync Method
	int32_t sendFiles(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendFiles(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send File To Multiple Users

Parameters:

+ `fromUid` 

  sender user id

+ `toUids` 

  receiver user id set

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

+ `fileData` 

  file content 

+ `fileName` 

  file name

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter mid, message id
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter mid, message id



#### SendGroupFile

	//-- Sync Method
	int32_t sendGroupFile(int64_t& mid, int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupFile(int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Group File

Parameters:

+ `fromUid` 

  sender user id

+ `groupId` 

  group id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

+ `fileData` 

  file content

+ `fileName` 

  file name

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter mid, message id
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter mid, message id



#### SendRoomFile

	//-- Sync Method
	int32_t sendRoomFile(int64_t& mid, int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomFile(int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Room File

Parameters:

+ `fromUid` 

  sender user id

+ `roomId` 

  room id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

+ `fileData` 

  file content

+ `fileName` 

  file name

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter mid, message id
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter mid, message id



#### BroadcastFile

	//-- Sync Method
	int32_t broadcastFile(int64_t& mid, int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastFile(int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Broadcast File

Parameters:

+ `fromUid` 

  sender user id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

+ `fileData` 

  file content

+ `fileName` 

  file name

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter mid, message id
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter mid, message id


