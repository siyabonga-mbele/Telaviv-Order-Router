#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include "../include/RouterEngine.h"

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "   TELAVIV ORDER ROUTER - CONCURRENCY HARNESS    " << std::endl;
    std::cout << "==================================================\n" << std::endl;

    RouterEngine engine;
    engine.StartEngine(4); // Start 4 worker threads

    const int TOTAL_ORDERS = 10000;
    std::cout << "[SIMULATION] Dispatching " << TOTAL_ORDERS << " orders across producer threads..." << std::endl;

    // Simulate multi-threaded client order submissions
    auto producer = [&engine](int startId, int count) {
        for (int i = 0; i < count; ++i) {
            Order order;
            order.orderId = startId + i;
            strncpy(order.symbol, "EURUSD", sizeof(order.symbol));
            order.type = OrderType::BUY;
            order.price = 1.0850;
            order.quantity = 1000;
            order.status = OrderStatus::PENDING;

            engine.SubmitOrder(order);
        }
    };

    std::thread t1(producer, 1000, 2500);
    std::thread t2(producer, 3500, 2500);
    std::thread t3(producer, 6000, 2500);
    std::thread t4(producer, 8500, 2500);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Allow workers time to process queue
    std::this_thread::sleep_for(std::chrono::seconds(2));
    engine.StopEngine();

    std::cout << "\n--- [METRICS REPORT] ---" << std::endl;
    std::cout << "Expected Orders Processed : " << TOTAL_ORDERS << std::endl;
    std::cout << "Actual Orders Processed   : " << engine.GetProcessedCount() << std::endl;
    std::cout << "==================================================" << std::endl;

    return 0;
}