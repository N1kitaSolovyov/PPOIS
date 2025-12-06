#pragma once
#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>

class Supplier {
private:
    int id;
    std::string name;
    std::string contactInfo;
    std::vector<std::string> suppliedItems;
    double rating;
    bool isActive;

public:
    Supplier(int supplierId, const std::string& supplierName, const std::string& contact);
    void addSuppliedItem(const std::string& itemName);
    void removeSuppliedItem(const std::string& itemName);
    void setRating(double newRating);
    void setActive(bool active);
    int getId() const;
    std::string getName() const;
    std::string getContactInfo() const;
    double getRating() const;
    bool getIsActive() const;
    std::vector<std::string> getSuppliedItems() const;
    std::string getStatus() const;
};

#endif