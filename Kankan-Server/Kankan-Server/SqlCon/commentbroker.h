#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "relationalbroker.h"
#include "../Entity/comment.h"

class CommentBroker : public RelationalBroker
{
public:
    ~CommentBroker();
    static CommentBroker* getInstance();

    // 获取评论对象
    // id：评论的id
    std::shared_ptr<Comment> getComment(std::string& id);

    //获取评论的user_id
    std::string getNetizen(std::string& id);

    //添加评论
    void addComment(const std::string &id, const std::string &text, const std::string &manuscriptId, const std::string &netizenId);

    //删除评论
    void deleteComment(const std::string &commentId);

private:
    CommentBroker();
    static CommentBroker* m_commentBroker;
};

#endif // COMMENTBROKER_H
