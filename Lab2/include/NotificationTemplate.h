#pragma once
#ifndef NOTIFICATION_TEMPLATE_H
#define NOTIFICATION_TEMPLATE_H

#include <string>
#include <map>

class NotificationTemplate {
private:
    std::string name;
    std::string content;
    std::map<std::string, std::string> variables;

public:
    NotificationTemplate(const std::string& templateName, const std::string& templateContent);
    void setVariable(const std::string& key, const std::string& value);
    std::string generateMessage(const std::map<std::string, std::string>& parameters) const;
    std::string getName() const;
    void setContent(const std::string& newContent);
    std::string getContent() const;
};

#endif#pragma once
