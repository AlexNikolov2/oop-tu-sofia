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
    void formattedDisplay(const char *format);
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
        cout << "Time is: " << hours << ":" << minutes << ":" << seconds << " (24-hour format).\n";
    }
}

void timeclock::formattedDisplay(const char *format)
{
    if (format == "AM")
    {
        int displayHours = hours % 12;
        displayHours = (displayHours == 0) ? 12 : displayHours;
        cout << "Time is: " << displayHours << " hours, " << minutes << " minutes, " << seconds << " seconds AM.\n";
    }
    else if (format == "PM")
    {
        int displayHours = hours % 12;
        displayHours = (displayHours == 0) ? 12 : displayHours;
        cout << "Time is: " << displayHours << " hours, " << minutes << " minutes, " << seconds << " seconds PM.\n";
    }
}

int main()
{

    timeclock t1;
    t1.display();
    t1.formattedDisplay("AM");
    t1.formattedDisplay("PM");

    timeclock t2;
    t2.display();
    t2.formattedDisplay("AM");
    t2.formattedDisplay("PM");

    timeclock *ptr;
    ptr = new timeclock;
    ptr->display();
    ptr->formattedDisplay("AM");
    ptr->formattedDisplay("PM");
    delete ptr;

    return 0;
}