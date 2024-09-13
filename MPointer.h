#ifndef MPOINTER_H
#define MPOINTER_H

#include <atomic>
#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* ptr;
    std::atomic<int>* refCount;

public:
    MPointer();
    ~MPointer();
    MPointer(const MPointer& other);
    MPointer& operator=(const MPointer& other);
    T& operator*() const;
    T* operator->() const;
    T getValue() const;
    void setValue(const T& value);
    T* operator&() const;

    static MPointer<T> New();

private:
    void release();
};

#include "MPointer.tpp"
#endif // MPOINTER_H
