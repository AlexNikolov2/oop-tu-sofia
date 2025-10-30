#include <iostream>
using namespace std;

class truck;

// Task 2: Friend Function Approach
class car
{
    int passengers;
    int speed;

public:
    car(int p, int s)
    {
        passengers = p;
        speed = s;
    }
    friend int sp_greater(car c, truck t);
    friend double travel_time(car c, double distance);
    friend double travel_time(truck t, double distance);
};

class truck
{
    int weight;
    int speed;

public:
    truck(int w, int s)
    {
        weight = w;
        speed = s;
    }
    friend int sp_greater(car c, truck t);
    friend double travel_time(car c, double distance);
    friend double travel_time(truck t, double distance);
};

int sp_greater(car c, truck t)
{
    return c.speed - t.speed;
}

double travel_time(car c, double distance)
{
    if (c.speed <= 0)
        return -1; // Грешка
    return distance / c.speed;
}

double travel_time(truck t, double distance)
{
    if (t.speed <= 0)
        return -1; // Грешка0*
    return distance / t.speed;
}

// Task 3: Member Function Approach
class car_member;
class truck_member;

class car_member
{
    int passengers;
    int speed;

public:
    car_member(int p, int s)
    {
        passengers = p;
        speed = s;
    }
    int sp_greater(truck_member t);
    double travel_time_member(double distance);
};

class truck_member
{
    int weight;
    int speed;

public:
    truck_member(int w, int s)
    {
        weight = w;
        speed = s;
    }
    friend int car_member::sp_greater(truck_member t);
    friend double car_member::travel_time_member(double distance);
    double travel_time_member(double distance);
};

int car_member::sp_greater(truck_member t)
{
    return speed - t.speed;
}

double car_member::travel_time_member(double distance)
{
    if (speed <= 0)
        return -1;
    return distance / speed;
}

double truck_member::travel_time_member(double distance)
{
    if (speed <= 0)
        return -1;
    return distance / speed;
}

int main()
{
    int t;

    cout << "============================================\n";
    cout << "TASK 2: Friend Function Approach\n";
    cout << "============================================\n";

    car c1(6, 55), c2(2, 120);
    truck t1(10000, 55), t2(20000, 72);

    cout << "\nComparing c1 and t1:\n";
    t = sp_greater(c1, t1);
    if (t < 0)
        cout << "Truck is faster.\n";
    else if (t == 0)
        cout << "Car and truck speed is the same.\n";
    else
        cout << "Car is faster.\n";

    cout << "\nComparing c2 and t2:\n";
    t = sp_greater(c2, t2);
    if (t < 0)
        cout << "Truck is faster.\n";
    else if (t == 0)
        cout << "Car and truck speed is the same.\n";
    else
        cout << "Car is faster.\n";

    double distance = 300.0;
    cout << "\n=== Travel Time Calculation (Distance: " << distance << " km) ===\n";
    cout << "Car c1 (speed: 55 km/h) will take: " << travel_time(c1, distance) << " hours\n";
    cout << "Car c2 (speed: 120 km/h) will take: " << travel_time(c2, distance) << " hours\n";
    cout << "Truck t1 (speed: 55 km/h) will take: " << travel_time(t1, distance) << " hours\n";
    cout << "Truck t2 (speed: 72 km/h) will take: " << travel_time(t2, distance) << " hours\n";

    cout << "\n============================================\n";
    cout << "TASK 3: Member Function Approach\n";
    cout << "============================================\n";

    car_member cm1(6, 55), cm2(2, 120);
    truck_member tm1(10000, 55), tm2(20000, 72);

    cout << "\nComparing cm1 and tm1:\n";
    t = cm1.sp_greater(tm1);
    if (t < 0)
        cout << "Truck is faster.\n";
    else if (t == 0)
        cout << "Car and truck speed is the same.\n";
    else
        cout << "Car is faster.\n";

    cout << "\nComparing cm2 and tm2:\n";
    t = cm2.sp_greater(tm2);
    if (t < 0)
        cout << "Truck is faster.\n";
    else if (t == 0)
        cout << "Car and truck speed is the same.\n";
    else
        cout << "Car is faster.\n";

    cout << "\n=== Travel Time Calculation (Distance: " << distance << " km) ===\n";
    cout << "Car cm1 (speed: 55 km/h) will take: " << cm1.travel_time_member(distance) << " hours\n";
    cout << "Car cm2 (speed: 120 km/h) will take: " << cm2.travel_time_member(distance) << " hours\n";
    cout << "Truck tm1 (speed: 55 km/h) will take: " << tm1.travel_time_member(distance) << " hours\n";
    cout << "Truck tm2 (speed: 72 km/h) will take: " << tm2.travel_time_member(distance) << " hours\n";

    return 0;
}
