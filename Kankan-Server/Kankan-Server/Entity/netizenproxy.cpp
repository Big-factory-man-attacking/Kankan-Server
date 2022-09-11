#include "netizenproxy.h"
#include "../SqlCon/netizenbroker.h"
#include "netizen.h"
#include <iostream>

using json = nlohmann::json;

NetizenProxy::NetizenProxy(std::string id) :
    m_id{id}, m_netizen{}
{

}

NetizenProxy::~NetizenProxy()
{

}

void NetizenProxy::addNetizen(std::string id, std::string password, std::string nickname)
{
    NetizenBroker::getInstance()->addNetizen(id, password, nickname);
}

nlohmann::json NetizenProxy::getInfo(const std::string& id)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(id);
    return m_netizen->getInfo();
}

void NetizenProxy::deleteManuscript(const std::string &manuscriptId)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);

    m_netizen->deleteManuscript(manuscriptId);
}

void NetizenProxy::modifyHeadportrait(const std::string &newHeadportrait)
{
    if (m_netizen == nullptr)
       m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);

    m_netizen->modifyHeadportrait(newHeadportrait);
    NetizenBroker::getInstance()->modifyHeadportrait(m_id, newHeadportrait);

}

void NetizenProxy::modifyNickname(const std::string &newNickname)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);

    m_netizen->modifyNickname(newNickname);
    NetizenBroker::getInstance()->modifyNickname(m_id, newNickname);
}

bool NetizenProxy::modifyPassword(const std::string &oldPassword, const std::string &newPassword)
{
    if (!NetizenBroker::getInstance()->qualifyNetizenPassword(m_id, oldPassword))
        return false;

    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);

    NetizenBroker::getInstance()->modifyPassword(m_id, newPassword);
    return true;
}

void NetizenProxy::modifyManuscriptInfo(const nlohmann::json &newManuscriptInfo)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);

    m_netizen->modifyManuscriptInfo(newManuscriptInfo);
}

void NetizenProxy::focusOn(const std::string &followerId, const std::string &followerNickname)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);
    m_netizen->focusOn(followerId);

    NetizenBroker::getInstance()->focusOn(m_id, m_netizen->nickname(), followerId, followerNickname);
}

void NetizenProxy::takeOff(const std::string &followerId)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);
    m_netizen->takeOff(followerId);
    NetizenBroker::getInstance()->takeOff(m_id, followerId);
}

