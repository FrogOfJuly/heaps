#include "IHeap.h"

#pragma once

class BinaryHeap : public IHeap {
protected:
    class Node {
    public:
        explicit Node(int key) : value(key) {}

        Node(const Node& other) {
            *this = other;
        }

        Node& operator=(const Node& other) {
            if (this == &other) {
                return *this;
            }
            delete left;
            delete right;
            left = other.left;
            right = other.right;
            value = other.value;

            return *this;
        }

        virtual ~Node() {
            delete left;
            delete right;
        }

        Node* left = nullptr;
        Node* right = nullptr;
        int value = 0;
    };

    void copy(const BinaryHeap &other) {
        root = other.root;
        numOfNodes = other.numOfNodes;
    }

    virtual Node* meldTrees(Node* root1, Node* root2) = 0;

    virtual Node* createTreeFromOneElement(int key) ;

    Node* root = nullptr;

    int numOfNodes = 0;
public:
    BinaryHeap() = default;

    BinaryHeap(const BinaryHeap& other) {
        copy(other);
    }

    BinaryHeap& operator=(const BinaryHeap& other) {
        if (this == &other) {
            return *this;
        }
        delete root;
        copy(other);
        return *this;
    }

    ~BinaryHeap() {
        delete root;
    }

    int getMin() const override ;

    void extractMin() override ;

    void insert(int key) override ;

    int size() const override ;

};

int BinaryHeap::getMin() const {
    return root ? root->value : -1;
}

void BinaryHeap::extractMin() {
    if (!root) {
        return;
    }
    auto left = root->left;
    auto right = root->right;
    root->left = nullptr;
    root->right = nullptr;
    delete root;
    root = meldTrees(left, right);
    numOfNodes--;
}

void BinaryHeap::insert(int key) {
    auto toAdd = createTreeFromOneElement(key);
    root = meldTrees(root, toAdd);
    numOfNodes++;
}

int BinaryHeap::size() const {
    return numOfNodes;
}

BinaryHeap::Node* BinaryHeap::createTreeFromOneElement(int key) {
    Node* result = new Node(key);
    return result;
}