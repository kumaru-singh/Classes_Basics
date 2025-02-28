// Project 6: High-Performance Multi-Threaded Task Queue (std::thread & std::mutex)
// 🔹 Concept: Use std::thread for concurrent task execution and std::mutex for thread safety.
// 🔹 Real-World Use Case: A multi-threaded task queue that efficiently processes tasks in parallel, similar to job schedulers in operating systems.
// 🔹 Why Multi-Threading?

// Improves performance by utilizing multiple CPU cores.
// Prevents bottlenecks in single-threaded execution.
// Demonstrates concurrency concepts essential for interview discussions.


// 📌 Step 1: Define the Task Queue
// Each task is stored in a queue and executed by worker threads.

// 🖥️ Code: Include Necessary Libraries
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>


// 📌 Step 2: Implement Thread-Safe Task Queue
// We use:
// ✅ std::queue<std::function<void()>> → Stores tasks.
// ✅ std::mutex → Prevents race conditions.
// ✅ std::condition_variable → Notifies threads when tasks are available.

// 🖥️ Code: Task Queue Class

class TaskQueue {
    private:
        std::queue<std::function<void()>> tasks;
        std::mutex mtx;
        std::condition_variable cv;
        bool stop = false;
    
    public:
        void pushTask(std::function<void()> task) {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.push(std::move(task));
            cv.notify_one(); // Notify a worker thread
        }
    
        std::function<void()> popTask() {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !tasks.empty() || stop; });
    
            if (tasks.empty()) return nullptr;
    
            auto task = std::move(tasks.front());
            tasks.pop();
            return task;
        }
    
        void shutdown() {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
            cv.notify_all();
        }
    };
    

//     📌 Step 3: Worker Threads for Task Execution
// We spawn multiple threads that continuously fetch and execute tasks.

// 🖥️ Code: Worker Thread Function

void worker(TaskQueue& queue, int id) {
    while (true) {
        auto task = queue.popTask();
        if (!task) break; // Exit if no tasks left

        std::cout << "Worker " << id << " executing task...\n";
        task(); // Execute the task
    }
}


// 📌 Step 4: Main Function to Test Multi-Threaded Processing
// We create multiple worker threads and push tasks dynamically.

// 🖥️ Code: Main Function

int main() {
    TaskQueue queue;

    // Spawn worker threads
    std::vector<std::thread> workers;
    for (int i = 0; i < 3; ++i) {
        workers.emplace_back(worker, std::ref(queue), i + 1);
    }

    // Add tasks to the queue
    queue.pushTask([] { std::cout << "Task A completed\n"; });
    queue.pushTask([] { std::cout << "Task B completed\n"; });
    queue.pushTask([] { std::cout << "Task C completed\n"; });
    queue.pushTask([] { std::cout << "Task D completed\n"; });

    // Allow time for processing
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Shutdown the queue
    queue.shutdown();

    // Join all worker threads
    for (auto& worker : workers) {
        worker.join();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
// 🚀 Output:
// Worker 1 executing task...
// Task A completed
// Worker 2 executing task...
// Task B completed
// Worker 3 executing task...
// Task C completed
// Worker 1 executing task...
// Task D completed
// All tasks completed.


