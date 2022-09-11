#include "commentproxy.h"
#include "netizen.h"
#include "../SqlCon/commentbroker.h"
#include <iostream>

CommentProxy::CommentProxy(std::string &id) : m_id{id}
{

}

CommentProxy::~CommentProxy()
{

}

nlohmann::json CommentProxy::getCommentInfo(std::string id)
{
    // 实例化评论对象
    if (m_comment == nullptr)
        m_comment = CommentBroker::getInstance()->getComment(m_id);

    std::string netizenId = CommentBroker::getInstance()->getNetizen(id);
    auto netizen = std::make_pair(netizenId, NetizenProxy(netizenId));
    nlohmann::json netizenInfo = netizen.second.getInfo(netizen.first);

    nlohmann::json js;
    js["id"] = m_id;
    js["text"] = m_comment->getText();
    js["netizenInfo"] = netizenInfo;
    return js;
}

void CommentProxy::addNewComment(const std::string &text, const std::string &manuscriptId, const std::string &netizenId)
{
    CommentBroker::getInstance()->addComment(m_id, text, manuscriptId, netizenId);

}

void CommentProxy::deleteComment(const std::string &commentId)
{
    CommentBroker::getInstance()->deleteComment(commentId);
}
