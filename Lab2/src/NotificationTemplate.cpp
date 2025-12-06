#include "NotificationTemplate.h"

NotificationTemplate::NotificationTemplate(const std::string& templateName, const std::string& templateContent)
    : name(templateName), content(templateContent) {
}

void NotificationTemplate::setVariable(const std::string& key, const std::string& value) {
    variables[key] = value;
}

std::string NotificationTemplate::generateMessage(const std::map<std::string, std::string>& parameters) const {
    std::string result = content;

    // First replace with template variables
    for (const auto& var : variables) {
        std::string placeholder = "{{" + var.first + "}}";
        size_t pos = 0;
        while ((pos = result.find(placeholder, pos)) != std::string::npos) {
            result.replace(pos, placeholder.length(), var.second);
            pos += var.second.length();
        }
    }

    // Then replace with parameters (override variables)
    for (const auto& param : parameters) {
        std::string placeholder = "{{" + param.first + "}}";
        size_t pos = 0;
        while ((pos = result.find(placeholder, pos)) != std::string::npos) {
            result.replace(pos, placeholder.length(), param.second);
            pos += param.second.length();
        }
    }

    return result;
}

std::string NotificationTemplate::getName() const {
    return name;
}

void NotificationTemplate::setContent(const std::string& newContent) {
    content = newContent;
}

std::string NotificationTemplate::getContent() const {
    return content;
}