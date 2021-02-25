#pragma once
//
// Created by Varick Erickson 2/3/2021.
//

#ifndef CHUNKLIST_CHUNKLIST_H
#define CHUNKLIST_CHUNKLIST_H

#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

// These error classes are done. No modifications are required.
// See ChunkList_demo.cpp for an example of how they are used.
class InvalidArrayLength {
public:
    string Msg() {
        return "Invalid array length used for constructor.";
    }
};

class IndexOutOfBounds {
public:
    string Msg() {
        return "Index is out of bounds";
    }
};

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

class EmptyList {
public:
    string Msg() {
        return "List is empty";
    }
};

// Put your pre/post conditions here.


template <class T>
struct Node {
public:
    Node* next;
    int len;
    T values[ARRAY_SIZE];
};


template<class T>
class ChunkList {
public:
    // Constructors
    ChunkList();
    ChunkList(T arr[], int arrLen);

    // Deconstructor
    ~ChunkList();

    // Add/remove elements
    void Append(T value);
    void Remove(T value);

    // Stuff to find out about the ChunkList
    int GetLength();
    double LoadFactor();
    bool Contains(T value);

    // Accessing elements
    T GetIndex(int i);
    void ResetIterator();
    T GetNextItem();

    bool IsEmpty();
private:

   

    Node<T>* head;
    Node<T>* tail;

    // iterator
    Node<T>* iterNode;     // What node are were currently on?
    int arrPos;         // Within the node, what element are we looking at?

    int listLen;        // Total elements
    int numChunks;      // Total chunks/nodes
};

#endif //CHUNKLIST_CHUNKLIST_H

