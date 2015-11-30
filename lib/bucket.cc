#include "bucket.h"


Bucket::Bucket(int k, int v, float epsilon, float max_size){
    for (int i = 0; i < k; ++i) {
        size.push_back(0);
    }
    for (int i = 0; i < v; ++i) {
        label.push_back(-1);
    }
    this->epsilon = epsilon;
    this->max_size = max_size;
    this->noparts = k;
}

Bucket::Bucket(){
    
}


void Bucket::add(int k, int node, int v){
    size[k] += v;
    label[node] = k;
}

bool Bucket::is_full(int k, int v){
    if (size[k] + v <= max_size * ( 1+ epsilon)) {
        return false;
    } else {
        return true;
    }
}


void Bucket::print(){
    ofstream foutput("output.txt");
    for (int i = 0; i < label.size(); ++i) {
        foutput << i << " " << label[i] << endl;
    }
    foutput.close();
}

bool pairCompare(const std::pair<int, int>& firstElem, const std::pair<int, int>& secondElem) {
    return firstElem.second < secondElem.second;
    
}

void Bucket::init(vector< pair <int,int> > nodes){
    int k = 0;
    sort(nodes.begin(), nodes.end(), pairCompare);
    for (int i = 0; i < nodes.size(); ++i) {
        cout << nodes[i].first << " size " << nodes[i].second << endl;
        if (!this->is_full(k, nodes[i].second)) {
            this->add(k,nodes[i].first, nodes[i].second);
        } else {
            if (k + 1 == this->noparts) {
                this->add(k,nodes[i].first, nodes[i].second);
            } else {
                k++;
                this->add(k,nodes[i].first, nodes[i].second);
            }
            
        }
    }
}

