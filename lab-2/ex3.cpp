#include <iostream>

using namespace std;

class truck; // Предварителна декларация

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
    int sp_greater(truck t);
    double travel_time(double distance);
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
    friend int car::sp_greater(truck t);
    friend double car::travel_time(double distance);
    double travel_time(double distance);
};

int car::sp_greater(truck t)
{
    return speed - t.speed; // Тъй като sp_greater() е член на car, то трябва да се подаде само
} // обектът за камион

/* Изчислява времето за изминаване на зададени километри за автомобил.
Формула: T = S / V, където S е разстояние, V е скорост, T е време */
double car::travel_time(double distance)
{
    if (speed <= 0)
        return -1; // Грешка
    return distance / speed;
}

double truck::travel_time(double distance)
{
    if (speed <= 0)
        return -1; // Грешка
    return distance / speed;
}

int main()
{
    int t;
    car c1(6, 55), c2(2, 120);
    truck t1(10000, 55), t2(20000, 72);

    cout << "Comparing c1 and t1 :\n";
    t = c1.sp_greater(t1); // Извиква се като член-функция на car
    if (t < 0)
        cout << "Truck is faster.\n";
    else if (t == 0)
        cout << "Car and truck speed is the same.\n";
    else
        cout << "Car is faster.\n";

    cout << "\nComparing c2 and t2 :\n";
    t = c2.sp_greater(t2); // Извиква се като член-функция на car
    if (t < 0)
        cout << "Truck is faster.\n";
    else if (t == 0)
        cout << "Car and truck speed is the same.\n";
    else
        cout << "Car is faster.\n";

    // Нова функционалност: изчисляване на време за изминаване
    double distance = 300; // км

    cout << "\n=== Travel Time Calculation (Distance: " << distance << " km) ===\n";
    cout << "Car c1 (speed: 55 km/h) will take: " << c1.travel_time(distance) << " hours\n";
    cout << "Car c2 (speed: 120 km/h) will take: " << c2.travel_time(distance) << " hours\n";
    cout << "Truck t1 (speed: 55 km/h) will take: " << t1.travel_time(distance) << " hours\n";
    cout << "Truck t2 (speed: 72 km/h) will take: " << t2.travel_time(distance) << " hours\n";

    return 0;
}
