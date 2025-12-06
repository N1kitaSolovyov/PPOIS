#include "EmailNewsletter.h"
#include <iostream>

EmailNewsletter::EmailNewsletter(int id, const std::string& subj, const std::string& cont)
    : newsletterId(id), subject(subj), content(cont), isSent(false), templateType("basic") {
}

void EmailNewsletter::addRecipient(const std::string& email) {
    recipientEmails.push_back(email);
}

void EmailNewsletter::send() {
    if (!recipientEmails.empty()) {
        isSent = true;
        std::cout << "Newsletter sent to " << recipientEmails.size() << " recipients" << std::endl;
    }
}

void EmailNewsletter::setTemplate(const std::string& templateName) {
    templateType = templateName;
}

int EmailNewsletter::getRecipientCount() const {
    return static_cast<int>(recipientEmails.size());
}

bool EmailNewsletter::isNewsletterSent() const {
    return isSent;
}