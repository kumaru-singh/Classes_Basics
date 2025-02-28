//Multi-Attribute Task Sorting


// 🔹 Concept: Use std::tuple to store multiple attributes of tasks and sort them.
// 🔹 Real-World Use Case: A task sorting system that sorts tasks based on priority, deadline, and complexity.
// 🔹 Why std::tuple? Instead of defining custom comparison functions, std::tuple allows us to compare multiple values at once for sorting

// 📌 Step 1: Define Task with Multiple Attributes
// Each task has:
// ✅ A Title (string)
// ✅ A Priority Level (int, 1-10)
// ✅ A Deadline (string, YYYY-MM-DD format)
// ✅ A Complexity Level (int, 1-10)

// 🖥️ Code: Task Definition


#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

// Task structure with a tuple for sorting
struct Task {
    std::string title;
    int priority;       // 1 (Low) - 10 (High)
    std::string deadline; // YYYY-MM-DD format
    int complexity;     // 1 (Easy) - 10 (Hard)

    // Constructor
    Task(std::string t, int p, std::string d, int c)
        : title(std::move(t)), priority(p), deadline(std::move(d)), complexity(c) {}

    // Function to return tuple for sorting
    std::tuple<int, std::string, int> getSortingKey() const {
        return std::make_tuple(priority, deadline, complexity);
    }
};


// 📌 Step 2: Function to Display Task Details
// Display the task details including title, priority, deadline, and complexity.
// 🖥️ Code: Display Task Function

void displayTask(const Task& task) {
    std::cout << "Task: " << task.title 
              << " | Priority: " << task.priority
              << " | Deadline: " << task.deadline
              << " | Complexity: " << task.complexity << "\n";
}


// 📌 Step 3: TaskManager Class to Manage Tasks
// We use std::sort with std::tuple for multi-attribute sorting.
// 🔹 Sorting Order: Higher priority → Earlier deadline → Higher complexity

// 🖥️ Code: Task Manager

class TaskManager {
    private:
        std::vector<Task> tasks;
    
    public:
        void addTask(const Task& task) {
            tasks.push_back(task);
        }
    
        void sortTasks() {
            std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                return a.getSortingKey() > b.getSortingKey(); // Higher priority first
            });
        }
    
        void showAllTasks() const {
            for (const auto& task : tasks) {
                displayTask(task);
            }
        }
    };
    

//📌 Step 4: Main Function to Test Sorting
// We create tasks with different priorities, deadlines, and complexities.

// 🖥️ Code: Main Function

int main() {
    TaskManager manager;

    // Adding tasks
    manager.addTask(Task("Submit AI Report", 8, "2025-03-10", 6));
    manager.addTask(Task("Fix Security Bug", 10, "2025-02-28", 9));
    manager.addTask(Task("Prepare Presentation", 7, "2025-03-05", 5));
    manager.addTask(Task("Refactor Codebase", 9, "2025-02-25", 7));

    std::cout << "Before Sorting:\n";
    manager.showAllTasks();

    // Sort tasks based on priority, deadline, and complexity
    manager.sortTasks();

    std::cout << "\nAfter Sorting:\n";
    manager.showAllTasks();

    return 0;
}


// ✅ Why is this project valuable?
// Uses std::tuple for efficient multi-attribute sorting.
// Demonstrates real-world task prioritization.
// Teaches advanced sorting techniques for interviews.
