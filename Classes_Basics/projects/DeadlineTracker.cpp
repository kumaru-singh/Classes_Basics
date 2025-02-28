//Deadline Tracker
//Step 1: Define Task with an Optional Deadline

#include <iostream>
#include <optional>
#include <vector>
#include <string>

// Task structure with optional deadline
struct Task {
    std::string title;
    std::optional<std::string> deadline; // May or may not have a deadline

    Task(std::string t, std::optional<std::string> d = std::nullopt)
        : title(std::move(t)), deadline(std::move(d)) {}
};
//Step 2: Function to Display Task Details
//Code: Display Task Function

void displayTask(const Task& task) {
    std::cout << "Task: " << task.title << "\n";
    if (task.deadline) {
        std::cout << "  Deadline: " << task.deadline.value() << "\n";
    } else {
        std::cout << "  Deadline: No Deadline Assigned\n";
    }
    std::cout << "----------------------\n";
}

//Step 3: TaskManager Class to Manage Tasks
//Code: TaskManager Class

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
    

//Step 4: Main Function to Test the TaskManager
//Code: Main Function

int main() {
    TaskManager manager;

    // Task with a deadline
    manager.addTask(Task("Submit AI Report", "2025-03-10"));

    // Task without a deadline
    manager.addTask(Task("Refactor C++ Code"));

    // Task with a deadline
    manager.addTask(Task("Prepare for Tech Talk", "2025-04-01"));

    // Display all tasks
    manager.showAllTasks();

    return 0;
}


//Output
//Task: Submit AI Report


// Task: Submit AI Report
//   Deadline: 2025-03-10
// ----------------------
// Task: Refactor C++ Code
//   Deadline: No Deadline Assigned
// ----------------------
// Task: Prepare for Tech Talk
//   Deadline: 2025-04-01
// ----------------------

//In this example, we defined a Task structure with an optional deadline field using std::optional. 
// The TaskManager class manages tasks and allows adding tasks with or without deadlines. The displayTask function is used to print the details of each task, including the title and deadline (if present). The main function demonstrates adding tasks with and without deadlines and displaying all tasks using the TaskManager.
