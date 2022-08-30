#include "netizenbroker.h"
#include "../Entity/netizen.h"
#include <iostream>

NetizenBroker* NetizenBroker::m_netizenBroker = nullptr;

NetizenBroker::NetizenBroker()
{

}

NetizenBroker::~NetizenBroker()
{

}

NetizenBroker *NetizenBroker::getInstance()
{
    if (m_netizenBroker == nullptr)
        m_netizenBroker = new NetizenBroker();
    return m_netizenBroker;
}

bool NetizenBroker::qualifyNetizenId(std::string id)
{
    //根据id查找,如果找到返回true,否则返回false
    std::string sql = "select user_id from user";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        if (id == res->getString(1))
            return true;
    }

    return false;
}

bool NetizenBroker::qualifyNetizenPassword(std::string id, std::string password)
{
    //验证对应id的密码，正确返回true,错误返回false
    std::string sql = "select user_id, password from user";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        if (id == res->getString(1) && password == res->getString(2))
            return true;
    }

    return false;
}

void NetizenBroker::addNetizen(const std::string &id, const std::string &password, const std::string &nickname)
{
    std::string sql = "insert into user values( '" + id + "', '" + password + "', '" + nickname + "', null);";

    insert(sql);
}

std::shared_ptr<Netizen> NetizenBroker::findNetizenById(const std::string& id)
{
    //查找数据库，找出用户的nickname
    std::string nickname, headportrait;

    std::string sql = "select nickname, headportrait from user where user_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        nickname = res->getString(1).c_str();
        headportrait = res->getString(2).c_str();
    }

    //构造netizen对象
    std::shared_ptr<Netizen> netizen = std::make_shared<Netizen>(id, nickname, headportrait, findNetizenVideos(id),
                                                        findNetizenFans(id), findNetizenFollowers(id));

    std::cout << "Netizen对象实例化成功" << std::endl;

    return netizen;
}

std::vector<std::string> NetizenBroker::findNetizenVideos(const std::string& id)
{
    std::string sql = "select manuscript_id from manuscript where user_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> videoIds;
    while (res->next()) {
        videoIds.push_back(res->getString(1).c_str());
    }

    return videoIds;
}

std::vector<std::string> NetizenBroker::findNetizenFans(const std::string& id)
{
    std::string sql = "select fan_id from fan where user_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> fanIds;
    while (res->next()) {
        fanIds.push_back(res->getString(1).c_str());
    }

    return fanIds;
}

std::vector<std::string> NetizenBroker::findNetizenFollowers(const std::string& id)
{
    std::string sql = "select follower_id from follower where user_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> followerIds;
    while (res->next()) {
        followerIds.push_back(res->getString(1).c_str());
    }

    return followerIds;
}

void NetizenBroker::modifyHeadportrait(const std::string &id, const std::string &headportrait)
{
    std::string sql = "update user set headportrait = '" + headportrait + "' where user_id = '" + id + "'";

    std::cout << "修改头像sql:" << sql << std::endl;

    update(sql);

}

void NetizenBroker::modifyNickname(const std::string &id, const std::string &nickname)
{
    std::string sql = "update user set nickname = '" + nickname + "' where user_id = '" + id + "'";

    std::cout << "修改昵称sql：" << sql << std::endl;

    update(sql);
}

void NetizenBroker::modifyPassword(const std::string &id, const std::string password)
{
    std::string sql = "update user set password = '" + password + "' where user_id = '" + id + "'";

    std::cout << "修改密码sql：" << sql << std::endl;

    update(sql);
}

void NetizenBroker::focusOn(const std::string &fanId, const std::string &fanNickname, const std::string &followerId, const std::string &followerNickname)
{
    std::string sql = "insert into follower values('" + fanId + "','" + fanNickname + "','" + followerId + "','" + followerNickname + "');";

    insert(sql);

    sql = "insert into fan values('" + followerId + "','" + followerNickname + "','" + fanId + "','" + fanNickname + "');";

    insert(sql);
}

void NetizenBroker::takeOff(const std::string &fanId, const std::string &followerId)
{
    std::string sql = "delete from  follower where user_id = '" + fanId + "' and follower_id = '" + followerId + "';";

    Delete(sql);

    sql = "delete from fan where user_id = '" + followerId + "' and fan_id = '" + fanId + "';";

    Delete(sql);
}


