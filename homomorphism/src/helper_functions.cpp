#include "homomorphism/helper_functions.h"

#include <fstream>
#include <iostream>

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

std::string HelperFunctions::trimDreadnautOutput(PipeHandler& dread, size_t n) 
{
    std::ostringstream out;

    std::istringstream line;
    size_t v;

    std::string tmp = dread.nextLine();

    for (size_t i = 0; i < n; i++)
    {
        line.clear();
        line.str(dread.nextLine());

        line >> tmp >> tmp;

        while (line >> v) {
            if (i < v) {
                out << " " << v;
            }
        }

        out << ";";
    }

    return out.str();
}