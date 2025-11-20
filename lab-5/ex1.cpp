#include <iostream>
using namespace std;

class vehicle
{
    int wheels;
    double weight;

public:
    vehicle(int w, double wg) : wheels(w), weight(wg) {}
    void show_vehicle()
    {
        cout << "Wheels: " << wheels << ", Weight: " << weight << "kg" << endl;
    }
};

class motorized : virtual public vehicle
{
    int horsepower;

public:
    motorized(int w, double wg, int hp) : vehicle(w, wg), horsepower(hp) {}
    void show_motorized()
    {
        cout << "Horsepower: " << horsepower << "hp" << endl;
    }
};

class road_use : virtual public vehicle
{
    int passengers;

public:
    road_use(int w, double wg, int p) : vehicle(w, wg), passengers(p) {}
    void show_road_use()
    {
        cout << "Max passengers: " << passengers << endl;
    }
};

class car : public motorized, public road_use
{
    char type; // 's' за седан, 'v' за ван и т.н.
public:
    // Конструкторът трябва да инициализира директно виртуалния базов клас vehicle
    car(int w, double wg, int hp, int p, char t)
        : vehicle(w, wg), motorized(w, wg, hp), road_use(w, wg, p), type(t) {}

    void show()
    {
        cout << "--- Car Details ---" << endl;
        show_vehicle();
        show_motorized();
        show_road_use();
        cout << "Type: " << type << endl;
    }
};

int main()
{
    car myCar(4, 1500.5, 120, 5, 's');

    myCar.show();

    return 0;
}
