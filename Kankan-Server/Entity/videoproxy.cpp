#include "videoproxy.h"
#include "../SqlCon/videobroker.h"

VideoProxy::VideoProxy(std::string &id) : m_id{id}
{

}

VideoProxy::~VideoProxy()
{

}

std::string VideoProxy::getVideoInfo(std::string id)
{
    if (m_video == nullptr)
        m_video = VideoBroker::getInstance()->getVideo(id);
    return m_video->getVideoInfo();
}
