#include <iostream>
#include <vector>
#include "../lib/graph.h"
#include "../lib/bucket.h"
#include "../lib/solver.h"

using namespace std;




int main(int argc, char** argv){
    string infile = "/Users/felipemoraes/KWayGraphPartitioning/graph_2.file";
    //string infile = "/Users/felipemoraes/KWayGraphPartitioning/src/input.txt";
    int noparts = 2;

    if (argc < 2) {
        cout << "Usage: ./kpartition --infile [input_file] --noparts" << endl;
        return 1;
    }
    for(int i=0; i<argc; i++){
        string param(argv[i]);
        if(param == "--infile" || param == "-i"){
            i++;
            infile = string(argv[i]);
        }
        if(param == "--noparts" || param == "-k"){
            i++;
            noparts = atoi(argv[i]);
        }
    }
    Graph graph(infile);
    vector< pair<int, int> > nodes;
    //cout << "Number of Vertices: " << graph.V << endl;
    //graph.print();
    float sum = 0;
    for (int i = 0; i < graph.V; ++i) {
        nodes.push_back(make_pair(i,graph.size[i]));
        sum += graph.size[i];
    }
    Bucket bucket(noparts, graph.V, 0.1, sum/noparts);
    bucket.init(nodes);
    Solver solver(graph,bucket);
    int num_iterations = 0;
    while (solver.best_so_far > 0 && num_iterations < graph.E) {
        solver.pass();
        num_iterations++;
        cout << "Iteration : " << num_iterations << " Global cost: " << solver.global_cost << endl;
    }
    solver.best_bucket.print();
    cout << solver.best_so_far << endl;
    
    return 1;
}
