#include <iostream>
#include "Restaurant.h"

int main() {
    Restaurant restaurant("Gourmet Paradise", "123 Main Street", "555-0123");

    // Регистрация клиентов
    restaurant.registerCustomer("Alice Smith", "555-1001", "alice@email.com");
    restaurant.registerCustomer("Bob Johnson", "555-1002", "bob@email.com");

    // Найм персонала
    restaurant.hireWaiter("John Doe", 25000.0, "555-2001");
    restaurant.hireChef("Gordon Ramsay", 50000.0, "French", 15);

    // Демонстрация работы ресторана
    std::time_t reservationTime = std::time(nullptr) + 86400; // Завтра
    restaurant.makeReservation(1, 1, reservationTime, 4);

    Order* order = restaurant.createOrder(1, 1);
    if (order) {
        restaurant.addItemToOrder(order->getId(), 1, 2); // 2 Caesar Salad
        restaurant.addItemToOrder(order->getId(), 4, 4); // 4 Orange Juice
        restaurant.processOrder(order->getId());
        restaurant.completeOrder(order->getId());

        Payment* payment = restaurant.processPayment(order->getId(), PaymentMethod::CREDIT_CARD);
        if (payment) {
            std::cout << "Payment processed: $" << payment->getAmount() << std::endl;
            delete payment;
        }
    }

    restaurant.generateDailyReport();
    restaurant.generateStaffReport();

    std::cout << "\n=== Restaurant Demo Completed ===" << std::endl;
    return 0;
}