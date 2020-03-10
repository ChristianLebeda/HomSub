#include "homomorphism/join_handler.h"

std::vector<size_t> & JoinHandler::join(std::vector<size_t> &first, std::vector<size_t> &second) {
    for (size_t i = 0; i < first.size(); ++i) {
        first[i] *= second[i];
    }

    return first;
}