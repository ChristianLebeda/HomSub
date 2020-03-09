#ifndef HOMOMORPHISM_REMAPPER_H
#define HOMOMORPHISM_REMAPPER_H

#include <vector>

// Used to modify the state of the DP
// A desired vertex is either moving from or to the last position
class Remapper {
public:
    // Moves the vertex from pos to the last position
    virtual void Extract(std::vector<size_t> in, std::vector<size_t> out, size_t pos) = 0;
    // Moves the vertex from the last position to pos
    virtual void Insert(std::vector<size_t> in, std::vector<size_t> out, size_t pos) = 0;
};

#endif
