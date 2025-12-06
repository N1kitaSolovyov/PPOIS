#pragma once
#ifndef MARKETING_CAMPAIGN_H
#define MARKETING_CAMPAIGN_H

#include <string>
#include <vector>
#include "SocialMediaPost.h"
#include "EmailNewsletter.h"

class MarketingCampaign {
private:
    int campaignId;
    std::string name;
    std::string targetAudience;
    double budget;
    std::vector<SocialMediaPost> socialMediaPosts;
    EmailNewsletter newsletter;
    bool isActive;

public:
    MarketingCampaign(int id, const std::string& campaignName,
        const std::string& audience, double campaignBudget);
    void launchCampaign();
    void stopCampaign();
    void addSocialMediaPost(const SocialMediaPost& post);
    void sendNewsletter();
    double calculateROI(double revenue) const;
    bool isCampaignActive() const;
};

#endif