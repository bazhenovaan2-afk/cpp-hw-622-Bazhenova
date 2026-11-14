#pragma once
#include <vector>
#include <iostream>
#include <memory>

template <typename T, int Cap>
class Registry {
private:
    std::vector<std::unique_ptr<T>> items2;

public:
    void add(std::unique_ptr<T> item) {
        if (items2.size() < Cap) {
            items2.push_back(std::move(item));
        }
    }

    size_t size() const {
        return items2.size();
    }

    const T& operator[](size_t index) const {
        return *items2[index];
    }

    T& operator[](size_t index) {
        return *items2[index];
    }
};

template <typename T, int Cap>
std::ostream& operator<<(std::ostream& os, const Registry<T, Cap>& reg) {
    for (size_t i = 0; i < reg.size(); ++i) {
        os << reg[i] << "\n";
    }
    return os;
}

template <>
class Registry<std::string, 0> {
public:
    void add(const std::string&) {}
    size_t size() const { return 0; }
};
