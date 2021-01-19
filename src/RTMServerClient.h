#ifndef RTM_SERVER_CLIENT_H
#define RTM_SERVER_CLIENT_H
#include <thread>
#include <mutex>
#include <map>
#include <fstream>
#include <streambuf>
#include "fpnn.h"
#include "md5.h"
#include "hex.h"
#include "FPLog.h"
#include "TimeUtil.h"
#include "RTMProcessor.h"
#include "RTMServerPushMonitor.h"
#include "RTMServerConfig.h"
#include "RTMStructures.h"
#include "RTMErrorCode.h"
#include "MidGenerator.h"

namespace rtm 
{
    using namespace std;
    using namespace fpnn;

    class RTMServerClient
    {

        class ListenStatusInfo
        {
        public:
            bool allP2P;
            bool allGroups;
            bool allRooms;
            bool allEvents;
            set<int64_t> userIds;
            set<int64_t> groupIds;
            set<int64_t> roomIds;
            set<string> events;

            ListenStatusInfo(): allP2P(false), allGroups(false), allRooms(false), allEvents(false) {}
        };

        class RegressiveStrategy
        {
        public:
            int32_t connectFailedMaxIntervalMilliseconds = 1500;
            int32_t startConnectFailedCount = 5;  
            int32_t firstIntervalSeconds = 2;
            int32_t maxIntervalSeconds = 120;
            int32_t linearRegressiveCount = 5;

            RegressiveStrategy(): 
                connectFailedMaxIntervalMilliseconds(1500), 
                startConnectFailedCount(5), firstIntervalSeconds(2), 
                maxIntervalSeconds(120), linearRegressiveCount(5) {}
        };

        class RegressiveStatus
        {
        public:
            int32_t connectFailedCount;
            int32_t regressiveConnectInterval;
        };

    public:
        RTMServerClient(int32_t pid, const string& secret, const string& endpoint);
        ~RTMServerClient();

        bool connect();
        bool connected();
        const string& endpoint();
        void close();
        void setQuestTimeout(int seconds);
        void setAutoReconnect(bool autoReconnect);
        void setServerPushMonitor(shared_ptr<RTMServerPushMonitor> serverMonitor);
        void setRegressiveConnectStrategy(RegressiveStrategy strategy);

        bool enableEncryptorByDerData(const string &derData, bool packageMode = true, bool reinforce = false);
        bool enableEncryptorByPemData(const string &PemData, bool packageMode = true, bool reinforce = false);
        bool enableEncryptorByDerFile(const char *derFilePath, bool packageMode = true, bool reinforce = false);
        bool enableEncryptorByPemFile(const char *pemFilePath, bool packageMode = true, bool reinforce = false);
        void enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode = true, bool reinforce = false);

        int32_t sendChat(int64_t& mid, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
        void sendChat(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendCmd(int64_t& mid, int64_t fromUid, int64_t toUid, const string& message, const string& attrs, int32_t timeout = 0);
        void sendCmd(int64_t fromUid, int64_t toUid, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendMessage(int64_t& mid, int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
        void sendMessage(int64_t fromUid, int64_t toUid, int8_t mtype, const string& message, const string& attrs, 
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendMessages(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
        void sendMessages(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendChats(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
        void sendChats(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendCmds(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, int32_t timeout = 0);
        void sendCmds(int64_t fromUid, const set<int64_t>& toUids, const string& message, const string& attrs, std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendGroupMessage(int64_t& mid, int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
        void sendGroupMessage(int64_t fromUid, int64_t groupId, int8_t mtype, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendGroupChat(int64_t& mid, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
        void sendGroupChat(int64_t fromUid, int64_t groupId, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendGroupCmd(int64_t& mid, int64_t fromUid, int64_t groupId, const string& message, const string& attrs, int32_t timeout = 0);
        void sendGroupCmd(int64_t fromUid, int64_t groupId, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendRoomMessage(int64_t& mid, int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
        void sendRoomMessage(int64_t fromUid, int64_t roomId, int8_t mtype, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendRoomChat(int64_t& mid, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
        void sendRoomChat(int64_t fromUid, int64_t roomId, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t sendRoomCmd(int64_t& mid, int64_t fromUid, int64_t roomId, const string& message, const string& attrs, int32_t timeout = 0);
        void sendRoomCmd(int64_t fromUid, int64_t roomId, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t broadcastMessage(int64_t& mid, int64_t fromUid, int8_t mtype, const string& message, const string& attrs, int32_t timeout = 0);
        void broadcastMessage(int64_t fromUid, int8_t mtype, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t broadcastChat(int64_t& mid, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
        void broadcastChat(int64_t fromUid, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t broadcastCmd(int64_t& mid, int64_t fromUid, const string& message, const string& attrs, int32_t timeout = 0);
        void broadcastCmd(int64_t fromUid, const string& message, const string& attrs,
                std::function<void (int64_t mid, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout = 0);
        void addFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteFriends(int64_t userId, const set<int64_t>& friends, int32_t timeout = 0);
        void deleteFriends(int64_t userId, const set<int64_t>& friends, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getFriends(set<int64_t>& friendUserIds, int64_t userId, int32_t timeout = 0);
        void getFriends(int64_t userId, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isFriend(bool& isFriend, int64_t userId, int64_t otherUserId, int32_t timeout = 0);
        void isFriend(int64_t userId, int64_t otherUserId, std::function<void (bool isFriend, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isFriends(set<int64_t>& friendUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout = 0);
        void isFriends(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> friendUserIds, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout = 0);
        void addBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteBlacks(int64_t userId, const set<int64_t>& blacks, int32_t timeout = 0);
        void deleteBlacks(int64_t userId, const set<int64_t>& blacks, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isBlack(bool& isBlack, int64_t userId, int64_t otherUserId, int32_t timeout = 0);
        void isBlack(int64_t userId, int64_t otherUserId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isBlacks(set<int64_t>& blackUserIds, int64_t userId, const set<int64_t>& otherUserIds, int32_t timeout = 0);
        void isBlacks(int64_t userId, const set<int64_t>& otherUserIds, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getBlacks(set<int64_t>& blackUserIds, int64_t userId, int32_t timeout = 0);
        void getBlacks(int64_t userId, std::function<void (set<int64_t> blackUserIds, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout = 0);
        void addGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, int32_t timeout = 0);
        void deleteGroupMembers(int64_t groupId, const set<int64_t>& userIds, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteGroup(int64_t groupId, int32_t timeout = 0);
        void deleteGroup(int64_t groupId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getGroupMembers(set<int64_t>& members, int64_t groupId, int32_t timeout = 0);
        void getGroupMembers(int64_t groupId, std::function<void (set<int64_t> members, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isGroupMember(bool& isMember, int64_t groupId, int64_t userId, int32_t timeout = 0);
        void isGroupMember(int64_t groupId, int64_t userId, std::function<void (bool isMember, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getUserGroups(set<int64_t>& groupIds, int64_t userId, int32_t timeout = 0);
        void getUserGroups(int64_t userId, std::function<void (set<int64_t> groupIds, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getToken(string& token, int64_t userId, int32_t timeout = 0);
        void getToken(int64_t userId, std::function<void (string token, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getOnlineUsers(set<int64_t>& onlineUserIds, const set<int64_t>& userIds, int32_t timeout = 0);
        void getOnlineUsers(const set<int64_t>& userIds, std::function<void (set<int64_t> onlineUserIds, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, int32_t timeout = 0);
        void addGroupBan(int64_t groupId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeGroupBan(int64_t groupId, int64_t userId, int32_t timeout = 0);
        void removeGroupBan(int64_t groupId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, int32_t timeout = 0);
        void addRoomBan(int64_t roomId, int64_t userId, int32_t banTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeRoomBan(int64_t roomId, int64_t userId, int32_t timeout = 0);
        void removeRoomBan(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addProjectBlack(int64_t userId, int32_t blackTime, int32_t timeout = 0);
        void addProjectBlack(int64_t userId, int32_t blackTime, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeProjectBlack(int64_t userId, int32_t timeout = 0);
        void removeProjectBlack(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isBanOfGroup(bool& isBan, int64_t groupId, int64_t userId, int32_t timeout = 0);
        void isBanOfGroup(int64_t groupId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isBanOfRoom(bool& isBan, int64_t roomId, int64_t userId, int32_t timeout = 0);
        void isBanOfRoom(int64_t roomId, int64_t userId, std::function<void (bool isBan, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t isProjectBlack(bool& isBlack, int64_t userId, int32_t timeout = 0);
        void isProjectBlack(int64_t userId, std::function<void (bool isBlack, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t fileToken(string& token, string& endpoint, int64_t from, FileTokenType fileType, int64_t toId, int32_t timeout = 0);
        int32_t fileToken(string& token, string& endpoint, int64_t from, FileTokenType fileType, const set<int64_t>& toIds, int32_t timeout = 0);
        void fileToken(int64_t from, FileTokenType fileType, int64_t toId, std::function<void (string token, string endpoint, int32_t errorCode)> callback, int32_t timeout = 0);
        void fileToken(int64_t from, FileTokenType fileType, const set<int64_t>& toIds, std::function<void (string token, string endpoint, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getGroupMessage(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
        void getGroupMessage(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getGroupChat(HistoryMessageResult& result, int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
        void getGroupChat(int64_t groupId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getRoomMessage(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
        void getRoomMessage(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getRoomChat(HistoryMessageResult& result, int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
        void getRoomChat(int64_t roomId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getBroadcastMessage(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, int32_t timeout = 0);
        void getBroadcastMessage(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getBroadcastChat(HistoryMessageResult& result, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, int32_t timeout = 0);
        void getBroadcastChat(bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int64_t uid, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getP2PMessage(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, int32_t timeout = 0);
        void getP2PMessage(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, const set<int8_t>& mtypes, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getP2PChat(HistoryMessageResult& result, int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, int32_t timeout = 0);
        void getP2PChat(int64_t userId, int64_t otherUserId, bool desc, int16_t count, int64_t beginMsec, int64_t endMsec, int64_t lastId, std::function<void (HistoryMessageResult result, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addRoomMember(int64_t roomId, int64_t userId, int32_t timeout = 0);
        void addRoomMember(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteRoomMember(int64_t roomId, int64_t userId, int32_t timeout = 0);
        void deleteRoomMember(int64_t roomId, int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
        void addListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
        void removeListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, int32_t timeout = 0);
        int32_t setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, int32_t timeout = 0);
        void setListen(const set<int64_t>& groupIds, const set<int64_t>& roomIds, const set<int64_t>& userIds, const set<string>& events, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        void setListen(bool allGroup, bool allRoom, bool allP2P, bool allEvent, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addDevice(int64_t userId, const string& appType, const string& deviceToken, int32_t timeout = 0);
        void addDevice(int64_t userId, const string& appType, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeDevice(int64_t userId, const string& deviceToken, int32_t timeout = 0);
        void removeDevice(int64_t userId, const string& deviceToken, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t addDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, int32_t timeout = 0);
        void addDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, int32_t timeout = 0);
        void removeDevicePushOption(int64_t userId, int8_t type, int64_t xid, const set<int8_t>& mtype, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getDevicePushOption(map<string, set<int8_t>>& p2p, map<string, set<int8_t>>& group, int64_t userId, int32_t timeout = 0);
        void getDevicePushOption(int64_t userId, std::function<void (map<string, set<int8_t>> p2p, map<string, set<int8_t>> group, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t removeToken(int64_t userId, int32_t timeout = 0);
        void removeToken(int64_t userId, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
        void deleteMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
        void deleteChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t kickout(int64_t userId, const string& ce, int32_t timeout = 0);
        void kickout(int64_t userId, const string& ce, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        bool loadFile(const string& filePath, string& fileData);
        int32_t sendFile(int64_t& mid, int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        void sendFile(int64_t fromUid, int64_t toUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        int32_t sendFiles(int64_t& mid, int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        void sendFiles(int64_t fromUid, const set<int64_t>& toUids, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        int32_t sendGroupFile(int64_t& mid, int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        void sendGroupFile(int64_t fromUid, int64_t groupId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        int32_t sendRoomFile(int64_t& mid, int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        void sendRoomFile(int64_t fromUid, int64_t roomId, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        int32_t broadcastFile(int64_t& mid, int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        void broadcastFile(int64_t fromUid, int8_t mtype, const string& fileData, const string& fileName, std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 0);
        int32_t translate(TranslatedInfo& translatedInfo, const string& text, TranslateLanguage destinationLanguage, TranslateLanguage sourceLanguage = None, TranslateType type = Chat, ProfanityType profanity = Off, int64_t userId = 0, int32_t timeout = 0);
        void translate(const string& text, TranslateLanguage destinationLanguage, std::function<void (TranslatedInfo translatedInfo, int32_t errorCode)> callback, TranslateLanguage sourceLanguage = None, TranslateType type = Chat, ProfanityType profanity = Off, int64_t userId = 0, int32_t timeout = 0);
        int32_t profanity(string& resultText, vector<string>& classification, const string& text, bool classify = false, int64_t userId = 0, int32_t timeout = 0);
        void profanity(const string& text, std::function<void (string resultText, vector<string> classification, int32_t errorCode)> callback, bool classify = false, int64_t userId = 0, int32_t timeout = 0);
        int32_t setUserInfo(int64_t userId, string* oinfo, string* pinfo, int32_t timeout = 0);
        void setUserInfo(int64_t userId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getUserInfo(string& oinfo, string& pinfo, int64_t userId, int32_t timeout = 0);
        void getUserInfo(int64_t userId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getUserOpenInfo(map<string, string>& info, const set<int64_t>& userIds, int32_t timeout = 0);
        void getUserOpenInfo(const set<int64_t>& userIds, std::function<void (map<string, string> info, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, int32_t timeout = 0);
        void setGroupInfo(int64_t groupId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getGroupInfo(string& oinfo, string& pinfo, int64_t groupId, int32_t timeout = 0);
        void getGroupInfo(int64_t groupId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, int32_t timeout = 0);
        void setRoomInfo(int64_t roomId, string* oinfo, string* pinfo, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getRoomInfo(string& oinfo, string& pinfo, int64_t roomId, int32_t timeout = 0);
        void getRoomInfo(int64_t roomId, std::function<void (string oinfo, string pinfo, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getRoomMembers(set<int64_t>& uids, int64_t roomid, int32_t timeout = 0);
        void getRoomMembers(int64_t roomId, std::function<void (set<int64_t> uids, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getRoomCount(map<string, int32_t>& count, int64_t roomid, int32_t timeout = 0);
        void getRoomCount(int64_t roomId, std::function<void (map<string, int32_t> count, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getMessage(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
        void getMessage(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t getMessageNum(int32_t& senderId, int32_t& messageNum, MessageCategory messageCategory, int64_t userId, set<int8_t> messageTypes = set<int8_t>(), int64_t begin = 0, int64_t end = 0, int32_t timeout = 0);
        void getMessageNum(MessageCategory messageCategory, int64_t userId, std::function<void (int32_t senderId, int32_t messageNum, int32_t errorCode)> callback, set<int8_t> messageTypes = set<int8_t>(), int64_t begin = 0, int64_t end = 0, int32_t timeout = 0);
        int32_t getChat(RetrievedMessage& retrievedMessage, int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, int32_t timeout = 0);
        void getChat(int64_t mid, int64_t fromUid, int64_t toId, MessageCategory messageCategory, std::function<void (RetrievedMessage retrievedMessage, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t dataSet(int64_t userId, const string& key, const string& value, int32_t timeout = 0);
        void dataSet(int64_t userId, const string& key, const string& value, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t dataDelete(int64_t userId, const string& key, int32_t timeout = 0);
        void dataDelete(int64_t userId, const string& key, std::function<void (int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t dataGet(string& value, int64_t userId, const string& key, int32_t timeout = 0);
        void dataGet(int64_t userId, const string& key, std::function<void (string value, int32_t errorCode)> callback, int32_t timeout = 0);
        int32_t speechToText(string& resultText, string& resultLanguage, const string& audio, int32_t autoType, const string& language, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);
        void speechToText(const string& audio, int32_t audioType, const string& language, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);
        int32_t textCheck(TextCheckResult& result, const string& text, int64_t userId = 0, int32_t timeout = 120);
        void textCheck(const string& text, std::function<void (TextCheckResult result, int32_t errorCode)> callback, int64_t userId = 0, int32_t timeout = 120);
        int32_t imageCheck(CheckResult& result, const string& image, int32_t imageType, int64_t userId = 0, int32_t timeout = 120);
        void imageCheck(const string& image, int32_t imageType, std::function<void (CheckResult result, int32_t errorCode)> callback, int64_t userId = 0, int32_t timeout = 120);
        int32_t audioCheck(CheckResult& result, const string& audio, int32_t audioType, const string& language, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);
        void audioCheck(const string& audio, int32_t audioType, const string& language, std::function<void (CheckResult result, int32_t errorCode)> callback, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);
        int32_t videoCheck(CheckResult& result, const string& video, int32_t videoType, const string& videoName, int64_t userId = 0, int32_t timeout = 120);
        void videoCheck(const string& video, int32_t videoType, const string& videoName, std::function<void (CheckResult result, int32_t errorCode)> callback, int64_t userId = 0, int32_t timeout = 120);

        static void buildFileInfo(RTMMessage& message);
        static void parseFileMessage(RTMMessage& message);
        static void parseFileAttrs(RTMMessage& message);
        static bool checkFileMessageType(int8_t messageType);
    private:
        void _connectedCallback(const ConnectionInfo& connInfo);
        void _closedCallback(const ConnectionInfo& connInfo, bool closeByError);
        string _calcMD5(const string& content);
        bool _checkAnswerError(FPAnswerPtr answer, QuestResult& result, int32_t errorCode = -1);
        void _makeSignAndSalt(int32_t ts, const string& cmd, string& sign, int64_t& salt);
        FPQuestPtr _getSendMessageQuest(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, int64_t& mid);
        FPQuestPtr _getSendMessagesQuest(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, int64_t& mid);
        FPQuestPtr _getSendGroupMessageQuest(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, int64_t& mid);
        FPQuestPtr _getSendRoomMessageQuest(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, int64_t& mid);
        FPQuestPtr _getBroadcastMessageQuest(int64_t from, int8_t mtype, const string& message, const string& attrs, int64_t& mid);
        FPQuestPtr _getAddFriendsQuest(int64_t uid, const set<int64_t>& friends);
        FPQuestPtr _getDeleteFriendsQuest(int64_t uid, const set<int64_t>& friends);
        FPQuestPtr _getGetFriendsQuest(int64_t uid);
        FPQuestPtr _getIsFriendQuest(int64_t uid, int64_t fuid);
        FPQuestPtr _getIsFriendsQuest(int64_t uid, const set<int64_t>& fuids);
        FPQuestPtr _getAddBlacksQuest(int64_t uid, const set<int64_t>& blacks);
        FPQuestPtr _getDeleteBlacksQuest(int64_t uid, const set<int64_t>& blacks);
        FPQuestPtr _getIsBlackQuest(int64_t uid, int64_t buid);
        FPQuestPtr _getGetBlacksQuest(int64_t uid);
        FPQuestPtr _getIsBlacksQuest(int64_t uid, const set<int64_t>& buids);
        FPQuestPtr _getAddGroupMembersQuest(int64_t gid, const set<int64_t>& uids);
        FPQuestPtr _getDeleteGroupMembersQuest(int64_t gid, const set<int64_t>& uids);
        FPQuestPtr _getDeleteGroupQuest(int64_t gid);
        FPQuestPtr _getGetGroupMembersQuest(int64_t gid);
        FPQuestPtr _getIsGroupMemberQuest(int64_t gid, int64_t uid);
        FPQuestPtr _getGetUserGroupsQuest(int64_t uid);
        FPQuestPtr _getGetTokenQuest(int64_t uid);
        FPQuestPtr _getGetOnlineUsersQuest(const set<int64_t>& uids);
        FPQuestPtr _getAddGroupBanQuest(int64_t gid, int64_t uid, int32_t btime);
        FPQuestPtr _getRemoveGroupBanQuest(int64_t gid, int64_t uid);
        FPQuestPtr _getAddRoomBanQuest(int64_t rid, int64_t uid, int32_t btime);
        FPQuestPtr _getRemoveRoomBanQuest(int64_t rid, int64_t uid);
        FPQuestPtr _getAddProjectBlackQuest(int64_t uid, int32_t btime);
        FPQuestPtr _getRemoveProjectBlackQuest(int64_t uid);
        FPQuestPtr _getIsBanOfGroupQuest(int64_t gid, int64_t uid);
        FPQuestPtr _getIsBanOfRoomQuest(int64_t rid, int64_t uid);
        FPQuestPtr _getIsProjectBlackQuest(int64_t uid);
        FPQuestPtr _getFileTokenQuest(const SendFileInfo& info);
        FPQuestPtr _getGetGroupMessageQuest(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes, int64_t uid);
        FPQuestPtr _getGetRoomMessageQuest(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes, int64_t uid);
        FPQuestPtr _getGetBroadcastMessageQuest(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes, int64_t uid);
        FPQuestPtr _getGetP2PMessageQuest(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, const set<int8_t>& mtypes);
        FPQuestPtr _getAddRoomMemberQuest(int64_t rid, int64_t uid);
        FPQuestPtr _getDeleteRoomMemberQuest(int64_t rid, int64_t uid);
        FPQuestPtr _getAddListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, const set<int64_t>& uids, const set<string>& events);
        FPQuestPtr _getRemoveListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, const set<int64_t>& uids, const set<string>& events);
        FPQuestPtr _getSetListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, const set<int64_t>& uids, const set<string>& events);
        FPQuestPtr _getSetListenQuest(bool allGroup, bool allRoom, bool allP2P, bool allEvent);
        FPQuestPtr _getAddDeviceQuest(int64_t uid, const string& appType, const string& deviceToken);
        FPQuestPtr _getRemoveDeviceQuest(int64_t uid, const string& deviceToken);
        FPQuestPtr _getAddOptionQuest(int64_t uid, int8_t type, int64_t xid, const set<int8_t>& mtype);
        FPQuestPtr _getRemoveOptionQuest(int64_t uid, int8_t type, int64_t xid, const set<int8_t>& mtype);
        FPQuestPtr _getGetOptionQuest(int64_t uid);
        FPQuestPtr _getRemoveTokenQuest(int64_t uid);
        FPQuestPtr _getDeleteMessageQuest(int64_t mid, int64_t from, int64_t xid, int8_t type);
        FPQuestPtr _getKickoutQuest(int64_t uid, const string& ce);
        FPQuestPtr _getSendFileQuest(const string& token, int64_t from, SendFileInfo info, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs, int64_t& mid);
        int32_t _sendFileProcess(int64_t& mid, FileTokenType tokenType, int64_t from, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, const string& fileName, const string& fileExtension, const map<string, string>& attrs = map<string, string>(), int32_t timeout = 120);
        void _sendFileProcess(FileTokenType tokenType, int64_t from, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, const string& fileName, 
        std::function<void (int64_t mid, int32_t errorCode)> callback, const string& fileExtension = "", const map<string, string>& attrs = map<string, string>(), int32_t timeout = 120);
        FPQuestPtr _getTranslateQuest(const string& text, const string& dst, const string& src, const string& type, const string& profanity, int64_t uid);
        FPQuestPtr _getProfanityQuest(const string& text, bool classify, int64_t uid);
        FPQuestPtr _getSetUserInfoQuest(int64_t uid, string* oinfo, string* pinfo);
        FPQuestPtr _getGetUserInfoQuest(int64_t uid);
        FPQuestPtr _getGetUserOpenInfoQuest(const set<int64_t>& uids);
        FPQuestPtr _getSetGroupInfoQuest(int64_t gid, string* oinfo, string* pinfo);
        FPQuestPtr _getGetGroupInfoQuest(int64_t gid);
        FPQuestPtr _getSetRoomInfoQuest(int64_t rid, string* oinfo, string* pinfo);
        FPQuestPtr _getGetRoomInfoQuest(int64_t rid);
        FPQuestPtr _getGetRoomMembersQuest(int64_t rid);
        FPQuestPtr _getGetRoomCountQuest(int64_t rid);
        FPQuestPtr _getGetMessageQuest(int64_t mid, int64_t from, int64_t xid, int8_t type);
        FPQuestPtr _getGetMessageNumQuest(int8_t type, int64_t xid, set<int8_t> mtypes, int64_t begin, int64_t end);
        FPQuestPtr _getSpeechToTextQuest(const string& audio, int32_t audioType, const string& language, const string& codec, int32_t sampleRate, int64_t userId);
        FPQuestPtr _getTextCheckQuest(const string& text, int64_t userId);
        FPQuestPtr _getImageCheckQuest(const string& image, int32_t imageType, int64_t userId);
        FPQuestPtr _getAudioCheckQuest(const string& audio, int32_t audioType, const string& language, const string& codec, int32_t sampleRate, int64_t userId);
        FPQuestPtr _getVideoCheckQuest(const string& video, int32_t videoType, const string& videoName, int64_t userId);
        bool _checkCheckType(int32_t type);
        string _getSendFileType(FileTokenType sendType);
        void _checkRoutine();
        void _routine();
        void _checkFileGateClients();
        TCPClientPtr _fecthFileGateClient(string endpoint);
        void _activeFileGateClient(string endpoint, TCPClientPtr client);
        void _updateTimeout(int32_t& timeout, int64_t& lastActionTimestamp);
        int32_t _fileTokenAction(string& token, string& endpoint, int64_t from, FileTokenType fileType, int64_t toId, const set<int64_t>& toIds, int32_t timeout);
        void _fileTokenAction(int64_t from, FileTokenType fileType, int64_t toId, const set<int64_t>& toIds, std::function<void (string token, string endpoint, int32_t errorCode)> callback, int32_t timeout);
        HistoryMessageResult _buildHistoryMessageResult(int64_t toId, FPAnswerPtr answer, bool isP2P);
        void _getCommonMessage(vector<struct CommonMessage>& messageList, FPAReader& reader, bool isP2P);
        void _adjustHistoryMessageResultForP2PMessage(HistoryMessageResult& result, int64_t selfUid, int64_t peerUserUid);
        string _buildFileAttrs(const string& sign, const string& fileName, const string& fileExtension, const map<string, string>& attrs);
        RetrievedMessage _buildRetrievedMessage(FPAnswerPtr answer);
        FPQuestPtr _getDataSetQuest(int64_t uid, const string& key, const string& value);
        FPQuestPtr _getDataDeleteQuest(int64_t uid, const string& key);
        FPQuestPtr _getDataGetQuest(int64_t uid, const string& key);
        void _listenStatusRestoration();
        void _tryReconnect();
        void _regressiveReconnect();

        bool _stop;
        TCPClientPtr _client;
        int32_t _pid;
        string _secret;
        bool _autoReconnect;
        shared_ptr<RTMProcessor> _processor;
        map<string, map<TCPClientPtr, long> > _fileClientMap;
        mutex _fileClientMapLock;
        thread _routineThread;
        bool _routineStart;
        mutex _opLock;
        ListenStatusInfo _listenStatusInfo;
        RegressiveStrategy _regressiveStrategy;
        RegressiveStatus _regressiveStatus;
        bool _isReconnect;
        bool _canReconnect;
        int64_t _lastConnectTime;
        int64_t _lastCloseTime;
        bool _requireClose;
        int32_t _questTimeout;
    };

    typedef shared_ptr<RTMServerClient> RTMServerClientPtr;
}

#endif
