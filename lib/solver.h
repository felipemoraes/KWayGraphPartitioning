#ifndef SOLVER
#define SOLVER


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include "graph.h"
#include "bucket.h"
#include <random>

using namespace std;


class Solver {
public:
    Graph graph;
    Bucket bucket;
    Bucket best_bucket;
    float pm;
    float pl;
    float pb;
    float best_so_far;
    vector< pair<int,float> > local_cost;
    float global_cost;
    Solver(Graph graph,Bucket bucket);
    void update_costs();
    void pass();
    int best_label(int node);
    int select_best_to_change(int node, int k);
    void save_best_bucket();
    
};



#endif
