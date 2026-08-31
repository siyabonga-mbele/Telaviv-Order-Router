#include "../include/WorkerPool.h"
#include <iostream>
#include <chrono>

WorkerPool::WorkerPool(OrderQueue& queue, TelemetryMetrics& metrics)
    : orderQueue(queue), metrics(metrics), running(false) {}

void WorkerPool::WorkerLoop(int workerId) {
    while (running) {
        Order order;
        if (orderQueue.Pop(order)) {
            // Simulate processing order with liquidity providers
            metrics.RecordOrderProcessed();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void WorkerPool::Start(size_t threadCount) {
    running = true;
    for (size_t i = 0; i < threadCount; ++i) {
        workers.emplace_back(&WorkerPool::WorkerLoop, this, i + 1);
    }
}

void WorkerPool::Stop() {
    running = false;
}

// BROKEN [ROUT-204]: Destructor does not call join() on worker threads leading to std::terminate
WorkerPool::~WorkerPool() {
    Stop();
}