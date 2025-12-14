#include <iostream>

using namespace std;

class CircleArea
{
private:
    double radius;

public:
    CircleArea(double r) : radius(r) {}
    double getRadius() const { return radius; }
};

class Circle : public CircleArea
{
public:
    Circle(double r) : CircleArea(r) {}
    virtual ~Circle() {}
    double getRadius() const { return CircleArea::getRadius(); }
};

int main()
{
    int n;
    cout << "Enter number of circles: ";
    cin >> n;

    Circle **circles = new Circle *[n];

    for (int i = 0; i < n; ++i)
    {
        double r;
        cout << "Enter radius for circle " << (i + 1) << ": ";
        cin >> r;
        circles[i] = new Circle(r);
    }

    cout << "\nYou have created the following circles:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Circle " << (i + 1) << " with radius: " << circles[i]->getRadius() << "\n";
        delete circles[i];
    }
    delete[] circles;
    return 0;
};