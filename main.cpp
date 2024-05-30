#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> stop_thread(false);

void checkInternetConnection() {
    while (!stop_thread) {
        if (system("ping -c 1 google.com > /dev/null 2>&1") == 0) {
            std::cout << "The PC is connected to the internet." << std::endl;
        } else {
            std::cout << "The PC is not connected to the internet." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main() {
    std::thread t(checkInternetConnection);
    std::this_thread::sleep_for(std::chrono::seconds(180));
    stop_thread = true;
    t.join();
    return 0;
}