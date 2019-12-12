#include "BinaryHeap.h"
#include <iostream>

class LeftistHeap : public BinaryHeap {
public:
    LeftistHeap() = default;

    explicit LeftistHeap(int key) {
        root = createTreeFromOneElement(key);
        numOfNodes = 1;
    }

    void meld(IHeap &other) override ;

    void clear() override ;

private:
    class LeftistNode : public Node {
    public:
        explicit LeftistNode(int key) : Node(key) {}
        int rank = 0;
    };

    Node* meldTrees(Node* root1, Node* root2) override ;

    Node* createTreeFromOneElement(int key) override ;

    static LeftistNode* cast(Node* other) {
        if (!other)
            return nullptr;
        return &dynamic_cast<LeftistNode&>(*other);
    }
};

LeftistHeap::Node* LeftistHeap::createTreeFromOneElement(int key) {
    Node* result = new LeftistNode(key);
    return result;
}

LeftistHeap::Node* LeftistHeap::meldTrees(BinaryHeap::Node* root1, BinaryHeap::Node* root2) {
    auto leftist1 = cast(root1);
    auto leftist2 = cast(root2);
    if (!root1) {
        return root2;
    }

    if (!root2) {
        return root1;
    }

    if (leftist1->value > leftist2->value) {
        std::swap(leftist1, leftist2);
    }

    leftist1->right = meldTrees(leftist1->right, leftist2);
    int rankLeft = leftist1->left ? cast(leftist1->left)->rank : 0;
    int rankRight = leftist1->right ? cast(leftist1->right)->rank : 0;
    if (rankLeft < rankRight) {
        std::swap(leftist1->left, leftist1->right);
        std::swap(rankLeft, rankRight);
    }
    leftist1->rank = rankRight + 1;
    return leftist1;
}

void LeftistHeap::meld(IHeap& other) {
    auto& casted = dynamic_cast<LeftistHeap&>(other);
    root = meldTrees(root, casted.root);
    numOfNodes += casted.numOfNodes;
    casted.root = nullptr;
    casted.numOfNodes = 0;
}

void LeftistHeap::clear() {
    *this = LeftistHeap();
}

