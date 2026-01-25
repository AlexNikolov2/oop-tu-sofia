#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class Product
{
protected:
    char *title;
    double price;

    void copyTitle(const char *t)
    {
        if (t)
        {
            title = new char[strlen(t) + 1];
            strcpy(title, t);
        }
        else
        {
            title = nullptr;
        }
    }

public:
    Product() : title(nullptr), price(0.0) {}

    Product(const char *t, double p) : title(nullptr)
    {
        setTitle(t);
        setPrice(p);
    }

    Product(const Product &other) : title(nullptr), price(other.price)
    {
        copyTitle(other.title);
    }

    Product &operator=(const Product &other)
    {
        if (this != &other)
        {
            delete[] title;
            copyTitle(other.title);
            price = other.price;
        }
        return *this;
    }

    virtual ~Product()
    {
        delete[] title;
    }

    void setTitle(const char *t)
    {
        if (t && strlen(t) >= 3 && strlen(t) <= 40)
        {
            delete[] title;
            copyTitle(t);
        }
        else
        {
            throw invalid_argument("Title must be between 3 and 40 characters");
        }
    }

    void setPrice(double p)
    {
        if (p > 0)
        {
            price = p;
        }
        else
        {
            throw invalid_argument("Price must be positive");
        }
    }

    const char *getTitle() const { return title; }
    double getPrice() const { return price; }

    virtual void display() const
    {
        cout << "Title: " << title << ", Price: " << price;
    }

    virtual string getType() const = 0;
};

class OnlineProduct : public Product
{
private:
    char *url;

    void copyUrl(const char *u)
    {
        if (u)
        {
            url = new char[strlen(u) + 1];
            strcpy(url, u);
        }
        else
        {
            url = nullptr;
        }
    }

public:
    OnlineProduct() : Product(), url(nullptr) {}

    OnlineProduct(const char *t, double p, const char *u) : Product(t, p), url(nullptr)
    {
        copyUrl(u);
    }

    OnlineProduct(const OnlineProduct &other) : Product(other), url(nullptr)
    {
        copyUrl(other.url);
    }

    OnlineProduct &operator=(const OnlineProduct &other)
    {
        if (this != &other)
        {
            Product::operator=(other);
            delete[] url;
            copyUrl(other.url);
        }
        return *this;
    }

    ~OnlineProduct()
    {
        delete[] url;
    }

    const char *getUrl() const { return url; }

    void display() const override
    {
        Product::display();
        cout << ", URL: " << url;
    }

    string getType() const override { return "Online"; }

    friend ostream &operator<<(ostream &os, const OnlineProduct &p)
    {
        os << "Online Product - Title: " << p.title << ", Price: " << p.price << ", URL: " << p.url;
        return os;
    }
};

class PhysicalProduct : public Product
{
private:
    int quantity;

public:
    PhysicalProduct() : Product(), quantity(0) {}

    PhysicalProduct(const char *t, double p, int q) : Product(t, p), quantity(q) {}

    void setQuantity(int q) { quantity = q; }
    int getQuantity() const { return quantity; }

    void display() const override
    {
        Product::display();
        cout << ", Quantity: " << quantity;
    }

    string getType() const override { return "Physical"; }

    friend ostream &operator<<(ostream &os, const PhysicalProduct &p)
    {
        os << "Physical Product - Title: " << p.title << ", Price: " << p.price << ", Quantity: " << p.quantity;
        return os;
    }
};

// Search by title and return count or URL
void searchByTitle(const vector<Product *> &products, const char *searchTitle)
{
    int physicalCount = 0;
    int onlineCount = 0;
    string foundUrl = "";

    for (const auto &product : products)
    {
        if (strcmp(product->getTitle(), searchTitle) == 0)
        {
            if (product->getType() == "Physical")
            {
                physicalCount++;
            }
            else if (product->getType() == "Online")
            {
                onlineCount++;
                OnlineProduct *op = dynamic_cast<OnlineProduct *>(product);
                if (op)
                {
                    foundUrl = op->getUrl();
                }
            }
        }
    }

    cout << "Search results for '" << searchTitle << "':" << endl;
    if (physicalCount > 0)
    {
        cout << "  Physical products: " << physicalCount << endl;
    }
    if (onlineCount > 0)
    {
        cout << "  Online products: " << onlineCount;
        if (!foundUrl.empty())
        {
            cout << ", URL: " << foundUrl;
        }
        cout << endl;
    }
    if (physicalCount == 0 && onlineCount == 0)
    {
        cout << "  No products found" << endl;
    }
}

// Search in price range
void searchByPriceRange(const vector<Product *> &products, double minPrice, double maxPrice)
{
    cout << "Products in price range " << minPrice << " - " << maxPrice << ":" << endl;
    bool found = false;

    for (const auto &product : products)
    {
        if (product->getPrice() >= minPrice && product->getPrice() <= maxPrice)
        {
            product->display();
            cout << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "  No products found in this price range" << endl;
    }
}

int main()
{
    vector<Product *> products;

    try
    {
        // Create some products
        products.push_back(new OnlineProduct("Laptop", 1200.50, "https://shop.com/laptop"));
        products.push_back(new PhysicalProduct("Laptop", 1200.50, 5));
        products.push_back(new OnlineProduct("Mouse", 25.99, "https://shop.com/mouse"));
        products.push_back(new PhysicalProduct("Keyboard", 75.00, 10));
        products.push_back(new PhysicalProduct("Monitor", 350.00, 3));
        products.push_back(new OnlineProduct("Software License", 99.99, "https://shop.com/software"));

        // Display all products
        cout << "All Products:" << endl;
        for (const auto &product : products)
        {
            product->display();
            cout << endl;
        }
        cout << endl;

        // Test operator <<
        cout << "Using operator <<:" << endl;
        OnlineProduct *op = dynamic_cast<OnlineProduct *>(products[0]);
        if (op)
            cout << *op << endl;

        PhysicalProduct *pp = dynamic_cast<PhysicalProduct *>(products[1]);
        if (pp)
            cout << *pp << endl;
        cout << endl;

        // Search by title
        searchByTitle(products, "Laptop");
        cout << endl;

        searchByTitle(products, "Mouse");
        cout << endl;

        // Search by price range
        searchByPriceRange(products, 50.0, 500.0);
        cout << endl;

        searchByPriceRange(products, 1000.0, 1500.0);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    // Clean up
    for (auto product : products)
    {
        delete product;
    }

    return 0;
}
