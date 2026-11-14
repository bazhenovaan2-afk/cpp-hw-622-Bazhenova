#include "Inventory.hpp"

std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    item.print(os);
    return os;
}