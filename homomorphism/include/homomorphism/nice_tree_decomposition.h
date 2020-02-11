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
    std::shared_ptr<NTDNode> left;
    std::shared_ptr<NTDNode> right;
};

class NiceTreeDecomposition
{
public:
    NiceTreeDecomposition(std::vector<NTDNode> l) : leaves_(l) {};
    std::shared_ptr<NiceTreeDecomposition> FromTd(std::shared_ptr<TreeDecomposition> td);
private:
    std::vector<NTDNode> leaves_;
    std::shared_ptr<NTDNode> convertNode(size_t from, size_t node, std::shared_ptr<TreeDecomposition> td);
    static std::shared_ptr<NTDNode> createLeaf();
    static std::shared_ptr<NTDNode> createIntroduce(std::shared_ptr<NTDNode> child, size_t vert);
};

#endif /* NICE_TREE_DECOMPOSITIOM_H_ */
