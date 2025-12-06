#include "Restaurant.h"
#include <iostream>
#include <algorithm>
#include "SecurityIncident.h"
#include "SocialMediaPost.h"

Restaurant::Restaurant(const std::string& name, const std::string& address, const std::string& phone)
    : name(name), address(address), phone(phone),
    mainKitchen(1, "Main Kitchen"), centralInventory(1),
    kitchenCoordinator(mainKitchen), nextOrderId(1),
    nextReservationId(1), nextCustomerId(1), nextDeliveryId(1), currentCampaign(nullptr) {
    initialize();
}

Restaurant::~Restaurant() {
    if (currentCampaign != nullptr) {
        delete currentCampaign;
    }
}

void Restaurant::initialize(int tableCount) {
    // Создаем столы
    for (int i = 1; i <= tableCount; ++i) {
        tables.emplace_back(i, (i % 4) + 2);
    }

    // Добавляем базовые позиции в меню
    addMenuItem("Caesar Salad", 12.99, "appetizer", 4.0);
    addMenuItem("Grilled Salmon", 24.99, "main", 8.0);
    addMenuItem("Chocolate Cake", 8.99, "dessert", 2.0);
    addMenuItem("Orange Juice", 3.99, "beverage", 0.5);

    // Инициализация системы безопасности
    setupSecurity();

    // Настройка уведомлений и склада
    setupDefaultNotificationTemplates();

    // Добавляем начальные товары на склад
    addStockItem("Salmon", "seafood", 50, 15.0);
    addStockItem("Lettuce", "vegetables", 100, 2.0);
    addStockItem("Chocolate", "dessert", 30, 8.0);
    addStockItem("Orange", "beverage", 200, 0.5);

    // Добавляем поставщика по умолчанию
    stockManager.addSupplier("Fresh Foods Inc.", "555-1234");

    std::cout << "Restaurant fully initialized with all systems" << std::endl;
}

void Restaurant::setupSecurity() {
    securitySystem.addCamera(SecurityCamera(1, "main_entrance", "outdoor"));
    securitySystem.addCamera(SecurityCamera(2, "dining_area", "indoor"));
    securitySystem.addCamera(SecurityCamera(3, "kitchen", "indoor"));
    securitySystem.addCamera(SecurityCamera(4, "storage", "indoor"));
    std::cout << "Security system initialized with 4 cameras" << std::endl;
}

Customer* Restaurant::registerCustomer(const std::string& name, const std::string& phone, const std::string& email) {
    int customerId = nextCustomerId++;
    customers.emplace_back(customerId, name, phone);
    if (!email.empty()) {
        customers.back().setEmail(email);
    }
    loyaltyProgram.enrollCustomer(customerId);

    // Интеграция с аналитикой и уведомлениями
    analyticsService.trackCustomerBehavior(customerId, "registered");
    notificationService.registerCustomer(customerId, "device_token_" + std::to_string(customerId));

    std::cout << "Customer " << name << " registered" << std::endl;
    return &customers.back();
}

Customer* Restaurant::findCustomerById(int customerId) {
    for (auto& customer : customers) {
        if (customer.getId() == customerId) {
            return &customer;
        }
    }
    return nullptr;
}

bool Restaurant::makeReservation(int customerId, int tableNumber, std::time_t time, int partySize) {
    Customer* customer = findCustomerById(customerId);
    if (!customer) return false;

    for (auto& table : tables) {
        if (table.getNumber() == tableNumber && table.canAccommodate(partySize) && table.isAvailable()) {
            int reservationId = nextReservationId++;
            reservations.emplace_back(reservationId, customerId, tableNumber, time, partySize);
            table.setStatus(TableStatus::RESERVED);

            // Отправляем уведомление о бронировании
            sendReservationReminder(customerId, reservationId);
            analyticsService.trackCustomerBehavior(customerId, "made_reservation");

            return true;
        }
    }
    return false;
}

bool Restaurant::cancelReservation(int reservationId) {
    auto it = std::remove_if(reservations.begin(), reservations.end(),
        [reservationId](const Reservation& res) {
            return res.getId() == reservationId;
        });

    if (it != reservations.end()) {
        int tableNumber = it->getTableNumber();
        for (auto& table : tables) {
            if (table.getNumber() == tableNumber) {
                table.setStatus(TableStatus::FREE);
                break;
            }
        }
        reservations.erase(it, reservations.end());
        return true;
    }
    return false;
}

Order* Restaurant::createOrder(int customerId, int tableNumber) {
    Customer* customer = findCustomerById(customerId);
    if (!customer) return nullptr;

    int orderId = nextOrderId++;
    activeOrders.emplace_back(orderId, tableNumber, customerId);

    Waiter* waiter = assignWaiterToTable(tableNumber);
    if (waiter) {
        // Связь заказа с официантом
    }

    analyticsService.trackCustomerBehavior(customerId, "order_created");
    return &activeOrders.back();
}

bool Restaurant::addItemToOrder(int orderId, int menuItemId, int quantity) {
    Order* order = findOrderById(orderId);
    MenuItem* menuItem = findMenuItemById(menuItemId);

    if (!order || !menuItem) return false;

    OrderItem item(menuItemId, menuItem->getName(), quantity, menuItem->getBasePrice());
    order->addItem(item);
    return true;
}

bool Restaurant::processOrder(int orderId) {
    Order* order = findOrderById(orderId);
    if (!order) return false;

    return kitchenCoordinator.submitOrderToKitchen(*order);
}

bool Restaurant::completeOrder(int orderId) {
    kitchenCoordinator.completeOrder(orderId);

    Order* order = findOrderById(orderId);
    if (order) {
        Customer* customer = findCustomerById(order->getCustomerId());
        if (customer) {
            double orderTotal = order->calculateTotal();
            loyaltyProgram.addPoints(customer->getId(), orderTotal);

            // Отправляем уведомление и обновляем аналитику
            sendOrderNotification(customer->getId(), orderId);
            analyticsService.trackCustomerBehavior(customer->getId(), "order_completed");

            // Обновляем аналитику продаж с общей суммой заказа
            updateSalesAnalytics("total", orderTotal);
        }
    }
    return true;
}

Order* Restaurant::findOrderById(int orderId) {
    for (auto& order : activeOrders) {
        if (order.getId() == orderId) {
            return &order;
        }
    }
    return nullptr;
}

void Restaurant::hireWaiter(const std::string& name, double salary, const std::string& phone) {
    int waiterId = staffManager.hireEmployee(name, "waiter", salary);
    waiters.emplace_back(waiterId, name, salary, phone);
}

void Restaurant::hireChef(const std::string& name, double salary, const std::string& specialty, int experience) {
    int chefId = staffManager.hireEmployee(name, "chef", salary);
    chefs.emplace_back(chefId, name, salary, specialty, experience);
    mainKitchen.addChef(&chefs.back());
}

Waiter* Restaurant::assignWaiterToTable(int tableNumber) {
    for (auto& waiter : waiters) {
        if (waiter.getAssignedTableCount() < 5) {
            waiter.assignTable(tableNumber);
            return &waiter;
        }
    }
    return nullptr;
}

void Restaurant::addMenuItem(const std::string& name, double price, const std::string& category, double cost) {
    int itemId = static_cast<int>(menu.getItemCount()) + 1;
    menu.addItem(MenuItem(itemId, name, price, category, cost));
}

MenuItem* Restaurant::findMenuItemById(int itemId) {
    return menu.findItemById(itemId);
}

Payment* Restaurant::processPayment(int orderId, PaymentMethod method) {
    Order* order = findOrderById(orderId);
    if (!order) return nullptr;

    double amount = order->calculateTotal();
    int paymentId = static_cast<int>(activeOrders.size()) + 1;

    Payment* payment = new Payment(paymentId, orderId, amount, method);
    if (payment->processPayment()) {
        expenseTracker.addExpense(Expense(paymentId, "revenue", amount, "Order payment"));
        analyticsService.trackCustomerBehavior(order->getCustomerId(), "payment_completed");
        return payment;
    }

    delete payment;
    return nullptr;
}

void Restaurant::recordExpense(const std::string& category, double amount, const std::string& description) {
    int expenseId = static_cast<int>(expenseTracker.getTotalExpenses()) + 1;
    expenseTracker.addExpense(Expense(expenseId, category, amount, description));
}

void Restaurant::generateDailyReport() {
    std::cout << "=== DAILY REPORT: " << name << " ===" << std::endl;
    std::cout << "Active Orders: " << activeOrders.size() << std::endl;
    std::cout << "Reservations: " << reservations.size() << std::endl;
    std::cout << "Customers: " << customers.size() << std::endl;
    std::cout << "Waiters: " << waiters.size() << std::endl;
    std::cout << "Chefs: " << chefs.size() << std::endl;

    double revenue = getDailyRevenue();
    std::cout << "Daily Revenue: $" << revenue << std::endl;

    std::cout << "Security Status: " << securitySystem.getSecurityStatus() << std::endl;
    if (currentCampaign != nullptr) {
        std::cout << "Active Marketing Campaign: " << (currentCampaign->isCampaignActive() ? "Yes" : "No") << std::endl;
    }

    std::cout << "Notifications Sent: " << notificationService.getNotificationHistory().size() << std::endl;
    std::cout << "Total Stock Value: $" << stockManager.calculateTotalStockValue() << std::endl;
}

double Restaurant::getDailyRevenue() const {
    double total = 0.0;
    for (const auto& order : activeOrders) {
        total += order.calculateTotal();
    }
    return total;
}

void Restaurant::generateStaffReport() {
    std::cout << "=== STAFF REPORT ===" << std::endl;
    std::cout << "Total Employees: " << staffManager.getTotalEmployees() << std::endl;
    std::cout << "Total Payroll: $" << staffManager.calculateTotalPayroll() << std::endl;
    std::cout << "Average Salary: $" << staffManager.calculateAverageSalary() << std::endl;
}

double Restaurant::getTotalPayroll() const {
    return staffManager.calculateTotalPayroll();
}

void Restaurant::armSecuritySystem() {
    securitySystem.armSystem();
}

void Restaurant::disarmSecuritySystem() {
    securitySystem.disarmSystem();
}

bool Restaurant::checkEmployeeAccess(int employeeId, const std::string& area) {
    return securitySystem.checkAccess(employeeId, area);
}

void Restaurant::recordSecurityIncident(const std::string& incidentType, const std::string& description, int reporterId) {
    SecurityIncident incident(nextReservationId++, incidentType, description, reporterId);
    securitySystem.recordIncident(incident);
    std::cout << "Security incident recorded: " << incidentType << std::endl;
}

void Restaurant::launchMarketingCampaign(const std::string& campaignName, const std::string& targetAudience, double budget) {
    if (currentCampaign != nullptr) {
        stopMarketingCampaign();
    }

    currentCampaign = new MarketingCampaign(nextReservationId++, campaignName, targetAudience, budget);
    currentCampaign->launchCampaign();
}

void Restaurant::stopMarketingCampaign() {
    if (currentCampaign != nullptr) {
        currentCampaign->stopCampaign();
        delete currentCampaign;
        currentCampaign = nullptr;
    }
}

void Restaurant::addNewsletterRecipient(const std::string& email) {
    if (currentCampaign != nullptr) {
        std::cout << "Added recipient to marketing campaign: " << email << std::endl;
    }
}

void Restaurant::createSocialMediaPost(const std::string& platform, const std::string& content) {
    if (currentCampaign != nullptr) {
        SocialMediaPost post(nextReservationId++, platform, content);
        currentCampaign->addSocialMediaPost(post);
        std::cout << "Social media post created for " << platform << std::endl;
    }
}

// Новые методы интеграции
void Restaurant::generateAnalyticsReport() {
    std::cout << "=== ADVANCED ANALYTICS REPORT ===" << std::endl;
    analyticsService.generateDailyReport();
}

void Restaurant::sendOrderNotification(int customerId, int orderId) {
    Customer* customer = findCustomerById(customerId);
    if (customer && !customer->getPhone().empty()) {
        std::string message = "Dear " + customer->getName() +
            ", your order #" + std::to_string(orderId) +
            " is ready! Thank you for choosing " + name + "!";

        notificationService.sendSMS(customer->getPhone(), message);
        notificationService.sendPushNotification(customerId, message);
    }
}

void Restaurant::sendReservationReminder(int customerId, int reservationId) {
    Customer* customer = findCustomerById(customerId);
    if (customer) {
        std::string message = "Reservation confirmed at " + name +
            ". We look forward to serving you!";

        notificationService.sendSMS(customer->getPhone(), message);
    }
}

void Restaurant::setupDefaultNotificationTemplates() {
    NotificationTemplate reservationTemplate("reservation",
        "Hello {{customer_name}}, your reservation at {{restaurant_name}} is confirmed for {{time}}.");
    NotificationTemplate orderTemplate("order_ready",
        "Dear {{customer_name}}, your order #{{order_id}} is ready. Total: ${{amount}}.");

    notificationService.addTemplate(reservationTemplate);
    notificationService.addTemplate(orderTemplate);

    notificationService.getSMSSender().setApiKey("restaurant_sms_api_key");
    notificationService.getSMSSender().connect();
}

void Restaurant::addStockItem(const std::string& name, const std::string& category, int quantity, double cost) {
    stockManager.addStockItem(name, category, quantity, cost);
}

void Restaurant::processStockDelivery(int supplierId, const std::vector<std::pair<std::string, int>>& items) {
    std::time_t deliveryTime = std::time(nullptr) + 86400;
    Delivery delivery(nextDeliveryId++, supplierId, deliveryTime);

    for (const auto& item : items) {
        StockItem* stockItem = stockManager.findItemByName(item.first);
        if (stockItem) {
            delivery.addItem(stockItem->getId(), item.second);
        }
    }

    stockManager.processDelivery(delivery);
    std::cout << "Processed delivery from supplier " << supplierId << std::endl;
}

void Restaurant::checkLowStockItems() {
    auto lowStockItems = stockManager.getLowStockItems(10);
    if (!lowStockItems.empty()) {
        std::cout << "LOW STOCK ALERT: " << lowStockItems.size() << " items need restocking" << std::endl;
        for (const auto& item : lowStockItems) {
            std::cout << " - " << item.getName() << " (only " << item.getQuantity() << " left)" << std::endl;
        }

        notificationService.sendSMS("555-MANAGER",
            "Low stock alert: " + std::to_string(lowStockItems.size()) + " items need attention.");
    }
}

void Restaurant::generateInventoryReport() {
    stockManager.generateInventoryReport();
    std::cout << "Total Stock Value: $" << stockManager.calculateTotalStockValue() << std::endl;
}

void Restaurant::trackCustomerBehavior(int customerId, const std::string& behavior) {
    analyticsService.trackCustomerBehavior(customerId, behavior);
}

void Restaurant::updateSalesAnalytics(const std::string& category, double amount) {
    analyticsService.trackSalesData(category, amount);
}