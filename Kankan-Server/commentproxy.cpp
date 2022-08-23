#include "commentproxy.h"
#include "commentbroker.h"

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
