#include <iostream>
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;

    void start() {
        cout << brand << " " << model << " is starting." << endl;
    }

    void stop() {
        cout << brand << " " << model << " has stopped." << endl;
    }
};

int main() {
    Car car1;
    car1.brand = "Toyota";
    car1.model = "Camry";
    car1.year = 2023;

    car1.start();
    car1.stop();

    return 0;
}
