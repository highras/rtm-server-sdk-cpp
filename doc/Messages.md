# RTM Server C++ SDK API Docs: Message

[TOC]

### Message api



#### sendMessage

	//-- Sync Method
	int32_t sendMessage(int64_t& mid, int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendMessage(int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send P2P Message

Parameters:

+ `fromUid` 

  sender user id

+ `toUid` 

  receiver user id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

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



#### sendMessages

	//-- Sync Method
	int32_t sendMessages(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendMessages(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Multiple P2P Messages

Parameters:

+ `fromUid` 

  sender user id

+ `toUids` 

  receiver user id set

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

+ `message` 

  message

+ `attrs` 

  addtional infomation

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
	int32_t sendGroupMessage(int64_t& mid, int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendGroupMessage(int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Group Chat Message

Parameters:

+ `fromUid` 

  sender user id

+ `groupId` 

  group id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

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



#### sendRoomMessage

	//-- Sync Method
	int32_t sendRoomMessage(int64_t& mid, int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void sendRoomMessage(int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Room Message

Parameters:

+ `fromUid` 

  sender user id

+ `roomId` 

  room id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

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



#### broadcastMessage

	//-- Sync Method
	int32_t broadcastMessage(int64_t& mid, int64_t fromUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
	
	//-- Async Method
	void broadcastMessage(int64_t fromUid, int8_t mtype, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);

Send Broadcast Message

Parameters:

+ `fromUid` 

  sender user id

+ `mtype` 

  message type ,refer [RTM Structures](Structures.md)

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



#### getGroupMessage

	//-- Sync Method
	int32_t getGroupMessage(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getGroupMessage(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get Group History Messages

Parameters:

+ `groupId` 

  group id

+ `desc` 

  true:  descending， false: ascending

+ `count` 

  message count

+ `beginMsec` 

  begin time in milliseconds

+ `endMsec` 

  end time in milliseconds

+ `lastId` 

  the cursorId of the last message returned by the last call, the first time returns 0

+ `mtypes` 

  message type set

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



#### getRoomMessage

	//-- Sync Method
	int32_t getRoomMessage(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getRoomMessage(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get Room History Message

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

+ `mtypes` 

  message type set

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



#### getBroadcastMessage

	//-- Sync Method
	int32_t getBroadcastMessage(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
	
	//-- Async Method
	void getBroadcastMessage(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get Broadcast History Message

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

+ `mtypes` 

  message type set

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



#### getP2PMessage

	//-- Sync Method
	int32_t getP2PMessage(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int32_t timeout = 0);
	
	//-- Async Method
	void getP2PMessage(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);

Get P2P History Message

Parameters:

+ `userId` 

  user id

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

+ `mtypes` 

  message type set

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



#### getMessage

	//-- Sync Method
	int32_t getMessage(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void getMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout = 0);

Get Message

Parameters:

+ `mid` 

  message id

+ `fromUid` 

  sender user id

+ `toId` 

  groupId or roomId or userId

+ `messageCategory` 

  message type ,refer [RTM Structures](Structures.md)

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output message RetrievedMessage, retrieved message
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output message RetrievedMessage, retrieved message

#### getMessageNum

	//-- Sync Method
  int32_t getMessageNum(int32_t& senderId, int32_t& messageNum, MessageCategory messageCategory, int64_t userId, set<int8_t> messageTypes = set<int8_t>(), int64_t begin = 0, int64_t end = 0, int32_t timeout = 0);

	//-- Async Method
  void getMessageNum(MessageCategory messageCategory, int64_t userId, std::function<void (int32_t senderId, int32_t messageNum, int32_t errorCode)> callback, set<int8_t> messageTypes = set<int8_t>(), int64_t begin = 0, int64_t end = 0, int32_t timeout = 0);

Get Message Num

Parameters:

+ `messageCategory`
  message type, GroupMessage and RoomMessage is available, refer [RTM Structures](Structures.md)

+ `messageTypes` 

  mesagge type list, return all if messageTypes is empty

+ `begin`

  begin timestamp in milliseconds

+ `end`

  end timestamp in milliseconds

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
  * output message senderId 
  * output message messageNum
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output message senderId 
  * output message messageNum


#### deleteMessage

	//-- Sync Method
	int32_t deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
	
	//-- Async Method
	void deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Delete Message

Parameters:

+ `mid` 

  message id

+ `fromUid` 

  sender user id

+ `toId` 

  groupId or roomId or userId

+ `messageCategory` 

  message type, refer [RTM Structures](Structures.md)

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success

