#include <set>
#include <algorithm>
#include "IHeap.h"

class StlHeap : public IHeap {
public:
    StlHeap() = default;

    explicit StlHeap(int key) {
        heap.insert(key);
    }

    void insert(int) override ;
    int getMin() const override ;
    void extractMin() override ;
    void meld(IHeap&) override ;
    void clear() override ;
    int size() const override ;
private:
    std::multiset<int> heap;
};

void StlHeap::insert(int key) {
    heap.insert(key);
}

int StlHeap::getMin() const {
    return *heap.begin();
}

void StlHeap::extractMin() {
    heap.erase(heap.begin());
}

int StlHeap::size() const {
    return heap.size();
}

void StlHeap::clear() {
    *this = StlHeap();
}

void StlHeap::meld(IHeap& other) {
    auto other_casted = dynamic_cast<StlHeap&>(other);
    heap.insert(other_casted.heap.begin(), other_casted.heap.end());
    other.clear();
}

