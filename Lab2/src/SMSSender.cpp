#include "SMSSender.h"
#include <iostream>

SMSSender::SMSSender() : apiKey("default_key"), senderId("Restaurant"), isConnected(false) {}

void SMSSender::setApiKey(const std::string& key) {
    apiKey = key;
}

void SMSSender::setSenderId(const std::string& id) {
    senderId = id;
}

bool SMSSender::connect() {
    isConnected = !apiKey.empty();
    std::cout << "SMS Service " << (isConnected ? "connected" : "disconnected") << std::endl;
    return isConnected;
}

bool SMSSender::sendSMS(const std::string& phoneNumber, const std::string& message) {
    if (!isConnected) {
        std::cout << "SMS Service not connected" << std::endl;
        return false;
    }

    if (phoneNumber.empty() || message.empty()) {
        return false;
    }

    // Simulate SMS sending
    std::cout << "SENDING SMS [" << senderId << "] to " << phoneNumber << ": " << message << std::endl;
    return true;
}

std::string SMSSender::getStatus() const {
    return isConnected ? "Connected" : "Disconnected";
}

void SMSSender::disconnect() {
    isConnected = false;
    std::cout << "SMS Service disconnected" << std::endl;
}