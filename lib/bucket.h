#ifndef BUCKET
#define BUCKET


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <limits.h>
#include <vector>

using namespace std;


class Bucket {
public:
    vector<int> size;
    vector<int> label;
    float epsilon;
    int noparts;
    float max_size;
    Bucket(int k, int v, float epsilon, float max_size);
    Bucket();
    void add(int k, int node, int v);
    bool is_full(int k, int v);
    void print();
    void init(vector< pair <int,int> > nodes);
};



#endif
