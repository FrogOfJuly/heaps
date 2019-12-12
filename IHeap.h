class IHeap {
public:
    virtual void insert(int) = 0;
    virtual int getMin() const = 0;
    virtual void extractMin() = 0;
    virtual void meld(IHeap&) = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;
};