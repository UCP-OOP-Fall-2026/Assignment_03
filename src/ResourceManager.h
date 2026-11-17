#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Product.h"

class ResourceManager {
public:
    void updateStock(Product* product, int amount) const;
    void displayInventory(const Product* products, int count) const;
};

#endif
