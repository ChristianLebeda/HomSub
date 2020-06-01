#ifndef HOMOMORPHISM_HELPERFUNCTIONS_H_
#define HOMOMORPHISM_HELPERFUNCTIONS_H_

#include <string>

class HelperFunctions
{
public:
    static bool hasPrefix(const std::string& str, const std::string& prefix);
    static bool hasSuffix(const std::string& str, const std::string& suffix);
    static bool saveToFile(const std::string& str, const std::string& filename);
    static std::string trimDreadnautOutput(std::ifstream& output, size_t n);
    static size_t pow(size_t n, size_t k);
};

#endif
