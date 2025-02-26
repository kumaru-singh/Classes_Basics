#include<iostream>
#include<string>
using namespace std;

class BankAccount {
    public:
    string name;
    int accountNumber;
    double balance;
    double intrestRate;

    double depositAmount(double amount){
        balance += amount;
        return balance;
    }

    double withdrawAmount(double amount){
        if(balance < amount){
            cout<<"Insufficient balance"<<endl;
            return balance;
        } else {
            balance -= amount;
            return balance;
        } 
    }

    // Default Constructor
    BankAccount() {
        accountNumber = "000000000";
        balance = 0.0;
        cout << "Default Constructor Called!" << endl;
    }


    BankAccount(string n, int a, double b, double i):name(n), accountNumber(a), balance(b), intrestRate(i){
        cout<<"Account for "<<n<<" created successfully !"<<endl;
    };

    void display(){
        cout<<"Name: "<<name<<endl;
        cout<<"Account Number: "<<accountNumber<<endl;
        cout<<"Balance: "<<balance<<endl;
        cout<<"Intrest Rate: "<<intrestRate<<endl;
    }
};

int main(){
    BankAccount account1("John Doe", 123456, 1000, 0.05);
    account1.display();
    account1.depositAmount(500);
    account1.display();
    account1.withdrawAmount(2000);
    account1.display();
    account1.withdrawAmount(500);
    account1.display();
    return 0;
}