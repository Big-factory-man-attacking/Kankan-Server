#ifndef NETIZENPROXY_H
#define NETIZENPROXY_H

#include <memory>
#include "netizeninterface.h"
#include <vector>
#include "json.hpp"

class Netizen;

class NetizenProxy : public NetizenInterface
{
public:
    NetizenProxy(std::string id);
    ~NetizenProxy();

    // 注册
    void addNetizen(std::string id, std::string password, std::string nickname);

    nlohmann::json getInfo(const std::string& id);

    // 删除稿件
    void deleteManuscript(const std::string& manuscriptId);

    // 修改头像
    void modifyHeadportrait(const std::string& newHeadportrait);

    // 修改昵称
    void modifyNickname(const std::string& newNickname);

    // 修改密码
    bool modifyPassword(const std::string& oldPassword, const std::string& newPassword);

    // 修改稿件信息
    void modifyManuscriptInfo(const nlohmann::json& newManuscriptInfo);

    // 添加关注
    void focusOn(const std::string& followerId, const std::string& followerNickname);

    // 取关
    void takeOff(const std::string& followerId);

private:
    std::string m_id;
    std::shared_ptr<Netizen> m_netizen;
};

#endif // NETIZENPROXY_H
