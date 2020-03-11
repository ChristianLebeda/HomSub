#ifndef HOMOMORPHISM_THESIS_JOIN_HANDLER_H
#define HOMOMORPHISM_THESIS_JOIN_HANDLER_H

#include <vector>

//TODO: If more techniques are added this will become abstract
class JoinHandler {
public:
    // The first vector might be overridden to store the output
    std::vector<size_t>& join(std::vector<size_t>& first, std::vector<size_t>& second);
};

#endif
