#pragma once
#ifndef SOCIAL_MEDIA_POST_H
#define SOCIAL_MEDIA_POST_H

#include <string>
#include <ctime>

class SocialMediaPost {
private:
    int postId;
    std::string platform; // "instagram", "facebook", "twitter"
    std::string content;
    std::time_t scheduledTime;
    int likes;
    int shares;
    bool isPublished;

public:
    SocialMediaPost(int id, const std::string& plat, const std::string& cont);
    void publish();
    void schedule(std::time_t scheduleTime);
    void addLike();
    void addShare();
    std::string getEngagementRate() const;
    bool isPostPublished() const;
};

#endif