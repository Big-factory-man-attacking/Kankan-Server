#include "commentbroker.h"
#include <iostream>

CommentBroker* CommentBroker::m_commentBroker = nullptr;

CommentBroker::~CommentBroker()
{

}

CommentBroker *CommentBroker::getInstance()
{
    if (m_commentBroker == nullptr)
        m_commentBroker = new CommentBroker();
    return m_commentBroker;
}

std::shared_ptr<Comment> CommentBroker::getComment(std::string &id)
{
    //检索数据库，创建对象
    std::string sql = "select comment_id, text from comment where comment_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
    }

    std::shared_ptr<Comment> comment = std::make_shared<Comment>(parameters[0], parameters[1]);

    //返回对象
    std::cout << "Comment对象实例化成功" << std::endl;
    return comment;
}

std::string CommentBroker::getNetizen(std::string &id)
{
    std::string sql = "select user_id from comment where comment_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::string parameter;
    while (res->next()) {
        parameter = res->getString(1).c_str();
    }
    return parameter;
}



void CommentBroker::addComment(const std::string &id, const std::string &text, const std::string &manuscriptId, const std::string &netizenId)
{
    std::string sql = "insert into comment values( '" + id + "', '" + text + "', '" + manuscriptId + "','" + netizenId + "');";
    std::cout << "添加评论sql：" << sql << std::endl;

    insert(sql);
}

void CommentBroker::deleteComment(const std::string &id)
{
    std::string sql = "delete from comment where comment_id = '" + id + "'";
    std::cout << "删除评论sql：" << sql << std::endl;
    Delete(sql);
}

CommentBroker::CommentBroker()
{

}
