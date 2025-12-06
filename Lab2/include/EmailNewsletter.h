#pragma once
#ifndef EMAIL_NEWSLETTER_H
#define EMAIL_NEWSLETTER_H

#include <string>
#include <vector>

class EmailNewsletter {
private:
    int newsletterId;
    std::string subject;
    std::string content;
    std::vector<std::string> recipientEmails;
    bool isSent;
    std::string templateType;

public:
    EmailNewsletter(int id, const std::string& subj, const std::string& cont);
    void addRecipient(const std::string& email);
    void send();
    void setTemplate(const std::string& templateName);
    int getRecipientCount() const;
    bool isNewsletterSent() const;
};

#endif