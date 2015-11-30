#include "graph.h"

AdjListNode::AdjListNode(int dest, int weight) {
    this->dest = dest;
    this->weight = weight;
    this->next = NULL;
}

Graph::Graph(int V, int E){
    this->V = V;
    this->E = E;
    array = (AdjList*) malloc(V * sizeof(AdjList));
    size = (int*) malloc(V*sizeof(int));
    for (int i = 0; i < V; ++i)
        array[i].head = NULL;
    for (int i = 0; i < V; ++i)
        size[i] = -1;
}

Graph::Graph(){
    
}

Graph::Graph(string filename){
    readFromFile(filename);
}


void Graph::addEdge(int src, int dest, int weight) {

    AdjListNode* newNode = new AdjListNode(dest, weight);
    newNode->next = array[src].head;
    array[src].head = newNode;
    
    AdjListNode*  newNodeUndirected = new AdjListNode(src, weight);
    newNodeUndirected->next = array[dest].head;
    array[dest].head = newNodeUndirected;
}

void Graph::addNode(int src, int weight){
    size[src] = weight;
}

void Graph::print(){
    for (int i = 0; i < V; ++i) {
        cout << "Node "<< i << " :"<< endl;
        AdjListNode *tmp = array[i].head;
        while (tmp != NULL) {
            cout << tmp->dest << " " << tmp->weight << endl;
            tmp = tmp->next;
        }
    }
}

void Graph::readFromFile(string filename){
    FILE *fp;
    int nnodes,nedges;
    fp = fopen(filename.c_str(), "r");
    fscanf(fp, "%d%d",&nnodes,&nedges);
    cout << nnodes << " " << nedges << endl ;
    this->V = nnodes;
    this->E = nedges;
    array = (AdjList*) malloc(V * sizeof(AdjList));
    size = (int*) malloc(V*sizeof(int));
    for (int i = 0; i < V; ++i)
        array[i].head = NULL;
    for (int i = 0; i < V; ++i)
        size[i] = -1;
    
    for (int i = 0; i < nedges; i++){
        int weight, ignore, src, dest;
        fscanf(fp, "%d%d%d%d", &weight, &ignore, &src, &dest);
        this->addEdge(src, dest, weight);
    }
    
    for (int i = 0; i < nnodes; i++){
        int size;
        fscanf(fp, "%d", &size);
        this->addNode(i, size);
    }
    fclose(fp);
   
}