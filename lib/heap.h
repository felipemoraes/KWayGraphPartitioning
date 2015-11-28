#ifndef HEAP
#define HEAP


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


class MinHeapNode {
public:
    int  v;
    int key;
    MinHeapNode(int v, int key);
};


class MinHeap {
public:
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    MinHeapNode **array;
    MinHeap(int capacity);
};

#endif