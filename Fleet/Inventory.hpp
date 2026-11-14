#pragma once

#include <string>
#include <iostream>

class InventoryItem {
    public:
        virtual ~InventoryItem() = default;
        virtual std::string inventoryId() const = 0;
        virtual std::string name() const = 0;
        virtual std::string describe() const = 0; 
        virtual void print(std::ostream& os) const = 0; 

        bool operator<(const InventoryItem& other) const {
            return inventoryId() < other.inventoryId();
        }
};

class EnergyConsumer {
    public:
        virtual ~EnergyConsumer() = default;
        virtual double dailyEnergy() const = 0;
};
