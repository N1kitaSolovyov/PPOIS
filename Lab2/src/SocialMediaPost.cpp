#include "SocialMediaPost.h"
#include <iostream>

SocialMediaPost::SocialMediaPost(int id, const std::string& plat, const std::string& cont)
    : postId(id), platform(plat), content(cont), likes(0), shares(0), isPublished(false) {
    scheduledTime = std::time(nullptr);
}

void SocialMediaPost::publish() {
    isPublished = true;
    std::cout << "Post published on " << platform << std::endl;
}

void SocialMediaPost::schedule(std::time_t scheduleTime) {
    scheduledTime = scheduleTime;
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &scheduleTime);
    std::cout << "Post scheduled for " << buffer;
}

void SocialMediaPost::addLike() {
    likes++;
}

void SocialMediaPost::addShare() {
    shares++;
}

std::string SocialMediaPost::getEngagementRate() const {
    return "Likes: " + std::to_string(likes) + ", Shares: " + std::to_string(shares);
}

bool SocialMediaPost::isPostPublished() const {
    return isPublished;
}