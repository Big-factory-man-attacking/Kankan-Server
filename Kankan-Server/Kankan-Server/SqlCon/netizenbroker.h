#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include <memory>
#include "relationalbroker.h"
#include <vector>

class Netizen;

class NetizenBroker : public RelationalBroker
{
public:
    ~NetizenBroker();
    static NetizenBroker* getInstance();

    // 根据用户ID检验用户是否存在
    // id：用户输入id
    bool qualifyNetizenId(std::string id);

    // 检验用户的id与key是否匹配
    // id:用户输入id
    // key:用户输入密码key
    bool qualifyNetizenPassword(std::string id, std::string key);

    // 添加新的用户记录
     void addNetizen(const std::string& id, const std::string& password, const std::string& nickname);

    // 通过用户id查找相关用户数据
    // id:用户id
    std::shared_ptr<Netizen> findNetizenById(const std::string& id);

    // 通过用户id查找所有稿件id
    std::vector<std::string> findNetizenVideos(const std::string& id);

    // 通过用户id查找所有粉丝id
    std::vector<std::string> findNetizenFans(const std::string& id);

    // 通过用户id查找所有关注者id
    std::vector<std::string> findNetizenFollowers(const std::string& id);

    // 修改用户的头像
    void modifyHeadportrait(const std::string& id, const std::string& headportrait);

    // 修改用户的昵称
    void modifyNickname(const std::string& id, const std::string& nickname);

    // 修改用户的密码
    void modifyPassword(const std::string& id, const std::string password);

    // 关注
    void focusOn(const std::string& fanId, const std::string& fanNickname,
                 const std::string& followerId, const std::string& followerNickname);

    // 取关
    void takeOff(const std::string& fanId, const std::string& followerId);
private:
    NetizenBroker();
    static NetizenBroker* m_netizenBroker;
};

#endif // NETIZENBROKER_H
