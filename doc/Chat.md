# RTM Server C++ SDK API Docs: Chat

[TOC]

### Chat api



#### SendChat

	//-- Sync Method
	int32_t sendChat(int64_t& mid, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendChat(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send P2P Chat Message

Parameters:

+ `fromUid` 

  sender user id

+ `toUid` 

  receiver user id

+ `message` 

  chat message

+ `attrs` 

  additional information

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters:

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter mid, message id
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter mid, message id



#### SendCmd

	//-- Sync Method
	int32_t sendCmd(int64_t& mid, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendCmd(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send P2P Command Message

Parameters:

+ `fromUid` 

  sender user id

+ `toUid` 

  receiver user id

+ `message` 

  message

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



#### SendChats

	//-- Sync Method
	int32_t sendChats(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendChats(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Mutiple P2P Chat Message

Parameters:

+ `fromUid` 

  sender user id

+ `toUids` 

  receiver user id set

+ `message` 

  message

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



#### SendCmds

	//-- Sync Method
	int32_t sendCmds(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendCmds(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Multiple Command Messages

Parameters:

+ `fromUid` 

  sender user id

+ `toUids` 

  receiver user id set

+ `message` 

  message

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



#### sendGroupChat

	//-- Sync Method
	int32_t sendGroupChat(int64_t& mid, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupChat(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Group Chat Message

Parameters:

+ `fromUid` 

  sender user id

+ `groupId` 

  group id

+ `message` 

  message

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



#### sendGroupCmd

	//-- Sync Method
	int32_t sendGroupCmd(int64_t& mid, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupCmd(int64_t fromUid, int64_t groupId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Group Command Message

Parameters:

+ `fromUid` 

  sender user id

+ `groupId` 

  group id

+ `message` 

  message

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



#### sendRoomChat

	//-- Sync Method
	int32_t sendRoomChat(int64_t& mid, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomChat(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Room Chat Message

Parameters:

+ `fromUid` 

  sender user id

+ `roomId` 

  room id

+ `message` 

  message 

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



#### sendRoomCmd

	//-- Sync Method
	int32_t sendRoomCmd(int64_t& mid, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomCmd(int64_t fromUid, int64_t roomId, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Room Command Message

Parameters:

+ `fromUid` 

  sender user id

+ `roomId` 

  room id

+ `message` 

  message

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



#### broadcastChat

	//-- Sync Method
	int32_t broadcastChat(int64_t& mid, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastChat(int64_t fromUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Broadcast Chat Message

Parameters:

+ `fromUid` 

  sender user id

+ `message` 

  message 

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



#### broadcastCmd

	//-- Sync Method
	int32_t broadcastCmd(int64_t& mid, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastCmd(int64_t fromUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Broadcast Command Message

Parameters:

+ `fromUid` 

  sender user id

+ `message` 

  message

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



#### getGroupChat

	//-- Sync Method
	int32_t getGroupChat(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupChat(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get Group Chat History Messages

Parameters:

+ `groupId` 

  group id

+ `desc` 

  true:  descending， false: ascending

+ `count` 

  message count

+ `beginMsec` 

  begin timestamp in milliseconds

+ `endMsec` 

  end timestamp in milliseconds

+ `lastId` 

  the cursorId of the last message returned by the last call, the first time returns 0

+ `uid` 

  caller user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter HistoryMessageResult, History Message Result
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter HistoryMessageResult, History Message Result



#### getRoomChat

	//-- Sync Method
	int32_t getRoomChat(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getRoomChat(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get Room Chat History Messages

Parameters:

+ `roomId` 

  room id

+ `desc` 

  true:  descending， false: ascending

+ `count` 

  message count

+ `beginMsec` 

  begin timestamp in milliseconds

+ `endMsec` 

  end timestamp in milliseconds

+ `lastId` 

  the cursorId of the last message returned by the last call, the first time returns 0

+ `uid` 

  caller user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter HistoryMessageResult, History Message Result
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter HistoryMessageResult, History Message Result



#### getBroadcastChat

	//-- Sync Method
	int32_t getBroadcastChat(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getBroadcastChat(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get Broadcast Chat History Messages

Parameters:

+ `desc` 

  true:  descending， false: ascending

+ `count` 

  message count

+ `beginMsec` 

  begin timestamp in milliseconds

+ `endMsec` 

  end timestamp in milliseconds

+ `lastId` 

  the cursorId of the last message returned by the last call, the first time returns 0

+ `uid` 

  caller user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter HistoryMessageResult, History Message Result
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter HistoryMessageResult, History Message Result



#### getP2PChat

	//-- Sync Method
	int32_t getP2PChat(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int32_t timeout = 0);
	
	//-- Async Method
	void getP2PChat(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get P2P Chat History Messages

Parameters:

+ `userId` 

  group id

+ `otherUserId` 

  target user id

+ `desc` 

  true:  descending， false: ascending

+ `count` 

  message count

+ `beginMsec` 

  begin timestamp in milliseconds

+ `endMsec` 

  end timestamp in milliseconds

+ `lastId` 

  the cursorId of the last message returned by the last call, the first time returns 0

+ `uid` 

  caller user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output parameter HistoryMessageResult, History Message Result
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter HistoryMessageResult, History Message Result



#### getChat

	//-- Sync Method
	int32_t getChat(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void getChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout = 0);

Get Chat Message

Parameters:

+ `mid` 

  message id

+ `fromUid` 

  sender user id

+ `toId` 

  groupId or roomId or userId

+ `messageCategory` 

  message type , refer [RTM Structures](Structures.md)

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output message RetrievedMessage, retrieved message
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output message RetrievedMessage, retrieved message



#### deleteChat

	//-- Sync Method
	int32_t deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Delete Chat Message

Parameters:

+ `mid` 

  message id

+ `fromUid` 

  sender user id

+ `toId` 

  groupId or roomId or userId

+ `messageCategory` 

  message type , refer [RTM Structures](Structures.md)

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

