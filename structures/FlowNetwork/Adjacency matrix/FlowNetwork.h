#pragma once

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <iostream>
#include "Matrix.h"

template<class T, class C = int>
class FlowNetwork{

    // node 0 is source
    // last node (size()-1) is sink
    // nodes in between are inner nodes (from 1 to size()-2)

    Matrix<C> capacity;
    Matrix<C> flow;
    std::vector<T> data;

public:
    FlowNetwork();
    FlowNetwork(std::size_t inner_nodes_size, const T& value = T());
    FlowNetwork(const T& source_v, std::initializer_list<T> inner_nodes_v, const T& sink_v);
    FlowNetwork(const FlowNetwork<T,C>& other);
    FlowNetwork<T,C>& operator=(const FlowNetwork<T,C>& other);

    std::size_t size();
    bool empty();
    void clear();

    std::size_t sourceNode();
    std::size_t sinkNode();

    T getData(std::size_t node);
    T& at(std::size_t node);
    void setData(std::size_t node, const T& value);
    bool existsDirectedEdge(std::size_t node1, std::size_t node2);

    std::vector<std::pair<std::size_t,C> > getNeighbours(std::size_t node);

    void addNode(const T& value);
    void addDirectedEdge(std::size_t node1, std::size_t node2, const C& capacity);

    void removeNode(std::size_t node);
    void removeDirectedEdge(std::size_t node1, std::size_t node2);

    C getCapacity(std::size_t node1, std::size_t node2);
    void setCapacity(std::size_t node1, std::size_t node2, const C& capacity);

    C getFlow(std::size_t node1, std::size_t node2);
    void clearFlow();


    C EdmondsKarp();
    C Dinic();


    bool operator==(const FlowNetwork<T,C>& other);
    bool operator!=(const FlowNetwork<T,C>& other);

    void printCapacity();
    void printValues();
    void printFlow();

private:
    void DinicLevelGraphBFS(std::size_t* level);
    bool DinicDFS(std::size_t node, std::size_t* level, std::size_t* parent);
};


template<class T, class C>
FlowNetwork<T,C>::FlowNetwork() : capacity(2,2, C()), flow(2,2, C()), data(2, T()) {}
template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(std::size_t inner_nodes_size, const T& value)
    : capacity(2+inner_nodes_size, 2+inner_nodes_size, C()),
      flow(2+inner_nodes_size, 2+inner_nodes_size, C()),
      data(2+inner_nodes_size, value) {}
template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(const T& source_v, std::initializer_list<T> inner_nodes_v, const T& sink_v)
    : capacity(2+inner_nodes_v.size(), 2+inner_nodes_v.size(), C()),
      flow(2+inner_nodes_v.size(), 2+inner_nodes_v.size(), C()) {
    // source
    data.push_back(source_v);
    // inner nodes
    for(auto it = inner_nodes_v.begin(); it != inner_nodes_v.end(); it++)
        data.push_back(*it);
    // sink
    data.push_back(sink_v);
}
template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(const FlowNetwork<T,C>& other){
    data = other.data;
    capacity = other.capacity;
    flow = other.flow;
}
template<class T, class C>
FlowNetwork<T,C>& FlowNetwork<T,C>::operator=(const FlowNetwork<T,C>& other){
    if(this != &other){
        data = other.data;
        capacity = other.capacity;
        flow = other.flow;
    }
    return *this;
}


template<class T, class C>
std::size_t FlowNetwork<T,C>::size(){
    // source, sink and inner nodes
    return data.size();
}
template<class T, class C>
bool FlowNetwork<T,C>::empty(){
    // does graph contains only source and sink (no inner nodes) and has no edges
    return (size() == 2 && capacity.at(0,1) == C());
}
template<class T, class C>
void FlowNetwork<T,C>::clear(){
    // remove inner nodes
    data.erase(data.begin()+1, data.end()-1);
    capacity.resize(2,2);
    capacity.fill(C());
    flow.resize(2,2);
    flow.fill(C());
}

template<class T, class C>
std::size_t FlowNetwork<T,C>::sourceNode(){
    return 0;
}
template<class T, class C>
std::size_t FlowNetwork<T,C>::sinkNode(){
    return size()-1;
}


template<class T, class C>
T FlowNetwork<T,C>::getData(std::size_t node){
    return data.at(node);
}
template<class T, class C>
T& FlowNetwork<T,C>::at(std::size_t node){
    return data.at(node);
}
template<class T, class C>
void FlowNetwork<T,C>::setData(std::size_t node, const T& value){
    data.at(node) = value;
}
template<class T, class C>
bool FlowNetwork<T,C>::existsDirectedEdge(std::size_t node1, std::size_t node2){
    return (capacity.at(node1, node2) != C());
}

template<class T, class C>
std::vector<std::pair<std::size_t,C> > FlowNetwork<T,C>::getNeighbours(std::size_t node){
    std::vector<std::pair<std::size_t,C> > ns;
    for(std::size_t i=0; i<size(); i++)
        if(capacity.at(node,i) != C())
            ns.push_back(std::make_pair(i, capacity.at(node,i)));
    return ns;
}


template<class T, class C>
void FlowNetwork<T,C>::addNode(const T& value){
    data.insert(data.end()-1, value);
    capacity.insertRow(size()-1);
    capacity.insertColumn(size()-1);
    flow.insertRow(size()-1);
    flow.insertColumn(size()-1);
}
template<class T, class C>
void FlowNetwork<T,C>::addDirectedEdge(std::size_t node1, std::size_t node2, const C& capacity){
    if(node1 != node2 && node1 != sinkNode() && node2 != sourceNode()){
        if(!existsDirectedEdge(node1, node2))
            this->capacity.at(node1, node2) = capacity;
    }
}


template<class T, class C>
void FlowNetwork<T,C>::removeNode(std::size_t node){
    if(node != sourceNode() && node != sinkNode()){
        data.erase(data.begin() + node);

        capacity.removeRow(node);
        capacity.removeColumn(node);
        flow.removeRow(node);
        flow.removeColumn(node);
    }
}
template<class T, class C>
void FlowNetwork<T,C>::removeDirectedEdge(std::size_t node1, std::size_t node2){
    capacity.at(node1, node2) = C();
}


template<class T, class C>
C FlowNetwork<T,C>::getCapacity(std::size_t node1, std::size_t node2){
    return capacity.at(node1,node2);
}
template<class T, class C>
void FlowNetwork<T,C>::setCapacity(std::size_t node1, std::size_t node2, const C& capacity){
    this->capacity.at(node1, node2) = capacity;
}

template<class T, class C>
C FlowNetwork<T,C>::getFlow(std::size_t node1, std::size_t node2){
    return flow.at(node1,node2);
}
template<class T, class C>
void FlowNetwork<T,C>::clearFlow(){
    flow.fill(C());
}


template<class T, class C>
C FlowNetwork<T,C>::EdmondsKarp(){
    // max flow
    // capacities must be non-negative

    C max_flow = C();

    clearFlow();

    bool* visited = new bool[size()];
    std::size_t* parent = new std::size_t[size()];

    bool path_found = true;
    while(path_found){
        path_found = false;
        for(std::size_t i=0; i<size(); i++){
            visited[i] = false;
            parent[i] = -1;
        }

        // find augmenting path using BFS
        std::queue<std::size_t> q;
        q.push(sourceNode());
        visited[sourceNode()] = true;
        while(!q.empty()){
            std::size_t v = q.front();
            q.pop();

            if(v == sinkNode()){
                path_found = true;
                break;
            }

            for(std::size_t i=0; i<size(); i++)
                if(capacity.at(v,i) - flow.at(v,i) > C() && visited[i] == false){
                    visited[i] = true;
                    parent[i] = v;
                    q.push(i);
                }
        }

        if(path_found){
            // get min residual capacity
            std::size_t u = sinkNode();
            C min_res_cap = capacity.at(parent[u], u) - flow.at(parent[u],u);
            u = parent[u];
            while(parent[u] != -1){
                if(capacity.at(parent[u],u) - flow.at(parent[u],u) < min_res_cap)
                    min_res_cap = capacity.at(parent[u],u) - flow.at(parent[u],u);
                u = parent[u];
            }
            max_flow += min_res_cap;

            // change flow
            u = sinkNode();
            while(parent[u] != -1){
                flow.at(parent[u], u) += min_res_cap;
                flow.at(u, parent[u]) -= min_res_cap;
                u = parent[u];
            }
        }
    }
    delete[] visited;
    delete[] parent;

    return max_flow;
}

template<class T, class C>
C FlowNetwork<T,C>::Dinic(){
    // max flow
    // capacities must be non-negative

    C max_flow = C();

    clearFlow();

    std::size_t* level = new std::size_t[size()];
    std::size_t* parent = new std::size_t[size()];

    while(true){
        // create level graph
        for(std::size_t i=0; i<size(); i++)
            level[i] = -1;
        DinicLevelGraphBFS(level);

        if(level[sinkNode()] == -1)
            break;

        bool path_found;
        do{
            for(std::size_t i=0; i<size(); i++)
                parent[i] = -1;

            // run DFS
            path_found = DinicDFS(sourceNode(), level, parent);

            if(path_found){
                // get min residual capacity
                std::size_t u = sinkNode();
                C min_res_cap = capacity.at(parent[u], u) - flow.at(parent[u],u);
                u = parent[u];
                while(parent[u] != -1){
                    if(capacity.at(parent[u],u) - flow.at(parent[u],u) < min_res_cap)
                        min_res_cap = capacity.at(parent[u],u) - flow.at(parent[u],u);
                    u = parent[u];
                }
                max_flow += min_res_cap;

                // change flow
                u = sinkNode();
                while(parent[u] != -1){
                    flow.at(parent[u], u) += min_res_cap;
                    flow.at(u, parent[u]) -= min_res_cap;
                    u = parent[u];
                }
            }
        }while(path_found);
    }

    delete[] level;
    delete[] parent;

    return max_flow;
}
template<class T, class C>
void FlowNetwork<T,C>::DinicLevelGraphBFS(std::size_t* level){
    std::queue<std::size_t> q;
    q.push(sourceNode());

    level[sourceNode()] = 0;
    while(!q.empty()){
        std::size_t v = q.front();
        q.pop();

        if(v == sinkNode())
            break;

        for(std::size_t i=0; i<size(); i++)
            if(level[i] == -1 && capacity.at(v,i) - flow.at(v,i) > C()){
                level[i] = level[v]+1;
                q.push(i);
            }
    }
}
template<class T, class C>
bool FlowNetwork<T,C>::DinicDFS(std::size_t node, std::size_t* level, std::size_t* parent){
    if(node != sinkNode()){
        bool found = false;
        for(int i = 0; i < size(); i++)
            if(level[i] != -1 && level[i] > level[node] &&
               capacity.at(node,i) - flow.at(node,i) > C()){
                parent[i] = node;
                found = found || DinicDFS(i, level, parent);
            }
        if(found == false) // prune dead end
            level[node] = -1;
        return found;
    }
    return true;
}






template<class T, class C>
bool FlowNetwork<T,C>::operator==(const FlowNetwork<T,C>& other){
    return (data == other.data && capacity == other.capacity && flow == other.flow);
}
template<class T, class C>
bool FlowNetwork<T,C>::operator!=(const FlowNetwork<T,C>& other){
    return !(*this == other);
}

// ============================================

template<class T, class C>
void FlowNetwork<T,C>::printCapacity(){
    if(size() > 0){
        std::cout << "   ";
        for(int i=0; i<capacity.sizeN(); i++)
            std::cout << i << ' ';
        std::cout << std::endl << ' ' << char(218);
        for(int i=0; i < 2*capacity.sizeN(); i++)
            std::cout << char(196);
        std::cout << std::endl;

        for(int i=0; i<capacity.sizeM(); i++){
            std::cout << i << char(179) << ' ';
            for(int j=0; j<capacity.sizeN(); j++){
                std::cout << capacity.at(i,j) << ' ';
            }
            std::cout << std::endl;
        }
    }
}
template<class T, class C>
void FlowNetwork<T,C>::printValues(){
    std::size_t i = 0;
    for(auto it = data.begin(); it != data.end(); it++, i++){
        std::cout << i << ": " << *it << std::endl;
    }
}
template<class T, class C>
void FlowNetwork<T,C>::printFlow(){
    if(size() > 0){
        std::cout << "   ";
        for(int i=0; i<flow.sizeN(); i++)
            std::cout << i << "   ";
        std::cout << std::endl << ' ' << char(218);
        for(int i=0; i < 4*flow.sizeN(); i++)
            std::cout << char(196);
        std::cout << std::endl;

        for(int i=0; i<flow.sizeM(); i++){
            std::cout << i << char(179) << ' ';
            for(int j=0; j<flow.sizeN(); j++){
                std::cout << flow.at(i,j) << '/' << capacity.at(i,j) << ' ';
            }
            std::cout << std::endl;
        }
    }
}
