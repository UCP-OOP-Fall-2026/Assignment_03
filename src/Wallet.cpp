#include "Wallet.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

int Wallet::walletsCreated = 0;

Wallet::Wallet(int id, const std::string& owner, double balance)
    : id(id), owner(owner), balance(balance), transactions(nullptr),
      transactionCount(0), transactionCapacity(0) {
    if (balance < 0) throw std::invalid_argument("Initial balance cannot be negative");
    ++walletsCreated;
}

Wallet::Wallet(const Wallet& other)
    : id(other.id), owner(other.owner), balance(other.balance),
      transactions(other.transactionCount > 0
                       ? new double[other.transactionCount]
                       : nullptr),
      transactionCount(other.transactionCount),
      transactionCapacity(other.transactionCount) {
    // Copy each transaction so this wallet owns its separate history array.
    for (int i = 0; i < transactionCount; ++i) {
        transactions[i] = other.transactions[i];
    }
    ++walletsCreated;
}

Wallet::~Wallet() {
    delete[] transactions;
}

Wallet& Wallet::operator=(const Wallet& other) {
    if (this == &other) {
        return *this;
    }

    double* copiedTransactions = nullptr;
    if (other.transactionCount > 0) {
        copiedTransactions = new double[other.transactionCount];
        for (int i = 0; i < other.transactionCount; ++i) {
            copiedTransactions[i] = other.transactions[i];
        }
    }

    delete[] transactions;
    transactions = copiedTransactions;
    transactionCount = other.transactionCount;
    transactionCapacity = other.transactionCount;
    owner = other.owner;
    balance = other.balance;

    // The wallet ID is const, so assignment preserves this object's ID.
    return *this;
}

void Wallet::record(double amount) {
    if (transactionCount == transactionCapacity) {
        const int newCapacity = transactionCapacity == 0
                                    ? 4
                                    : transactionCapacity * 2;
        double* largerArray = new double[newCapacity];

        for (int i = 0; i < transactionCount; ++i) {
            largerArray[i] = transactions[i];
        }

        delete[] transactions;
        transactions = largerArray;
        transactionCapacity = newCapacity;
    }

    transactions[transactionCount] = amount;
    ++transactionCount;
}

void Wallet::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit must be positive");
    }

    record(amount);
    balance += amount;
}

bool Wallet::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    record(-amount);
    balance -= amount;
    return true;
}

double Wallet::operator+(const Wallet& other) const {
    return balance + other.balance;
}

double Wallet::operator-(const Wallet& other) const {
    return balance - other.balance;
}

bool Wallet::operator==(const Wallet& other) const {
    return std::round(balance * 100) == std::round(other.balance * 100);
}

int Wallet::totalCreated() {
    return walletsCreated;
}

std::ostream& operator<<(std::ostream& out, const Wallet& wallet) {
    out << "Wallet ID: " << wallet.id
        << "\nOwner: " << wallet.owner
        << "\nBalance: Rs. " << wallet.balance
        << "\nTransactions:\n";

    for (int i = 0; i < wallet.transactionCount; ++i) {
        if (wallet.transactions[i] >= 0) {
            out << "Deposit: Rs. " << wallet.transactions[i] << '\n';
        } else {
            out << "Withdraw: Rs. " << -wallet.transactions[i] << '\n';
        }
    }

    return out;
}

void compareWallets(const Wallet& first, const Wallet& second) {
    const double firstBalanceInCents = std::round(first.balance * 100);
    const double secondBalanceInCents = std::round(second.balance * 100);

    if (firstBalanceInCents > secondBalanceInCents) {
        std::cout << first.owner << " has a higher balance.\n";
    } else if (secondBalanceInCents > firstBalanceInCents) {
        std::cout << second.owner << " has a higher balance.\n";
    } else {
        std::cout << "Wallets have equal balances.\n";
    }
}
