#pragma once
#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
    public:
        FleetError(const std::string& str_err) : std::runtime_error(str_err) {}
};

class InspectionError : public FleetError {
    public:
        InspectionError(const std::string& str_err) : FleetError(str_err) {}
};

class ArgumentError : public FleetError {
    public:
        ArgumentError(const std::string& str_err) : FleetError(str_err) {}
}
