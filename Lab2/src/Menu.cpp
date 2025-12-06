#include "Menu.h"
#include <algorithm>

Menu::Menu() {}

void Menu::addItem(const MenuItem& item) {
    items.push_back(item);
}

void Menu::removeItem(int itemId) {
    items.erase(std::remove_if(items.begin(), items.end(),
        [itemId](const MenuItem& item) {
            return item.getId() == itemId;
        }), items.end());
}

MenuItem* Menu::findItemById(int itemId) {
    for (auto& item : items) {
        if (item.getId() == itemId) return &item;
    }
    return nullptr;
}

std::vector<MenuItem> Menu::findItemsByCategory(const std::string& category) const {
    std::vector<MenuItem> result;
    for (const auto& item : items) {
        if (item.getCategory() == category) result.push_back(item);
    }
    return result;
}

std::vector<MenuItem> Menu::getAvailableItems() const {
    std::vector<MenuItem> result;
    for (const auto& item : items) {
        if (item.getIsAvailable()) result.push_back(item);
    }
    return result;
}

std::vector<MenuItem> Menu::getItems() const { return items; }
int Menu::getItemCount() const { return items.size(); }

std::vector<std::string> Menu::getCategories() const {
    std::vector<std::string> categories;
    for (const auto& item : items) {
        if (std::find(categories.begin(), categories.end(), item.getCategory()) == categories.end()) {
            categories.push_back(item.getCategory());
        }
    }
    return categories;
}