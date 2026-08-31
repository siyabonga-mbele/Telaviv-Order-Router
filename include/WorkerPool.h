#pragma once
#include <vector>
#include <thread>
#include <atomic>
#include "OrderQueue.h"
#include "TelemetryMetrics.h"

class WorkerPool {
private:
    std::vector<std::thread> workers;
    OrderQueue& orderQueue;
    TelemetryMetrics& metrics;
    std::atomic<bool> running;

    void WorkerLoop(int workerId);

public:
    WorkerPool(OrderQueue& queue, TelemetryMetrics& metrics);
    ~WorkerPool(); // BROKEN: Destructor does not properly join threads on shutdown
    void Start(size_t threadCount);
    void Stop();
};