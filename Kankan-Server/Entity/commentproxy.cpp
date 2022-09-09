#include "commentproxy.h"
#include "../SqlCon/commentbroker.h"

CommentProxy::CommentProxy(std::string &id) : m_id{id}
{

}

CommentProxy::~CommentProxy()
{

}

std::string CommentProxy::getCommentInfo(std::string id)
{
    // 实例化评论对象
    if (m_comment == nullptr)
        m_comment = CommentBroker::getInstance()->getComment(id);

    return m_comment->getText();
}

void CommentProxy::addNewComment(const std::string &text, const std::string &manuscriptId, const std::string &netizenId)
{
    CommentBroker::getInstance()->addComment(m_id, text, manuscriptId, netizenId);

}
