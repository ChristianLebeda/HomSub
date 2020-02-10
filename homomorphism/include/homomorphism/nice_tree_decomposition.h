//
//  nice_tree_decomposition.h
//  homomorphism
//
//  Created by Jonas Mortensen on 10/02/2020.
//

#ifndef NICE_TREE_DECOMPOSITIOM_H_
#define NICE_TREE_DECOMPOSITIOM_H_

#include <memory>
#include <vector>
#include "tree_decomposition.h"

enum NTDNodeType { JOIN, FORGET, INTRODUCE, LEAF};

struct NTDNode {
    NTDNodeType nodeType;
    size_t vertex;
    struct NTDNode *left;
    struct NTDNode *right;
};

class NiceTreeDecomposition
{
public:
    NiceTreeDecomposition(std::vector<NTDNode> l) : leaves_(l) {};
    std::shared_ptr<NiceTreeDecomposition> FromTd(std::shared_ptr<TreeDecomposition> td);
private:
    std::vector<NTDNode> leaves_;
};

#endif /* NICE_TREE_DECOMPOSITIOM_H_ */
