#ifndef PRODUCT_H
#define PRODUCT_H

#include <iosfwd>
#include <string>

class ResourceManager;

class Product {
    const int id;
    std::string name;
    std::string category;
    double price;
    int quantity;
    int* stockHistory;
    int historyCount;
    int historyCapacity;
    static int stored;

    void recordStock();

public:
    Product(int id, const std::string& name, const std::string& category, double price, int quantity);
    Product(const Product& other);
    ~Product();

    Product& operator=(const Product& other);
    int getId() const;
    double getPrice() const;
    int getQuantity() const;
    int stockHistorySize() const;
    void addStock(int amount);

    int operator+(const Product& other) const;
    bool operator==(const Product& other) const;
    bool operator>(const Product& other) const;
    Product& operator++();
    Product operator++(int);
    int& operator[](int index);
    int operator[](int index) const;

    static int totalStored();
    friend class ResourceManager;
    friend std::ostream& operator<<(std::ostream&, const Product&);
};

#endif
