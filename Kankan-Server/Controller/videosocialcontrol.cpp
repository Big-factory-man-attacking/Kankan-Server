#include "Controller/videosocialcontrol.h"
#include "Entity/netizen.h"
#include "SqlCon/netizenbroker.h"
#include <iostream>
#include <utility>
#include <time.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "SqlCon/manuscriptbroker.h"

extern "C" {
    #include <libavutil/timestamp.h>
    #include <libavformat/avformat.h>
}

using json = nlohmann::json;

VideoSocialControl::VideoSocialControl()
{

}

//注册
nlohmann::json VideoSocialControl::registerAccount(json js)
{
    //利用boost/uuid库生成uuid
    boost::uuids::random_generator gen;
    boost::uuids::uuid  uid = gen();

    std::string id = to_string(uid);

    std::cout << id << std::endl;

    //注册成功后直接登录
    //初始用户数据库无数据,无需进行用户数据的init
    std::shared_ptr<NetizenProxy> netizenProxy = std::make_shared<NetizenProxy>(id);

    std::string password = js["password"].get<std::string>();
    std::string nickname = js["nickname"].get<std::string>();
    netizenProxy->addNetizen(id, password, nickname);
    return {};
}

//登录
json VideoSocialControl::login(json js)
{
    std::string id = js["id"].get<std::string>();
    std::string key = js["key"].get<std::string>();

    json info;
    if (NetizenBroker::getInstance()->qualifyNetizenId(id)) {
        std::cout << "用户id存在" << std::endl;
        if (NetizenBroker::getInstance()->qualifyNetizenPassword(id, key)) {
            std::cout << "密码正确" << std::endl;

            auto netizen = NetizenBroker::getInstance()->findNetizenById(id);

            info = netizen->init();//初始化稿件（含视频）、粉丝列表、关注列表初始化
         //   std::cout << info.dump(4);
        } else {
            std::cout << "密码错误" << std::endl;
        }
    } else {
        std::cout << "用户id不存在" << std::endl;
    }
    return info;
}

json VideoSocialControl::getSomeVideos()
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

json VideoSocialControl::loadVideo(json js)
{
    std::string id = js["id"].get<std::string>();
    //首先找到对应的稿件
    auto manuscript = ManuscriptBroker::getInstance()->getManuscript(id);

    //读取稿件的数据
    json manuscriptInfo = manuscript->getManuscriptInfo();

    return manuscriptInfo;
}

nlohmann::json VideoSocialControl::focusOn(nlohmann::json js)
{
    std::string fanId = js["fanId"].get<std::string>();
    std::string followerId = js["followerId"].get<std::string>();
    std::string followerNickname = js["followerNickname"].get<std::string>();
    auto fanProxy = std::make_shared<NetizenProxy>(fanId);

    fanProxy->focusOn(followerId, followerNickname);
    return {};
}

nlohmann::json VideoSocialControl::takeOff(json js)
{
    std::string fanId = js["fanId"].get<std::string>();
    std::string followerId = js["followerId"].get<std::string>();
    auto fanProxy = std::make_shared<NetizenProxy>(fanId);

    fanProxy->takeOff(followerId);
    return {};
}


nlohmann::json VideoSocialControl::modifyHeadportrait(json js)
{
    std::string netizenId = js["netizenId"].get<std::string>();
    std::string newHeadportrait = js["newHeadportrait"].get<std::string>();
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->modifyHeadportrait(newHeadportrait);
    return {};
}

nlohmann::json VideoSocialControl::modifyNickname(json js)
{
    std::string netizenId = js["netizenId"].get<std::string>();
    std::string newNickname = js["newNickname"].get<std::string>();
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->modifyNickname(newNickname);
    return {};
}

json VideoSocialControl::modifyPassword(json js)
{
    std::string netizenId = js["netizenId"].get<std::string>();
    std::string oldPassword = js["oldPassword"].get<std::string>();
    std::string newPassword = js["newPassword"].get<std::string>();
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);

    nlohmann::json res;
    res["flag"] = netizenProxy->modifyPassword(oldPassword, newPassword);
    return res;
}


nlohmann::json VideoSocialControl::modifyManuscriptInfo(json js)
{
    std::string netizenId = js["netizenId"].get<std::string>();
    json newManuscriptInfo = js["newManuscriptInfo"];
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->modifyManuscriptInfo(newManuscriptInfo);
    return {};
}

nlohmann::json VideoSocialControl::deleteManuscript(json js)
{
    std::string netizenId = js["netizenId"].get<std::string>();
    std::string manuscriptId = js["manuscriptId"].get<std::string>();
    auto netizenProxy = std::make_shared<NetizenProxy>(netizenId);
    netizenProxy->deleteManuscript(manuscriptId);
    return {};
}

nlohmann::json VideoSocialControl::commentManuscript(nlohmann::json js)
{
    //利用boost/uuid库生成uuid
    boost::uuids::random_generator gen;
    boost::uuids::uuid  uid = gen();
    std::string id = to_string(uid);

    std::string netizenId = js["netizenId"].get<std::string>();
    std::string manuscriptId = js["manuscriptId"].get<std::string>();
    auto manuscriptProxy = std::make_shared<ManuscriptProxy>(manuscriptId);
    std::string text =  js["text"].get<std::string>();

    manuscriptProxy->addNewComment(id, netizenId, text);
    return {};
}

json VideoSocialControl::dealPost(json h)
{
    std::string s = h["type"].get<std::string>();
    json data = h["data"];
    json res;
    if (s == "register") {
        res = registerAccount(data);
    } else if (s == "login") {
        res["netizen"] = login(data);
        if (res["netizen"].empty()) {
            res["flag"] = "0";
        } else {
            res["flag"] = "1";
        }
    } else if (s == "getSomeVideos") {
        std::cout << "getSomeVideos" << std::endl;
        res = getSomeVideos();
    } else if (s == "loadVideo") {
        res = loadVideo(data);
    } else if (s == "focusOn") {
        res = focusOn(data);
    } else if (s == "takeOff") {
        takeOff(data);
    } else if (s == "modifyHeadportrait") {
        res = modifyHeadportrait(data);
    } else if (s == "modifyNickname") {
        res = modifyNickname(data);
    } else if (s == "modifyPassword") {
        res = modifyPassword(data);
    } else if (s == "modifyManuscriptInfo") {
        res = modifyManuscriptInfo(data);
    } else if (s == "commentManuscript") {
        res = commentManuscript(data);
    } else if (s == ""){
        res = deleteManuscript(data);
    }
 //   std::cout << res.dump(4) << std::endl;
    return res;
}


