#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "MPointer.h"
#include <iostream>

template <typename T>
class Node {
public:
    MPointer<T> data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(MPointer<T>::New()), next(nullptr), prev(nullptr) {
        data.setValue(value);
    }
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList();
    void append(const T& value);
    void quickSort();
    void bubbleSort();
    void insertionSort();
    void printList() const;

    // Métodos de acceso para pruebas
    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }

private:
    Node<T>* partition(Node<T>* low, Node<T>* high);
    void quickSortRec(Node<T>* low, Node<T>* high);
};

#include "DoublyLinkedList.tpp"

#endif // DOUBLYLINKEDLIST_H
