#include "IHeap.h"
#include "LeftistHeap.h"
#include "ScewHeap.h"

class IHeapFactory {
public:
    virtual IHeap* createEmptyHeap() = 0;

    virtual IHeap* createOneElementHeap(int) = 0;
};

class LeftistHeapFactory : public IHeapFactory{
    IHeap* createEmptyHeap() override {
        return new LeftistHeap();
    }

    IHeap* createOneElementHeap(int key) override {
        return new LeftistHeap(key);
    }
};

class ScewHeapFactory : public IHeapFactory{
    IHeap* createEmptyHeap() override {
        return new ScewHeap();
    }

    IHeap* createOneElementHeap(int key) override {
        auto* result = new ScewHeap();
        result->insert(key);
        return result;
    }
};


class StlHeapFactory : public IHeapFactory{
    IHeap* createEmptyHeap() override {
        return new StlHeap();
    }

    IHeap* createOneElementHeap(int key) override {
        return new StlHeap(key);
    }
};