#include <iostream>
#include <variant>
#include <vector>
#include <string>

// Task structures
struct Meeting {
    std::string agenda;
    int duration; // in minutes
};

struct Coding {
    std::string project;
    int complexity; // Scale from 1 to 10
};

struct StudySession {
    std::string subject;
    int hours;
};

// Using std::variant to store multiple task types
using Task = std::variant<Meeting, Coding, StudySession>;


void displayTask(const Task& task) {
    std::visit([](auto&& t) {
        using T = std::decay_t<decltype(t)>;
        if constexpr (std::is_same_v<T, Meeting>) {
            std::cout << "[Meeting] Agenda: " << t.agenda 
                      << ", Duration: " << t.duration << " mins\n";
        } else if constexpr (std::is_same_v<T, Coding>) {
            std::cout << "[Coding] Project: " << t.project 
                      << ", Complexity: " << t.complexity << "/10\n";
        } else if constexpr (std::is_same_v<T, StudySession>) {
            std::cout << "[Study] Subject: " << t.subject 
                      << ", Hours: " << t.hours << "\n";
        }
    }, task); 
}

// TaskManager class to manage tasks
class TaskManager {
    private:
        std::vector<Task> tasks;
    
    public:
        void addTask(const Task& task) {
            tasks.push_back(task);
        }
    
        void showAllTasks() const {
            std::cout << "---- Task List ----\n";
            for (const auto& task : tasks) {
                displayTask(task);
            }
        }
    };
    

    int main() {
        TaskManager manager;
    
        // Create different types of tasks
        manager.addTask(Meeting{"Discuss AI Research", 45});
        manager.addTask(Coding{"C++ Task Scheduler", 8});
        manager.addTask(StudySession{"Data Structures", 3});
    
        // Display tasks
        manager.showAllTasks();
        return 0;
    }
    