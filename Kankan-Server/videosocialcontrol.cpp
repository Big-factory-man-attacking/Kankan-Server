#include "videosocialcontrol.h"
#include "netizen.h"
#include "netizenbroker.h"
#include <iostream>
#include <utility>
#include <time.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "manuscriptbroker.h"

extern "C" {
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
}

using json = nlohmann::json;

VideoSocialControl::VideoSocialControl()
{

}

//注册
void VideoSocialControl::registerAccount(std::string password, std::string nickname)
{
    //利用boost/uuid库生成uuid
    boost::uuids::random_generator gen;
    boost::uuids::uuid  uid = gen();

    std::string id = to_string(uid);

    std::cout << id << std::endl;

    //注册成功后直接登录
    //初始用户数据库无数据,无需进行用户数据的init
    std::shared_ptr<NetizenProxy> netizenProxy = std::make_shared<NetizenProxy>(id);

    netizenProxy->addNetizen(id, password, nickname);
}

//登录
nlohmann::json VideoSocialControl::login(std::string id, std::string key)
{
    nlohmann::json info;
    if (NetizenBroker::getInstance()->qualifyNetizenId(id)) {
        std::cout << "用户id存在" << std::endl;
        if (NetizenBroker::getInstance()->qualifyNetizenPassword(id, key)) {
            std::cout << "密码正确" << std::endl;

            auto netizen = NetizenBroker::getInstance()->findNetizenById(id);

            info = netizen->init();//初始化稿件（含视频）、粉丝列表、关注列表初始化
            std::cout << info.dump(4);
            return info;
        } else {
            std::cout << "密码错误" << std::endl;
            return info;
        }
    } else {
        std::cout << "用户id不存在" << std::endl;
        return info;
    }
}

nlohmann::json VideoSocialControl::getSomeVideos()
{
    //获取一些稿件的id
    std::map<std::string, std::string> manuscriptIds;
    manuscriptIds = ManuscriptBroker::getInstance()->getManuscripts();

    //创建稿件的proxy
    std::unordered_map<std::string, ManuscriptProxy> _manuscripts;
    for (auto& id : manuscriptIds)
        _manuscripts.insert(std::make_pair(id.first, ManuscriptProxy(id.first)));

    //创建网民的proxy
    std::unordered_multimap<std::string, NetizenProxy> _netizens;
    for (auto& id : manuscriptIds)
        _netizens.insert(std::make_pair(id.second, NetizenProxy(id.second)));


    //获取稿件、对应创作者的摘要信息
    json manuscriptInfos;

    for (auto& manuscript : _manuscripts) {
        json manuscriptInfo = manuscript.second.getManuscriptInfo(manuscript.first);
        manuscriptInfos["manuscriptInfo"].push_back(manuscriptInfo);
    }

    for (auto& netizen : _netizens) {
        json netizenInfo = netizen.second.getInfo(netizen.first);
        manuscriptInfos["netizenInfo"].push_back(netizenInfo);
    }
    std::cout << manuscriptInfos.dump(4) << std::endl;
    return manuscriptInfos;
}

nlohmann::json VideoSocialControl::loadVideo(std::string id)
{
    //首先找到对应的稿件
    auto manuscript = ManuscriptBroker::getInstance()->getManuscript(id);

    //读取稿件的数据
    json manuscriptInfo = manuscript->getManuscriptInfo();

    return manuscriptInfo;
}

void VideoSocialControl::focusOn(std::string fanId, std::string followerId, std::string followerNickname)
{
    auto fanProxy = std::make_shared<NetizenProxy>(fanId);

    fanProxy->focusOn(followerId, followerNickname);

}

void VideoSocialControl::takeOff(std::string fanId, std::string followerId)
{
    auto fanProxy = std::make_shared<NetizenProxy>(fanId);

    fanProxy->takeOff(followerId);
}


void VideoSocialControl::modifyHeadportrait(const std::string &netizenId, const std::string &newHeadportrait)
{
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->modifyHeadportrait(newHeadportrait);
}

void VideoSocialControl::modifyNickname(const std::string &netizenId, const std::string &newNickname)
{
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->modifyNickname(newNickname);
}

bool VideoSocialControl::modifyPassword(const std::string &netizenId, const std::string &oldPassword, const std::string &newPassword)
{
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    return netizenProxy->modifyPassword(oldPassword, newPassword);
}


void VideoSocialControl::modifyManuscriptInfo(const std::string &netizenId, nlohmann::json newManuscriptInfo)
{
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->modifyManuscriptInfo(newManuscriptInfo);
}

void VideoSocialControl::deleteManuscript(const std::string &netizenId, const std::string &manuscriptId)
{
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->deleteManuscript(manuscriptId);
}


