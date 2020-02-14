#include <homomorphism/helper_functions.h>
#include <iostream>
#include <fstream>

bool HelperFunctions::hasSuffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool HelperFunctions::saveToFile(const std::string& str, const std::string& filename)
{
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    out << str;
    return true;
}