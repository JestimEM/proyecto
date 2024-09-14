#ifndef MPOINTER_H
#define MPOINTER_H

#include <atomic>
#include <utility> // Para std::swap
#include <stdexcept> // For std::runtime_error

template <typename T>
class MPointer;

template <typename T>
class MPointerGC {
private:
    struct Node {
        MPointer<T>* mpointer; // Store MPointer instead of raw pointer
        Node* next;

        Node(MPointer<T>* ptr) : mpointer(ptr), next(nullptr) {}
    };

    static MPointerGC* instance;
    Node* head;
    std::atomic<int> nextId; // To generate unique IDs

    MPointerGC() : head(nullptr), nextId(1) {}

public:
    static void Initialize() {
        if (instance == nullptr) {
            instance = new MPointerGC();
        }
    }

    static void Finalize() {
        if (instance != nullptr) {
            Node* current = instance->head;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            delete instance;
            instance = nullptr;
        }
    }

    static int RegisterPointer(MPointer<T>* ptr) {
        Node* newNode = new Node(ptr);
        newNode->next = instance->head;
        instance->head = newNode;
        return instance->nextId++; // Return and increment the ID
    }

    static void DeregisterPointer(const MPointer<T>* ptr) {
        Node* current = instance->head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->mpointer == ptr) {
                if (previous == nullptr) {
                    instance->head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
};

template<typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;

template <class T>
class MPointer {
public:
    MPointer() : pointer(nullptr), refCount(new std::atomic<int>(1)), id(0) {}

    static MPointer<T> New() {
        MPointer<T> newPtr;
        newPtr.pointer = new T();
        newPtr.id = MPointerGC<T>::RegisterPointer(&newPtr); // Get ID from GC
        return newPtr;
    }

    T& operator*() const {
        if (pointer == nullptr) {
            throw std::runtime_error("Null pointer dereference");
        }
        return *pointer;
    }

    T* operator->() const {
        if (pointer == nullptr) {
            throw std::runtime_error("Null pointer dereference");
        }
        return pointer;
    }

    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            decrementRefCountAndCleanup();
            pointer = other.pointer;
            refCount = other.refCount;
            id = other.id; // Copy the ID
            ++(*refCount);
        }
        return *this;
    }

    MPointer<T>& operator=(const T& value) {
        if (pointer == nullptr) {
            throw std::runtime_error("Assignment to null MPointer");
        }
        *pointer = value;
        return *this;
    }

    // Copy constructor
    MPointer(const MPointer<T>& other)
        : pointer(other.pointer), refCount(other.refCount), id(other.id) {
        ++(*refCount);
    }

    // Move constructor
    MPointer(MPointer<T>&& other) noexcept
        : pointer(other.pointer), refCount(other.refCount), id(other.id) {
        other.pointer = nullptr;
        other.refCount = nullptr;
        other.id = 0;
    }

    // Move assignment
    MPointer<T>& operator=(MPointer<T>&& other) noexcept {
        if (this != &other) {
            decrementRefCountAndCleanup();
            pointer = other.pointer;
            refCount = other.refCount;
            id = other.id;
            other.pointer = nullptr;
            other.refCount = nullptr;
            other.id = 0;
        }
        return *this;
    }

    T& operator&() const {
        if (pointer == nullptr) {
            throw std::runtime_error("Null pointer dereference");
        }
        return *pointer;
    }

    int getId() const {
        return id;
    }

    ~MPointer() {
        decrementRefCountAndCleanup();
    }

private:
    T* pointer;
    std::atomic<int>* refCount;
    int id; // To store the unique ID

    void decrementRefCountAndCleanup() {
        if (refCount && --(*refCount) == 0) {
            delete pointer;
            delete refCount;
            MPointerGC<T>::DeregisterPointer(this);
        }
    }
};

#endif // MPOINTER_H