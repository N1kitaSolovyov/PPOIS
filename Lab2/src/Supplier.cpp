#include "Supplier.h"
#include <algorithm>

Supplier::Supplier(int supplierId, const std::string& supplierName, const std::string& contact)
    : id(supplierId), name(supplierName), contactInfo(contact), rating(0.0), isActive(true) {
}

void Supplier::addSuppliedItem(const std::string& itemName) {
    suppliedItems.push_back(itemName);
}

void Supplier::removeSuppliedItem(const std::string& itemName) {
    suppliedItems.erase(
        std::remove(suppliedItems.begin(), suppliedItems.end(), itemName),
        suppliedItems.end()
    );
}

void Supplier::setRating(double newRating) {
    rating = newRating;
}

void Supplier::setActive(bool active) {
    isActive = active;
}

int Supplier::getId() const {
    return id;
}

std::string Supplier::getName() const {
    return name;
}

std::string Supplier::getContactInfo() const {
    return contactInfo;
}

double Supplier::getRating() const {
    return rating;
}

bool Supplier::getIsActive() const {
    return isActive;
}

std::vector<std::string> Supplier::getSuppliedItems() const {
    return suppliedItems;
}

std::string Supplier::getStatus() const {
    return isActive ? "ACTIVE" : "INACTIVE";
}