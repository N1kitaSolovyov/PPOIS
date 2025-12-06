#include "OrderItem.h"

OrderItem::OrderItem(int menuItemId, const std::string& itemName,
    int quantity, double unitPrice)
    : menuItemId(menuItemId), itemName(itemName),
    quantity(quantity), unitPrice(unitPrice) {
}

double OrderItem::calculateSubtotal() const {
    return quantity * unitPrice;
}

int OrderItem::getMenuItemId() const { return menuItemId; }
std::string OrderItem::getItemName() const { return itemName; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getUnitPrice() const { return unitPrice; }
std::string OrderItem::getSpecialRequest() const { return specialRequest; }

void OrderItem::setQuantity(int newQuantity) {
    if (newQuantity > 0) quantity = newQuantity;
}

void OrderItem::setSpecialRequest(const std::string& request) {
    specialRequest = request;
}