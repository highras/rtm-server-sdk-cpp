#include <iostream>
#include "rtm.h"

using namespace std;
using namespace rtm;

class MyMonitor: public RTMServerMonitor
{
    void connected(const ConnectionInfo& connInfo) 
    {
        cout << "connected" << endl;    
    }

    void connectionWillClose(const ConnectionInfo& connInfo, bool closeByError) 
    {
        cout << "connectionWillClose, closeByError: " << closeByError << endl; 
    }

    void pushP2PMessage(int64_t from, int64_t to, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime) 
    {
        cout << "from: " << from << " to: " << to << " mtype: " << mtype << " mid: " << mid << " message: " << message << " attrs: " << attrs << " mtime: " << mtime << endl;   
    }

    void pushGroupMessage(int64_t from, int64_t gid, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime) 
    {
        cout << "from: " << from << " gid: " << gid << " mtype: " << mtype << " mid: " << mid << " message: " << message << " attrs: " << attrs << " mtime: " << mtime << endl;   
    }

     void pushRoomMessage(int64_t from, int64_t rid, int8_t mtype, int64_t mid, const string& message, const string& attrs, int64_t mtime)
    {
        cout << "from: " << from << " rid: " << rid << " mtype: " << mtype << " mid: " << mid << " message: " << message << " attrs: " << attrs << " mtime: " << mtime << endl;   
    }

    void pushEvent(int32_t pid, const string& event, int64_t uid, int32_t time, const string& endpoint, const string& data)
    {
        cout << "pid: " << pid << " event: " << event << " uid: " << uid << " time: " << time << " endpoint: " << endpoint << " data: " << data << endl; 
    }

};

int main(int argc, const char** argv)
{
    RTMServerClientPtr client(new RTMServerClient(11000001, "ef3617e5-e886-4a4e-9eef-7263c0320628", "52.83.245.22:13315", true, 5000));
    client->setServerMonitor(make_shared<MyMonitor>());
    
    {
        QuestResult result = client->addListen({}, {}, true, {"login"});
        cout << "addListen sync: " << endl;
        if (result.isError()) {
            cout << result.errorCode << " " << result.errorInfo << endl;
        } else {
            cout << "ok" << endl;
        }
    }

    {
        SendMessageResult result = client->sendMessage(1, 123, 51, "test", "");

        cout << "sendMessage sync: " << endl;
        if (result.isError()) {
            cout << result.errorCode << " " << result.errorInfo << endl;
        } else {
            cout << result.mid << endl;
            cout << result.mtime << endl;
        }
        
        client->sendMessage(1, 123, 51, "test", "", [](SendMessageResult result) {
            cout << "sendMessage async: " << endl;
            if (result.isError()) {
                cout << result.errorCode << " " << result.errorInfo << endl;
            } else {
                cout << result.mid << endl;
                cout << result.mtime << endl;
            }
        });
    }

    {
        QuestResult result = client->addFriends(1, {11, 22, 33});
        cout << "addFriends sync: " << endl;
        if (result.isError()) {
            cout << result.errorCode << " " << result.errorInfo << endl;
        } else {
            cout << "ok" << endl;
        }

        client->addFriends(1, {11, 22, 33}, [](QuestResult result) {
            cout << "addFriends async: " << endl;
            if (result.isError()) {
                cout << result.errorCode << " " << result.errorInfo << endl;
            } else {
                cout << "ok" << endl;
            }
        });
    }

    {
        string fileData;
        if (client->loadFile("/tmp/logo.png", fileData)) {
            SendFileResult result = client->sendFile(1, 12345, 50, fileData);
            cout << "sendFile sync: " << endl;
            if (result.isError()) {
                cout << result.errorCode << " " << result.errorInfo << endl;
            } else {
                cout << result.mid << endl;
                cout << result.mtime << endl;
            }

            client->sendFile(1, 12345, 50, fileData, [](SendFileResult result){
                cout << "sendFile async: " << endl;
                if (result.isError()) {
                    cout << result.errorCode << " " << result.errorInfo << endl;
                } else {
                    cout << result.mid << endl;
                    cout << result.mtime << endl;
                }            
            });
        }
    }

    while (true)
        sleep(1);

    return 0;
}
