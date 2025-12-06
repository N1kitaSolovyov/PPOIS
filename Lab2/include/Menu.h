#pragma once
#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include <vector>
#include <string>

class Menu {
private:
    std::vector<MenuItem> items;

public:
    Menu();

    // Item management
    void addItem(const MenuItem& item);
    void removeItem(int itemId);
    MenuItem* findItemById(int itemId);
    std::vector<MenuItem> findItemsByCategory(const std::string& category) const;
    std::vector<MenuItem> getAvailableItems() const;

    // Getters
    std::vector<MenuItem> getItems() const;
    int getItemCount() const;
    std::vector<std::string> getCategories() const;
};

#endif