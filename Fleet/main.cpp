#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cctype>

#include "errors.hpp"
#include "Inventory.hpp"
#include "things.hpp"
#include "transport.hpp"
#include "Service.hpp"
#include "Registry.hpp"


struct ModelSpec {
    std::string name;
};


class El_Bike : public Transport, public EnergyConsumer {
    double energy2;
public:
    El_Bike(std::string id, std::string name, double energy, int score)
        : Transport(id, name, score), energy2(energy) {}

    std::string describe() const override {
        return "Electric Bike: " + name2;
    }

    double dailyEnergy() const override {
        return energy2;
    }
};

int main() {
    Registry<InventoryItem, 1000> park;
    std::map<std::string, std::shared_ptr<InventoryItem>> sharedItems;
    std::weak_ptr<InventoryItem> focus;
    std::map<std::string, std::shared_ptr<ModelSpec>> models;
    std::map<std::string, std::shared_ptr<ModelSpec>> itemModels;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "quit") break;

        try {
            if (cmd == "add") {
                std::string type;
                iss >> type;

                if (type == "scooter") {
                    std::string id, name;
                    double energy;
                    int score;
                    if (!(iss >> id >> name >> energy >> score))
                        throw ArgumentError("invalid arguments for add scooter");
                    if (id.empty()) throw ArgumentError("empty id");
                    if (energy < 0) throw ArgumentError("negative energy");
                    if (score < 1 || score > 10) throw ArgumentError("score out of range 1..10");

                    ServiceCenter::inspect(name);

                    auto item = std::make_unique<El_samokat>(id, name, energy, score);
                    InventoryItem* raw = item.get();
                    park.add(std::move(item));
                    sharedItems[id] = std::shared_ptr<InventoryItem>(raw, [](InventoryItem*){});
                    auto& spec = models[name];
                    if (!spec) spec = std::make_shared<ModelSpec>(ModelSpec{name});
                    itemModels[id] = spec;
                } else if (type == "bike") {
                    std::string id, name;
                    int score;
                    if (!(iss >> id >> name >> score))
                        throw ArgumentError("invalid arguments for add bike");
                    if (id.empty()) throw ArgumentError("empty id");
                    if (score < 1 || score > 10) throw ArgumentError("score out of range 1..10");

                    ServiceCenter::inspect(name);

                    auto item = std::make_unique<Bicycle>(id, name, score);
                    InventoryItem* raw = item.get();
                    park.add(std::move(item));
                    sharedItems[id] = std::shared_ptr<InventoryItem>(raw, [](InventoryItem*){});
                } else if (type == "ebike") {
                    std::string id, name;
                    double energy;
                    int score;
                    if (!(iss >> id >> name >> energy >> score))
                        throw ArgumentError("invalid arguments for add ebike");
                    if (id.empty()) throw ArgumentError("empty id");
                    if (energy < 0) throw ArgumentError("negative energy");
                    if (score < 1 || score > 10) throw ArgumentError("score out of range 1..10");

                    ServiceCenter::inspect(name);

                    auto item = std::make_unique<El_Bike>(id, name, energy, score);
                    InventoryItem* raw = item.get();
                    park.add(std::move(item));
                    sharedItems[id] = std::shared_ptr<InventoryItem>(raw, [](InventoryItem*){});
                    auto& spec = models[name];
                    if (!spec) spec = std::make_shared<ModelSpec>(ModelSpec{name});
                    itemModels[id] = spec;
                } else if (type == "helmet") {
                    std::string id, name;
                    if (!(iss >> id >> name))
                        throw ArgumentError("invalid arguments for add helmet");
                    if (id.empty()) throw ArgumentError("empty id");

                    auto item = std::make_unique<Helmet>(id, name);
                    InventoryItem* raw = item.get();
                    park.add(std::move(item));
                    sharedItems[id] = std::shared_ptr<InventoryItem>(raw, [](InventoryItem*){});
                } else if (type == "dock") {
                    std::string id, name;
                    double energy;
                    if (!(iss >> id >> name >> energy))
                        throw ArgumentError("invalid arguments for add dock");
                    if (id.empty()) throw ArgumentError("empty id");
                    if (energy < 0) throw ArgumentError("negative energy");

                    auto item = std::make_unique<Dock>(id, name, energy);
                    InventoryItem* raw = item.get();
                    park.add(std::move(item));
                    sharedItems[id] = std::shared_ptr<InventoryItem>(raw, [](InventoryItem*){});
                } else {
                    throw ArgumentError("unknown add type: " + type);
                }
            } else if (cmd == "energy") {
                double total = 0.0;
                for (size_t i = 0; i < park.size(); ++i) {
                    if (auto ec = dynamic_cast<const EnergyConsumer*>(&park[i]))
                        total += ec->dailyEnergy();
                }
                std::cout << std::fixed << std::setprecision(1) << total << "\n";
            } else if (cmd == "novice") {
                for (size_t i = 0; i < park.size(); ++i) {
                    if (auto t = dynamic_cast<const Transport*>(&park[i])) {
                        if (t->getScore() >= 6)
                            std::cout << t->inventoryId() << " " << t->name() << "\n";
                    }
                }
            } else if (cmd == "list") {
                std::vector<const InventoryItem*> items;
                for (size_t i = 0; i < park.size(); ++i)
                    items.push_back(&park[i]);
                std::sort(items.begin(), items.end(),
                          [](const InventoryItem* a, const InventoryItem* b) {
                              return *a < *b;
                          });
                for (auto* item : items)
                    std::cout << *item << "\n";
            } else if (cmd == "focus") {
                std::string id;
                if (!(iss >> id)) throw ArgumentError("missing id for focus");
                auto it = sharedItems.find(id);
                if (it == sharedItems.end())
                    throw ArgumentError("item not found: " + id);
                focus = it->second;
            } else if (cmd == "show_focus") {
                if (auto sp = focus.lock())
                    std::cout << sp->inventoryId() << " " << sp->name() << "\n";
                else
                    std::cout << "expired\n";
            } else if (cmd == "remove") {
                std::string id;
                if (!(iss >> id)) throw ArgumentError("missing id for remove");
                bool found = false;
                for (size_t i = 0; i < park.size(); ++i) {
                    if (park[i].inventoryId() == id) {
                        found = true;
                        break;
                    }
                }
                if (!found) throw ArgumentError("item not found: " + id);
                sharedItems.erase(id);
                itemModels.erase(id);
                park.removeById(id);
            } else {
                throw ArgumentError("unknown command: " + cmd);
            }
        } catch (const FleetError& e) {
            std::cout << "error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << "\n";
        }
    }
}
