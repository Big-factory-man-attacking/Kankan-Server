#ifndef MANUSCRIPTBROKER_H
#define MANUSCRIPTBROKER_H

#include "relationalbroker.h"
#include "manuscript.h"

class ManuscriptBroker : public RelationalBroker
{
public:
    ~ManuscriptBroker();
    static ManuscriptBroker* getInstance();

    // 返回稿件对象
    // id：稿件id
    std::shared_ptr<Manuscript> getManuscript(const std::string& id);

    //获取一些稿件的id
    std::map<std::string, std::string> getManuscripts();

    // 修改稿件的信息
    void modifyManuscriptInfo(const std::string& id, const std::string& description, const std::string& title, const std::string& label,
                              const std::string& subarea, const std::string& isOriginal, const std::string& cover, const std::string& date);

    // 删除稿件
    // manuscriptId：稿件id
    void deleteManuscript(const std::string& manuscriptId);

private:
    ManuscriptBroker();
    static ManuscriptBroker* m_manuscriptBroker;
};

#endif // MANUSCRIPTBROKER_H
