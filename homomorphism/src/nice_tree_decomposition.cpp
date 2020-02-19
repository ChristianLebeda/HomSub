#include "homomorphism/nice_tree_decomposition.h"

#include <iostream>
#include <stdio.h>

std::shared_ptr<NiceTreeDecomposition> NiceTreeDecomposition::FromTd(std::shared_ptr<TreeDecomposition> td)
{
    return std::make_shared<NiceTreeDecomposition>(convertNode(-1, 0, td), td->getGraph(), td->getWidth());
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::convertNode(size_t from, size_t node, std::shared_ptr<TreeDecomposition> td)
{
    std::unordered_set<size_t> children = td->getGraph()->getNeighbourhood(node);
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
        return connectToChild(childNode, td->getBag(child), td->getBag(node));
    } else {
        std::unordered_set<size_t>::iterator it = children.begin();
        size_t firstChild = *it;
        it++;
        
        std::shared_ptr<NTDNode> currentChildNode = convertNode(node, firstChild, td);
        
        std::shared_ptr<NTDNode> currentNode = connectToChild(currentChildNode, td->getBag(firstChild), td->getBag(node));
        
        for(; it != children.end(); it++) {
            currentChildNode = convertNode(node, *it, td);
            
            currentNode = createJoin(currentNode, connectToChild(currentChildNode, td->getBag(*it), td->getBag(node)));
        }
        
        return currentNode;
    }
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::connectToChild(std::shared_ptr<NTDNode> childNode, std::unordered_set<size_t> childBag, std::unordered_set<size_t> parentBag)
{
    std::shared_ptr<NTDNode> current = childNode;
    
    //Create forget node for each missing vert in parent
    for(size_t v : childBag) {
        if(parentBag.find(v) == parentBag.end()) {
            
            current = createForget(current, v);
        }
    }
    
    //Create introduce node for each missing vert in child
    for(size_t v : parentBag) {
        if(childBag.find(v) == childBag.end()) {
            current = createIntroduce(current, v);
        }
    }
    
    return current;
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
    introduce->nodeType = NTDNodeType::INTRODUCE;
    introduce->left = child;
    introduce->right = child;
    introduce->vertex = vert;
    return introduce;
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::createForget(std::shared_ptr<NTDNode> child, size_t vert)
{
    std::shared_ptr<NTDNode> forget = std::make_shared<NTDNode>();
    forget->nodeType = NTDNodeType::FORGET;
    forget->left = child;
    forget->right = child;
    forget->vertex = vert;
    return forget;
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::createJoin(std::shared_ptr<NTDNode> leftChild, std::shared_ptr<NTDNode> rightChild)
{
    std::shared_ptr<NTDNode> join = std::make_shared<NTDNode>();
    join->nodeType = NTDNodeType::JOIN;
    join->left = leftChild;
    join->right = rightChild;
    join->vertex = -1;
    return join;
}

void NiceTreeDecomposition::print(std::shared_ptr<NTDNode> node)
{
    switch (node->nodeType) {
        case NTDNodeType::INTRODUCE:
            std::cout << "Introduce:" << node->vertex << std::endl;
            print(node->left);
            break;
        case NTDNodeType::FORGET:
            std::cout << "Forget:" << node->vertex << std::endl;
            print(node->left);
            break;
        case NTDNodeType::JOIN:
            std::cout << "Join" << std::endl;
            print(node->left);
            print(node->right);
            break;
        case NTDNodeType::LEAF:
            std::cout << "Leaf" << std::endl;
            break;
        default:
            break;
    }
    
}

std::shared_ptr<NTDNode> NiceTreeDecomposition::getRoot()
{
    return root_;
}

size_t NiceTreeDecomposition::getWidth()
{
    return width_;
}
