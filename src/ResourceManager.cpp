#include "ResourceManager.h"

#include <iostream>
#include <stdexcept>

void ResourceManager::updateStock(Product* product, int amount) const {
    if (product == nullptr) {
        return;
    }

    if (product->quantity + amount < 0) {
        throw std::invalid_argument("Stock cannot become negative.");
    }

    product->quantity += amount;
    product->recordStock();
}

void ResourceManager::displayInventory(const Product* products, int count) const {
    for (int i = 0; i < count; ++i) {
        std::cout << products[i];
    }
}
