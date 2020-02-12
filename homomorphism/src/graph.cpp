#include <sstream>
#include <bitset>
#include "homomorphism/graph.h"
#include "homomorphism/graph6helper.h"

std::string Graph::toGraph6() {
    std::ostringstream str;
    str << "G" << Graph6helper::N(vertCount());
    std::bitset<6> buffer;
    int idx = 6;
    for (size_t u = 1; u < vertCount(); u++)
    {
        for (size_t v = 0; v < u; v++)
        {
            buffer.set(--idx, edgeExist(u, v));
            if (!idx) {
                str << Graph6helper::R(buffer.to_ulong());
                idx = 6;
            }
        }
    }

    if (idx != 6) {
        while (idx) {
            buffer.set(--idx, false);
        }
        str << Graph6helper::R(buffer.to_ulong());
    }

    return str.str();
}

std::string Graph::toString()
{
    std::ostringstream out;
    out << "Graph of size (" << vertCount() << "," << edgeCount() << ")";
    return out.str();
}

void Graph::prettyPrint(std::ostream& os)
{
    os << "Graph with " << vertCount() << " vertices and " << edgeCount() << " edges:\n";
    for (size_t u = 0; u < vertCount(); u++) {
        os << "[ ";
        for (size_t v = 0; v < vertCount(); v++) {
            os << edgeExist(u, v) << " ";
        }
        os << "]" << std::endl;
    }
}
