# Лабораторная работа №2: Система управления рестораном


| Entity | Fields | Behaviors | Associations |
|--------|--------|-----------|-------------|
| AccessControl | 2 | 6 | → |
| AnalyticsService | 4 | 9 | → CustomerAnalytics, SalesAnalytics, PerformanceMetrics |
| Chef | 3 | 7 | → Order |
| Customer | 6 | 12 | → |
| CustomerAnalytics | 4 | 11 | → |
| Delivery | 7 | 15 | → Supplier, StockItem |
| Discount | 7 | 14 | → |
| DiscountService | 0 | 5 | → Customer, Order, Discount |
| EmailNewsletter | 6 | 6 | → |
| Employee | 7 | 12 | → |
| Expense | 6 | 8 | → |
| ExpenseTracker | 3 | 8 | → Expense |
| InsufficientFundsException | 0 | 0 | → |
| InvalidPasswordException | 0 | 0 | → |
| TableNotAvailableException | 0 | 0 | → |
| ReservationConflictException | 0 | 0 | → |
| OrderProcessingException | 0 | 0 | → |
| InventoryShortageException | 0 | 0 | → |
| PaymentFailedException | 0 | 0 | → |
| CustomerNotFoundException | 0 | 0 | → |
| EmployeeNotAvailableException | 0 | 0 | → |
| MenuItemUnavailableException | 0 | 0 | → |
| DiscountExpiredException | 0 | 0 | → |
| KitchenOverloadException | 0 | 0 | → |
| Inventory | 3 | 7 | → |
| InventoryReport | 4 | 7 | → Report |
| Kitchen | 5 | 8 | → Order, Chef |
| KitchenOrderCoordinator | 3 | 6 | → Kitchen, Order |
| LoyaltyProgram | 3 | 8 | → |
| MarketingCampaign | 7 | 7 | → EmailNewsletter, SocialMediaPost |
| Menu | 1 | 9 | → MenuItem |
| MenuItem | 8 | 16 | → |
| NotificationService | 4 | 9 | → SMSSender, PushNotification, NotificationTemplate |
| NotificationTemplate | 3 | 6 | → |
| Order | 9 | 22 | → OrderItem |
| OrderItem | 5 | 9 | → MenuItem |
| OrderStatus | 0 | 0 | → |
| Payment | 7 | 9 | → Order |
| PaymentMethod | 0 | 0 | → |
| PaymentStatus | 0 | 0 | → |
| PerformanceMetrics | 2 | 9 | → |
| PricingService | 1 | 6 | → MenuItem, Discount, Order |
| PushNotification | 3 | 8 | → |
| Report | 6 | 6 | → |
| Reservation | 7 | 12 | → Customer, Table |
| ReservationService | 0 | 5 | → Reservation, Table |
| Restaurant | 25 | 42 | → Table, Customer, Reservation, Order, Waiter, Chef, Menu, MenuItem, Payment, SecuritySystem, LoyaltyProgram, AnalyticsService, NotificationService, ExpenseTracker, StaffManager, StockManager, Delivery, MarketingCampaign |
| SalesAnalytics | 4 | 9 | → |
| SalesReport | 4 | 8 | → Report |
| SecurityCamera | 5 | 7 | → |
| SecurityIncident | 6 | 5 | → Employee |
| SecurityMonitor | 1 | 3 | → SecurityIncident |
| SecuritySystem | 5 | 8 | → SecurityCamera, SecurityMonitor, AccessControl |
| Shift | 7 | 11 | → Employee |
| ShiftSchedule | 2 | 8 | → Shift |
| SMSSender | 3 | 7 | → |
| SocialMediaPost | 7 | 7 | → |
| StaffManager | 4 | 16 | → Employee, Chef, Waiter, Shift |
| StockItem | 8 | 15 | → |
| StockManager | 7 | 13 | → StockItem, Supplier, Delivery |
| Supplier | 6 | 12 | → |
| Table | 3 | 7 | → |
| TableStatus | 0 | 0 | → |
| TaxCalculator | 1 | 5 | → MenuItem, Order |
| Waiter | 2 | 7 | → Table |

## Итоговая статистика

- **Всего классов:** 65
- **Поля:** 193
- **Поведения:** 275
- **Ассоциации:** 67
