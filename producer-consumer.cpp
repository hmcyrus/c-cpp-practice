#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 5;  // Maximum number of items in the buffer

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable bufferEmpty;
std::condition_variable bufferFull;

void producer(int id) {
    for (int i = 1; i <= 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate some work

        std::unique_lock<std::mutex> lock(mtx);
        bufferFull.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });  // Wait until buffer is not full

        buffer.push(i);
        std::cout << "Producer " << id << " produced item: " << i << std::endl;

        lock.unlock();
        bufferEmpty.notify_all();  // Notify consumer that buffer is not empty
    }
}

void consumer(int id) {
    for (int i = 1; i <= 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(750));  // Simulate some work

        std::unique_lock<std::mutex> lock(mtx);
        bufferEmpty.wait(lock, [] { return !buffer.empty(); });  // Wait until buffer is not empty

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed item: " << item << std::endl;

        lock.unlock();
        bufferFull.notify_all();  // Notify producer that buffer is not full
    }
}

int main() {
    std::thread producerThread1(producer, 1);
    std::thread producerThread2(producer, 2);
    std::thread consumerThread1(consumer, 1);
    std::thread consumerThread2(consumer, 2);

    producerThread1.join();
    producerThread2.join();
    consumerThread1.join();
    consumerThread2.join();

    return 0;
}
