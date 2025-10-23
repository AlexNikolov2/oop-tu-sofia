#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class timeclock
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    timeclock();
    void display(const char *format = "24-hour");
    void formattedDisplay();
    ~timeclock()
    {
        cout << "\nDestructing object timeclock!\n";
    }
};
timeclock::timeclock()
{
    do
    {
        cout << "\n\nEnter time in hours, minutes and seconds:\n";
        cin >> hours >> minutes >> seconds;
        if (!((hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60) && (seconds >= 0 && seconds < 60)))
            cout << "\nInvalid time! Try again.";
    } while (!((hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60) && (seconds >= 0 && seconds < 60)));
}
void timeclock::display(const char *format)
{
    if (strcmp(format, "12-hour") == 0)
    {
        int displayHours = hours % 12;
        displayHours = (displayHours == 0) ? 12 : displayHours;
        cout << "Time is: " << displayHours << " hours, " << minutes << " minutes, " << seconds << " seconds (12-hour format).\n";
    }
    else
    {
        cout << "Time is: " << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << " (24-hour format).\n";
    }
}

void timeclock::formattedDisplay()
{
    if (hours < 12)
    {
        int displayHours = hours % 12;
        displayHours = (displayHours == 0) ? 12 : displayHours;
        cout << "Time is: " << (displayHours < 10 ? "0" : "") << displayHours << " : " << (minutes < 10 ? "0" : "") << minutes << " : " << (seconds < 10 ? "0" : "") << seconds << " AM.\n";
    }
    else
    {
        int displayHours = hours % 12;
        displayHours = (displayHours == 0) ? 12 : displayHours;
        cout << "Time is: " << (displayHours < 10 ? "0" : "") << displayHours << " : " << (minutes < 10 ? "0" : "") << minutes << " : " << (seconds < 10 ? "0" : "") << seconds << " PM.\n";
    }
}

int main()
{

    timeclock t1;
    t1.display();
    t1.formattedDisplay();

    timeclock t2;
    t2.display();
    t2.formattedDisplay();

    timeclock *ptr;
    ptr = new timeclock;
    ptr->display();
    ptr->formattedDisplay();
    delete ptr;

    return 0;
}