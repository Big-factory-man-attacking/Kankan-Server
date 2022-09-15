#ifndef VIDEOPROXY_H
#define VIDEOPROXY_H

#include <memory>
#include "videointerface.h"
#include <vector>
#include <string>

class Video;

class VideoProxy : public VideoInterface
{
public:
    VideoProxy(std::string& id);
    ~VideoProxy();

    // 获取视频的地址
    std::string getVideoInfo(std::string& id);
private:
    std::string m_id;
    std::shared_ptr<Video> m_video;
};

#endif // VIDEOPROXY_H
