#include "Utils.h"
#include <iostream>
#include <string>
#include <functional>

namespace Utils {
    // Simple hash function for strings
    int hashKey(const std::string& key) {
        std::hash<std::string> hashFn;
        return hashFn(key); // Using std::hash for simplicity
    }
}
