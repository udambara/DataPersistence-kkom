#include "DataPersistence/OrderWorkflow.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>

namespace dp {

namespace {

long long NowEpochSec() {
    return static_cast<long long>(std::time(nullptr));
}

}

OrderWorkflow::OrderWorkflow(SampleRepository& sampleRepo, OrderRepository& orderRepo)
    : m_sampleRepo(sampleRepo), m_orderRepo(orderRepo) {}

bool OrderWorkflow::IsLineBusy(const std::vector<Order>& orders) const {
    return std::any_of(orders.begin(), orders.end(), [](const Order& o) {
        return o.status == OrderStatus::PRODUCING && o.productionStartEpochSec > 0;
    });
}

void OrderWorkflow::Approve(Order order) {
    std::optional<Sample> sample = m_sampleRepo.FindById(order.sampleId);
    if (!sample.has_value()) {
        return;
    }

    if (sample->stock >= order.quantity) {
        order.status = OrderStatus::CONFIRMED;
        m_orderRepo.Update(order);
        return;
    }

    int shortage = order.quantity - sample->stock;
    int actualProductionQty = static_cast<int>(std::ceil(shortage / sample->yield));

    order.status = OrderStatus::PRODUCING;
    order.shortageQty = shortage;
    order.totalProductionSeconds =
        static_cast<long long>(sample->avgProductionTimeMinutes * actualProductionQty);

    bool lineBusy = IsLineBusy(m_orderRepo.GetAll());
    order.productionStartEpochSec = lineBusy ? 0 : NowEpochSec();

    m_orderRepo.Update(order);
}

void OrderWorkflow::Reject(Order order) {
    order.status = OrderStatus::REJECTED;
    m_orderRepo.Update(order);
}

void OrderWorkflow::Tick() {
    std::vector<Order> orders = m_orderRepo.GetAll();

    auto currentIt = std::find_if(orders.begin(), orders.end(), [](const Order& o) {
        return o.status == OrderStatus::PRODUCING && o.productionStartEpochSec > 0;
    });

    if (currentIt != orders.end()) {
        long long elapsed = NowEpochSec() - currentIt->productionStartEpochSec;
        if (elapsed >= currentIt->totalProductionSeconds) {
            std::string errorMessage;
            m_sampleRepo.AdjustStock(currentIt->sampleId, currentIt->shortageQty, errorMessage);
            currentIt->status = OrderStatus::CONFIRMED;
            m_orderRepo.Update(*currentIt);
            orders = m_orderRepo.GetAll();
        }
    }

    if (IsLineBusy(orders)) {
        return;
    }

    auto waitingIt = std::find_if(orders.begin(), orders.end(), [](const Order& o) {
        return o.status == OrderStatus::PRODUCING && o.productionStartEpochSec == 0;
    });
    if (waitingIt != orders.end()) {
        waitingIt->productionStartEpochSec = NowEpochSec();
        m_orderRepo.Update(*waitingIt);
    }
}

}
