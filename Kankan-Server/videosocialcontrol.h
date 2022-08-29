#ifndef VIDEOSOCIALCONTROL_H
#define VIDEOSOCIALCONTROL_H

#include <string>
#include <memory>
#include <vector>
#include "json.hpp"

extern "C" {
    #include <arpa/inet.h>
};

class Netizen;

class VideoSocialControl
{
public:
    VideoSocialControl();


    // 注册
    // password:用户设置的密码
    void registerAccount(nlohmann::json js);

    // 登录
    // id:用户输入的帐号
    // key:用户输入的密码
    nlohmann::json login(nlohmann::json js);

    // 假设服务器记录每次上传视频的id，保存为一个列表，首页总是显示最新的一批视频
    nlohmann::json getSomeVideos();

    // 用户选择了某个稿件进行观看，加载稿件的完整信息
    nlohmann::json loadVideo(nlohmann::json js);

    // 关注
    // fanId:当前使用者id
    // followerId:被关注者id
    void focusOn(nlohmann::json js);

    // 取关
    // fanId:当前使用者id
    // followerId:被关注者id
    void takeOff(nlohmann::json js);

    // 修改用户头像
    void modifyHeadportrait(nlohmann::json js);

    // 修改用户昵称
    void modifyNickname(nlohmann::json js);

    // 修改用户密码
    nlohmann::json modifyPassword(nlohmann::json js);

    // 修改稿件信息
    void modifyManuscriptInfo(nlohmann::json js);

    // 删除稿件
    void deleteManuscript(nlohmann::json js);

    nlohmann::json handle(nlohmann::json h);
private:
    struct sockaddr_in cliaddr;
};

#endif // VIDEOSOCIALCONTROL_H
