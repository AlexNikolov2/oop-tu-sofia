#include <iostream>
#include <cmath>

using namespace std;

class rectangle
{
private:
    double length;
    double width;

public:
    rectangle();
    double face();
    double face(double *);
    void show(char *);
    ~rectangle()
    {
        cout << "\nDestructing object rectangle!\n";
    }
};

rectangle::rectangle()
{
    do
    {
        cout << "\n\nEnter length and width of rectangle:\n";
        cin >> length >> width;
        if (!((length > 0) && (width > 0)))
            cout << "\nInvalid dimensions! Try again.";
    } while (!((length > 0) && (width > 0)));
}

double rectangle::face()
{
    return length * width;
}

double rectangle::face(double *p)
{
    *p = 2 * (length + width);
    return length * width;
}

void rectangle::show(char *name)
{
    cout << "Rectangle " << name << ":\n";
    cout << "length = " << length << ", width = " << width << "\n";
}

int main()
{
    rectangle rec1;
    double p, s;
    rec1.show("rec1");
    cout << "\nThe face of rectangle1 is s = " << rec1.face();

    rectangle rec2;
    rec2.show("rec2");
    s = rec2.face(&p);
    cout << "\nThe face of rectangle2 is s = " << s << ", and the perimeter is p = " << p;

    return 0;
}