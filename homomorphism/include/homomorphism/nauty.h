#ifndef HOMOMORPHISM_NAUTY_H
#define HOMOMORPHISM_NAUTY_H

#include "homomorphism/spasm_reducer.h"

#include <memory>
#include <string>
#include <vector>

#include "homomorphism/pipe_handler.h"
#include "homomorphism/spasm.h"

struct NautyEntry
{
    std::string graph;
    size_t n;
    int coefficient;
    bool operator<(const NautyEntry& rhs) const {
        return graph < rhs.graph;
    }
};

class Nauty : public SpasmReducer
{
public:
    void Test(std::vector<SpasmEntry> spasm);
    std::vector<SpasmEntry> joinIsomorphic(const std::vector<SpasmEntry>& spasm) override;
private:
    std::vector<NautyEntry> convertToNauty(const std::vector<SpasmEntry>& spasm);
    std::vector<NautyEntry> combineEntries(std::vector<NautyEntry> entries);
    std::vector<SpasmEntry> convertToSpasm(const std::vector<NautyEntry>& entries);
};


#endif

