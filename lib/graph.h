#ifndef GRAPH
#define GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>

using namespace std;

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
    int V,E;
    AdjList* array;
    Graph(int V, int E);
    Graph(string filename);
    Graph();
    void addEdge(int src, int dest, int weight);
    void addNode(int src, int size);
    void print();
    int* size;
    void readFromFile(string filename);
};

#endif