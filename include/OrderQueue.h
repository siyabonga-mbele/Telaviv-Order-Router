#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Common.h"

class OrderQueue {
private:
    std::queue<Order> queue;
    std::mutex queueMutex;
    std::condition_variable cv;

public:
    OrderQueue() = default;
    void Push(const Order& order);
    bool Pop(Order& order); // BROKEN: Pop logic has race conditions under high contention
    bool IsEmpty();
    size_t Size();
};