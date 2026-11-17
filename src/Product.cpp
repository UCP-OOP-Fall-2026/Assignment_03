#include "Product.h"

#include <iostream>
#include <stdexcept>

int Product::stored = 0;

Product::Product(int id, const std::string& name, const std::string& category,
                 double price, int quantity)
    : id(id), name(name), category(category), price(price), quantity(quantity),
      stockHistory(nullptr), historyCount(0), historyCapacity(0) {
    if (price < 0 || quantity < 0) {
        throw std::invalid_argument("Price and quantity cannot be negative.");
    }

    recordStock();
    ++stored;
}

Product::Product(const Product& other)
    : id(other.id), name(other.name), category(other.category),
      price(other.price), quantity(other.quantity),
      stockHistory(other.historyCount > 0 ? new int[other.historyCount] : nullptr),
      historyCount(other.historyCount), historyCapacity(other.historyCount) {
    // Give the copied product its own stock-history array.
    for (int i = 0; i < historyCount; ++i) {
        stockHistory[i] = other.stockHistory[i];
    }
    ++stored;
}

Product::~Product() {
    delete[] stockHistory;
    --stored;
}

Product& Product::operator=(const Product& other) {
    if (this == &other) {
        return *this;
    }

    int* copiedHistory = nullptr;
    if (other.historyCount > 0) {
        copiedHistory = new int[other.historyCount];
        for (int i = 0; i < other.historyCount; ++i) {
            copiedHistory[i] = other.stockHistory[i];
        }
    }

    delete[] stockHistory;
    stockHistory = copiedHistory;
    historyCount = other.historyCount;
    historyCapacity = other.historyCount;
    name = other.name;
    category = other.category;
    price = other.price;
    quantity = other.quantity;

    // The product ID is const, so assignment keeps this object's ID.
    return *this;
}

int Product::getId() const {
    return id;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

int Product::stockHistorySize() const {
    return historyCount;
}

void Product::recordStock() {
    if (historyCount == historyCapacity) {
        const int newCapacity = historyCapacity == 0 ? 4 : historyCapacity * 2;
        int* largerHistory = new int[newCapacity];

        for (int i = 0; i < historyCount; ++i) {
            largerHistory[i] = stockHistory[i];
        }

        delete[] stockHistory;
        stockHistory = largerHistory;
        historyCapacity = newCapacity;
    }

    stockHistory[historyCount] = quantity;
    ++historyCount;
}

void Product::addStock(int amount) {
    if (quantity + amount < 0) {
        throw std::invalid_argument("Stock cannot become negative.");
    }

    quantity += amount;
    recordStock();
}

int Product::operator+(const Product& other) const {
    if (id != other.id) {
        throw std::invalid_argument("Products must have the same ID to combine stock.");
    }
    return quantity + other.quantity;
}

bool Product::operator==(const Product& other) const {
    return id == other.id;
}

bool Product::operator>(const Product& other) const {
    return price > other.price;
}

Product& Product::operator++() {
    addStock(1);
    return *this;
}

Product Product::operator++(int) {
    Product oldProduct(*this);
    ++(*this);
    return oldProduct;
}

int& Product::operator[](int index) {
    if (index < 0 || index >= historyCount) {
        throw std::out_of_range("Stock history index is out of range.");
    }
    return stockHistory[index];
}

int Product::operator[](int index) const {
    if (index < 0 || index >= historyCount) {
        throw std::out_of_range("Stock history index is out of range.");
    }
    return stockHistory[index];
}

int Product::totalStored() {
    return stored;
}

std::ostream& operator<<(std::ostream& out, const Product& product) {
    out << "Product ID: " << product.id
        << "\nName: " << product.name
        << "\nCategory: " << product.category
        << "\nPrice: Rs. " << product.price
        << "\nQuantity: " << product.quantity << '\n';
    return out;
}
