#pragma once

#include <string>
#include "third_party/nlohmann/json.hpp"

namespace dp {

enum class OrderStatus {
    RESERVED,
    CONFIRMED,
    PRODUCING,
    RELEASE,
    REJECTED
};

std::string ToString(OrderStatus status);
OrderStatus OrderStatusFromString(const std::string& text);

struct Order {
    std::string id;
    std::string sampleId;
    std::string customerName;
    int quantity = 0;
    OrderStatus status = OrderStatus::RESERVED;
};

void to_json(nlohmann::json& j, const Order& o);
void from_json(const nlohmann::json& j, Order& o);

}
