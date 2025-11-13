#pragma once
#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "MenuItem.h"

class Menu {
private:
    std::vector<MenuItem> items;

public:
    Menu();

    // Базовые операции с коллекцией
    void addItem(const MenuItem& item);
    void removeItem(int itemId);
    MenuItem* findItemById(int itemId);
    std::vector<MenuItem> findItemsByCategory(const std::string& category) const;
    std::vector<MenuItem> getAvailableItems() const;

    // Геттеры
    std::vector<MenuItem> getItems() const;
    int getItemCount() const;
};

#endif