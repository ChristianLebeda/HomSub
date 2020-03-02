#ifndef HOMOMORPHISM_HELPERFUNCTIONS_H_
#define HOMOMORPHISM_HELPERFUNCTIONS_H_

#include <string>

#include "homomorphism/pipe_handler.h"

class HelperFunctions
{
public:
    static bool hasPrefix(const std::string& str, const std::string& prefix);
    static bool hasSuffix(const std::string& str, const std::string& suffix);
    static bool saveToFile(const std::string& str, const std::string& filename);
    static std::string trimDreadnautOutput(std::ifstream& output, size_t n);
    static std::string trimDreadnautOutput(PipeHandler& output, size_t n);
};

#endif
