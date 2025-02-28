// Project 5: Efficient Memory Logging System (std::pair)
// 🔹 Concept: Use std::pair to store log entries with timestamps.
// 🔹 Real-World Use Case: A memory logging system that records key events (e.g., memory allocations, warnings, errors) with timestamps.
// 🔹 Why std::pair? We can efficiently store and retrieve time-stamped log entries without defining a separate struct.

// 📌 Step 1: Define Log Entry with std::pair
// Each log entry has:
// ✅ A Timestamp (std::string)
// ✅ A Log Message (std::string)

// 🖥️ Code: Log Entry Definition

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

// Function to get the current timestamp
std::string getCurrentTime() {
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buffer);
}

// Log Entry using std::pair (timestamp, message)
using LogEntry = std::pair<std::string, std::string>;

// 📌 Step 2: Logging System with std::vector<std::pair<>>
// We store logs in a vector for easy retrieval.

// 🖥️ Code: Log System

class Logger {
    private:
        std::vector<LogEntry> logs; // Stores (timestamp, message)
    
    public:
        void log(const std::string& message) {
            logs.emplace_back(getCurrentTime(), message);
        }
    
        void showLogs() const {
            for (const auto& entry : logs) {
                std::cout << "[" << entry.first << "] " << entry.second << "\n";
            }
        }
    };
    

    // 📌 Step 3: Main Function to Test Logging System
    // We log some memory operations and errors.
    
    // 🖥️ Code: Main Function



    int main() {
        Logger memoryLogger;
    
        memoryLogger.log("Memory allocation of 256 MB successful.");
        memoryLogger.log("Memory usage crossed 80% threshold.");
        memoryLogger.log("Memory deallocation of 128 MB completed.");
        memoryLogger.log("Critical Error: Out of Memory!");
    
        std::cout << "Memory Logs:\n";
        memoryLogger.showLogs();
    
        return 0;
    }

    // 📌 Step 4: Expected Output


//     Memory Logs:
// [2025-02-28 14:30:15] Memory allocation of 256 MB successful.
// [2025-02-28 14:30:16] Memory usage crossed 80% threshold.
// [2025-02-28 14:30:18] Memory deallocation of 128 MB completed.
// [2025-02-28 14:30:20] Critical Error: Out of Memory!

// 🚀 Output: The memory logging system efficiently stores and displays log entries with timestamps, helping track key events in the system.


// ✅ Why is this project valuable?
// Uses std::pair for clean timestamp-message storage.
// Simulates real-world logging systems (used in OS, servers, memory management).
// Demonstrates efficient time-stamped logging for debugging.