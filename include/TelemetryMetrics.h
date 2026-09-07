#pragma once
#include <iostream>
#include <cstdint>
#include <atomic> //for thread safety

class TelemetryMetrics {
private:
    std::atomic<uint64_t> processedOrderCount; // BROKEN: fixed

public:
    TelemetryMetrics();
    void RecordOrderProcessed();
    uint64_t GetTotalProcessed() const;
    void Reset();
};