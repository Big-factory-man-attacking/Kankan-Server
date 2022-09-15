#include "manuscriptbroker.h"
#include <vector>
#include <iostream>

ManuscriptBroker* ManuscriptBroker::m_manuscriptBroker = nullptr;

ManuscriptBroker::~ManuscriptBroker()
{

}

ManuscriptBroker *ManuscriptBroker::getInstance()
{
    if (m_manuscriptBroker == nullptr)
        m_manuscriptBroker = new ManuscriptBroker();
    return m_manuscriptBroker;
}

std::shared_ptr<Manuscript> ManuscriptBroker::getManuscript(const std::string& id)
{
    //检查对象是否存在于缓存中

    //检索数据库，创建manuscript对象
    std::string sql = "select * from manuscript where manuscript_id = '" + id + "'";

    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    bool isOriginal;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());    //稿件id
        parameters.push_back(res->getString(2).c_str());    //稿件描述
        parameters.push_back(res->getString(3).c_str());    //稿件标题
        parameters.push_back(res->getString(4).c_str());    //标签
        parameters.push_back(res->getString(5).c_str());    //分区
        isOriginal = res->getBoolean(6);                    //是否为原创
        parameters.push_back(res->getString(7).c_str());    //封面
        parameters.push_back(res->getString(8).c_str());    //发布日期
        std::string i = res->getString(9).c_str();
    }


    // 找到对应的评论id
    std::vector<std::string> commentIds;
    sql = "select comment_id from comment where manuscript_id = '" + id + "'";

    res = query(sql);
    while (res->next())
        commentIds.push_back(res->getString(1).c_str());

    //找到对应的视频id
    sql = "select video_id from video where manuscript_id = '" + id + "'";

    res = query(sql);
    std::string result;
    while (res->next()) {
        result = res->getString(1).c_str();
    }

    std::shared_ptr<Manuscript> manuscript = std::make_shared<Manuscript>(parameters[0], parameters[1], parameters[2],parameters[3],
                                                           parameters[4], isOriginal, parameters[5], parameters[6],
                                                            commentIds, result);
    std::cout << "Manuscript对象实例化成功" << std::endl;

    //返回manuscript对象
    return manuscript;
}

std::map<std::string, std::string> ManuscriptBroker::getManuscripts()
{
    std::string sql = "select manuscript_id, user_id from manuscript";

    std::cout << "获取稿件的id：" << sql << std::endl;

    std::shared_ptr<sql::ResultSet> res = query(sql);

    std::map<std::string, std::string> manuscriptIds;

    while (res->next()) {
        manuscriptIds.insert({res->getString(1).c_str(), res->getString(2).c_str()});
    }


    return manuscriptIds;
}

void ManuscriptBroker::modifyManuscriptInfo(const std::string& id, const std::string &description, const std::string &title, const std::string &label,
                                            const std::string &subarea, bool isOriginal, const std::string &cover, const std::string &date)
{
    std::string sql = "update manuscript set description = '" + description + "', title =  '" + title + "', label = '" +
            label + "', subarea = '" + subarea + "', isOriginal = '" + std::to_string(isOriginal) + "', cover = '" + cover + "', date = '" +
            date + "' where manuscript_id = '" + id + "'";

    std::cout << "修改稿件信息sql:" << sql << std::endl;


    update(sql);
}

void ManuscriptBroker::deleteManuscript(const std::string &manuscriptId)
{
    std::string sql = "delete from manuscript where manuscript_id = '" + manuscriptId + "'";

    std::cout << "删除稿件sql：" << sql << std::endl;

    Delete(sql);
}

void ManuscriptBroker::addManuscript(const std::string &id, const std::string &description, const std::string &title, const std::string &label, const std::string &subarea, bool isOriginal, const std::string &cover, const std::string &date, const std::string& netizenId)
{
    std::string sql = "insert into manuscript values( '" + id + "', '" + description + "', '" + title + "','" + label + "','" + subarea + "'," + std::to_string(isOriginal) + ",'" + cover + "','" + date + "','" + netizenId +"');";

    insert(sql);
    std::cout << "添加稿件sql：" << sql << std::endl;
}



ManuscriptBroker::ManuscriptBroker()
{

}
