#include "NotificationService.h"
#include <iostream>

NotificationService::NotificationService() {}

void NotificationService::sendSMS(const std::string& phoneNumber, const std::string& message) {
    if (smsSender.sendSMS(phoneNumber, message)) {
        sentNotifications.push_back("SMS to " + phoneNumber + ": " + message);
        std::cout << "SMS sent successfully to " << phoneNumber << std::endl;
    }
    else {
        std::cout << "Failed to send SMS to " << phoneNumber << std::endl;
    }
}

void NotificationService::sendPushNotification(int customerId, const std::string& message) {
    if (pushNotification.sendNotification(customerId, message)) {
        sentNotifications.push_back("Push to customer " + std::to_string(customerId) + ": " + message);
        std::cout << "Push notification sent to customer " << customerId << std::endl;
    }
    else {
        std::cout << "Failed to send push notification to customer " << customerId << std::endl;
    }
}

// ÈÑÏÐÀÂËÅÍÍÀß ÔÓÍÊÖÈß: ïåðåèìåíîâàí ïàðàìåòð
void NotificationService::addTemplate(const NotificationTemplate& newTemplate) {
    templates.push_back(newTemplate);
}

void NotificationService::sendTemplatedNotification(int customerId, const std::string& templateName,
    const std::map<std::string, std::string>& parameters) {
    for (const auto& temp : templates) {
        if (temp.getName() == templateName) {
            std::string message = temp.generateMessage(parameters);
            sendPushNotification(customerId, message);
            return;
        }
    }
    std::cout << "Template not found: " << templateName << std::endl;
}

std::vector<std::string> NotificationService::getNotificationHistory() const {
    return sentNotifications;
}

void NotificationService::clearHistory() {
    sentNotifications.clear();
}

void NotificationService::registerCustomer(int customerId, const std::string& deviceToken) {
    pushNotification.registerCustomer(customerId, deviceToken);
}

SMSSender& NotificationService::getSMSSender() {
    return smsSender;
}