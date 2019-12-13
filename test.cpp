#include <gtest/gtest.h>
#include "heaps.h"
#include "random"
#include <vector>
#include <iostream>

int randInt(int left, int right) {
    return rand() % (right - left + 1) + left;
}

void addHeap(std::vector<IHeap*>& heaps, IHeapFactory& factory, int key) {
    heaps.push_back(factory.createOneElementHeap(key));
}

void insert(std::vector<IHeap*>& heaps, IHeapFactory& factory, int index, int key) {
    heaps[index]->insert(key);
}

void testHeap(IHeapFactory& factory, int numOfOperations) {
    std::vector<IHeap*> heaps;
    StlHeapFactory stlFactory;
    std::vector<IHeap*> stlHeaps;

    for (int it = 0; it < numOfOperations; it++) {
        int type = randInt(1, 5);
        if (type == 1 && heaps.size() < 10) {
            int key = randInt(1, 100);
            addHeap(heaps, factory, key);
            addHeap(stlHeaps, stlFactory, key);
        } else if (type == 2) {
            if (stlHeaps.empty()) continue;
            int key = randInt(1, 100);
            int index = randInt(0, static_cast<int>(stlHeaps.size()) - 1);
            insert(heaps, factory, index, key);
            insert(stlHeaps, stlFactory, index, key);
        } else if (type == 3) {
            if (stlHeaps.empty()) continue;
            int index = randInt(0, static_cast<int>(stlHeaps.size()) - 1);
            if (stlHeaps[index]->empty()) continue;
            EXPECT_EQ(heaps[index]->getMin(), stlHeaps[index]->getMin());
        } else if (type == 4) {
            if (stlHeaps.empty()) continue;
            int index = randInt(0, static_cast<int>(stlHeaps.size()) - 1);
            if (stlHeaps[index]->empty()) continue;
            heaps[index]->extractMin();
            stlHeaps[index]->extractMin();
        } else if (type == 5) {
            if (stlHeaps.size() < 2) continue;
            int index1 = randInt(0, static_cast<int>(stlHeaps.size()) - 1);
            int index2 = randInt(0, static_cast<int>(stlHeaps.size()) - 1);
            if (index1 == index2) continue;
            stlHeaps[index1]->meld(*stlHeaps[index2]);
            heaps[index1]->meld(*heaps[index2]);
        }
    }
}

TEST(BasicTests, TestName) {
    auto factory = ScewHeapFactory();
    testHeap(factory, 10000);
}