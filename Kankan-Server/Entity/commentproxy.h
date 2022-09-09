#ifndef COMMENTPROXY_H
#define COMMENTPROXY_H

#include <memory>
#include <string>
#include "commentinterface.h"

class Comment;

class CommentProxy : public CommentInterface
{
public:
    CommentProxy(std::string& id);
    ~CommentProxy();

    // 返回评论的内容
    // id：对应评论的id
    std::string getCommentInfo(std::string id);
    void addNewComment(const std::string &text, const std::string &manuscriptId, const std::string &netizenId);
    void deleteComment();
private:
    std::string m_id;
    std::shared_ptr<Comment> m_comment;
};

#endif // COMMENTPROXY_H
