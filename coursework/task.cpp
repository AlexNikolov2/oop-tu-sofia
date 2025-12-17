#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

static char* copy_cstr(const char* src) {
    if (!src) return nullptr;
    size_t len = strlen(src);
    char* dst = new char[len + 1];
    strcpy(dst, src);
    return dst;
}

class Person {
protected:
    char* name;
    char* egn;
    char* address;

public:
    Person()
        : name(nullptr), egn(nullptr), address(nullptr) {}

    Person(const char* n, const char* e, const char* a)
        : name(copy_cstr(n)), egn(copy_cstr(e)), address(copy_cstr(a)) {}

    Person(const Person& other)
        : name(copy_cstr(other.name)),
          egn(copy_cstr(other.egn)),
          address(copy_cstr(other.address)) {}

    Person& operator=(const Person& other) {
        if (this == &other) return *this;

        delete[] name;
        delete[] egn;
        delete[] address;

        name = copy_cstr(other.name);
        egn = copy_cstr(other.egn);
        address = copy_cstr(other.address);

        return *this;
    }

    virtual ~Person() {
        delete[] name;
        delete[] egn;
        delete[] address;
    }

    const char* getEGN() const { return egn ? egn : ""; }
    const char* getAddress() const { return address ? address : ""; }
    const char* getName() const { return name ? name : ""; }

    virtual void print(ostream& os) const {
        os << "Име: " << getName()
           << ", ЕГН: " << getEGN()
           << ", Адрес: " << getAddress();
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
        p.print(os);            
        return os;
    }
};

class PropertyOwner : public Person {
private:
    static const int MAXP = 5;
    char* props[MAXP];
    int n; 

public:
    PropertyOwner() : Person(), n(0) {
        for (int i = 0; i < MAXP; i++) props[i] = nullptr;
    }

    PropertyOwner(const char* nme, const char* eg, const char* adr,
                  const vector<string>& propertyAddresses)
        : Person(nme, eg, adr), n(0) {
        for (int i = 0; i < MAXP; i++) props[i] = nullptr;

        for (size_t i = 0; i < propertyAddresses.size() && n < MAXP; i++) {
            props[n++] = copy_cstr(propertyAddresses[i].c_str());
        }
    }

    PropertyOwner(const PropertyOwner& other) : Person(other), n(other.n) {
        for (int i = 0; i < MAXP; i++) props[i] = nullptr;
        for (int i = 0; i < n; i++) props[i] = copy_cstr(other.props[i]);
    }

    PropertyOwner& operator=(const PropertyOwner& other) {
        if (this == &other) return *this;

        Person::operator=(other);

        for (int i = 0; i < MAXP; i++) {
            delete[] props[i];
            props[i] = nullptr;
        }

        n = other.n;
        for (int i = 0; i < n; i++) props[i] = copy_cstr(other.props[i]);

        return *this;
    }

    ~PropertyOwner() override {
        for (int i = 0; i < MAXP; i++) delete[] props[i];
    }

    int propertyCount() const { return n; }
    const char* propertyAt(int i) const {
        if (i < 0 || i >= n || !props[i]) return "";
        return props[i];
    }

    bool addressMatchesAnyProperty() const {
        for (int i = 0; i < n; i++) {
            if (props[i] && strcmp(getAddress(), props[i]) == 0) return true;
        }
        return false;
    }

    void print(ostream& os) const override {
        Person::print(os);
        os << "\n  Имоти (" << n << "):";
        if (n == 0) {
            os << " няма";
        } else {
            for (int i = 0; i < n; i++) os << "\n   - " << propertyAt(i);
        }
    }
};

static bool readLineOwner(const string& line, PropertyOwner& out) {
    vector<string> parts;
    string token;
    for (size_t i = 0, start = 0; i <= line.size(); i++) {
        if (i == line.size() || line[i] == ';') {
            parts.push_back(line.substr(start, i - start));
            start = i + 1;
        }
    }

    if (parts.size() < 4) return false;

    string name = parts[0];
    string egn = parts[1];
    string address = parts[2];
    int count = 0;

    try {
        count = stoi(parts[3]);
    } catch (...) {
        return false;
    }

    vector<string> props;
    for (int i = 0; i < count; i++) {
        size_t idx = 4 + (size_t)i;
        if (idx >= parts.size()) break;
        props.push_back(parts[idx]);
    }

    out = PropertyOwner(name.c_str(), egn.c_str(), address.c_str(), props);
    return true;
}

static vector<PropertyOwner> loadFromFile(const string& filename) {
    vector<PropertyOwner> people;
    ifstream in(filename);
    if (!in) return people;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        PropertyOwner p;
        if (readLineOwner(line, p)) people.push_back(p);
    }
    return people;
}

static bool saveToFile(const string& filename, const vector<PropertyOwner>& people) {
    ofstream out(filename);
    if (!out) return false;

    for (const auto& p : people) {
        out << p.getName() << ';'
            << p.getEGN() << ';'
            << p.getAddress() << ';'
            << p.propertyCount();
        for (int i = 0; i < p.propertyCount(); i++) out << ';' << p.propertyAt(i);
        out << "\n";
    }
    return true;
}

static void printOwnersWhoseAddressMatchesProperty(const vector<PropertyOwner>& people) {
    cout << "Лица, чиито адрес съвпада с някой от адресите на притежаваните имоти:\n";
    bool found = false;

    for (const auto& p : people) {
        if (p.addressMatchesAnyProperty()) {
            cout << "---------------------------------\n";
            cout << p << "\n";
            found = true;
        }
    }

    if (!found) cout << "(няма намерени)\n";
}

static void printPropertiesByEGN(const vector<PropertyOwner>& people, const string& egn) {
    for (const auto& p : people) {
        if (egn == p.getEGN()) {
            cout << "Намерено лице:\n" << p << "\n";
            return;
        }
    }
    cout << "Няма лице с ЕГН: " << egn << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string filename = "people.txt";
    vector<PropertyOwner> people = loadFromFile(filename);

    if (people.empty()) {
        people.push_back(PropertyOwner(
            "Иван Петров", "9001012345", "София, ул. А 1",
            {"София, ул. А 1", "Пловдив, бул. Б 10", "Бургас, жк В 5"}
        ));
        people.push_back(PropertyOwner(
            "Мария Георгиева", "9202023456", "Варна, ул. Г 7",
            {"Шумен, ул. Д 3", "Добрич, ул. Е 9"}
        ));
        saveToFile(filename, people);
        cout << "Създаден е примерен файл: " << filename << "\n\n";
    }

    while (true) {
        cout << "\n=== МЕНЮ ===\n"
             << "1) Извеждане на всички лица\n"
             << "2) (Зад.1) Лица с адрес, който съвпада с имот\n"
             << "3) (Зад.2) Извеждане на имотите по ЕГН\n"
             << "4) Запис във файл\n"
             << "0) Изход\n"
             << "Избор: ";

        int choice = -1;
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;

        if (choice == 1) {
            for (const auto& p : people) {
                cout << "---------------------------------\n";
                cout << p << "\n";
            }
        } else if (choice == 2) {
            printOwnersWhoseAddressMatchesProperty(people);
        } else if (choice == 3) {
            cout << "Въведи ЕГН: ";
            string e;
            getline(cin, e);
            printPropertiesByEGN(people, e);
        } else if (choice == 4) {
            if (saveToFile(filename, people)) cout << "Записано в " << filename << "\n";
            else cout << "Грешка при запис!\n";
        } else {
            cout << "Невалиден избор.\n";
        }
    }

    return 0;
}
