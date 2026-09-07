#include "../include/TelemetryMetrics.h"

TelemetryMetrics::TelemetryMetrics() : processedOrderCount(0) {}

// BROKEN [ROUT-201]: Concurrent writes from multiple worker threads cause data races!
void TelemetryMetrics::RecordOrderProcessed() {
    //processedOrderCount++;
    processedOrderCount.fetch_add(1, std::memory_order_relaxed);
}

uint64_t TelemetryMetrics::GetTotalProcessed() const {
    return processedOrderCount.load(std::memory_order_relaxed);
}

void TelemetryMetrics::Reset() {
    // Unimplemented
    processedOrderCount.store(0, std::memory_order_relaxed);
}