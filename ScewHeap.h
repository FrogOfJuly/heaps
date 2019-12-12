#include "BinaryHeap.h"
#include <iostream>

class ScewHeap : public BinaryHeap {
public:
    void meld(IHeap &other) override ;

    void clear() override ;

private:
    Node* meldTrees(Node* root1, Node* root2) override ;
};

void ScewHeap::meld(class IHeap & other) {
    auto& casted = dynamic_cast<ScewHeap&>(other);
    root = meldTrees(root, casted.root);
    numOfNodes += casted.numOfNodes;
    casted.root = nullptr;
    casted.numOfNodes = 0;
}

ScewHeap::Node* ScewHeap::meldTrees(BinaryHeap::Node *root1, BinaryHeap::Node *root2) {
    if (!root1)
        return root2;

    if (!root2)
        return root1;

    if (root1->value > root2->value)
        std::swap(root1, root2);

    root1->right = meldTrees(root1->right, root2);
    std::swap(root1->left, root1->right);

    return root1;
}

void ScewHeap::clear() {
    *this = ScewHeap();
}