#include <iostream>
#include "rtm.h"

using namespace std;
using namespace rtm;

class MyRTMServerMonitor: public RTMServerPushMonitor
{
    void connected(const string& endpoint, bool connected, bool isReconnect) 
    {
        cout << "connectedCallback endpoint: " << endpoint << " connected: " << connected << " isReconnect: " << isReconnect << endl;
    }

    void closed(const string& endpoint, bool causedByError, bool isReconnect) 
    {
        cout << "closedCallback endpoint: " << endpoint << " causedByError: " << causedByError << " isReconnect: " << isReconnect << endl;
    }

    void printMessage(const string& method, RTMMessage message)
    {
        cout << method << endl;
        cout << "fromUid: " << message.fromUid << " toId: " << message.toId << " messageType: " << message.messageType << " messageId: " << message.messageId << " message: " << message.message << " attrs: " << message.attrs << " modifiedTime: " << message.modifiedTime << endl;

        if (message.audioInfo != nullptr) {
            cout << "audioInfo->sourceLanguage: " <<  message.audioInfo->sourceLanguage << " audioInfo->recognizedLanguage: " << message.audioInfo->recognizedLanguage << " audioInfo->recognizedText: " << message.audioInfo->recognizedText << " audioInfo->duration: " << message.audioInfo->duration << endl;
        }

        if (message.translatedInfo != nullptr) {
            cout << "translatedInfo->sourceLanguage: " << message.translatedInfo->sourceLanguage << " translatedInfo->targetLanguage: " << message.translatedInfo->targetLanguage << " message.translatedInfo->sourceText: " << message.translatedInfo->sourceText << " translatedInfo->targetText: " << message.translatedInfo->targetText << endl;
        }
    } 

    void pushP2PMessage(RTMMessage message) 
    {
        printMessage("pushP2PMessage", message); 
    }

    void pushGroupMessage(RTMMessage message) 
    {
        printMessage("pushGroupMessage", message); 
    }

    void pushRoomMessage(RTMMessage message)
    {
        printMessage("pushRoomMessage", message);  
    }

    void pushP2PFile(RTMMessage message) 
    {
        printMessage("pushP2PFile", message); 
    }

    void pushGroupFile(RTMMessage message) 
    {
        printMessage("pushGroupFile", message); 
    }

    void pushRoomFile(RTMMessage message) 
    {
        printMessage("pushRoomFile", message); 
    }

    void pushP2PChat(RTMMessage message) 
    {
        printMessage("pushP2PChat", message); 
    }

    void pushP2PAudio(RTMMessage message) 
    {
        printMessage("pushP2PAudio", message); 
    }

    void pushP2PCmd(RTMMessage message) 
    {
        printMessage("pushP2PCmd", message); 
    }

    void pushGroupChat(RTMMessage message) 
    {
        printMessage("pushGroupChat", message); 
    }

    void pushGroupAudio(RTMMessage message) 
    {
        printMessage("pushGroupAudio", message); 
    }

    void pushGroupCmd(RTMMessage message) 
    {
        printMessage("pushGroupCmd", message); 
    }

    void pushRoomChat(RTMMessage message) 
    {
        printMessage("pushRoomChat", message); 
    }

    void pushRoomAudio(RTMMessage message) 
    {
        printMessage("pushRoomAudio", message); 
    }

    void pushRoomCmd(RTMMessage message) 
    {
        printMessage("pushRoomCmd", message); 
    }

    void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data)
    {
        cout << "pid: " << pid << " event: " << event << " uid: " << uid << " time: " << time << " endpoint: " << endpoint << " data: " << data << endl; 
    }

    void ping()
    {
        cout << "ping" << endl;
    }

};

bool isErrorCode(const string& method, int32_t errorCode)
{
    if (errorCode != FPNN_EC_OK) {
        cout << method << " quest error, errorCode: " << errorCode << endl; 
        return true;
    }
    cout << method << " quest success" << endl; 
    return false;
}

void testToken(RTMServerClientPtr client)
{
    string token;
    int32_t errorCode =  client->getToken(token, 123456);
    if (!isErrorCode("[Sync getToken]", errorCode))
        cout << "get token: " << token << endl;

    client->getToken(123456, [](string token, int32_t errorCode){
        if (!isErrorCode("[Async getToken]", errorCode))
            cout << "get token: " << token << endl;
    });

    errorCode = client->removeToken(123456);
    isErrorCode("[Sync removeToken]", errorCode);

    client->removeToken(123456, [](int32_t errorCode){
        isErrorCode("[Async removeToken]", errorCode);
    });

    errorCode = client->addDevice(123456, "apns", "xxx");
    isErrorCode("[Sync addDevice]", errorCode);

    client->addDevice(123456, "apns", "xxx", [](int32_t errorCode){
        isErrorCode("[Async addDevice]", errorCode);
    });

    errorCode = client->removeDevice(123456, "xxx");
    isErrorCode("[Sync removeDevice]", errorCode);

    client->removeDevice(123456, "xxx", [](int32_t errorCode){
        isErrorCode("[Async removeDevice]", errorCode);
    });

    errorCode = client->kickout(123456, "");
    isErrorCode("[Sync kickout]", errorCode);

    client->kickout(123456, "", [](int32_t errorCode){
        isErrorCode("[Async kickout]", errorCode);
    });
}

void testChat(RTMServerClientPtr client)
{
    int32_t modifyTime;
    int32_t errorCode = client->sendChat(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendChat]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendChat(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendChat]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendAudio(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendAudio]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendAudio(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendAudio]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendCmd(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendCmd]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendCmd(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendCmd]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendGroupChat(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendGroupChat]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendGroupChat(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupChat]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendGroupAudio(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendGroupAudio]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendGroupAudio(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupAudio]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendGroupCmd(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendGroupCmd]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendGroupCmd(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupCmd]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendRoomChat(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendRoomChat]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendRoomChat(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomChat]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendRoomAudio(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendRoomAudio]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendRoomAudio(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomAudio]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->sendRoomCmd(modifyTime, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendRoomCmd]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendRoomCmd(123, 123456, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomCmd]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->broadcastChat(modifyTime, 111, "test message", "");
    if (!isErrorCode("[Sync broadcastChat]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->broadcastChat(111, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async broadcastChat]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->broadcastAudio(modifyTime, 111, "test message", "");
    if (!isErrorCode("[Sync broadcastAudio]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->broadcastAudio(111, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async broadcastAudio]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    errorCode = client->broadcastCmd(modifyTime, 111, "test message", "");
    if (!isErrorCode("[Sync broadcastCmd]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->broadcastCmd(111, "test message", "", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async broadcastCmd]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    });

    HistoryMessageResult result;
    errorCode = client->getGroupChat(result, 123456, true, 20, 0, 0, 0, 0);
    if (!isErrorCode("[Sync getGroupChat]", errorCode))
        cout << "HistoryMessageResult.count: " << result.count << endl;

    client->getGroupChat(123456, true, 20, 0, 0, 0, 0, [](HistoryMessageResult result, int32_t errorCode) {
        if (!isErrorCode("[Async getGroupChat]", errorCode))
            cout << "HistoryMessageResult.count: " << result.count << endl;
    });
}

void testListen(RTMServerClientPtr client)
{
    int32_t errorCode =  client->addListen({123, 456}, {123, 456}, {123, 456}, {"login", "logout"});
    isErrorCode("[Sync addListen]", errorCode);

    client->addListen({123, 456}, {123, 456}, {123, 456}, {"login", "logout"}, [](int32_t errorCode) {
        isErrorCode("[Async addListen]", errorCode);
    });

    errorCode = client->removeListen({123, 456}, {123, 456}, {123, 456}, {"login", "logout"});
    isErrorCode("[Sync removeListen]", errorCode);

    client->removeListen({123, 456}, {123, 456}, {123, 456}, {"login", "logout"}, [](int32_t errorCode) {
        isErrorCode("[Async removeListen]", errorCode);
    });

    errorCode = client->setListen({123, 456}, {123, 456}, {123, 456}, {"login", "logout"});
    isErrorCode("[Sync setListen]", errorCode);

    client->setListen({123, 456}, {123, 456}, {123, 456}, {"login", "logout"}, [](int32_t errorCode) {
        isErrorCode("[Async setListen]", errorCode);
    });

    errorCode = client->setListen(true, true, true, true);
    isErrorCode("[Sync setListen (all)]", errorCode);

    client->setListen(true, true, true, true, [](int32_t errorCode){
        isErrorCode("[Async setListen (all)]", errorCode);
    });
}

void testFile(RTMServerClientPtr client)
{
    string fileData;
    if (!client->loadFile("/Users/zhaojianjun/Downloads/audio1.bin", fileData))
        return;
    
    int32_t modifyTime;
    int32_t errorCode = client->sendFile(modifyTime, 111, 123456, 50, fileData, "audio1.bin", 10);
    if (!isErrorCode("[Sync sendFile]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendFile(111, 123456, 50, fileData, "audio1.bin", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendFile]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    }, 10);

    errorCode = client->sendGroupFile(modifyTime, 111, 123456, 50, fileData, "audio1.bin", 10);
    if (!isErrorCode("[Sync sendGroupFile]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendGroupFile(111, 123456, 50, fileData, "audio1.bin", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupFile]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    }, 10);

    errorCode = client->sendRoomFile(modifyTime, 111, 123456, 50, fileData, "audio1.bin", 10);
    if (!isErrorCode("[Sync sendRoomFile]", errorCode))
        cout << "get modifyTime: " << modifyTime << endl;

    client->sendRoomFile(111, 123456, 50, fileData, "audio1.bin", [](int32_t modifyTime, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomFile]", errorCode))
            cout << "get modifyTime: " << modifyTime << endl;
    }, 10);
}

void testFriend(RTMServerClientPtr client)
{
    int32_t errorCode = client->addFriends(123456, {123, 456});
    isErrorCode("[Sync addFriends]", errorCode);

    client->addFriends(123456, {123, 456}, [](int32_t errorCode) {
        isErrorCode("[Async addFriends]", errorCode);
    });

    errorCode = client->deleteFriends(123456, {123, 456});
    isErrorCode("[Sync deleteFriends]", errorCode);

    client->deleteFriends(123456, {123, 456}, [](int32_t errorCode) {
        isErrorCode("[Async deleteFriends]", errorCode);
    });

    set<int64_t> friendUserIds;
    errorCode = client->getFriends(friendUserIds, 123456);
    if (!isErrorCode("[Sync getFriends]", errorCode))
        cout << "friendUserIds.size: " << friendUserIds.size() << endl;

    client->getFriends(123456, [](set<int64_t> friendUserIds, int32_t errorCode) {
        if (!isErrorCode("[Async getFriends]", errorCode))
        cout << "friendUserIds.size: " << friendUserIds.size() << endl;
    });
}

void testGroup(RTMServerClientPtr client)
{
    int32_t errorCode = client->addGroupMembers(123456, {123, 456});
    isErrorCode("[Sync addGroupMembers]", errorCode);

    client->addGroupMembers(123456, {123, 456}, [](int32_t errorCode) {
        isErrorCode("[Async addGroupMembers]", errorCode);
    });

    errorCode = client->deleteGroupMembers(123456, {123, 456});
    isErrorCode("[Sync deleteGroupMembers]", errorCode);

    client->deleteGroupMembers(123456, {123, 456}, [](int32_t errorCode) {
        isErrorCode("[Async deleteGroupMembers]", errorCode);
    });

    errorCode = client->deleteGroup(123456);
    isErrorCode("[Sync deleteGroup]", errorCode);

    client->deleteGroup(123456, [](int32_t errorCode) {
        isErrorCode("[Async deleteGroup]", errorCode);
    });
}

void testRoom(RTMServerClientPtr client)
{
    int32_t errorCode = client->addRoomBan(123, 123456, 10);
    isErrorCode("[Sync addRoomBan]", errorCode);

    client->addRoomBan(123, 123456, 10, [](int32_t errorCode) {
        isErrorCode("[Async addRoomBan]", errorCode);
    });

    errorCode = client->removeRoomBan(123, 123456);
    isErrorCode("[Sync removeRoomBan]", errorCode);

    client->removeRoomBan(123, 123456, [](int32_t errorCode) {
        isErrorCode("[Async removeRoomBan]", errorCode);
    });
}

void testUser(RTMServerClientPtr client)
{
    set<int64_t> onlineUserIds;
    int32_t errorCode = client->getOnlineUsers(onlineUserIds, {123456, 654321});
    if (!isErrorCode("[Sync getOnlineUsers]", errorCode))
        cout << "onlineUserIds.size: " << onlineUserIds.size() << endl;

    client->getOnlineUsers({123456, 654321}, [](set<int64_t> onlineUserIds, int32_t errorCode) {
        if (!isErrorCode("[Async getOnlineUsers]", errorCode))
            cout << "onlineUserIds.size: " << onlineUserIds.size() << endl;
    });

    errorCode = client->addProjectBlack(123456, 10);
    isErrorCode("[Sync addProjectBlack]", errorCode);

    client->addProjectBlack(123456, 10, [](int32_t errorCode) {
        isErrorCode("[Async addProjectBlack]", errorCode);
    });

    errorCode = client->removeProjectBlack(123456);
    isErrorCode("[Sync addRoomMember]", errorCode);

    client->removeProjectBlack(123456, [](int32_t errorCode) {
        isErrorCode("[Async addRoomMember]", errorCode);
    });

    bool isBlack;
    errorCode = client->isProjectBlack(isBlack, 123456);
    if (!isErrorCode("[Sync isProjectBlack]", errorCode))
        cout << "isBlack: " << isBlack << endl;

    client->isProjectBlack(123456, [](bool isBlack, int32_t errorCode) {
        if (!isErrorCode("[Async isProjectBlack]", errorCode))
            cout << "isBlack: " << isBlack << endl;
    });
}

int main(int argc, const char** argv)
{
    RTMServerClientPtr client(new RTMServerClient(11000001, "ef3617e5-e886-4a4e-9eef-7263c0320628", "161.189.171.91:13315"));
    client->setServerPushMonitor(make_shared<MyRTMServerMonitor>());
    
    testListen(client);

    testToken(client);
    testChat(client);
    testFile(client);
    testFriend(client);
    testGroup(client);
    testRoom(client);
    testUser(client);

    while (true)
        sleep(1);

    return 0;
}
