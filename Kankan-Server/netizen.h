#ifndef NETIZEN_H
#define NETIZEN_H

#include <string>
#include <unordered_map>
#include <utility>
#include "manuscriptproxy.h"
#include "netizenproxy.h"
#include "netizeninterface.h"
#include <vector>
#include "json.hpp"

class Netizen : public NetizenInterface
{
public:
    Netizen() = delete;
    Netizen(std::string id, std::string password, std::string nickname);
    ~Netizen();

    Netizen(std::string id, std::string nickname, std::string headPortrait, std::vector<std::string> manuscriptsId,
            std::vector<std::string> fansId, std::vector<std::string> followersId);

    // 登录后进行信息初始化
    nlohmann::json init();

    // 返回网民的id,昵称和头像
    nlohmann::json getInfo();

    // 修改网民的头像
    void modifyHeadportrait(const std::string& newHeadportrait);

    // 修改网民的昵称
    void modifyNickname(const std::string& newNickname);

    // 修改稿件信息
    void modifyManuscriptInfo(nlohmann::json newManuscriptInfo);

    // 删除稿件
    void deleteManuscript(const std::string& manuscriptId);

    // 关注
    void focusOn(const std::string& followerId);

    // 取关
    void takeOff(const std::string& followerId);

    // 返回头像
    std::string nickname() {return m_nickname;};

private:
    std::string m_id;                                               //用户id
    std::string m_headPortrait;                                     //用户头像
    std::string m_password;                                         //用户密码
    std::string m_nickname;                                         //用户昵称
    std::unordered_map<std::string, ManuscriptProxy> _manuscripts;         //稿件(稿件id，代理)
    std::unordered_map<std::string, NetizenProxy> _fans;                   //粉丝(粉丝id，代理)
    std::unordered_map<std::string, NetizenProxy> _followers;              //关注者(关注者id, 代理)
};

#endif // NETIZEN_H
