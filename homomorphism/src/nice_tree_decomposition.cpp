//
//  nice_tree_decomposition.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 10/02/2020.
//

#include <stdio.h>
#include "homomorphism/nice_tree_decomposition.h"

std::shared_ptr<NiceTreeDecomposition> NiceTreeDecomposition::FromTd(std::shared_ptr<TreeDecomposition> td)
{
    return nullptr;
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::convertNode(size_t from, size_t node, std::shared_ptr<TreeDecomposition> td)
{
    std::set<size_t> children = td->getGraph()->getNeighbourhood(node);
    children.erase(from);
    
    if(children.size() == 0) {
        std::shared_ptr<NTDNode> current = createLeaf();
        
        //Introduce verts of bag
        for( size_t v : td->getBag(node)) {
            current = createIntroduce(current, v);
        }
        
        return current;
    } else if (children.size() == 1) {
        size_t child = *children.begin();
        std::shared_ptr<NTDNode> childNode = convertNode(node, child, td);
        
        //CALL connectToChild
    } else {
        std::set<size_t>::iterator it = children.begin();
        size_t firstChild = *it;
        it++;
        
        std::shared_ptr<NTDNode> currentChildNode = convertNode(node, firstChild, td);
        
        //currentNode ConnectToShild
        
        for(; it != children.end(); it++) {
            currentChildNode = convertNode(node, *it, td);
            
            //Currnt node combine
        }
        
    }
    
    
    
    return nullptr;
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::createLeaf()
{
    std::shared_ptr<NTDNode> leaf = std::make_shared<NTDNode>();
    leaf->nodeType = LEAF;
    return leaf;
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::createIntroduce(std::shared_ptr<NTDNode> child, size_t vert)
{
    std::shared_ptr<NTDNode> introduce = std::make_shared<NTDNode>();
    introduce->nodeType = INTRODUCE;
    introduce->left = child;
    introduce->right = child;
    introduce->vertex = vert;
    return introduce;
}
