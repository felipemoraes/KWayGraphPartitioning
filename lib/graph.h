#ifndef GRAPH
#define GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


class AdjListNode {
public:
    int dest;
    int weight;
    AdjListNode* next;
    AdjListNode(int dest, int weight);
};

class AdjList {
public:
    AdjListNode *head;
};

class Graph {
public:
    int V;
    AdjList* array;
    Graph(int V);
    void addEdge(int src, int dest, int weight);
};

#endif