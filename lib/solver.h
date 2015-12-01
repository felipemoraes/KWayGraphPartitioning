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
#include <boost/heap/fibonacci_heap.hpp>
#include <unordered_set>
using namespace std;


struct cost_function {
    int id;
    float cost;
    cost_function(int i,float cost)
    { id = i; this->cost = cost;}
    bool operator<(const cost_function& x) const {
        return cost > x.cost;
    }
};

struct compare_cost {
    bool operator()(const cost_function &n1, const cost_function &n2) const { return (n1.cost < n2.cost); }
};

typedef boost::heap::fibonacci_heap<cost_function, boost::heap::compare<compare_cost> >::handle_type handle_t;


class Solver {
public:
    Graph graph;
    Bucket bucket;
    Bucket best_bucket;
    float pm;
    float pl;
    float pb;
    float best_so_far;
    boost::heap::fibonacci_heap<cost_function, boost::heap::compare<compare_cost> > local_cost;
    std::vector<handle_t> tab_handle;
    float global_cost;
    Solver(Graph graph,Bucket bucket);
    void update_local_costs(int vertex1, int vertex2);
    void update_global_cost();
    void pass();
    int best_label(int node);
    int select_best_to_change(int node, int k);
    void save_best_bucket();
    
};



#endif
