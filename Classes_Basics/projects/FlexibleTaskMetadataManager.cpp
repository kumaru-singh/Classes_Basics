//Step 1: Define Task and Metadata System
// Code: Task and Metadata Storage
#include <iostream>
#include <any>
#include <unordered_map>
#include <vector>
#include <string>
#include <typeinfo>

// Task structure with metadata
struct Task {
    std::string title;
    std::unordered_map<std::string, std::any> metadata; // Flexible metadata storage

    // Add metadata (can be any type)
    template <typename T>
    void addMetadata(const std::string& key, const T& value) {
        metadata[key] = value;
    }

    // Retrieve metadata safely
    template <typename T>
    T getMetadata(const std::string& key) const {
        try {
            return std::any_cast<T>(metadata.at(key));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: Type mismatch for metadata key '" << key << "'\n";
            throw;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Key '" << key << "' not found\n";
            throw;
        }
    }
};

//Step 2: Function to Display Task Details
//Code: Display Task Function

void displayTask(const Task& task) {
    std::cout << "Task: " << task.title << "\n";

    for (const auto& [key, value] : task.metadata) {
        std::cout << "  " << key << ": ";

        // Type-safe retrieval of metadata
        if (value.type() == typeid(int)) {
            std::cout << std::any_cast<int>(value);
        } else if (value.type() == typeid(double)) {
            std::cout << std::any_cast<double>(value);
        } else if (value.type() == typeid(std::string)) {
            std::cout << std::any_cast<std::string>(value);
        } else {
            std::cout << "[Unknown Type]";
        }
        std::cout << "\n";
    }
    std::cout << "----------------------\n";
}

//Step 3: Add Tasks with Metadata
//Code: Task Manager

class TaskManager {
    private:
        std::vector<Task> tasks;
    
    public:
        void addTask(const Task& task) {
            tasks.push_back(task);
        }
    
        void showAllTasks() const {
            for (const auto& task : tasks) {
                displayTask(task);
            }
        }
    };
    

//Step 4: Main Function to Test the Metadata System
//Code: Main Function

int main() {
    TaskManager manager;

    Task t1{"Complete AI Research Paper"};
    t1.addMetadata("Priority", 5);          // Integer priority level
    t1.addMetadata("Deadline", std::string("2025-03-15"));
    t1.addMetadata("Estimated Time", 12.5); // Estimated hours (double)

    Task t2{"Bug Fix in Codebase"};
    t2.addMetadata("Assigned To", std::string("John Doe"));
    t2.addMetadata("Complexity", 8); // Integer complexity level

    manager.addTask(t1);
    manager.addTask(t2);

    // Display all tasks with metadata
    manager.showAllTasks();

    return 0;
}

//Output:
//Task: Complete AI Research Paper  Task: Complete AI Research Paper
//   Priority: 5
//   Deadline: 2025-03-15
//   Estimated Time: 12.5
// ----------------------
// Task: Bug Fix in Codebase
//   Assigned To: John Doe
//   Complexity: 8
// ----------------------


