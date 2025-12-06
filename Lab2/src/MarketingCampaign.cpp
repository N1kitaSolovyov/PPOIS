#include "MarketingCampaign.h"
#include <iostream>

MarketingCampaign::MarketingCampaign(int id, const std::string& campaignName,
    const std::string& audience, double campaignBudget)
    : campaignId(id), name(campaignName), targetAudience(audience),
    budget(campaignBudget), isActive(false),
    newsletter(id, "Welcome to " + campaignName, "Join our campaign!") {
}

void MarketingCampaign::launchCampaign() {
    isActive = true;
    std::cout << "Marketing campaign '" << name << "' launched!" << std::endl;
}

void MarketingCampaign::stopCampaign() {
    isActive = false;
    std::cout << "Marketing campaign '" << name << "' stopped." << std::endl;
}

void MarketingCampaign::addSocialMediaPost(const SocialMediaPost& post) {
    socialMediaPosts.push_back(post);
}

void MarketingCampaign::sendNewsletter() {
    newsletter.send();
}

double MarketingCampaign::calculateROI(double revenue) const {
    return budget > 0 ? (revenue - budget) / budget * 100 : 0.0;
}

bool MarketingCampaign::isCampaignActive() const {
    return isActive;
}