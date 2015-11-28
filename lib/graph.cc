#include "graph.h"

AdjListNode::AdjListNode(int dest, int weight) {
    next = (AdjListNode*) malloc(sizeof(AdjListNode));
    next->dest = dest;
    next->weight = weight;
    next->next = NULL;
}

Graph::Graph(int V){
    this->V = V;
    array = (AdjList*) malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        array[i].head = NULL;
}

void Graph::addEdge(int src, int dest, int weight) {

    AdjListNode* newNode = new AdjListNode(dest, weight);
    newNode->next = array[src].head;
    array[src].head = newNode;
    
    AdjListNode*  newNodeUndirected = new AdjListNode(src, weight);
    newNodeUndirected->next = array[dest].head;
    array[dest].head = newNode;
}