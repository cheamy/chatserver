#ifndef CHATSERVICE_H
#define CHATSERVIVE_H

// #include "../../thirdparty/json.hpp"
#include <muduo/net/TcpConnection.h>
#include <functional>
#include <unordered_map>
#include <mutex>

using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "groupmodel.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "json.hpp"

using json = nlohmann::json;

using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

class ChatService
{
public:
    static ChatService *instance();

    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 服务器异常，重置业务
    void reset();

    MsgHandler getHandler(int msgid);

private:
    ChatService();

    unordered_map<int, MsgHandler> _msgHandlerMap;

    unordered_map<int, TcpConnectionPtr> _userConnMap;

    mutex _connMutex;

    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;
};

#endif