#include "heap.h"

MinHeapNode::MinHeapNode(int v, int key) {
    this->v = v;
    this->key = key;
}

MinHeap::MinHeap(int capacity){
    this->pos = (int *)malloc(capacity * sizeof(int));
    this->size = 0;
    this->capacity = capacity;
    this->array =
    (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    
    if (left < minHeap->size &&
        minHeap->array[left]->key < minHeap->array[smallest]->key )
        smallest = left;
    
    if (right < minHeap->size &&
        minHeap->array[right]->key < minHeap->array[smallest]->key )
        smallest = right;
    
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
        
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap){
    if (isEmpty(minHeap))
        return NULL;
    
    // Store the root node
    MinHeapNode* root = minHeap->array[0];
    
    // Replace root node with last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
    
    return root;
}


void decreaseKey(MinHeap* minHeap, int v, int key){
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
    
    // Get the node and update its key value
    minHeap->array[i]->key = key;
    
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
        
        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(MinHeap *minHeap, int v){
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}
