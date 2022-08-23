#include "netizen.h"
#include <string>
#include <iostream>

using json = nlohmann::json;

Netizen::Netizen(std::string id, std::string password, std::string nickname) :
    m_id{id}, m_password{password}, m_nickname{nickname}
{
}

Netizen::~Netizen()
{

}


Netizen::Netizen(std::string id, std::string nickname, std::string headPortrait, std::vector<std::string> manuscriptsId,
                 std::vector<std::string> fansId, std::vector<std::string> followersId) :
    m_id{id}, m_headPortrait{headPortrait}, m_password{" "}, m_nickname{nickname}
{
    for (auto vId : manuscriptsId) {
        _manuscripts.insert(std::make_pair(vId, ManuscriptProxy(vId)));
//        std::cout << "稿件id：" << vId << std::endl;
    }

    for (auto fanId : fansId) {
        _fans.insert(std::make_pair(fanId, NetizenProxy(fanId)));
//        std::cout << "粉丝id：" << fanId << std::endl;
    }

    for (auto followerId : followersId) {
        _followers.insert(std::make_pair(followerId, NetizenProxy(followerId)));
//        std::cout << "关注者id：" << followerId << std::endl;
    }
}

nlohmann::json Netizen::init()
{
    nlohmann::json netizenInfo;
    netizenInfo["id"] = m_id;
    netizenInfo["nickname"] = m_nickname;
    netizenInfo["headportrait"] = m_headPortrait;
    for (auto& manuscript : _manuscripts){
        nlohmann::json v = manuscript.second.getManuscriptInfo(manuscript.first);
        netizenInfo["videos"].push_back(v);
    }
    if (_manuscripts.size() == 0) netizenInfo["videos"] = "";

    for (auto& fan : _fans) {
        nlohmann::json f = fan.second.getInfo(fan.first);
        netizenInfo["fans"].push_back(f);
    }
    if (_fans.size() == 0) netizenInfo["fans"] = "";

    for (auto& follower : _followers) {
        nlohmann::json f = follower.second.getInfo(follower.first);
        netizenInfo["followers"].push_back(f);
    }
    if (_followers.size() == 0) netizenInfo["followers"] = "";


    return netizenInfo;
}

nlohmann::json Netizen::getInfo()
{
    json results;
    results["id"] = m_id;
    results["headPortrait"] = m_headPortrait;
    results["nickname"] = m_nickname;

    //测试
//    std::cout << "NetizenInfo: " ;
//    std::cout << results.dump(4) << std::endl;

    return results;
}

void Netizen::modifyHeadportrait(const std::string &newHeadportrait)
{
    m_headPortrait = newHeadportrait;
}

void Netizen::modifyNickname(const std::string &newNickname)
{
    m_nickname = newNickname;
}

void Netizen::modifyManuscriptInfo(nlohmann::json newManuscriptInfo)
{
    // 解析出稿件id
    std::string manuscriptId = newManuscriptInfo["id"].get<std::string>();

    //修改_manuscripts中对应的那个manucriptproxy对象中的manscript实体的信息,通过proxy找broker修改数据库信息；
    auto manscript = _manuscripts.find(manuscriptId);
    manscript->second.modifyManuscriptInfo(newManuscriptInfo);
}

void Netizen::deleteManuscript(const std::string &manuscriptId)
{
    for (auto it = _manuscripts.begin(); it != _manuscripts.end(); it++) {
        if (it->first == manuscriptId) {
            it->second.deleteManuscript(manuscriptId);
            _manuscripts.erase(it);
            break;
        }
    }
}

void Netizen::focusOn(const std::string &followerId)
{
    _followers.insert({followerId,NetizenProxy(followerId)});
}

void Netizen::takeOff(const std::string &followerId)
{
    for (auto it = _followers.begin(); it != _followers.end(); it++) {
        if (it->first == followerId){
            _followers.erase(it);
            break;
        }
    }
}

