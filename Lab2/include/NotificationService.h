#pragma once
#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <vector>
#include <string>
#include <memory>
#include "SMSSender.h"
#include "PushNotification.h"
#include "NotificationTemplate.h"

class NotificationService {
private:
    SMSSender smsSender;
    PushNotification pushNotification;
    std::vector<NotificationTemplate> templates;
    std::vector<std::string> sentNotifications;

public:
    NotificationService();
    void sendSMS(const std::string& phoneNumber, const std::string& message);
    void sendPushNotification(int customerId, const std::string& message);
    void addTemplate(const NotificationTemplate& newTemplate); // Исправлено: newTemplate вместо template
    void sendTemplatedNotification(int customerId, const std::string& templateName,
        const std::map<std::string, std::string>& parameters);
    std::vector<std::string> getNotificationHistory() const;
    void clearHistory();
    void registerCustomer(int customerId, const std::string& deviceToken);
    SMSSender& getSMSSender();
};

#endif