#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

using namespace std;

class Temperature
{
protected:
    double temp;

public:
    Temperature(double t) : temp(t) {}
    virtual ~Temperature() {}

    virtual void setTemp(double t)
    {
        temp = t;
    }
    virtual double getTemp() const
    {
        return temp;
    }

    virtual void toFahrenheit()
    {
        temp = (temp * 9.0 / 5.0) + 32.0;
    }

    virtual void toCelsius()
    {
        temp = (temp - 32.0) * 5.0 / 9.0;
    }

    virtual void display() const
    {
        cout << fixed << setprecision(2) << temp << "°";
    }
};

class Celsius : public Temperature
{
public:
    Celsius(double t) : Temperature(t) {}
    void toFahrenheit() override
    {
        temp = (temp * 9.0 / 5.0) + 32.0;
    }
    void display() const override
    {
        cout << fixed << setprecision(2) << temp << "°C";
    }
};

class Fahrenheit : public Temperature
{
public:
    Fahrenheit(double t) : Temperature(t) {}
    void toCelsius() override
    {
        temp = (temp - 32.0) * 5.0 / 9.0;
    }
    void display() const override
    {
        cout << fixed << setprecision(2) << temp << "°F";
    }
};

int main()
{
    vector<unique_ptr<Temperature>> temps;
    temps.push_back(make_unique<Celsius>(25.0));
    temps.push_back(make_unique<Fahrenheit>(77.0));
    temps.push_back(make_unique<Celsius>(0.0));
    temps.push_back(make_unique<Fahrenheit>(32.0));

    cout << "Original Temperatures:\n";
    for (const auto &t : temps)
    {
        t->display();
        cout << "\n";
    }

    cout << "\nConverted Temperatures:\n";
    for (const auto &t : temps)
    {
        if (dynamic_cast<Celsius *>(t.get()))
        {
            t->toFahrenheit();
        }
        else
        {
            t->toCelsius();
        }
        t->display();
        cout << "\n";
    }

    return 0;
}