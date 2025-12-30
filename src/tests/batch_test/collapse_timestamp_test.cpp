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
    std::string logFile = "collapse_timestamp_test.log";
    std::ofstream(logFile, std::ios::trunc).close();

    L::initialize(logFile);
    L::enableEchoMode(false);
    // Enable timestamps (default is DateTime)
    L::setTimestampMode(L::TimestampMode::EpochMilliseconds); 
    L::setBatchInterval(std::chrono::milliseconds(2000));
    L::setCollapseRepeatedMessages(true);

    std::cout << "Logging repeated messages with timestamps..." << std::endl;
    L().info() << "Repeated Message";
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Ensure timestamp diff
    L().info() << "Repeated Message";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    L().info() << "Repeated Message";

    L::flush();

    // Check if collapsed
    if (!fileContains(logFile, "Repeated Message (x3)")) {
        std::cerr << "File should contain 'Repeated Message (x3)' even with different timestamps!" << std::endl;
        
        // Print file content for debugging
        std::ifstream file(logFile);
        std::cout << "File content:\n" << file.rdbuf() << std::endl;
        
        return 1;
    }

    std::cout << "Test passed!" << std::endl;
    return 0;
}
