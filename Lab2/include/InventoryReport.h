#pragma once
#ifndef INVENTORY_REPORT_H
#define INVENTORY_REPORT_H

#include "Report.h"
#include <map>
#include <vector>

class InventoryReport : public Report {
private:
    std::map<std::string, int> currentStock;
    std::map<std::string, int> lowStockItems;
    double totalInventoryValue;
    int lowStockThreshold;

public:
    InventoryReport(int id, const std::string& title);

    void addStockItem(const std::string& itemName, int quantity, double unitCost = 0.0);
    void analyzeStockLevels();

    void generate() override;
    void display() const override;

    void setLowStockThreshold(int threshold);
    std::vector<std::string> getLowStockItems() const;
};

#endif