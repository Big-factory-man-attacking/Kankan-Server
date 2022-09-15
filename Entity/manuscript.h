#ifndef MANUSCRIPT_H
#define MANUSCRIPT_H

#include <string>
#include <memory>
#include "manuscriptinterface.h"
#include <vector>
#include <unordered_map>
#include "videoproxy.h"
#include "commentproxy.h"
#include "json.hpp"

class Video;

class Manuscript : public ManuscriptInterface
{
public:
    Manuscript() = delete;
    Manuscript(std::string id, std::string description, std::string title, std::string label,
          std::string subarea, bool isOriginal, std::string cover, std::string date,
          std::vector<std::string> commentIds, std::string videoId);
    ~Manuscript();

    //获取稿件的数据
    nlohmann::json getManuscriptInfo();
    //添加评论
    void addNewComment(std::string& commentId, const std::string& netizenId, const std::string& text);
    //删除评论
    void deleteComment(std::string& commentId);

    // 修改稿件信息
    void modifyManuscriptInfo(std::string description, std::string title, std::string label, std::string subarea,
                         bool isOriginal, std::string cover, std::string date);
private:
    std::string m_id;           //稿件id
    std::string m_description;  //简介
    std::string m_title;        //标题
    std::string m_label;        //标签
    std::string m_subarea;      //分区
    bool m_isOriginal;          //是否是转载
    std::string m_cover;        //封面
    std::string m_date;         //发布时间(需考虑是否使用date)

    std::unordered_map<std::string, CommentProxy> _comments;    // 评论
    std::pair<std::string, VideoProxy> m_video;                 // 视频
};

#endif // MANUSCRIPT_H
