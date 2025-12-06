#pragma once
#ifndef PUSH_NOTIFICATION_H
#define PUSH_NOTIFICATION_H

#include <string>
#include <map>

class PushNotification {
private:
    std::map<int, std::string> customerTokens;
    std::string serverKey;
    bool isActive;

public:
    PushNotification();
    void setServerKey(const std::string& key);
    void registerCustomer(int customerId, const std::string& deviceToken);
    void unregisterCustomer(int customerId);
    bool sendNotification(int customerId, const std::string& message);
    bool broadcastNotification(const std::string& message);
    int getRegisteredCount() const;
    void setActive(bool active);
};

#endif