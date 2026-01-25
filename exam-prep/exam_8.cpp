#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <regex>
#include <iomanip>

using namespace std;

// Базов клас Ticket
class Ticket
{
protected:
    string title;
    double price;
    string date;

    // Помощна функция за валидация на дата
    bool isValidDate(const string &d) const
    {
        // Проверка за формат YYYY-MM-DD
        regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
        return regex_match(d, datePattern);
    }

public:
    Ticket(const string &t, double p, const string &d)
    {
        setTitle(t);
        setPrice(p);
        setDate(d);
    }

    virtual ~Ticket() = default;

    void setTitle(const string &t)
    {
        if (t.length() < 3 || t.length() > 40)
        {
            throw invalid_argument("Title must be between 3 and 40 characters");
        }
        title = t;
    }

    void setPrice(double p)
    {
        if (p <= 0)
        {
            throw invalid_argument("Price must be greater than 0");
        }
        price = p;
    }

    void setDate(const string &d)
    {
        if (!isValidDate(d))
        {
            throw invalid_argument("Date must be in format YYYY-MM-DD");
        }
        date = d;
    }

    string getTitle() const { return title; }
    double getPrice() const { return price; }
    string getDate() const { return date; }

    virtual void print(ostream &os) const
    {
        os << "Title: " << title << ", Price: " << fixed << setprecision(2)
           << price << " BGN, Date: " << date;
    }

    virtual string getType() const = 0; // за да можем да различим типовете
};

// Наследник BusTicket
class BusTicket : public Ticket
{
private:
    int seatNumber;

public:
    BusTicket(const string &t, double p, const string &d, int seat)
        : Ticket(t, p, d)
    {
        setSeatNumber(seat);
    }

    void setSeatNumber(int seat)
    {
        if (seat <= 0)
        {
            throw invalid_argument("Seat number must be greater than 0");
        }
        seatNumber = seat;
    }

    int getSeatNumber() const { return seatNumber; }

    void print(ostream &os) const override
    {
        Ticket::print(os);
        os << ", Seat: " << seatNumber;
    }

    string getType() const override { return "BUS"; }
};

// Наследник TrainTicket
class TrainTicket : public Ticket
{
private:
    int wagon;
    int seatNumber;

public:
    TrainTicket(const string &t, double p, const string &d, int w, int seat)
        : Ticket(t, p, d)
    {
        setWagon(w);
        setSeatNumber(seat);
    }

    void setWagon(int w)
    {
        if (w <= 0)
        {
            throw invalid_argument("Wagon number must be greater than 0");
        }
        wagon = w;
    }

    void setSeatNumber(int seat)
    {
        if (seat <= 0)
        {
            throw invalid_argument("Seat number must be greater than 0");
        }
        seatNumber = seat;
    }

    int getWagon() const { return wagon; }
    int getSeatNumber() const { return seatNumber; }

    void print(ostream &os) const override
    {
        Ticket::print(os);
        os << ", Wagon: " << wagon << ", Seat: " << seatNumber;
    }

    string getType() const override { return "TRAIN"; }
};

// Претоварване на operator<<
ostream &operator<<(ostream &os, const Ticket &ticket)
{
    ticket.print(os);
    return os;
}

// Функция за търсене по title
void searchByTitle(const vector<unique_ptr<Ticket>> &tickets, const string &searchTitle)
{
    cout << "\n--- Searching for tickets with title: " << searchTitle << " ---\n";
    bool found = false;

    for (const auto &ticket : tickets)
    {
        if (ticket->getTitle() == searchTitle)
        {
            found = true;
            cout << *ticket;

            // Проверка на типа и извеждане на специфична информация
            if (BusTicket *busTicket = dynamic_cast<BusTicket *>(ticket.get()))
            {
                cout << " [Bus - Seat: " << busTicket->getSeatNumber() << "]";
            }
            else if (TrainTicket *trainTicket = dynamic_cast<TrainTicket *>(ticket.get()))
            {
                cout << " [Train - Wagon: " << trainTicket->getWagon()
                     << ", Seat: " << trainTicket->getSeatNumber() << "]";
            }
            cout << endl;
        }
    }

    if (!found)
    {
        cout << "No tickets found with title: " << searchTitle << endl;
    }
}

// Функция за търсене в ценови диапазон
void searchByPriceRange(const vector<unique_ptr<Ticket>> &tickets, double from, double to)
{
    cout << "\n--- Tickets in price range [" << fixed << setprecision(2)
         << from << " - " << to << "] BGN ---\n";
    bool found = false;

    for (const auto &ticket : tickets)
    {
        if (ticket->getPrice() >= from && ticket->getPrice() <= to)
        {
            found = true;
            cout << *ticket << endl;
        }
    }

    if (!found)
    {
        cout << "No tickets found in this price range." << endl;
    }
}

// Функция за изчисляване на средни цени
void calculateAveragePrices(const vector<unique_ptr<Ticket>> &tickets)
{
    double busSum = 0;
    int busCount = 0;
    double trainSum = 0;
    int trainCount = 0;

    for (const auto &ticket : tickets)
    {
        if (dynamic_cast<BusTicket *>(ticket.get()))
        {
            busSum += ticket->getPrice();
            busCount++;
        }
        else if (dynamic_cast<TrainTicket *>(ticket.get()))
        {
            trainSum += ticket->getPrice();
            trainCount++;
        }
    }

    cout << "\n--- Average Prices ---\n";
    if (busCount > 0)
    {
        cout << "Average bus ticket price: " << fixed << setprecision(2)
             << (busSum / busCount) << " BGN (from " << busCount << " tickets)\n";
    }
    else
    {
        cout << "No bus tickets available.\n";
    }

    if (trainCount > 0)
    {
        cout << "Average train ticket price: " << fixed << setprecision(2)
             << (trainSum / trainCount) << " BGN (from " << trainCount << " tickets)\n";
    }
    else
    {
        cout << "No train tickets available.\n";
    }
}

int main()
{
    vector<unique_ptr<Ticket>> tickets;

    try
    {
        int n;
        cout << "Enter number of tickets: ";
        cin >> n;
        cin.ignore(); // изчистване на буфера

        for (int i = 0; i < n; i++)
        {
            char type;
            cout << "\nTicket " << (i + 1) << ":\n";
            cout << "Type (B for Bus, T for Train): ";
            cin >> type;

            string title, date;
            double price;

            cout << "Title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Price: ";
            cin >> price;

            cout << "Date (YYYY-MM-DD): ";
            cin >> date;

            if (type == 'B' || type == 'b')
            {
                int seat;
                cout << "Seat number: ";
                cin >> seat;
                tickets.push_back(make_unique<BusTicket>(title, price, date, seat));
                cout << "Bus ticket added successfully!\n";
            }
            else if (type == 'T' || type == 't')
            {
                int wagon, seat;
                cout << "Wagon number: ";
                cin >> wagon;
                cout << "Seat number: ";
                cin >> seat;
                tickets.push_back(make_unique<TrainTicket>(title, price, date, wagon, seat));
                cout << "Train ticket added successfully!\n";
            }
            else
            {
                cout << "Invalid ticket type! Skipping...\n";
            }
        }

        // Извеждане на всички билети
        cout << "\n========================================\n";
        cout << "ALL TICKETS:\n";
        cout << "========================================\n";
        for (size_t i = 0; i < tickets.size(); i++)
        {
            cout << (i + 1) << ". " << *tickets[i] << endl;
        }

        // Търсене по title
        string searchTitle;
        cout << "\nEnter title to search for: ";
        cin.ignore();
        getline(cin, searchTitle);
        searchByTitle(tickets, searchTitle);

        // Търсене в ценови диапазон
        double from, to;
        cout << "\nEnter price range (from to): ";
        cin >> from >> to;
        searchByPriceRange(tickets, from, to);

        // Средни цени
        calculateAveragePrices(tickets);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
