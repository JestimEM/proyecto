#ifndef MPOINTER_TPP
#define MPOINTER_TPP

#include "MPointer.h"
#include <stdexcept>


template <typename T>
MPointer<T>::MPointer() : ptr(new T()), refCount(new std::atomic<int>(1)) {
    MPointerGC::getInstance()->registerPointer(ptr);
}


template <typename T>
MPointer<T>::~MPointer() {
    release();
}


template <typename T>
MPointer<T>::MPointer(const MPointer& other) : ptr(other.ptr), refCount(other.refCount) {
    (*refCount)++;
}


template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer& other) {
    if (this->ptr != other.ptr) {
        release();
        ptr = other.ptr;
        refCount = other.refCount;
        (*refCount)++;
    }
    return *this;
}


template <typename T>
T& MPointer<T>::operator*() const {
    if (!ptr) {
        throw std::runtime_error("Attempt to dereference a null pointer.");
    }
    return *ptr;
}


template <typename T>
T* MPointer<T>::operator->() const {
    if (!ptr) {
        throw std::runtime_error("Attempt to access members of a null pointer.");
    }
    return ptr;
}

template <typename T>
T MPointer<T>::getValue() const {
    if (!ptr) {
        throw std::runtime_error("Attempt to get value from a null pointer.");
    }
    return *ptr;
}


template <typename T>
void MPointer<T>::setValue(const T& value) {
    if (!ptr) {
        throw std::runtime_error("Attempt to set value on a null pointer.");
    }
    *ptr = value;
}


template <typename T>
T* MPointer<T>::operator&() const {
    if (!ptr) {
        throw std::runtime_error("Attempt to get address of a null pointer.");
    }
    return ptr;
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    return MPointer<T>();
}

template <typename T>
void MPointer<T>::release() {
    if (--(*refCount) == 0) {
        MPointerGC::getInstance()->unregisterPointer(ptr);
        delete ptr;
        delete refCount;
    }
}

#endif // MPOINTER_TPP
