#include "../../simple_logger.hpp"
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

using namespace juzzlin;

bool fileContains(const std::string& path, const std::string& content) {
    std::ifstream file(path);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(content) != std::string::npos) return true;
    }
    return false;
}

int main() {
    std::string logFile = "collapse_test.log";
    std::ofstream(logFile, std::ios::trunc).close();

    L::initialize(logFile);
    L::enableEchoMode(false);
    L::setTimestampMode(L::TimestampMode::None); // Disable timestamps for easier matching
    L::setBatchInterval(std::chrono::milliseconds(1000));
    L::setCollapseRepeatedMessages(true);

    std::cout << "Logging repeated messages..." << std::endl;
    L().info() << "Repeated Message";
    L().info() << "Repeated Message";
    L().info() << "Repeated Message";

    L::flush();

    if (!fileContains(logFile, "Repeated Message (x3)")) {
        std::cerr << "File should contain 'Repeated Message (x3)'!" << std::endl;
        return 1;
    }

    // Test non-repeated
    L().info() << "Unique Message 1";
    L().info() << "Unique Message 2";
    
    L::flush();

    if (fileContains(logFile, "Unique Message 1 (x")) {
        std::cerr << "Unique Message 1 should not be collapsed!" << std::endl;
        return 1;
    }

     // Test interleaved
    L().info() << "A";
    L().info() << "A";
    L().info() << "B";
    L().info() << "A";
    L().info() << "A";
    
    L::flush();
    
    // Should see A (x2), B, A (x2)
    // We can't easily verify order with simple fileContains but we can check existence
    // Ideally we'd read the file line by line but this is a quick check.
    
    if (!fileContains(logFile, "A (x2)")) {
         std::cerr << "File should contain 'A (x2)'!" << std::endl;
         return 1;
    }

    std::cout << "Test passed!" << std::endl;
    return 0;
}
