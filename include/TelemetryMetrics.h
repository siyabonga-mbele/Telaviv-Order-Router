#pragma once
#include <iostream>
#include <cstdint>

class TelemetryMetrics {
private:
    uint64_t processedOrderCount; // BROKEN: Shared non-atomic integer

public:
    TelemetryMetrics();
    void RecordOrderProcessed();
    uint64_t GetTotalProcessed() const;
    void Reset();
};