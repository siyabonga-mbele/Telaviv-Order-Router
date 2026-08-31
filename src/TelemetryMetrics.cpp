#include "../include/TelemetryMetrics.h"

TelemetryMetrics::TelemetryMetrics() : processedOrderCount(0) {}

// BROKEN [ROUT-201]: Concurrent writes from multiple worker threads cause data races!
void TelemetryMetrics::RecordOrderProcessed() {
    processedOrderCount++;
}

uint64_t TelemetryMetrics::GetTotalProcessed() const {
    return processedOrderCount;
}

void TelemetryMetrics::Reset() {
    // Unimplemented
}