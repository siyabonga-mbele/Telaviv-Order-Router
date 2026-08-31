#include "../include/RouterEngine.h"

RouterEngine::RouterEngine() : workerPool(queue, metrics) {}

void RouterEngine::SubmitOrder(const Order& order) {
    queue.Push(order);
}

void RouterEngine::StartEngine(size_t threadCount) {
    workerPool.Start(threadCount);
}

void RouterEngine::StopEngine() {
    workerPool.Stop();
}

uint64_t RouterEngine::GetProcessedCount() const {
    return metrics.GetTotalProcessed();
}