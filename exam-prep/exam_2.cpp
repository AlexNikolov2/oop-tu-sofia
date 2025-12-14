#include <iostream>

using namespace std;

class Point
{
private:
    int x, y;
    char symbol;

public:
    Point()
    {
        cout << "Enter symbol: ";
        cin >> symbol;
        cout << "Enter coordinates x and y: ";
        cin >> x >> y;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle() : center()
    {
        cout << "Enter radius: ";
        cin >> radius;
    }

    void display() const
    {
        cout << "Circle with center at (" << center.getX() << ", " << center.getY() << "), "
             << "radius: " << radius << ", symbol: '" << center.getSymbol() << "'";
    }
};

int main()
{
    int n;
    cout << "Enter number of circles: ";
    cin >> n;

    Circle *circles = new Circle[n];

    cout << "\nYou have created the following circles:\n";
    for (int i = 0; i < n; ++i)
    {
        circles[i].display();
        cout << "\n";
    }
    delete[] circles;
    return 0;
}