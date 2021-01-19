# RTM Server C++ SDK API Docs: Server Push Monitor

# Index

[TOC]

## Implement you RTMServerPushMonitor derived class

    class MyMonitor: public RTMServerPushMonitor
    {
        // listen connected event
        virtual void connected(const string& endpoint, bool connected, bool isReconnect) {}
    
        // listen closed event
        virtual void closed(const string& endpoint, bool causedByError, bool isReconnect) {}
    
        // listen p2p message
        virtual void pushP2PMessage(RTMMessage message) {}
    
        // listen group message
        virtual void pushGroupMessage(RTMMessage message) {}
    
        // listen room message
        virtual void pushRoomMessage(RTMMessage message) {}
    
        // listen p2p file message
        virtual void pushP2PFile(RTMMessage message) {}
    
        // listen group file message
        virtual void pushGroupFile(RTMMessage message) {}
    
        // listen room file message
        virtual void pushRoomFile(RTMMessage message) {}
    
        // listen p2p chat message
        virtual void pushP2PChat(RTMMessage message) {}
    
        // listen p2p command message
        virtual void pushP2PCmd(RTMMessage message) {}
    
        // listen group chat message 
        virtual void pushGroupChat(RTMMessage message) {}
    
        // listen group command message
        virtual void pushGroupCmd(RTMMessage message) {}
    
        // listen room chat message
        virtual void pushRoomChat(RTMMessage message) {}
    
        // listen room command message
        virtual void pushRoomCmd(RTMMessage message) {}
    
        // push event (only login and logout event are supported)
        virtual void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data) {}
    
        // server ping
        virtual void ping() {}
    };



### Set Server Push Monitor

	client->setServerPushMonitor(make_shared<MyMonitor>());



### SetListen / AddListen api



#### AddListen

	//-- Sync Method
	int32_t addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
	
	//-- Async Method
	void addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Add Listen for Server Push Monitor. Add incrementally, only valid for the current connection

Parameters:

+ `groupIds` 

	group id set to listen

+ `roomIds`

	room id set to listen

+ `userIds`

  user id set to listen

+ `events`

  event set to listen，only login and logout are supported

+ `int timeout`

	timeout in second，default 0(global configuration)



Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
* output parameter errorCode, FPNN_EC_OK for success



#### RemoveListen

	//-- Sync Method
	int32_t removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
	
	//-- Async Method
	void removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Remove Listen for Server Push Monitor. Remove incrementally, only valid for the current connection

Parameters:

+ `groupIds` 

  group id set to listen

+ `roomIds`

  room id set to listen

+ `userIds`

  user id set to listen

+ `events`

  event set to listen，only login and logout are supported

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success



#### SetListen

	//-- Sync Method
	int32_t setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
	int32_t setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, int32_t timeout = 0);
	       
	//-- Async Method
	void setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
	void setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);

Set Listen for Server Push Monitor. Parameters please refer to AddListen. Full coverage, only valid for the current connection

Parameters:

+ `groupIds` 

  group id set to listen

+ `roomIds`

  room id set to listen

+ `userIds`

  user id set to listen

+ `events`

  event set to listen，only login and logout are supported

+ `allGroup`

  listen all the group messages

+ `allRoom`

  listen all the room messages

+ `allP2P`

  listen all the p2p messages

+ `allEvent`

  listen all the events

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_CODE for success
+ Async method return nothing：
  * output parameter errorCode, FPNN_EC_OK for success