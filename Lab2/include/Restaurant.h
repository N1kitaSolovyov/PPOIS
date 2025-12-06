#pragma once
#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <vector>
#include <algorithm>
#include "Menu.h"
#include "Kitchen.h"
#include "Inventory.h"
#include "Table.h"
#include "Waiter.h"
#include "Chef.h"
#include "Customer.h"
#include "Reservation.h"
#include "Order.h"
#include "Payment.h"
#include "StaffManager.h"
#include "LoyaltyProgram.h"
#include "ExpenseTracker.h"
#include "KitchenOrderCoordinator.h"
#include "SecuritySystem.h"
#include "MarketingCampaign.h"
#include "AnalyticsService.h"
#include "NotificationService.h"
#include "StockManager.h"
#include "Delivery.h"

class Restaurant {
private:
    std::string name;
    std::string address;
    std::string phone;

    Menu menu;
    Kitchen mainKitchen;
    Inventory centralInventory;
    KitchenOrderCoordinator kitchenCoordinator;

    std::vector<Table> tables;
    std::vector<Waiter> waiters;
    std::vector<Chef> chefs;
    std::vector<Customer> customers;
    std::vector<Reservation> reservations;
    std::vector<Order> activeOrders;

    StaffManager staffManager;
    LoyaltyProgram loyaltyProgram;
    ExpenseTracker expenseTracker;

    SecuritySystem securitySystem;
    MarketingCampaign* currentCampaign;

    AnalyticsService analyticsService;
    NotificationService notificationService;
    StockManager stockManager;

    int nextOrderId;
    int nextReservationId;
    int nextCustomerId;
    int nextDeliveryId;

public:
    Restaurant(const std::string& name, const std::string& address, const std::string& phone);
    ~Restaurant();

    void initialize(int tableCount = 20);

    // Основные операции
    Customer* registerCustomer(const std::string& name, const std::string& phone, const std::string& email = "");
    Customer* findCustomerById(int customerId);
    bool makeReservation(int customerId, int tableNumber, std::time_t time, int partySize);
    bool cancelReservation(int reservationId);
    Order* createOrder(int customerId, int tableNumber);
    bool addItemToOrder(int orderId, int menuItemId, int quantity);
    bool processOrder(int orderId);
    bool completeOrder(int orderId);
    Order* findOrderById(int orderId);

    // Управление персоналом
    void hireWaiter(const std::string& name, double salary, const std::string& phone = "");
    void hireChef(const std::string& name, double salary, const std::string& specialty = "general", int experience = 1);
    Waiter* assignWaiterToTable(int tableNumber);

    // Управление меню
    void addMenuItem(const std::string& name, double price, const std::string& category, double cost = 0.0);
    MenuItem* findMenuItemById(int itemId);

    // Финансовые операции
    Payment* processPayment(int orderId, PaymentMethod method);
    void recordExpense(const std::string& category, double amount, const std::string& description);

    // Отчетность
    void generateDailyReport();
    double getDailyRevenue() const;
    void generateStaffReport();
    double getTotalPayroll() const;

    // Безопасность и маркетинг
    void setupSecurity();
    void armSecuritySystem();
    void disarmSecuritySystem();
    bool checkEmployeeAccess(int employeeId, const std::string& area);
    void recordSecurityIncident(const std::string& incidentType, const std::string& description, int reporterId);

    void launchMarketingCampaign(const std::string& campaignName, const std::string& targetAudience, double budget);
    void stopMarketingCampaign();
    void addNewsletterRecipient(const std::string& email);
    void createSocialMediaPost(const std::string& platform, const std::string& content);

    // Интеграция с новыми модулями
    void generateAnalyticsReport();
    void sendOrderNotification(int customerId, int orderId);
    void sendReservationReminder(int customerId, int reservationId);
    void setupDefaultNotificationTemplates();

    void addStockItem(const std::string& name, const std::string& category, int quantity, double cost);
    void processStockDelivery(int supplierId, const std::vector<std::pair<std::string, int>>& items);
    void checkLowStockItems();
    void generateInventoryReport();

    void trackCustomerBehavior(int customerId, const std::string& behavior);
    void updateSalesAnalytics(const std::string& category, double amount);

    // Геттеры
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getPhone() const { return phone; }
    Menu& getMenu() { return menu; }
    Kitchen& getKitchen() { return mainKitchen; }
    Inventory& getInventory() { return centralInventory; }
    std::vector<Table> getTables() const { return tables; }
    std::vector<Waiter> getWaiters() const { return waiters; }
    std::vector<Chef> getChefs() const { return chefs; }
    std::vector<Customer> getCustomers() const { return customers; }
    std::vector<Reservation> getReservations() const { return reservations; }
    SecuritySystem& getSecuritySystem() { return securitySystem; }
    MarketingCampaign* getCurrentCampaign() { return currentCampaign; }
    AnalyticsService& getAnalyticsService() { return analyticsService; }
    NotificationService& getNotificationService() { return notificationService; }
    StockManager& getStockManager() { return stockManager; }

    // Сеттеры
    void setName(const std::string& newName) { name = newName; }
    void setAddress(const std::string& newAddress) { address = newAddress; }
    void setPhone(const std::string& newPhone) { phone = newPhone; }
};

#endif