#include "Transport.hpp"

Transport::Transport(std::string id, std::string name, int score) 
    : id2(id), name2(name), just_score(score) {}

std::string Transport::inventoryId() const { return id2; }
std::string Transport::name() const { return name2; }
int Transport::getScore() const { return just_score; }

void Transport::print(std::ostream& os) const {
    os << id2 << " " << name2;
}

Bicycle::Bicycle(std::string id, std::string name, int score)
    : Transport(id, name, score) {}

El_samokat::El_samokat(std::string id, std::string name, double energy, int score)
    : Transport(id, name, score), energy_d(energy) {}

double El_samokat::dailyEnergy() const { 
    return energy_d; 
}