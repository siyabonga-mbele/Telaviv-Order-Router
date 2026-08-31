#pragma once
#include <string>
#include <cstdint>

enum class OrderType { BUY, SELL };
enum class OrderStatus { PENDING, EXECUTED, REJECTED };

struct Order {
    uint64_t orderId;
    char symbol[16];
    OrderType type;
    double price;
    uint32_t quantity;
    OrderStatus status;
};

struct ExecutionReport {
    uint64_t orderId;
    bool success;
    double executedPrice;
    char message[64];
};