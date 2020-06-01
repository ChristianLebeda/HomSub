#include "homomorphism/helper_functions.h"

#include <fstream>
#include <iostream>
#include <sstream>

bool HelperFunctions::hasSuffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool HelperFunctions::hasPrefix(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() &&
           str.compare(0, prefix.size(), prefix) == 0;
}

bool HelperFunctions::saveToFile(const std::string& str, const std::string& filename)
{
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    out << str;
    return true;
}


std::string HelperFunctions::trimDreadnautOutput(std::ifstream& dread, size_t n)
{
    std::ostringstream out;

    std::istringstream line;
    size_t v;

    std::string tmp;

    do {
        std::getline(dread, tmp);
    } while(!hasPrefix(tmp, "  0 :"));

    for (size_t i = 0; i < n; i++)
    {
        line.clear();
        if(i) {
            std::getline(dread, tmp);
        }

        line.str(tmp);

        line >> tmp >> tmp;

        while (line >> v) {
            if (i < v) {
                out << " " << v;
            }
        }

        out << " ; ";
    }

    return out.str();
}

size_t HelperFunctions::pow(size_t n, size_t k) {
    size_t result = 1;
    for (size_t i = 0; i < k; ++i) {
        result *= n;
    }
    return result;
}

