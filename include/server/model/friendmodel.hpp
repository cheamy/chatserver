#ifndef FRIENDMODLE_H
#define FRIENDMODLE_H

#include <vector>
#include "user.hpp"

using namespace std;

// 维护好友信息的操作接口
class FriendModel
{
public:
    // 添加好友
    void insert(int userid, int friendid);
    // 返回用户好友列表 friend
    vector<User> query(int userid);
};

#endif