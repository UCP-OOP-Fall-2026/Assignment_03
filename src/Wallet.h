#ifndef WALLET_H
#define WALLET_H

#include <iosfwd>
#include <string>

class Wallet {
    const int id;
    std::string owner;
    double balance;
    double* transactions;
    int transactionCount;
    int transactionCapacity;
    static int walletsCreated;

    void record(double amount);

public:
    Wallet(int id, const std::string& owner, double balance = 0);
    Wallet(const Wallet& other);
    ~Wallet();

    Wallet& operator=(const Wallet& other);
    void deposit(double amount);
    bool withdraw(double amount);

    double operator+(const Wallet& other) const;
    double operator-(const Wallet& other) const;
    bool operator==(const Wallet& other) const;

    static int totalCreated();
    friend void compareWallets(const Wallet&, const Wallet&);
    friend std::ostream& operator<<(std::ostream&, const Wallet&);
};

#endif
