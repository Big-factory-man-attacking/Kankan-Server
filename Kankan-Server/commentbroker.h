#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "relationalbroker.h"
#include "comment.h"

class CommentBroker : public RelationalBroker
{
public:
    ~CommentBroker();
    static CommentBroker* getInstance();

    // 获取评论对象
    // id：评论的id
    std::shared_ptr<Comment> getComment(std::string& id);
private:
    CommentBroker();
    static CommentBroker* m_commentBroker;
};

#endif // COMMENTBROKER_H
