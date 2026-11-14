#pragma once
#include "Inventory.hpp"
#include <string>

class Helmet : public InventoryItem {
    private:
        std::string id2;
        std::string name2;
    public:
        Helmet(std::string id, std::string name)
        : id2(id), name2(name) {}

        std::string inventoryId() const override { return id2; }
        std::string name() const override { return name2; }
        std::string describe() const override { return "Helmet: " + name2; }

        void print(std::ostream& os) const override {
            os << id2 << " " << name2;
        }
};

class Dock : public InventoryItem, public EnergyConsumer {
    private:
        std::string id2;
        std::string name2;
        double energy2;
    public:
        Dock(std::string id, std::string name, double energy)
        : id2(id), name2(name), energy2(energy) {}

        std::string inventoryId() const override { return id2; }
        std::string name() const override { return name2; }
        std::string describe() const override { return "Dock: " + name2; }

        double dailyEnergy() const override {
            return energy2;
        }

        void print(std::ostream& os) const override {
            os << id2 << " " << name2;
        }
};
