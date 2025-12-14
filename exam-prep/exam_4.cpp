#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class Data
{
private:
    int day, month, year;

public:
    Data(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    Data(const Data &other) : day(other.day), month(other.month), year(other.year) {}

    void print() const
    {
        cout << (day < 10 ? "0" : "") << day << "."
             << (month < 10 ? "0" : "") << month << "."
             << year;
    }
};

class Pacient
{
private:
    string ime;
    string egn;
    string oplakvane;
    Data dataPregled;

public:
    Pacient() : ime(""), egn(""), oplakvane(""), dataPregled() {}

    Pacient(const string &i, const string &e, const string &o, const Data &d)
        : ime(i), egn(e), oplakvane(o), dataPregled(d) {}

    string getOplakvane() const { return oplakvane; }

    void print() const
    {
        cout << "Ime: " << ime << ", EGN: " << egn << ", Oplakvane: " << oplakvane
             << ", Data: ";
        dataPregled.print();
        cout << "\n";
    }
};

int main()
{
    int n;
    cout << "Broi pacienti: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Pacient> p;
    p.reserve(n);

    for (int i = 0; i < n; i++)
    {
        string ime, egn, oplakvane;
        int d, m, y;

        cout << "\nPacient " << i + 1 << ":\n";
        cout << "Ime: ";
        getline(cin, ime);

        cout << "EGN: ";
        getline(cin, egn);

        cout << "Oplakvane: ";
        getline(cin, oplakvane);

        cout << "Data na pregled (den mesec godina): ";
        cin >> d >> m >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Data date(d, m, y);
        p.emplace_back(ime, egn, oplakvane, date);
    }

    string target;
    cout << "\nVuvedi oplakvane za tursene: ";
    getline(cin, target);

    cout << "\nPacienti s oplakvane \"" << target << "\":\n";
    bool found = false;
    for (const auto &x : p)
    {
        if (x.getOplakvane() == target)
        {
            x.print();
            found = true;
        }
    }

    if (!found)
        cout << "Nqma namereni pacienti.\n";

    return 0;
}
