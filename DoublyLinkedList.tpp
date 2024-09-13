#include "DoublyLinkedList.h"

// Constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Metodo para añadir un nodo al final de la lista
template <typename T>
void DoublyLinkedList<T>::append(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Metodo para imprimir la lista
template <typename T>
void DoublyLinkedList<T>::printList() const {
    Node<T>* temp = head;
    if (temp) {
        std::cout << temp->data.getValue();
        temp = temp->next;
    }
    while (temp) {
        std::cout << " " << temp->data.getValue();
        temp = temp->next;
    }
    std::cout << std::endl;
}




// Algoritmo Bubble Sort
template <typename T>
void DoublyLinkedList<T>::bubbleSort() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        Node<T>* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->data.getValue() > current->next->data.getValue()) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Algoritmo Insertion Sort
template <typename T>
void DoublyLinkedList<T>::insertionSort() {
    if (!head) return;

    Node<T>* sorted = nullptr;
    Node<T>* current = head;

    while (current != nullptr) {
        Node<T>* next = current->next;
        if (sorted == nullptr || sorted->data.getValue() >= current->data.getValue()) {
            current->next = sorted;
            current->prev = nullptr;
            if (sorted != nullptr) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            Node<T>* temp = sorted;
            while (temp->next != nullptr && temp->next->data.getValue() < current->data.getValue()) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }
        current = next;
    }
    head = sorted;
    if (sorted != nullptr) {
        Node<T>* last = sorted;
        while (last->next != nullptr) {
            last = last->next;
        }
        tail = last;
    }
}

// Algoritmo Quick Sort - Función de partición
template <typename T>
Node<T>* DoublyLinkedList<T>::partition(Node<T>* low, Node<T>* high) {
    T pivot = high->data.getValue();
    Node<T>* i = low->prev;
    for (Node<T>* j = low; j != high; j = j->next) {
        if (j->data.getValue() < pivot) {
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
}

// Algoritmo Quick Sort Recursivo
template <typename T>
void DoublyLinkedList<T>::quickSortRec(Node<T>* low, Node<T>* high) {
    if (high != nullptr && low != high && low != high->next) {
        Node<T>* pi = partition(low, high);
        quickSortRec(low, pi->prev);
        quickSortRec(pi->next, high);
    }
}

// Metodo Quick Sort
template <typename T>
void DoublyLinkedList<T>::quickSort() {
    Node<T>* high = head;
    while (high->next != nullptr) {
        high = high->next;
    }
    quickSortRec(head, high);
}
