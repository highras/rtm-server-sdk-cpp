#ifndef RTM_SERVER_CLIENT_H
#define RTM_SERVER_CLIENT_H
#include "fpnn.h"
#include "RTMProcessor.h"
#include "RTMServerMonitor.h"
#include "QuestResult.h"

using namespace std;
using namespace fpnn;

namespace rtm 
{

    struct FileTokenInfo
    {
        int64_t toUid;
        set<int64_t> toUids;
        int64_t groupId;
        int64_t roomId;

        FileTokenInfo(): toUid(0), groupId(0), roomId(0) {}
    };

    class RTMServerClient
    {
    public:
        RTMServerClient(int32_t pid, const string& secret, const string& endpoint, bool reconnect, int32_t timeout, 
                int32_t duplicateCacheSize = 100000);
        ~RTMServerClient();

        bool connected();
        const string& endpoint();
        void setQuestTimeout(int seconds);
        void setAutoReconnect(bool autoReconnect);
        void setServerMonitor(shared_ptr<RTMServerMonitor> serverMonitor);

        bool enableEncryptorByDerData(const string &derData, bool packageMode = true, bool reinforce = false);
        bool enableEncryptorByPemData(const string &PemData, bool packageMode = true, bool reinforce = false);
        bool enableEncryptorByDerFile(const char *derFilePath, bool packageMode = true, bool reinforce = false);
        bool enableEncryptorByPemFile(const char *pemFilePath, bool packageMode = true, bool reinforce = false);
        void enableEncryptor(const string& curve, const string& peerPublicKey, bool packageMode = true, bool reinforce = false);

        SendMessageResult sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0);
        void sendMessage(int64_t from, int64_t to, int8_t mtype, const string& message, const string& attrs, 
                std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendMessageResult sendMessages(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0);
        void sendMessages(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& message, const string& attrs,
                std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendMessageResult sendGroupMessage(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0);
        void sendGroupMessage(int64_t from, int64_t gid, int8_t mtype, const string& message, const string& attrs,
                std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendMessageResult sendRoomMessage(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0);
        void sendRoomMessage(int64_t from, int64_t rid, int8_t mtype, const string& message, const string& attrs,
                std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendMessageResult broadcastMessage(int64_t from, int8_t mtype, const string& message, const string& attrs, int64_t mid = 0, int32_t timeout = 0);
        void broadcastMessage(int64_t from, int8_t mtype, const string& message, const string& attrs,
                std::function<void (SendMessageResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        QuestResult addFriends(int64_t uid, const set<int64_t>& friends, int32_t timeout = 0);
        void addFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult deleteFriends(int64_t uid, const set<int64_t>& friends, int32_t timeout = 0);
        void deleteFriends(int64_t uid, const set<int64_t>& friends, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        GetFriendsResult getFriends(int64_t uid, int32_t timeout = 0);
        void getFriends(int64_t uid, std::function<void (GetFriendsResult result)> callback, int32_t timeout = 0);
        IsFriendResult isFriend(int64_t uid, int64_t fuid, int32_t timeout = 0);
        void isFriend(int64_t uid, int64_t fuid, std::function<void (IsFriendResult result)> callback, int32_t timeout = 0);
        IsFriendsResult isFriends(int64_t uid, const set<int64_t>& fuids, int32_t timeout = 0);
        void isFriends(int64_t uid, const set<int64_t>& fuids, std::function<void (IsFriendsResult result)> callback, int32_t timeout = 0);
        QuestResult addGroupMembers(int64_t gid, const set<int64_t>& uids, int32_t timeout = 0);
        void addGroupMembers(int64_t gid, const set<int64_t>& uids, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult deleteGroupMembers(int64_t gid, const set<int64_t>& uids, int32_t timeout = 0);
        void deleteGroupMembers(int64_t gid, const set<int64_t>& uids, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult deleteGroup(int64_t gid, int32_t timeout = 0);
        void deleteGroup(int64_t gid, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        GetGroupMembersResult getGroupMembers(int64_t gid, int32_t timeout = 0);
        void getFriends(int64_t uid, std::function<void (GetGroupMembersResult result)> callback, int32_t timeout = 0);
        IsGroupMemberResult isGroupMember(int64_t gid, int64_t uid, int32_t timeout = 0);
        void isGroupMember(int64_t gid, int64_t uid, std::function<void (IsGroupMemberResult result)> callback, int32_t timeout = 0);
        GetUserGroupsResult getUserGroups(int64_t uid, int32_t timeout = 0);
        void getUserGroups(int64_t uid, std::function<void (GetUserGroupsResult result)> callback, int32_t timeout = 0);
        GetTokenResult getToken(int64_t uid, int32_t timeout = 0);
        void getToken(int64_t uid, std::function<void (GetTokenResult result)> callback, int32_t timeout = 0);
        GetOnlineUsersResult getOnlineUsers(const set<int64_t>& uids, int32_t timeout = 0);
        void getOnlineUsers(const set<int64_t>& uids, std::function<void (GetOnlineUsersResult result)> callback, int32_t timeout = 0);
        QuestResult addGroupBan(int64_t gid, int64_t uid, int32_t btime, int32_t timeout = 0);
        void addGroupBan(int64_t gid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult removeGroupBan(int64_t gid, int64_t uid, int32_t timeout = 0);
        void removeGroupBan(int64_t gid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult addRoomBan(int64_t rid, int64_t uid, int32_t btime, int32_t timeout = 0);
        void addRoomBan(int64_t rid, int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult removeRoomBan(int64_t rid, int64_t uid, int32_t timeout = 0);
        void removeRoomBan(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult addProjectBlack(int64_t uid, int32_t btime, int32_t timeout = 0);
        void addProjectBlack(int64_t uid, int32_t btime, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult removeProjectBlack(int64_t uid, int32_t timeout = 0);
        void removeProjectBlack(int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        IsBanOfGroupResult isBanOfGroup(int64_t gid, int64_t uid, int32_t timeout = 0);
        void isBanOfGroup(int64_t gid, int64_t uid, std::function<void (IsBanOfGroupResult result)> callback, int32_t timeout = 0);
        IsBanOfRoomResult isBanOfRoom(int64_t rid, int64_t uid, int32_t timeout = 0);
        void isBanOfRoom(int64_t rid, int64_t uid, std::function<void (IsBanOfRoomResult result)> callback, int32_t timeout = 0);
        IsProjectBlackResult isProjectBlack(int64_t uid, int32_t timeout = 0);
        void isProjectBlack(int64_t uid, std::function<void (IsProjectBlackResult result)> callback, int32_t timeout = 0);
        FileTokenResult fileToken(int64_t from, const string& cmd, const FileTokenInfo& info, int32_t timeout = 0);
        void fileToken(int64_t from, const string& cmd, const FileTokenInfo& info, std::function<void (FileTokenResult result)> callback, int32_t timeout = 0);
        GetGroupMessageResult getGroupMessage(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0);
        void getGroupMessage(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetGroupMessageResult result)> callback, int32_t timeout = 0);
        GetRoomMessageResult getRoomMessage(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0);
        void getRoomMessage(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetRoomMessageResult result)> callback, int32_t timeout = 0);
        GetBroadcastMessageResult getBroadcastMessage(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0);
        void getBroadcastMessage(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetBroadcastMessageResult result)> callback, int32_t timeout = 0);
        GetP2PMessageResult getP2PMessage(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, int32_t timeout = 0);
        void getP2PMessage(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId, std::function<void (GetP2PMessageResult result)> callback, int32_t timeout = 0);
        QuestResult addRoomMember(int64_t rid, int64_t uid, int32_t timeout = 0);
        void addRoomMember(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult deleteRoomMember(int64_t rid, int64_t uid, int32_t timeout = 0);
        void deleteRoomMember(int64_t rid, int64_t uid, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult addListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, int32_t timeout = 0);
        void addListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult removeListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, int32_t timeout = 0);
        void removeListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult setListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all, int32_t timeout = 0);
        void setListen(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult addDevice(int64_t uid, const string& appType, const string& deviceToken, int32_t timeout = 0);
        void addDevice(int64_t uid, const string& appType, const string& deviceToken, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult removeDevice(int64_t uid, const string& deviceToken, int32_t timeout = 0);
        void removeDevice(int64_t uid, const string& deviceToken, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult deleteMessage(int64_t mid, int64_t from, int64_t xid, int8_t type, int32_t timeout = 0);
        void deleteMessage(int64_t mid, int64_t from, int64_t xid, int8_t type, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        QuestResult kickout(int64_t uid, const string& ce, int32_t timeout = 0);
        void kickout(int64_t uid, const string& ce, std::function<void (QuestResult result)> callback, int32_t timeout = 0);
        bool loadFile(const string& filePath, string& fileData);
        SendFileResult sendFile(int64_t from, int64_t to, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0);
        void sendFile(int64_t from, int64_t to, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendFileResult sendFiles(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0);
        void sendFiles(int64_t from, const set<int64_t>& tos, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendFileResult sendGroupFile(int64_t from, int64_t gid, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0);
        void sendGroupFile(int64_t from, int64_t gid, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendFileResult sendRoomFile(int64_t from, int64_t rid, int8_t mtype, const string& fileData, int64_t mid, int32_t timeout = 0);
        void sendRoomFile(int64_t from, int64_t rid, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0);
        SendFileResult broadcastFile(int64_t from, int8_t mtype, const string& fileData, int64_t mid = 0, int32_t timeout = 0);
        void broadcastFile(int64_t from, int8_t mtype, const string& fileData, std::function<void (SendFileResult result)> callback, int64_t mid = 0, int32_t timeout = 0);

    private:
        string _calcMD5(const string& content);
        bool _checkAnswerError(FPAnswerPtr answer, QuestResult& result, int32_t errorCode = -1);
        void _makeSignAndSalt(string& sign, int64_t& salt);
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
        FPQuestPtr _getFileTokenQuest(int64_t from, const string& cmd, const FileTokenInfo& info);
        FPQuestPtr _getGetGroupMessageQuest(int64_t gid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId);
        FPQuestPtr _getGetRoomMessageQuest(int64_t rid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId);
        FPQuestPtr _getGetBroadcastMessageQuest(bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId);
        FPQuestPtr _getGetP2PMessageQuest(int64_t uid, int64_t ouid, bool desc, int16_t num, int64_t begin, int64_t end, int64_t lastId);
        FPQuestPtr _getAddRoomMemberQuest(int64_t rid, int64_t uid);
        FPQuestPtr _getDeleteRoomMemberQuest(int64_t rid, int64_t uid);
        FPQuestPtr _getAddListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events);
        FPQuestPtr _getRemoveListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events);
        FPQuestPtr _getSetListenQuest(const set<int64_t>& gids, const set<int64_t>& rids, bool p2p, const set<string>& events, bool all);
        FPQuestPtr _getAddDeviceQuest(int64_t uid, const string& appType, const string& deviceToken);
        FPQuestPtr _getRemoveDeviceQuest(int64_t uid, const string& deviceToken);
        FPQuestPtr _getDeleteMessageQuest(int64_t mid, int64_t from, int64_t xid, int8_t type);
        FPQuestPtr _getKickoutQuest(int64_t uid, const string& ce);
        FPQuestPtr _getSendFileQuest(const string& token, int64_t from, const string& cmd, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, int64_t mid);
        SendFileResult _sendFileProcess(int64_t from, const string& cmd, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData, int64_t& mid, int32_t timeout);
        void _sendFileProcess(int64_t from, const string& cmd, int64_t to, const set<int64_t>& tos, int64_t gid, int64_t rid, int8_t mtype, const string& fileData,
                std::function<void (SendFileResult result)> callback, int64_t& mid, int32_t timeout);

        TCPClientPtr _client;
        int32_t _pid;
        string _secret;
        shared_ptr<RTMProcessor> _processor;
    };

    typedef shared_ptr<RTMServerClient> RTMServerClientPtr;
}

#endif
