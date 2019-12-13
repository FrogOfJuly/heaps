#include <iostream>
#include "heaps.h"

int main() {
    IHeap* heap1 = new ScewHeap();
    for (int i = 3; i < 8; i++) heap1->insert(i);
    IHeap* heap2 = new ScewHeap();
    for (int i = 0; i < 5; i++) heap2->insert(i);
    std::cout << heap1->size() << ' ' << heap2->size() << std::endl;
    heap1->meld(*heap2);
    std::cout << heap1->size() << ' ' << heap2->size() << std::endl << heap1->empty() << ' ' << heap2->empty() << std::endl;
    while (heap1->size() > 0) {
        std::cout << heap1->getMin() << ' ' << heap1->size() << std::endl;
        heap1->extractMin();
    }
    return 0;
}
