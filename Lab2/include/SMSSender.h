#pragma once
#ifndef SMS_SENDER_H
#define SMS_SENDER_H

#include <string>

class SMSSender {
private:
    std::string apiKey;
    std::string senderId;
    bool isConnected;

public:
    SMSSender();
    void setApiKey(const std::string& key);
    void setSenderId(const std::string& id);
    bool connect();
    bool sendSMS(const std::string& phoneNumber, const std::string& message);
    std::string getStatus() const;
    void disconnect();
};

#endif