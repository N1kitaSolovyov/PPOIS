#include "PushNotification.h"
#include <iostream>

PushNotification::PushNotification() : serverKey("default_server_key"), isActive(true) {}

void PushNotification::setServerKey(const std::string& key) {
    serverKey = key;
}

void PushNotification::registerCustomer(int customerId, const std::string& deviceToken) {
    customerTokens[customerId] = deviceToken;
    std::cout << "Customer " << customerId << " registered for push notifications" << std::endl;
}

void PushNotification::unregisterCustomer(int customerId) {
    customerTokens.erase(customerId);
    std::cout << "Customer " << customerId << " unregistered from push notifications" << std::endl;
}

bool PushNotification::sendNotification(int customerId, const std::string& message) {
    if (!isActive) {
        std::cout << "Push notifications are disabled" << std::endl;
        return false;
    }

    auto it = customerTokens.find(customerId);
    if (it != customerTokens.end()) {
        std::cout << "PUSH NOTIFICATION to customer " << customerId << " [" << it->second << "]: " << message << std::endl;
        return true;
    }

    std::cout << "Customer " << customerId << " not registered for push notifications" << std::endl;
    return false;
}

bool PushNotification::broadcastNotification(const std::string& message) {
    if (!isActive) return false;

    for (const auto& entry : customerTokens) {
        std::cout << "BROADCAST to customer " << entry.first << ": " << message << std::endl;
    }
    return true;
}

int PushNotification::getRegisteredCount() const {
    return static_cast<int>(customerTokens.size());
}

void PushNotification::setActive(bool active) {
    isActive = active;
    std::cout << "Push notifications " << (active ? "enabled" : "disabled") << std::endl;
}