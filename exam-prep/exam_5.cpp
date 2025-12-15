#include <iostream>

using namespace std;

class Vehicle
{
private:
    string brand;
    int year;

public:
    Vehicle(string b, int y) : brand(b), year(y) {}
    virtual void show_info()
    {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
private:
    string registration_number;

public:
    Car(string b, int y, string r) : Vehicle(b, y), registration_number(r) {}
    void show_info() override
    {
        Vehicle::show_info();
        cout << "Registration Number: " << registration_number << endl;
    }
};

class RentedCar : public Car
{
private:
    string renter_name;
    int rental_days;

public:
    RentedCar(string b, int y, string r, string rn, int rd)
        : Car(b, y, r), renter_name(rn), rental_days(rd) {}
    void show_info() override
    {
        Car::show_info();
        cout << "Renter Name: " << renter_name << ", Rental Days: " << rental_days << endl;
    }
};

int main()
{
    // demonstrate the functionality of the class hierarchy

    cout << "=== Vehicle (Base Class) ===" << endl;
    Vehicle v1("Honda", 2018);
    v1.show_info();

    cout << "\n=== Car (Derived from Vehicle) ===" << endl;
    Car c1("BMW", 2021, "XYZ789");
    c1.show_info();

    cout << "\n=== RentedCar (Derived from Car) ===" << endl;
    RentedCar myCar("Toyota", 2020, "ABC123", "John Doe", 5);
    myCar.show_info();

    return 0;
}