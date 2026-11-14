#pragma once
#include <string>
#include <algorithm>
#include "errors.hpp"
class ServiceCenter {
    public:
        static void inspect(const std::string& name) {
            std::string low = name;
            std::transform(low.begin(), low.end(), low.begin(), ::tolower);

            if (low.find("broken") != std::string::npos) {
                throw InspectionError("inspection rejected");
            }
        }
};
