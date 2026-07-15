#pragma once

#include <map>
#include <string>
#include <vector>
#include "DataPersistence/Order.h"

namespace dp {

class OrderRepository {
public:
    explicit OrderRepository(std::string filePath = "data/orders.json");

    bool Add(const Order& order, std::string& errorMessage);

    std::vector<Order> GetAll() const;

    // Counts orders per status, including statuses with zero orders.
    std::map<OrderStatus, int> CountByStatus() const;

private:
    std::string m_filePath;

    std::vector<Order> Load() const;
    void Save(const std::vector<Order>& orders) const;
};

}
