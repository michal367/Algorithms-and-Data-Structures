#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>

template<class T, class C = int>
class FlowNetwork{

    // node 0 is source
    // last node (size()-1) is sink
    // nodes in between are inner nodes (from 1 to size()-2)

    struct Edge{
        std::size_t node;
        C capacity;
        C flow;

        Edge(std::size_t node, const C& capacity) : node(node), capacity(capacity), flow() {}
        bool operator==(const Edge& other) const{
            return (node == other.node && capacity == other.capacity && flow == other.flow);
        }
    };

    std::vector<std::list<Edge> > neighbours;
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

    void printNodes();
    void printValues();
    void printFlow();

private:
    void DinicLevelGraphBFS(const std::vector<std::list<Edge> >& residual, std::size_t* level);
    bool DinicDFS(const std::vector<std::list<Edge> >& residual, std::size_t node, std::size_t* level, std::size_t* parent);
};


template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(){
    // source
    data.push_back(T());
    neighbours.push_back(std::list<Edge>());
    // sink
    data.push_back(T());
    neighbours.push_back(std::list<Edge>());
}
template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(std::size_t inner_nodes_size, const T& value){
    // source
    data.push_back(value);
    neighbours.push_back(std::list<Edge>());
    // inner nodes
    for(std::size_t i=0; i<inner_nodes_size; i++){
        data.push_back(value);
        neighbours.push_back(std::list<Edge>());
    }
    // sink
    data.push_back(value);
    neighbours.push_back(std::list<Edge>());
}
template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(const T& source_v, std::initializer_list<T> inner_nodes_v, const T& sink_v){
    // source
    data.push_back(source_v);
    neighbours.push_back(std::list<Edge>());
    // inner nodes
    for(auto it = inner_nodes_v.begin(); it != inner_nodes_v.end(); it++){
        data.push_back(*it);
        neighbours.push_back(std::list<Edge>());
    }
    // sink
    data.push_back(sink_v);
    neighbours.push_back(std::list<Edge>());
}
template<class T, class C>
FlowNetwork<T,C>::FlowNetwork(const FlowNetwork<T,C>& other){
    data = other.data;
    neighbours = other.neighbours;
}
template<class T, class C>
FlowNetwork<T,C>& FlowNetwork<T,C>::operator=(const FlowNetwork<T,C>& other){
    if(this != &other){
        data = other.data;
        neighbours = other.neighbours;
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
    return (size() == 2 && neighbours.at(0).size() == 0);
}
template<class T, class C>
void FlowNetwork<T,C>::clear(){
    // remove inner nodes
    data.erase(data.begin()+1, data.end()-1);
    neighbours.erase(neighbours.begin()+1, neighbours.end()-1);
    // remove source and sink neighbours
    neighbours.at(sourceNode()).clear();
    neighbours.at(sinkNode()).clear();
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
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2)
            return true;
    return false;
}

template<class T, class C>
std::vector<std::pair<std::size_t,C> > FlowNetwork<T,C>::getNeighbours(std::size_t node){
    std::vector<std::pair<std::size_t,C> > ns;
    for(auto it = neighbours.at(node).begin(); it != neighbours.at(node).end(); it++)
        ns.push_back(std::make_pair(it->node, it->capacity));
    return ns;
}


template<class T, class C>
void FlowNetwork<T,C>::addNode(const T& value){
    data.insert(data.end()-1, value);
    neighbours.insert(neighbours.end()-1, std::list<Edge>());

    std::size_t new_node = size()-2;
    for(std::size_t i=0; i<size(); i++)
        for(auto it = neighbours.at(i).begin(); it != neighbours.at(i).end(); it++)
            if(it->node == new_node)
                it->node++;
}
template<class T, class C>
void FlowNetwork<T,C>::addDirectedEdge(std::size_t node1, std::size_t node2, const C& capacity){
    if(node1 != node2 && node1 != sinkNode() && node2 != sourceNode()){
        if(!existsDirectedEdge(node1, node2))
            neighbours.at(node1).push_back(Edge(node2, capacity));
    }
}

template<class T, class C>
void FlowNetwork<T,C>::removeNode(std::size_t node){
    if(node != sourceNode() && node != sinkNode()){
        data.erase(data.begin() + node);
        neighbours.erase(neighbours.begin() + node);

        for(auto it = neighbours.begin(); it != neighbours.end(); it++)
            for(auto it2 = it->begin(); it2 != it->end();)
                if(it2->node == node){
                    auto temp = it2;
                    it2++;
                    it->erase(temp);
                }
                else{
                    if(it2->node > node)
                        it2->node--;
                    it2++;
                }
    }
}
template<class T, class C>
void FlowNetwork<T,C>::removeDirectedEdge(std::size_t node1, std::size_t node2){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            neighbours.at(node1).erase(it);
            return;
        }
}

template<class T, class C>
C FlowNetwork<T,C>::getCapacity(std::size_t node1, std::size_t node2){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2)
            return it->capacity;
}
template<class T, class C>
void FlowNetwork<T,C>::setCapacity(std::size_t node1, std::size_t node2, const C& capacity){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            it->capacity = capacity;
            return;
        }
}

template<class T, class C>
C FlowNetwork<T,C>::getFlow(std::size_t node1, std::size_t node2){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2)
            return it->flow;
}
template<class T, class C>
void FlowNetwork<T,C>::clearFlow(){
    for(std::size_t i=0; i<size(); i++)
        for(auto itn = neighbours.at(i).begin(); itn != neighbours.at(i).end(); itn++)
            itn->flow = C();
}


template<class T, class C>
C FlowNetwork<T,C>::EdmondsKarp(){
    // max flow
    // capacities must be non-negative

    C max_flow = C();

    clearFlow();

    // create residual network
    std::vector<std::list<Edge> > residual = neighbours;
    for(std::size_t i=0; i<size(); i++)
        for(auto itr = residual.at(i).begin(); itr != residual.at(i).end(); itr++){
            if(itr->capacity > C()){
                bool found = false;
                for(auto itr2 = residual.at(itr->node).begin(); itr2 != residual.at(itr->node).end(); itr2++)
                    if(itr2->node == i){
                        found = true;
                        break;
                    }
                if(found == false)
                    residual.at(itr->node).push_back(Edge(i, C()));
            }
        }

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

            for(auto itr = residual.at(v).begin(); itr != residual.at(v).end(); itr++)
                if(itr->capacity > C() && visited[itr->node] == false){
                    visited[itr->node] = true;
                    parent[itr->node] = v;
                    q.push(itr->node);
                }
        }

        if(path_found){
            // get min residual capacity
            C min_res_cap = C();
            bool initialized = false;
            std::size_t u = sinkNode();
            while(parent[u] != -1){
                for(auto itr = residual.at(parent[u]).begin(); itr != residual.at(parent[u]).end(); itr++)
                    if(itr->node == u)
                        if(itr->capacity < min_res_cap || !initialized){
                            min_res_cap = itr->capacity;
                            initialized = true;
                        }
                u = parent[u];
            }
            max_flow += min_res_cap;

            // change residual capacities and flow
            u = sinkNode();
            while(parent[u] != -1){
                for(auto itr = residual.at(parent[u]).begin(); itr != residual.at(parent[u]).end(); itr++)
                    if(itr->node == u)
                        itr->capacity -= min_res_cap;
                for(auto itr = residual.at(u).begin(); itr != residual.at(u).end(); itr++)
                    if(itr->node == parent[u])
                        itr->capacity += min_res_cap;

                for(auto itn = neighbours.at(parent[u]).begin(); itn != neighbours.at(parent[u]).end(); itn++)
                    if(itn->node == u)
                        itn->flow += min_res_cap;

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

    // create residual network
    std::vector<std::list<Edge> > residual = neighbours;
    for(std::size_t i=0; i<size(); i++)
        for(auto itr = residual.at(i).begin(); itr != residual.at(i).end(); itr++){
            if(itr->capacity > C()){
                bool found = false;
                for(auto itr2 = residual.at(itr->node).begin(); itr2 != residual.at(itr->node).end(); itr2++)
                    if(itr2->node == i){
                        found = true;
                        break;
                    }
                if(found == false)
                    residual.at(itr->node).push_back(Edge(i, C()));
            }
        }

    std::size_t* level = new std::size_t[size()];
    std::size_t* parent = new std::size_t[size()];

    while(true){
        // create level graph
        for(std::size_t i=0; i<size(); i++)
            level[i] = -1;
        DinicLevelGraphBFS(residual, level);

        if(level[sinkNode()] == -1)
            break;

        bool path_found;
        do{
            for(std::size_t i=0; i<size(); i++)
                parent[i] = -1;

            // run DFS
            path_found = DinicDFS(residual, sourceNode(), level, parent);

            if(path_found){
                // get min residual capacity
                C min_res_cap = C();
                bool initialized = false;
                std::size_t u = sinkNode();
                while(parent[u] != -1){
                    for(auto itr = residual.at(parent[u]).begin(); itr != residual.at(parent[u]).end(); itr++)
                        if(itr->node == u)
                            if(itr->capacity < min_res_cap || !initialized){
                                min_res_cap = itr->capacity;
                                initialized = true;
                            }
                    u = parent[u];
                }
                max_flow += min_res_cap;

                // change residual capacities and flow
                u = sinkNode();
                while(parent[u] != -1){
                    for(auto itr = residual.at(parent[u]).begin(); itr != residual.at(parent[u]).end(); itr++)
                        if(itr->node == u)
                            itr->capacity -= min_res_cap;
                    for(auto itr = residual.at(u).begin(); itr != residual.at(u).end(); itr++)
                        if(itr->node == parent[u])
                            itr->capacity += min_res_cap;

                    for(auto itn = neighbours.at(parent[u]).begin(); itn != neighbours.at(parent[u]).end(); itn++)
                        if(itn->node == u)
                            itn->flow += min_res_cap;

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
void FlowNetwork<T,C>::DinicLevelGraphBFS(const std::vector<std::list<Edge> >& residual, std::size_t* level){
    std::queue<std::size_t> q;
    q.push(sourceNode());

    level[sourceNode()] = 0;
    while(!q.empty()){
        std::size_t v = q.front();
        q.pop();

        if(v == sinkNode())
            break;

        for(auto itr = residual.at(v).begin(); itr != residual.at(v).end(); itr++)
            if(level[itr->node] == -1 && itr->capacity > C()){
                level[itr->node] = level[v]+1;
                q.push(itr->node);
            }
    }
}
template<class T, class C>
bool FlowNetwork<T,C>::DinicDFS(const std::vector<std::list<Edge> >& residual, std::size_t node, std::size_t* level, std::size_t* parent){
    if(node != sinkNode()){
        bool found = false;
        for(auto itr = residual.at(node).begin(); itr != residual.at(node).end(); itr++)
            if(level[itr->node] != -1 && level[itr->node] > level[node] && itr->capacity > C()){
                parent[itr->node] = node;
                found = found || DinicDFS(residual, itr->node, level, parent);
            }
        if(found == false) // prune dead end
            level[node] = -1;
        return found;
    }
    return true;
}


template<class T, class C>
bool FlowNetwork<T,C>::operator==(const FlowNetwork<T,C>& other){
    return (data == other.data && neighbours == other.neighbours);
}
template<class T, class C>
bool FlowNetwork<T,C>::operator!=(const FlowNetwork<T,C>& other){
    return !(*this == other);
}

// ============================================

template<class T, class C>
void FlowNetwork<T,C>::printNodes(){
    std::size_t i = 0;
    for(auto it = neighbours.begin(); it != neighbours.end(); it++, i++){
        std::cout << i << ": " << data.at(i);
        if(i == sourceNode())
            std::cout << "  source    ";
        else if(i == sinkNode())
            std::cout << "  sink      ";
        else
            std::cout << "            ";
        std::cout << "neighbours: ";
        for(auto it2 = it->begin(); it2 != it->end(); it2++)
            std::cout << it2->node << "(c: " << it2->capacity << ") ";

        std::cout << std::endl;
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
    std::size_t i = 0;
    for(auto it = neighbours.begin(); it != neighbours.end(); it++, i++){
        std::cout << i << ": ";
        if(i == sourceNode())
            std::cout << " source   ";
        else if(i == sinkNode())
            std::cout << " sink     ";
        else
            std::cout << "          ";
        std::cout << "neighbours: ";
        for(auto it2 = it->begin(); it2 != it->end(); it2++)
            std::cout << it2->node << "(" << it2->flow << "/" << it2->capacity << ") ";

        std::cout << std::endl;
    }
}


