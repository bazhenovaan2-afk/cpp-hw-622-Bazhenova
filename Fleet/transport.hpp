#pragma once
#include "Inventory.hpp"

class Transport : public InventoryItem {
    protected:
        std::string id2;
        std::string name2;
        int just_score;
    public:
    Transport(std::string id, std::string name, int score) 
    : id2(id), name2(name), just_score(score) {}

    std::string inventoryId() const override { return id2; }
    std::string name() const override { return name2; }

    int getScore() const { return just_score; }

    void print(std::ostream& os) const override {
        os << id2 << " " << name2;
    }
};

class Bicycle : public Transport {
    public:
        Bicycle(std::string id, std::string name, int score)
            : Transport(id, name, score) {}
};

class El_samokat : public Transport, public EnergyConsumer {
    private:
        double energy_d;
    public:
    El_samokat(std::string id, std::string name, double energy, int score)
    : Transport(id, name, score), energy_d(energy) {}

    double dailyEnergy() const override { 
        return energy_d; 
    }
};