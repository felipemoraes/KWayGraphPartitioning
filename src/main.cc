#include <iostream>
#include "../lib/graph.h"


using namespace std;

int main(){
    Graph graph(6);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 3, 1);
    graph.addEdge(0, 3, 1);
    cout << "Number of Vertices: " << graph.V << endl;
    return 1;
}