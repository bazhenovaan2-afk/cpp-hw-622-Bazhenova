#pragma once

#include <iostream>
#include <string>

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

std::ostream& operator<<(std::ostream& os, const InventoryItem& item);

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double dailyEnergy() const = 0;
};
