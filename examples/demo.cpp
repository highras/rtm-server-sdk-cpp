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

        if (message.translatedInfo != nullptr) {
            cout << "translatedInfo->sourceLanguage: " << message.translatedInfo->sourceLanguage << " translatedInfo->targetLanguage: " << message.translatedInfo->targetLanguage << " message.translatedInfo->sourceText: " << message.translatedInfo->sourceText << " translatedInfo->targetText: " << message.translatedInfo->targetText << endl;
        }
        if (message.fileInfo != nullptr) {
            cout << "fileInfo->url: " << message.fileInfo->url << " fileInfo->surl: " << message.fileInfo->surl << 
                " fileInfo->language: " << message.fileInfo->language << " fileInfo->size: " << message.fileInfo->size <<
                " fileInfo->duration: " << message.fileInfo->duration << " fileInfo->isRTMAudio: " << message.fileInfo->isRTMAudio << endl;
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

    errorCode = client->addDevicePushOption(123456, P2PMessage, 654321, {66});
    isErrorCode("[Sync addDevicePushOption]", errorCode);

    client->addDevicePushOption(123456, P2PMessage, 654321, {67}, [](int32_t errorCode){
        isErrorCode("[Async addDevicePushOption]", errorCode);
    });

    errorCode = client->removeDevicePushOption(123456, P2PMessage, 654321, {66});
    isErrorCode("[Sync removeDevicePushOption]", errorCode);

    client->removeDevicePushOption(123456, P2PMessage, 654321, {67}, [](int32_t errorCode){
        isErrorCode("[Async removeDevicePushOption]", errorCode);
    });

    map<string, set<int8_t>> p2p;
    map<string, set<int8_t>> group;
    errorCode = client->getDevicePushOption(p2p, group, 123456);
    if (!isErrorCode("[Sync getDevicePushOption]", errorCode))
    {
        cout << "p2p: ";
        for (auto& kv : p2p)
        {
            cout << kv.first << ":" << endl;
            for (auto type : kv.second)
                cout << type << " ";
            cout << endl;
        }
        cout << endl;
        cout << "group: ";
        for (auto& kv : group)
        {
            cout << kv.first << ":" << endl;
            for (auto type : kv.second)
                cout << type << " ";
            cout << endl;
        }
        cout << endl;
    }

    client->getDevicePushOption(123456, [](map<string, set<int8_t>> p2p, map<string, set<int8_t>> group, int32_t errorCode) {
        if (!isErrorCode("[Sync getDevicePushOption]", errorCode))
        {
            cout << "p2p: ";
            for (auto &kv : p2p)
            {
                cout << kv.first << ":" << endl;
                for (auto type : kv.second)
                    cout << type << " ";
                cout << endl;
            }
            cout << endl;
            cout << "group: ";
            for (auto &kv : group)
            {
                cout << kv.first << ":" << endl;
                for (auto type : kv.second)
                    cout << type << " ";
                cout << endl;
            }
            cout << endl;
        }
    });

    errorCode = client->kickout(123456);
    isErrorCode("[Sync kickout]", errorCode);

    client->kickout(123456, [](int32_t errorCode){
        isErrorCode("[Async kickout]", errorCode);
    });
}

void testChat(RTMServerClientPtr client)
{
    int64_t mid;
    int32_t errorCode = client->sendChat(mid, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendChat]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendChat(123, 123456, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendChat]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->sendCmd(mid, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendCmd]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendCmd(123, 123456, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendCmd]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->sendGroupChat(mid, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendGroupChat]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendGroupChat(123, 123456, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupChat]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->sendGroupCmd(mid, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendGroupCmd]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendGroupCmd(123, 123456, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupCmd]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->sendRoomChat(mid, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendRoomChat]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendRoomChat(123, 123456, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomChat]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->sendRoomCmd(mid, 123, 123456, "test message", "");
    if (!isErrorCode("[Sync sendRoomCmd]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendRoomCmd(123, 123456, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomCmd]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->broadcastChat(mid, 111, "test message", "");
    if (!isErrorCode("[Sync broadcastChat]", errorCode))
        cout << "get mid: " << mid << endl;

    client->broadcastChat(111, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async broadcastChat]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    errorCode = client->broadcastCmd(mid, 111, "test message", "");
    if (!isErrorCode("[Sync broadcastCmd]", errorCode))
        cout << "get mid: " << mid << endl;

    client->broadcastCmd(111, "test message", "", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async broadcastCmd]", errorCode))
            cout << "get mid: " << mid << endl;
    });

    HistoryMessageResult result;
    errorCode = client->getGroupChat(result, 123456, true, 20, 0, 0, 0, 0);
    if (!isErrorCode("[Sync getGroupChat]", errorCode))
        cout << "HistoryMessageResult.count: " << result.count << endl;

    client->getGroupChat(123456, true, 20, 0, 0, 0, 0, [](HistoryMessageResult result, int32_t errorCode) {
        if (!isErrorCode("[Async getGroupChat]", errorCode))
            cout << "HistoryMessageResult.count: " << result.count << endl;
    });

    int32_t sender = 0;
    int32_t num = 0;
    errorCode = client->getMessageNum(sender, num, GroupMessage, 123456);
    if (!isErrorCode("[Sync getMessageNum]", errorCode))
        cout << "sender: " << sender << " num: " << num << endl;

    client->getMessageNum(GroupMessage, 123456, [](int32_t sender, int32_t num, int32_t errorCode) {
        if (!isErrorCode("[Async getMessageNum]", errorCode))
            cout << "sender: " << sender << " num: " << num << endl;
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
    
    int64_t mid;
    map<string, string> attrs;
    int32_t errorCode = client->sendFile(mid, 111, 123456, 50, fileData, "audio1.bin", "bin", attrs, 10);
    if (!isErrorCode("[Sync sendFile]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendFile(111, 123456, 50, fileData, "audio1.bin", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendFile]", errorCode))
            cout << "get mid: " << mid << endl;
    }, "bin", attrs, 10);

    errorCode = client->sendGroupFile(mid, 111, 123456, 50, fileData, "audio1.bin", "bin", attrs, 10);
    if (!isErrorCode("[Sync sendGroupFile]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendGroupFile(111, 123456, 50, fileData, "audio1.bin", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendGroupFile]", errorCode))
            cout << "get mid: " << mid << endl;
    }, "bin", attrs, 10);

    errorCode = client->sendRoomFile(mid, 111, 123456, 50, fileData, "audio1.bin", "bin", attrs, 10);
    if (!isErrorCode("[Sync sendRoomFile]", errorCode))
        cout << "get mid: " << mid << endl;

    client->sendRoomFile(111, 123456, 50, fileData, "audio1.bin", [](int64_t mid, int32_t errorCode) {
        if (!isErrorCode("[Async sendRoomFile]", errorCode))
            cout << "get mid: " << mid << endl;
    }, "bin", attrs, 10);
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

    errorCode = client->addGroupBan(0, 123456, 10, 10);
    isErrorCode("[Sync addGroupBan]", errorCode);

    client->addGroupBan(0, 123456, 10, [](int32_t errorCode) {
        isErrorCode("[Async addGroupBan]", errorCode);
    }, 10);

    errorCode = client->removeGroupBan(0, 123456, 10);
    isErrorCode("[Sync removeGroupBan]", errorCode);

    client->removeGroupBan(0, 123456, [](int32_t errorCode) {
        isErrorCode("[Async removeGroupBan]", errorCode);
    }, 10);
}

void testRoom(RTMServerClientPtr client)
{
    int32_t errorCode = client->addRoomMember(123, 123, 10);
    isErrorCode("[Sync addRoomMember]", errorCode);

    client->addRoomMember(123, 456, [](int32_t errorCode) {
        isErrorCode("[Async addRoomMember]", errorCode);
    }, 10);

    set<int64_t> uids;
    errorCode = client->getRoomMembers(uids, 123, 10);
    isErrorCode("[Sync getRoomMembers]", errorCode);
    
    client->getRoomMembers(123, [](set<int64_t> uids, int32_t errorCode) {
        isErrorCode("[Async getRoomMembers]", errorCode);
    }, 10);

    map<string, int32_t> count;
    errorCode = client->getRoomCount(count, 123, 10);
    isErrorCode("[Sync getRoomCount]", errorCode);
    
    client->getRoomCount(123, [](map<string, int32_t> count, int32_t errorCode) {
        isErrorCode("[Async getRoomCount]", errorCode);
    }, 10);

    errorCode = client->deleteRoomMember(123, 123, 10);
    isErrorCode("[Sync deleteRoomMember]", errorCode);

    client->deleteRoomMember(123, 456, [](int32_t errorCode) {
        isErrorCode("[Async deleteRoomMember]", errorCode);
    }, 10);


    errorCode = client->addRoomBan(123, 123456, 10, 10);
    isErrorCode("[Sync addRoomBan]", errorCode);

    client->addRoomBan(123, 123456, 10, [](int32_t errorCode) {
        isErrorCode("[Async addRoomBan]", errorCode);
    }, 10);

    errorCode = client->removeRoomBan(123, 123456, 10);
    isErrorCode("[Sync removeRoomBan]", errorCode);

    client->removeRoomBan(123, 123456, [](int32_t errorCode) {
        isErrorCode("[Async removeRoomBan]", errorCode);
    }, 10);

    errorCode = client->addRoomBan(0, 123456, 10, 10);
    isErrorCode("[Sync addRoomBan]", errorCode);

    client->addRoomBan(0, 123456, 10, [](int32_t errorCode) {
        isErrorCode("[Async addRoomBan]", errorCode);
    }, 10);

    errorCode = client->removeRoomBan(0, 123456, 10);
    isErrorCode("[Sync removeRoomBan]", errorCode);

    client->removeRoomBan(0, 123456, [](int32_t errorCode) {
        isErrorCode("[Async removeRoomBan]", errorCode);
    }, 10);

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
    isErrorCode("[Sync removeProjectBlack]", errorCode);

    client->removeProjectBlack(123456, [](int32_t errorCode) {
        isErrorCode("[Async removeProjectBlack]", errorCode);
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

void testRtc(RTMServerClientPtr client)
{
    int32_t errorCode = client->pullIntoVoiceRoom(123456, {123,456});
    isErrorCode("[Sync pullIntoVoiceRoom]", errorCode);

    client->pullIntoVoiceRoom(123456, {135,246}, [](int32_t errorCode){
        isErrorCode("[Async pullIntoVoiceRoom]", errorCode);
    });

    errorCode = client->inviteUserIntoVoiceRoom(123456, {123,456}, 111);
    isErrorCode("[Sync inviteUserIntoVoiceRoom]", errorCode);

    client->inviteUserIntoVoiceRoom(123456, {135,246}, 111, [](int32_t errorCode){
        isErrorCode("[Async inviteUserIntoVoiceRoom]", errorCode);
    });

    set<int64_t> roomIds;
    errorCode = client->getVoiceRoomList(roomIds);
    if (!isErrorCode("[Sync getVoiceRoomList]", errorCode))
        cout << "rids size: " << roomIds.size() << endl;

    roomIds.clear();
    client->getVoiceRoomList([](set<int64_t> roomIds, int32_t errorCode){
        if(!isErrorCode("[Async getVoiceRoomList]", errorCode))
            cout << "rids size: " << roomIds.size() << endl;
    });

    set<int64_t> uids;
    set<int64_t> managers;
    errorCode = client->getVoiceRoomMembers(uids, managers, 123456);
    if (!isErrorCode("[Sync getVoiceRoomMembers]", errorCode))
        cout << "uids size: " << uids.size() << ", managers size: " << managers.size() << endl;

    uids.clear();
    managers.clear();
    client->getVoiceRoomMembers(123456, [](set<int64_t> uids, set<int64_t> managers, int32_t errorCode){
        if(!isErrorCode("[Async getVoiceRoomMembers]", errorCode))
            cout << "uids size: " << uids.size() << ", managers size: " << managers.size() << endl;
    });
 
    int32_t count = 0;
    errorCode = client->getVoiceRoomMemberCount(count, 123456);
    if (!isErrorCode("[Sync getVoiceRoomMemberCount]", errorCode))
        cout << "count: " << count << endl;

    count = 0;
    client->getVoiceRoomMemberCount(123456, [](int32_t count, int32_t errorCode){
        if(!isErrorCode("[Async getVoiceRoomMemberCount]", errorCode))
            cout << "count: " << count << endl;
    });

    errorCode = client->setVoiceRoomMicStatus(123456, true);
    isErrorCode("[Sync setVoiceRoomMicStatus]", errorCode);

    client->setVoiceRoomMicStatus(123456, false, [](int32_t errorCode){
        isErrorCode("[Async setVoiceRoomMicStatus]", errorCode);
    });

    errorCode = client->kickoutFromVoiceRoom(123, 123456, 111);
    isErrorCode("[Sync kickoutFromVoiceRoom]", errorCode);

    client->kickoutFromVoiceRoom(456, 123456, 111, [](int32_t errorCode){
        isErrorCode("[Async kickoutFromVoiceRoom]", errorCode);
    }); 

    errorCode = client->closeVoiceRoom(123456);
    isErrorCode("[Sync closeVoiceRoom]", errorCode);

    client->closeVoiceRoom(123456, [](int32_t errorCode){
        isErrorCode("[Async closeVoiceRoom]", errorCode);
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
    testRtc(client);

    while (true)
        sleep(1);

    return 0;
}
