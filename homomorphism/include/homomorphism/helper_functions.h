#ifndef HOMOMORPHISM_HELPERFUNCTIONS_H_
#define HOMOMORPHISM_HELPERFUNCTIONS_H_

#include <string>

class HelperFunctions
{
public:
    static bool hasSuffix(const std::string& str, const std::string& suffix);
    static bool saveToFile(const std::string& str, const std::string& filename);
};

#endif
