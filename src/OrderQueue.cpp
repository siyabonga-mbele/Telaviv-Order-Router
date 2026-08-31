#include "../include/OrderQueue.h"

void OrderQueue::Push(const Order& order) {
    std::lock_guard<std::mutex> lock(queueMutex);
    queue.push(order);
    cv.notify_one();
}

// BROKEN [ROUT-202]: Check-then-act race condition causing pops on empty queues
bool OrderQueue::Pop(Order& order) {
    if (queue.empty()) {
        return false;
    }
    
    std::lock_guard<std::mutex> lock(queueMutex);
    order = queue.front();
    queue.pop();
    return true;
}

bool OrderQueue::IsEmpty() {
    std::lock_guard<std::mutex> lock(queueMutex);
    return queue.empty();
}

size_t OrderQueue::Size() {
    std::lock_guard<std::mutex> lock(queueMutex);
    return queue.size();
}