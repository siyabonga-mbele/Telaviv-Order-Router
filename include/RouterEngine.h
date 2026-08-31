#pragma once
#include "OrderQueue.h"
#include "WorkerPool.h"
#include "TelemetryMetrics.h"

class RouterEngine {
private:
    OrderQueue queue;
    TelemetryMetrics metrics;
    WorkerPool workerPool;

public:
    RouterEngine();
    void SubmitOrder(const Order& order);
    void StartEngine(size_t threadCount);
    void StopEngine();
    uint64_t GetProcessedCount() const;
};