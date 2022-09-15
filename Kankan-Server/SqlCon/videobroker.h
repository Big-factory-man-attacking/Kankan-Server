#ifndef VIDEOBROKER_H
#define VIDEOBROKER_H

#include "relationalbroker.h"
#include "../Entity/video.h"

class VideoBroker : public RelationalBroker
{
public:
    virtual ~VideoBroker();
    static VideoBroker* getInstance();
    void addVideo(const std::string& videoId, const std::string& videoAdress, const std::string& manuscriptId);

    std::shared_ptr<Video> getVideo(std::string& id);
private:
    VideoBroker();

    static VideoBroker* m_videoBroker;
};

#endif // VIDEOBROKER_H
