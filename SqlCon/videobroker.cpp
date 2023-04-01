#include "videobroker.h"
#include <iostream>

VideoBroker* VideoBroker::m_videoBroker = nullptr;

VideoBroker::~VideoBroker()
{

}

VideoBroker *VideoBroker::getInstance()
{
    if (m_videoBroker == nullptr)
        m_videoBroker = new VideoBroker();
    return m_videoBroker;
}

void VideoBroker::addVideo(const std::string &videoId, const std::string &videoAdress, const std::string &manuscriptId)
{
    std::string sql = "insert into video values( '" + videoId + "', '" + videoAdress + "', '" + manuscriptId + "');";
    insert(sql);

}

std::shared_ptr<Video> VideoBroker::getVideo(std::string &id)
{
    //检索数据库，创建video对象
    std::vector<std::string> parameters;
    std::string sql = "select * from video where video_id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
        parameters.push_back(res->getString(3).c_str());
    }

    std::cout << parameters[0] << parameters[1] << std::endl;
    std::shared_ptr<Video> video = std::make_shared<Video>(parameters[0], parameters[1]);
    //返回video对象
    std::cout << "Video对象实例化成功" << std::endl;
    return video;
}

VideoBroker::VideoBroker()
{

}
