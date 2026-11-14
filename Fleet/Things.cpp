#include "things.hpp"

Helmet::Helmet(std::string id, std::string name) : id2(id), name2(name) {}
std::string Helmet::inventoryId() const { return id2; }
std::string Helmet::name() const { return name2; }
std::string Helmet::describe() const { return "Helmet: " + name2; }
void Helmet::print(std::ostream& os) const {
    os << id2 << " " << name2;
}

Dock::Dock(std::string id, std::string name, double energy) : id2(id), name2(name), energy2(energy) {}
std::string Dock::inventoryId() const { return id2; }
std::string Dock::name() const { return name2; }
std::string Dock::describe() const { return "Dock: " + name2; }
double Dock::dailyEnergy() const { return energy2; }
void Dock::print(std::ostream& os) const {
    os << id2 << " " << name2;
}