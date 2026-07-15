#pragma once

#include "DataPersistence/SampleRepository.h"
#include "DataPersistence/OrderRepository.h"

namespace dp {

// Encapsulates the approve/reject decision and the production-line advancement
// (a demo-speed simulation: minutes of average production time are treated as seconds).
class OrderWorkflow {
public:
    OrderWorkflow(SampleRepository& sampleRepo, OrderRepository& orderRepo);

    // order must currently be RESERVED. Transitions to CONFIRMED (enough stock)
    // or PRODUCING (not enough stock; enqueued on the production line).
    void Approve(Order order);

    // order must currently be RESERVED. Transitions to REJECTED.
    void Reject(Order order);

    // Advances production state: completes the current job if its time has
    // elapsed, and starts the next queued job if the line is idle.
    // Should be called once per menu iteration.
    void Tick();

private:
    SampleRepository& m_sampleRepo;
    OrderRepository& m_orderRepo;

    bool IsLineBusy(const std::vector<Order>& orders) const;
};

}
