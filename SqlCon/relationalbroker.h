#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H

#include <unordered_map>
#include <mariadb/conncpp.hpp>

class RelationalBroker
{
public:
    RelationalBroker();
    virtual ~RelationalBroker();

    //执行数据库查询操作，返回数据集
    //sql:SQL语句
    std::shared_ptr<sql::ResultSet> query(std::string sql);

    //执行数据库插入操作
    //sql:SQL语句
    void insert(std::string sql);

    //执行数据库更新操作
    //sql:SQL语句
    void update(std::string sql);

    //执行数据库删除操作
    void Delete(const std::string& sql);
private:
    std::unique_ptr<sql::Connection> conn;
};

#endif // RELATIONALBROKER_H
