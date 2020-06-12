#ifndef Quest_Result_H
#define Quest_Result_H
#include <vector>

namespace rtm
{
    using namespace std;

	struct QuestResult
    {
        int32_t errorCode;
        string errorInfo;

        QuestResult()
        {
            errorCode = 0;
            errorInfo = "";
        }

        bool isError()
        {
            return errorCode > 0 || !errorInfo.empty();
        }
    };

	struct SendMessageResult: QuestResult
    {
        int64_t mid;
        int64_t mtime;
    };

    struct SendFileResult: SendMessageResult
    {
    };

    struct GetFriendsResult: QuestResult
    {
        set<int64_t> uids;
    };

    struct GetBlacksResult: QuestResult
    {
        set<int64_t> uids;
    };

    struct IsFriendResult: QuestResult
    {
        bool ok;
    };
    
    struct IsFriendsResult: QuestResult
    {
        set<int64_t> fuids;
    };

    struct IsBlacksResult: QuestResult
    {
        set<int64_t> buids;
    };

    struct GetGroupMembersResult: QuestResult
    {
        set<int64_t> uids;
    };
    
    struct IsGroupMemberResult: QuestResult
    {
        bool ok;
    };

    struct GetUserGroupsResult: QuestResult
    {
        set<int64_t> gids;
    };
    
    struct GetTokenResult: QuestResult
    {
        string token; 
    };

    struct GetOnlineUsersResult: QuestResult
    {
        set<int64_t> uids;
    };

    struct IsBanOfGroupResult: QuestResult
    {
        bool ok;
    };
    
    struct IsBanOfRoomResult: QuestResult
    {
        bool ok;
    };
    
    struct IsProjectBlackResult: QuestResult
    {
        bool ok;
    };

    struct FileTokenResult: QuestResult
    {
        string token;
        string endpoint;
    };

    struct GroupMessage
    {
        int64_t id;
        int64_t from;
        int8_t mtype;
        int64_t mid;
        bool deleted;
        string msg;
        string attrs;
        int64_t mtime;
        MSGPACK_DEFINE(id, from, mtype, mid, deleted, msg, attrs, mtime);
    };

    struct RoomMessage: GroupMessage
    {
    };

    struct BroadcastMessage: GroupMessage
    {
    };

    struct P2PMessage
    {
        int64_t id;
        int8_t direction;
        int8_t mtype;
        int64_t mid;
        bool deleted;
        string msg;
        string attrs;
        int64_t mtime;
        MSGPACK_DEFINE(id, direction, mtype, mid, deleted, msg, attrs, mtime);
    };

    struct GetGroupMessageResult: QuestResult
    {
        int16_t num;
        int64_t lastId;
        int64_t begin;
        int64_t end;
        vector<struct GroupMessage> msgs;
    };

    struct GetRoomMessageResult: QuestResult
    {
        int16_t num;
        int64_t lastId;
        int64_t begin;
        int64_t end;
        vector<struct RoomMessage> msgs;
    };

    struct GetBroadcastMessageResult: QuestResult
    {
        int16_t num;
        int64_t lastId;
        int64_t begin;
        int64_t end;
        vector<struct BroadcastMessage> msgs;
    };

    struct GetP2PMessageResult: QuestResult
    {
        int16_t num;
        int64_t lastId;
        int64_t begin;
        int64_t end;
        vector<struct P2PMessage> msgs;
    };

    struct TranslateResult: QuestResult
    {
        string source;
        string target;
        string sourceText;
        string targetText;
    };

    struct ProfanityResult: QuestResult
    {
        string text;
        vector<string> classification;
    };

    struct TranscribeResult: QuestResult
    {
        string text;
        string lang;
    };

    struct GetUserInfoResult: QuestResult
    {
        string oinfo;
        string pinfo;
    };

    struct GetUserOpenInfoResult: QuestResult
    {
        map<string, string> info;
    };

    struct GetGroupInfoResult: GetUserInfoResult 
    {
    };

    struct GetRoomInfoResult: GetUserInfoResult 
    {
    };

    struct GetMessageResult: QuestResult
    {
        int64_t id;
        int8_t mtype;
        string msg;
        string attrs;
        int64_t mtime;
    };
}

#endif
