#include "relationalbroker.h"
#include <iostream>
#include <mariadb/conncpp.hpp>
#include <stdexcept>


RelationalBroker::RelationalBroker()
{
    try{
        //Instantiate Driver
        sql::Driver* driver = sql::mariadb::get_driver_instance();

        //Configure Connection
        sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/Kankan");
        sql::Properties properties({{"user", "zc"}, {"password", "20010202"}});

        //建立连接
        conn= std::unique_ptr<sql::Connection>(driver->connect(url, properties));
    } catch (sql::SQLException& e) {
        std::cerr<< "Error Connecting to MariaDB Platform:" << e.what() << std::endl;
        abort();
    }
}

RelationalBroker::~RelationalBroker()
{
    conn->close();
}

std::shared_ptr<sql::ResultSet> RelationalBroker::query(std::string sql)
{
    try {
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        std::shared_ptr<sql::ResultSet> res(stmnt->executeQuery(sql));
        return res;
    } catch (sql::SQLException& e) {
        std::cerr << "Error selecting sql: " << e.what() << std::endl;
    }
}

void RelationalBroker::insert(std::string sql)
{
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(sql));
        stmnt->executeQuery();
    } catch (sql::SQLException& e) {
        std::cerr << "Error insert：" << e.what() << std::endl;
    }
}

void RelationalBroker::update(std::string sql)
{
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(sql));
        stmnt->executeQuery();
    } catch (sql::SQLException& e) {
        std::cerr << "Error update：" << e.what() << std::endl;
    }
}

void RelationalBroker::Delete(const std::string &sql)
{
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(sql));
        stmnt->executeQuery();
    } catch (sql::SQLException& e) {
        std::cerr << "Error delete：" << e.what() << std::endl;
    }
}
