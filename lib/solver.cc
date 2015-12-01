#include "solver.h"


Solver::Solver(Graph graph,Bucket bucket){
    this->graph = graph;
    this->bucket = bucket;
    this->pm = 1.00;
    this->pl = 0.95;
    this->pb = 1.00;
    global_cost = 0;
   
    for (int i = 0; i < graph.V; ++i) {
        float cost = 0;
        float size_neighbords = 0;
        int label = bucket.label[i];
        AdjListNode *neighbor = graph.array[i].head;
        while (neighbor != NULL ) {
            if (bucket.label[neighbor->dest] != label) {
                cost += neighbor->weight;
                global_cost += neighbor->weight;
            }
            size_neighbords += neighbor->weight;
            neighbor = neighbor->next;
        }
        auto t = local_cost.push(cost_function(i, cost/size_neighbords));
        tab_handle.push_back(t);

    }
    cout << "Inicio "<< local_cost.size() << endl;
    best_so_far = global_cost;
    this->best_bucket = bucket;
    //bucket.print();
    //cout << global_cost << endl;
    //cout << endl << endl;
}

bool pairCompareFloat(const std::pair<int, float>& firstElem, const std::pair<int, float>& secondElem) {
    return firstElem.second > secondElem.second;
    
}

int Solver::best_label(int node){
    vector< pair < int, float >> labels;
    for (int i = 0; i < bucket.noparts ; ++i ) {
        float local_cost = 0;
        float sum = 0;
        AdjListNode *neighbor = graph.array[node].head;
        while (neighbor != NULL ) {
            if (bucket.label[neighbor->dest] != i) {
                local_cost += neighbor->weight;
            }
            sum += neighbor->weight;
            neighbor = neighbor->next;
        }
        labels.push_back(make_pair(i, local_cost/sum));
    }
    sort(labels.rbegin(), labels.rend(), pairCompareFloat);
    return labels.front().first;
}

int Solver::select_best_to_change(int node, int k){
    
    vector< pair<int, float> > sizes;
    for (int i = 0; i < bucket.label.size(); ++i) {
        if (bucket.label[i] == k) {
            sizes.push_back(make_pair(i, abs(graph.size[i]-graph.size[node])));
        }
    }
    sort(sizes.rbegin(), sizes.rend(), pairCompareFloat);
    return sizes.front().first;
}


void Solver::pass(){

    
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::uniform_real_distribution<> dis_label(0, bucket.noparts);
    vector<cost_function> k_vertices;
    for (int i = 0; i < bucket.noparts; ++i) {
        k_vertices.push_back(local_cost.top());
        local_cost.pop();
    }
    for (auto it : k_vertices) {
        tab_handle[it.id] = local_cost.push(it);
    }
     for (auto it : k_vertices) {
        int select_vertex = it.id;
        int new_label = bucket.label[select_vertex];
        int old_label = new_label;
        int best_change = old_label;
        // disturbing
        
        if (dis(gen) < pl) {
            new_label = best_label(select_vertex);
            //maintain balance
            best_change = select_best_to_change(select_vertex, new_label);
            bucket.label[select_vertex] = new_label;
        } else {
            new_label = (int) dis_label(gen);
            best_change = select_best_to_change(select_vertex, new_label);
            bucket.label[select_vertex] = new_label;
            
        }
        
        //AdjListNode *tmp = graph.array[select_vertex].head;

        bucket.label[best_change] = old_label;
        update_local_costs(select_vertex,best_change);
    }
    
    update_global_cost();
    if (best_so_far > global_cost) {
        best_so_far = global_cost;
    }
    //cout << global_cost << endl;
   // bucket.print();
}

void Solver::update_local_costs(int vertex1, int vertex2){
    unordered_set<int> nodes_to_update;
    AdjListNode *tmp = graph.array[vertex1].head;
    float cost = 0;
    float size_neighbords = 0;
    int label = bucket.label[vertex1];
    while (tmp != NULL) {
        if (bucket.label[tmp->dest] != label) {
            cost += tmp->weight;
        }
        nodes_to_update.insert(tmp->dest);
        size_neighbords += tmp->weight;
        tmp = tmp->next;
    }
    tab_handle[vertex1] = local_cost.push(cost_function(vertex1, cost/size_neighbords));
    cost = 0;
    size_neighbords = 0;
    label = bucket.label[vertex2];
    tmp = graph.array[vertex2].head;
    while (tmp != NULL) {
        if (bucket.label[tmp->dest] != label) {
            cost += tmp->weight;
        }
        nodes_to_update.insert(tmp->dest);
        size_neighbords += tmp->weight;
        tmp = tmp->next;
    }
    local_cost.update(tab_handle[vertex2],cost_function(vertex2, cost/size_neighbords));
    for (auto i : nodes_to_update) {
        float cost = 0;
        float size_neighbords = 0;
        int label = bucket.label[i];
        AdjListNode *neighbor = graph.array[i].head;
        while (neighbor != NULL ) {
            if (bucket.label[neighbor->dest] != label) {
                cost += neighbor->weight;
                global_cost += neighbor->weight;
            }
            size_neighbords += neighbor->weight;
            neighbor = neighbor->next;
        }
        local_cost.update(tab_handle[i],cost_function(i, cost/size_neighbords));
    }
    
}
void Solver::update_global_cost(){
    global_cost = 0;
    for (int i = 0; i < graph.V; ++i) {
        int label = bucket.label[i];
        AdjListNode *neighbor = graph.array[i].head;
        while (neighbor != NULL ) {
            if (bucket.label[neighbor->dest] != label) {
                global_cost += neighbor->weight;
            }
            neighbor = neighbor->next;
        }
        
    }
    
}

void Solver::save_best_bucket(){
    best_bucket = bucket;
}
