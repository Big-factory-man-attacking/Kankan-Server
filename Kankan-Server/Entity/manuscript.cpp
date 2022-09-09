#include "manuscript.h"
#include "videoproxy.h"
#include <utility>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

Manuscript::Manuscript(std::string id, std::string description, std::string title, std::string label,
                       std::string subarea, bool isOriginal, std::string cover, std::string date,
                       std::vector<std::string> commentIds, std::string videoId) :
    m_id{id}, m_description{description}, m_title{title},
    m_label{label}, m_subarea{subarea}, m_isOriginal{isOriginal},
    m_cover{cover}, m_date{date}, m_video(std::make_pair(videoId, VideoProxy(videoId)))
{
    for (auto commentId : commentIds)
        _comments.insert(std::make_pair(commentId, CommentProxy(commentId)));
}

Manuscript::~Manuscript()
{

}

nlohmann::json Manuscript::getManuscriptInfo()
{
    json manuscriptInfo;

    manuscriptInfo["id"] = m_id;
    manuscriptInfo["description"] = m_description;
    manuscriptInfo["title"] = m_title;
    manuscriptInfo["label"] = m_label;
    manuscriptInfo["subarea"] = m_subarea;
    manuscriptInfo["isOriginal"] = std::to_string(m_isOriginal);
    manuscriptInfo["cover"] = m_cover;
    manuscriptInfo["date"] = m_date;
    manuscriptInfo["videoAddress"] = m_video.second.getVideoInfo(m_video.first);

    for (auto& comment: _comments) {
        json com;
        com["text"] = comment.second.getCommentInfo(comment.first);
        manuscriptInfo["comments"].push_back(com);
    }
    if (_comments.size() == 0) manuscriptInfo["comments"] = "";


    return manuscriptInfo;
}

void Manuscript::addNewComment(std::string &commentId, const std::string &netizenId, const std::string &text)
{
    CommentProxy commentProxy(commentId);
    _comments.insert(std::make_pair(commentId, commentProxy));
    commentProxy.addNewComment(text, m_id, netizenId);
}

void Manuscript::deleteComment(std::string &commentId)
{
    CommentProxy commentProxy(commentId);
    commentProxy.deleteComment();   //删除数据库中对应的评论数据
    _comments.erase(commentId);
}

void Manuscript::modifyManuscriptInfo(std::string description, std::string title, std::string label,
                                      std::string subarea, bool isOriginal, std::string cover, std::string date)
{
    m_description = description;
    m_title = title;
    m_label = label;
    m_subarea = subarea;
    m_isOriginal = isOriginal;
    m_cover = cover;
    m_date = date;
}
