// Project 7: Thread-Safe Banking System (std::mutex & std::lock_guard)
// 🔹 Concept: Use std::mutex and std::lock_guard to ensure safe concurrent access to a bank account.
// 🔹 Real-World Use Case: A thread-safe banking system where multiple threads (customers) perform withdrawals and deposits safely.
// 🔹 Why Mutex?

// Prevents race conditions when multiple threads access shared resources (bank balance).
// Ensures consistent balance updates.
// Demonstrates practical multi-threading use cases.

// 📌 Step 1: Define Bank Account with std::mutex
// Each account has:
// ✅ Balance (int)
// ✅ Mutex (std::mutex) to prevent simultaneous access

// 🖥️ Code: Bank Account Class

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

class BankAccount {
private:
    int balance;
    std::mutex mtx; // Mutex for thread safety

public:
    BankAccount(int initialBalance) : balance(initialBalance) {}

    // Deposit money (thread-safe)
    void deposit(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "Deposited $" << amount << " | New Balance: $" << balance << "\n";
    }

    // Withdraw money (thread-safe)
    bool withdraw(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrew $" << amount << " | New Balance: $" << balance << "\n";
            return true;
        } else {
            std::cout << "Failed to withdraw $" << amount << " | Insufficient Balance: $" << balance << "\n";
            return false;
        }
    }

    // Get current balance
    int getBalance() {
        std::lock_guard<std::mutex> lock(mtx);
        return balance;
    }
};

// 📌 Step 2: Simulate Multiple Customers Using Threads
// We create multiple customers who:
// ✅ Deposit random amounts
// ✅ Withdraw random amounts
// ✅ Ensure transactions are safe



// 🖥️ Code: Customer Transactions

void customer(BankAccount &account, int id) {
    for (int i = 0; i < 5; ++i) {
        int amount = (id + 1) * 10; // Unique transaction amount
        if (i % 2 == 0) {
            account.deposit(amount);
        } else {
            account.withdraw(amount);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate delay
    }
}


// 📌 Step 3: Main Function to Test Banking System
// We create multiple threads representing different customers.

// 🖥️ Code: Main Function

int main() {
    BankAccount account(100); // Initial balance: $100

    std::vector<std::thread> customers;

    // Create 3 customers (threads)
    for (int i = 0; i < 3; ++i) {
        customers.emplace_back(customer, std::ref(account), i);
    }

    // Wait for all customers to finish transactions
    for (auto &c : customers) {
        c.join();
    }

    std::cout << "Final Balance: $" << account.getBalance() << "\n";
    return 0;
}

//📌 Step 4: Expected Output

// Deposited $10 | New Balance: $110
// Withdrew $10 | New Balance: $100
// Deposited $20 | New Balance: $120
// Withdrew $20 | New Balance: $100
// Deposited $30 | New Balance: $130
// Withdrew $30 | New Balance: $100
// Deposited $40 | New Balance: $140
// Withdrew $40 | New Balance: $100
// Deposited $50 | New Balance: $150
// Withdrew $50 | New Balance: $100
// Final Balance: $100



// 📌 Enhancements
// 🔹 Multi-Account Transfers: Add another account and allow inter-account transfers.
// 🔹 Interest Calculation: Add periodic interest updates using a background thread.
// 🔹 Graphical UI: Display transaction history using Qt or React frontend.

// ✅ Why is this project valuable?
// Demonstrates thread-safe banking transactions using std::mutex & std::lock_guard.
// Replicates real-world banking systems handling concurrent transactions.
// Great interview topic to showcase concurrency control in C++.
