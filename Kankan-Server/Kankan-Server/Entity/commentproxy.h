#ifndef COMMENTPROXY_H
#define COMMENTPROXY_H

#include <memory>
#include <string>
#include "commentinterface.h"
#include "json.hpp"

class Comment;

class CommentProxy : public CommentInterface
{
public:
    CommentProxy(std::string& id);
    ~CommentProxy();

    // 返回评论的内容
    // id：对应评论的id
    nlohmann::json getCommentInfo(std::string id);

    //添加评论
    void addNewComment(const std::string &text, const std::string &manuscriptId, const std::string &netizenId);

    //删除评论
    void deleteComment(const std::string &commentId);
private:
    std::string m_id;
    std::shared_ptr<Comment> m_comment;
};

#endif // COMMENTPROXY_H
