#pragma once

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

#include "Matrix.h"
#include "DisjointSets.h"

#include <iostream>

template<class T, class W = int>
class WeightedGraph{
    // simple undirected/directed weighted graph with loops

    struct Edge{
        std::size_t node;
        W weight;

        Edge(std::size_t node, const W& weight) : node(node), weight(weight) {}
        bool operator==(const Edge& other) const{
            return (node == other.node && weight == other.weight);
        }
    };

    struct Node{
        T value;
        std::list<Edge> neighbours;

        Node(const T& value){
            this->value = value;
        }
        bool operator==(const Node& other) const{
            return (value == other.value && neighbours == other.neighbours);
        }
    };

    std::vector<Node> nodes;

public:
    WeightedGraph();
    WeightedGraph(std::size_t size, const T& value);
    WeightedGraph(std::initializer_list<T> il);
    WeightedGraph(const WeightedGraph<T,W>& other);
    WeightedGraph<T,W>& operator=(const WeightedGraph<T,W>& other);


    std::size_t size();
    std::size_t nodesAmount();
    std::size_t directedEdgesAmount();
    std::size_t edgesAmount();
    bool empty();
    void clear();

    T getData(std::size_t node);
    T& at(std::size_t node);
    void setData(std::size_t node, const T& value);
    bool existsDirectedEdge(std::size_t node1, std::size_t node2);

    std::vector<std::pair<std::size_t, W> > getNeighbours(std::size_t node);

    void addNode(const T& value);
    void addDirectedEdge(std::size_t node1, std::size_t node2, const W& weight);
    void addEdge(std::size_t node1, std::size_t node2, const W& weight);

    void removeNode(std::size_t node);
    void removeDirectedEdge(std::size_t node1, std::size_t node2);
    void removeEdge(std::size_t node1, std::size_t node2);

    W getWeight(std::size_t node1, std::size_t node2);
    void setWeight(std::size_t node1, std::size_t node2, const W& weight);
    void setWeightDirected(std::size_t node1, std::size_t node2, const W& weight);

    W minWeight();
    W maxWeight();

    template<class ForwardIt>
    W pathWeight(ForwardIt begin, ForwardIt end);
    W sumEdgesWeight(std::vector<std::pair<std::size_t,std::size_t> > edges);

    WeightedGraph<T,W> convertToUndirectedWeightedGraph();
    WeightedGraph<T,W> subgraph(const std::vector<std::size_t>& nodes);

    std::size_t degree();
    std::size_t degree2();
    std::size_t degree(std::size_t node);
    std::size_t indegree(std::size_t node);
    std::size_t outdegree(std::size_t node);


    std::vector<std::size_t> DFS();
    std::vector<std::size_t> DFSstack();
    std::vector<std::size_t> BFS();

    void transpose();

    std::vector<std::size_t> DFSpath(std::size_t start, std::size_t end);
    std::vector<std::size_t> DFSpath2(std::size_t start, std::size_t end);
    std::vector<std::size_t> BFSpath(std::size_t start, std::size_t end);
    bool existsDFSpath(std::size_t start, std::size_t end);

    WeightedGraph<T,W> DFspanningTrees(std::size_t start=0);
    WeightedGraph<T,W> BFspanningTrees(std::size_t start=0);


    std::vector<std::size_t> Dijkstra(std::size_t node1, std::size_t node2);
    std::vector<std::size_t> Dijkstra2(std::size_t node1, std::size_t node2);
    std::vector<std::size_t> Dijkstra3(std::size_t node1, std::size_t node2);

    std::vector<std::size_t> BellmanFord(std::size_t node1, std::size_t node2);

    std::pair<Matrix<W>, Matrix<int> > FloydWarshall();
    std::vector<std::vector<std::size_t> > FloydWarshallPaths();

    std::vector<std::size_t> travellingSalesmanProblem(std::size_t start=0);
    std::vector<std::size_t> shortestHamiltonianPath(std::size_t start=-1);

    std::pair<std::vector<std::size_t>,std::vector<std::size_t> > bipartiteSets();

    std::vector<std::pair<std::size_t,std::size_t> > maxWeightHungarianAlgorithm();
    std::vector<std::pair<std::size_t,std::size_t> > minWeightHungarianAlgorithm();

    WeightedGraph<T,W> KruskalMST();
    WeightedGraph<T,W> PrimMST();


    bool operator==(const WeightedGraph<T,W>& other);
    bool operator!=(const WeightedGraph<T,W>& other);

    void printNodes();
    void printValues();

private:
    void innerDFS(std::size_t node, bool* visited, std::vector<std::size_t>& result);

    void innerDFSpath(std::size_t start, std::size_t end, bool* visited, std::size_t* path);
    bool innerDFSpath2(std::size_t start, std::size_t end, bool* visited, std::vector<std::size_t>& path);

    void innerDFspanningTrees(std::size_t node, bool* visited, WeightedGraph<T,W>& tree);

    void innerTravellingSalesmanProblem(std::size_t node, std::size_t start,
                                     bool* visited, std::size_t counter,
                                     W& dist, W& min_dist, bool& found_sth,
                                     std::vector<std::size_t>& nodes,
                                     std::vector<std::size_t>& result);
    void innerShortestHamiltonianPath(std::size_t node,
                                     bool* visited, std::size_t counter,
                                     W& dist, W& min_dist, bool& found_sth,
                                     std::vector<std::size_t>& nodes,
                                     std::vector<std::size_t>& result);
};



template<class T, class W>
WeightedGraph<T,W>::WeightedGraph() {}
template<class T, class W>
WeightedGraph<T,W>::WeightedGraph(std::size_t size, const T& value){
    for(std::size_t i=0; i<size; i++){
        nodes.push_back(Node(value));
    }
}
template<class T, class W>
WeightedGraph<T,W>::WeightedGraph(std::initializer_list<T> il){
    for(auto it = il.begin(); it != il.end(); it++){
        nodes.push_back(Node(*it));
    }
}
template<class T, class W>
WeightedGraph<T,W>::WeightedGraph(const WeightedGraph<T,W>& other){
    nodes = other.nodes;
}
template<class T, class W>
WeightedGraph<T,W>& WeightedGraph<T,W>::operator=(const WeightedGraph<T,W>& other){
    if(this != &other){
        nodes = other.nodes;
    }
    return *this;
}



template<class T, class W>
std::size_t WeightedGraph<T,W>::size(){
    return nodes.size();
}
template<class T, class W>
std::size_t WeightedGraph<T,W>::nodesAmount(){
    return size();
}
template<class T, class W>
std::size_t WeightedGraph<T,W>::directedEdgesAmount(){
    std::size_t amount = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        amount += it->neighbours.size();
    return amount;
}
template<class T, class W>
std::size_t WeightedGraph<T,W>::edgesAmount(){
    std::set<std::set<std::size_t>> edges;

    for(std::size_t i=0; i<nodes.size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            edges.insert(std::set<std::size_t>({i, it->node}));

    return edges.size();
}
template<class T, class W>
bool WeightedGraph<T,W>::empty(){
    return (size() == 0);
}
template<class T, class W>
void WeightedGraph<T,W>::clear(){
    nodes.clear();
}


template<class T, class W>
T WeightedGraph<T,W>::getData(std::size_t node){
    return nodes.at(node).value;
}
template<class T, class W>
T& WeightedGraph<T,W>::at(std::size_t node){
    return nodes.at(node).value;
}
template<class T, class W>
void WeightedGraph<T,W>::setData(std::size_t node, const T& value){
    nodes.at(node).value = value;
}
template<class T, class W>
bool WeightedGraph<T,W>::existsDirectedEdge(std::size_t node1, std::size_t node2){
    auto it = nodes.at(node1).neighbours.begin();
    auto end = nodes.at(node1).neighbours.end();
    for(; it != end; it++)
        if(it->node == node2)
            return true;
    return false;
}

template<class T, class W>
std::vector<std::pair<std::size_t, W> > WeightedGraph<T,W>::getNeighbours(std::size_t node){
    std::vector<std::pair<std::size_t, W> > neighbours;
    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
        neighbours.push_back(std::make_pair(it->node, it->weight));
    return neighbours;
}


template<class T, class W>
void WeightedGraph<T,W>::addNode(const T& value){
    nodes.push_back(Node(value));
}
template<class T, class W>
void WeightedGraph<T,W>::addDirectedEdge(std::size_t node1, std::size_t node2, const W& weight){
    if(!existsDirectedEdge(node1, node2))
        nodes.at(node1).neighbours.push_back(Edge(node2, weight));
}
template<class T, class W>
void WeightedGraph<T,W>::addEdge(std::size_t node1, std::size_t node2, const W& weight){
    addDirectedEdge(node1, node2, weight);
    addDirectedEdge(node2, node1, weight);
}


template<class T, class W>
void WeightedGraph<T,W>::removeNode(std::size_t node){
    nodes.erase(nodes.begin() + node);

    for(auto it2 = nodes.begin(); it2 != nodes.end(); it2++)
        for(auto it3 = it2->neighbours.begin(); it3 != it2->neighbours.end();)
            if(it3->node == node){
                auto temp = it3;
                it3++;
                it2->neighbours.erase(temp);
            }
            else{
                if(it3->node > node)
                    it3->node--;
                it3++;
            }
}
template<class T, class W>
void WeightedGraph<T,W>::removeDirectedEdge(std::size_t node1, std::size_t node2){
    for(auto it = nodes.at(node1).neighbours.begin(); it != nodes.at(node1).neighbours.end();)
        if(it->node == node2){
            auto temp = it;
            it++;
            nodes.at(node1).neighbours.erase(temp);
        }
        else
            it++;
}
template<class T, class W>
void WeightedGraph<T,W>::removeEdge(std::size_t node1, std::size_t node2){
    removeDirectedEdge(node1, node2);
    removeDirectedEdge(node2, node1);
}


template<class T, class W>
W WeightedGraph<T,W>::getWeight(std::size_t node1, std::size_t node2){
    for(auto it = nodes.at(node1).neighbours.begin(); it != nodes.at(node1).neighbours.end(); it++)
        if(it->node == node2)
            return it->weight;
    return W();
}
template<class T, class W>
void WeightedGraph<T,W>::setWeight(std::size_t node1, std::size_t node2, const W& weight){
    for(auto it = nodes.at(node1).neighbours.begin(); it != nodes.at(node1).neighbours.end(); it++)
        if(it->node == node2)
            it->weight = weight;
    for(auto it = nodes.at(node2).neighbours.begin(); it != nodes.at(node2).neighbours.end(); it++)
        if(it->node == node1)
            it->weight = weight;
}
template<class T, class W>
void WeightedGraph<T,W>::setWeightDirected(std::size_t node1, std::size_t node2, const W& weight){
    for(auto it = nodes.at(node1).neighbours.begin(); it != nodes.at(node1).neighbours.end(); it++)
        if(it->node == node2)
            it->weight = weight;
}

template<class T, class W>
W WeightedGraph<T,W>::minWeight(){
    W min = W();
    bool initialized = false;
    for(std::size_t i=0; i<size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            if(it->weight < min || !initialized){
                min = it->weight;
                initialized = true;
            }
    return min;
}
template<class T, class W>
W WeightedGraph<T,W>::maxWeight(){
    W max = W();
    bool initialized = false;
    for(std::size_t i=0; i<size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            if(it->weight > max || !initialized){
                max = it->weight;
                initialized = true;
            }
    return max;
}

template<class T, class W>
template<class ForwardIt>
W WeightedGraph<T,W>::pathWeight(ForwardIt begin, ForwardIt end){
    W sum = W();
    if(begin != end)
        for(auto it = begin, it2 = begin+1; it2 != end; it++, it2++)
            sum = sum + getWeight(*it, *it2);
    return sum;
}
template<class T, class W>
W WeightedGraph<T,W>::sumEdgesWeight(std::vector<std::pair<std::size_t,std::size_t> > edges){
    W sum = W();
    for(auto it = edges.begin(); it != edges.end(); it++)
        sum = sum + getWeight(it->first, it->second);
    return sum;
}


template<class T, class W>
WeightedGraph<T,W> WeightedGraph<T,W>::convertToUndirectedWeightedGraph(){
    WeightedGraph<T,W> undig;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        undig.nodes.push_back(Node(it->value));

    int i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++)
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            undig.addEdge(i, it2->node, it2->weight);

    return undig;
}

template<class T, class W>
WeightedGraph<T,W> WeightedGraph<T,W>::subgraph(const std::vector<std::size_t>& nodes){
    WeightedGraph<T,W> sg;
    std::map<std::size_t, std::size_t> m;

    std::size_t i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        sg.addNode(this->nodes.at(*it).value);
        m.insert(std::pair<std::size_t,std::size_t>(*it, i++));
    }

    for(auto it = nodes.begin(); it != nodes.end(); it++){
        for(auto it2 = this->nodes.at(*it).neighbours.begin(); it2 != this->nodes.at(*it).neighbours.end(); it2++){
            auto mit = m.find(it2->node);
            if(mit != m.end()){
                sg.addDirectedEdge(m.find(*it)->second, mit->second, it2->weight);
            }
        }
    }

    return sg;
}


template<class T, class W>
std::size_t WeightedGraph<T,W>::degree(){
    std::size_t max = 0;
    for(std::size_t i=0; i < size(); i++){
        std::size_t deg = degree(i);
        if(deg > max)
            max = deg;
    }
    return max;
}

template<class T, class W>
std::size_t WeightedGraph<T,W>::degree2(){
    std::size_t* degrees = new std::size_t[size()];
    for(int i=0; i<size(); i++)
        degrees[i] = 0;

    for(int i=0; i<nodes.size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++){
            degrees[i]++;
            degrees[it->node]++;
        }

    std::size_t max = 0;
    for(std::size_t i=0; i < size(); i++)
        if(degrees[i] > max)
            max = degrees[i];

    delete[] degrees;
    return max;
}
template<class T, class W>
std::size_t WeightedGraph<T,W>::degree(std::size_t node){
    return indegree(node) + outdegree(node);
}
template<class T, class W>
std::size_t WeightedGraph<T,W>::indegree(std::size_t node){
    std::size_t amount = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            if(it2->node == node)
                amount++;
    }
    return amount;
}
template<class T, class W>
std::size_t WeightedGraph<T,W>::outdegree(std::size_t node){
    return nodes.at(node).neighbours.size();
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::DFS(){
    std::size_t g_size = size();

    bool* visited = new bool[g_size];
    for(int i=0; i<g_size; i++)
        visited[i] = false;

    std::vector<std::size_t> result;
    result.reserve(g_size);

    for(int i=0; i<g_size; i++){
        innerDFS(i, visited, result);
    }

    delete[] visited;

    return result;
}
template<class T, class W>
void WeightedGraph<T,W>::innerDFS(std::size_t node, bool* visited, std::vector<std::size_t>& result){
    if(visited[node] == false){
        visited[node] = true;
        result.push_back(node);

        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            innerDFS(it->node, visited, result);
    }
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::DFSstack(){
    std::size_t g_size = size();
    bool* visited = new bool[g_size];
    for(int i=0; i<g_size; i++)
        visited[i] = false;
    std::vector<std::size_t> result;
    result.reserve(g_size);


    std::stack<std::size_t> s;
    for(int i=0; i < g_size; i++){
        if(visited[i] == false){
            s.push(i);

            while(!s.empty()){
                std::size_t node = s.top();
                s.pop();

                if(visited[node] == false){
                    visited[node] = true;
                    result.push_back(node);

                    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
                        if(visited[it->node] == false)
                            s.push(it->node);
                }
            }
        }
    }


    delete[] visited;
    return result;
}

template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::BFS(){
    std::size_t g_size = size();
    bool* visited = new bool[g_size];
    for(int i=0; i<g_size; i++)
        visited[i] = false;
    std::vector<std::size_t> result;
    result.reserve(g_size);

    std::queue<std::size_t> q;
    for(int i=0; i<g_size; i++){
        if(visited[i] == false){
            visited[i] = true;
            q.push(i);

            while(!q.empty()){
                std::size_t node = q.front();
                q.pop();

                result.push_back(node);

                for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++){
                    if(visited[it->node] == false){
                        visited[it->node] = true;
                        q.push(it->node);
                    }
                }
            }
        }
    }

    delete[] visited;
    return result;
}


template<class T, class W>
void WeightedGraph<T,W>::transpose(){
    std::size_t g_size = size();
    std::list<Edge>* new_lists = new std::list<Edge>[g_size];

    for(int i=0; i<g_size; i++){
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++){
            new_lists[it->node].push_back(Edge(i, it->weight));
        }
    }

    for(int i=0; i<g_size; i++)
        nodes.at(i).neighbours = new_lists[i];
    delete[] new_lists;
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::DFSpath(std::size_t start, std::size_t end){
    if(start >= size() || end >= size())
        return std::vector<std::size_t>();

    if(start == end)
        return std::vector<std::size_t>({start});

    std::size_t* path = new std::size_t[size()];
    path[start] = -1;
    path[end] = -1;
    bool* visited = new bool[size()];
    for(int i=0; i<size(); i++)
        visited[i] = false;

    innerDFSpath(start, end, visited, path);

    std::vector<std::size_t> result;
    if(path[end] != -1){
        std::size_t v = end;
        while(v != -1){
            result.push_back(v);
            v = path[v];
        }

        std::reverse(result.begin(), result.end());
    }

    delete[] path;
    delete[] visited;

    return result;
}

template<class T, class W>
void WeightedGraph<T,W>::innerDFSpath(std::size_t start, std::size_t end, bool* visited, std::size_t* path){
    visited[start] = true;
    if(start != end){
        for(auto it = nodes.at(start).neighbours.begin(); it != nodes.at(start).neighbours.end(); it++){
            if(visited[it->node] == false){
                path[it->node] = start;
                innerDFSpath(it->node, end, visited, path);
            }
        }
    }
}

template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::DFSpath2(std::size_t start, std::size_t end){
    if(start >= size() || end >= size())
        return std::vector<std::size_t>();

    bool* visited = new bool[size()];
    for(int i=0; i<size(); i++)
        visited[i] = false;
    std::vector<std::size_t> path;

    if(innerDFSpath2(start, end, visited, path) == true){
        delete[] visited;
        return path;
    }
    delete[] visited;
    return std::vector<std::size_t>();
}

template<class T, class W>
bool WeightedGraph<T,W>::innerDFSpath2(std::size_t start, std::size_t end, bool* visited, std::vector<std::size_t>& path){
    visited[start] = true;
    path.push_back(start);
    if(start != end){
        bool found = false;
        for(auto it = nodes.at(start).neighbours.begin(); it != nodes.at(start).neighbours.end(); it++){
            if(visited[it->node] == false){
                found = found || innerDFSpath2(it->node, end, visited, path);
            }
        }
        if(found == false)
            path.pop_back();
        return found;
    }
    return true;
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::BFSpath(std::size_t start, std::size_t end){
    if(start >= size() || end >= size())
        return std::vector<std::size_t>();

    if(start == end)
        return std::vector<std::size_t>({start});

    std::size_t* path = new std::size_t[size()];
    path[start] = -1;
    path[end] = -1;
    bool* visited = new bool[size()];
    for(int i=0; i<size(); i++)
        visited[i] = false;

    std::queue<std::size_t> q;
    q.push(start);
    visited[start] = true;

    while(!q.empty()){
        std::size_t v = q.front();
        q.pop();

        if(v == end)
            break;

        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
            if(visited[it->node] == false){
                path[it->node] = v;
                q.push(it->node);
                visited[it->node] = true;
            }
        }
    }

    std::vector<std::size_t> result;
    if(path[end] != -1){
        std::size_t v = end;
        while(v != -1){
            result.push_back(v);
            v = path[v];
        }

        std::reverse(result.begin(), result.end());
    }

    delete[] path;
    delete[] visited;

    return result;
}

template<class T, class W>
bool WeightedGraph<T,W>::existsDFSpath(std::size_t start, std::size_t end){
    if(start >= size() || end >= size())
        return false;

    if(start == end)
        return true;

    bool* visited = new bool[size()];
    for(int i=0; i < size(); i++)
        visited[i] = false;

    std::stack<std::size_t> s;
    s.push(start);

    while(!s.empty()){
        std::size_t node = s.top();
        s.pop();

        if(visited[node] == false){
            if(node == end){
                delete[] visited;
                return true;
            }
            visited[node] = true;

            for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
                if(visited[it->node] == false)
                    s.push(it->node);
        }
    }

    delete[] visited;
    return false;
}


template<class T, class W>
WeightedGraph<T,W> WeightedGraph<T,W>::DFspanningTrees(std::size_t start){
    WeightedGraph<T,W> trees;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        trees.addNode(it->value);

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    innerDFspanningTrees(start, visited, trees);
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == false)
            innerDFspanningTrees(i, visited, trees);

    return trees;
}
template<class T, class W>
void WeightedGraph<T,W>::innerDFspanningTrees(std::size_t node, bool* visited, WeightedGraph<T,W>& trees){
    visited[node] = true;
    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
        if(visited[it->node] == false){
            trees.addDirectedEdge(node, it->node, it->weight);
            innerDFspanningTrees(it->node, visited, trees);
        }
}

template<class T, class W>
WeightedGraph<T,W> WeightedGraph<T,W>::BFspanningTrees(std::size_t start){
    WeightedGraph<T,W> trees;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        trees.addNode(it->value);

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    std::queue<std::size_t> q;

    q.push(start);
    visited[start] = true;
    while(!q.empty()){
        std::size_t v = q.front();
        q.pop();

        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
            if(visited[it->node] == false){
                q.push(it->node);
                visited[it->node] = true;
                trees.addDirectedEdge(v,it->node, it->weight);
            }
    }

    for(std::size_t i=0; i < size(); i++){
        if(visited[i] == false){
            q.push(i);
            visited[i] = true;

            while(!q.empty()){
                std::size_t v = q.front();
                q.pop();

                for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
                    if(visited[it->node] == false){
                        q.push(it->node);
                        visited[it->node] = true;
                        trees.addDirectedEdge(v,it->node, it->weight);
                    }
            }
        }
    }

    return trees;
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::Dijkstra(std::size_t node1, std::size_t node2){
    // version with linear search for minimum dist

    // graph must have non-negative edge weights

    if(node1 >= size() || node2 >= size())
        return std::vector<std::size_t>();
    if(node1 == node2)
        return std::vector<std::size_t>({node1});

    std::set<std::size_t> q;

    W* dist = new W[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++){
        //dist[i] = W();
        parent[i] = -1;
        q.insert(i);
    }
    dist[node1] = W();

    while(!q.empty()){
        std::size_t v = *(q.begin());
        W min_d = dist[v];
        for(auto it = q.begin(); it != q.end(); it++){
            if(parent[*it] != -1 && dist[*it] < min_d || *it == node1){
                v = *it;
                min_d = dist[v];
            }
        }

        q.erase(v);
        if(v == node2)
            break;

        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
            if(q.find(it->node) != q.end())
                if(dist[v] + it->weight < dist[it->node] || parent[it->node] == -1){
                    dist[it->node] = dist[v] + it->weight;
                    parent[it->node] = v;
                }
    }
    delete[] dist;

    // construct path
    std::vector<std::size_t> result;
    if(parent[node2] != -1){
        std::size_t v = node2;
        while(v != -1){
            result.push_back(v);
            v = parent[v];
        }
        std::reverse(result.begin(), result.end());
    }

    delete[] parent;
    return result;
}

template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::Dijkstra2(std::size_t node1, std::size_t node2){
    // version with priority queue

    // graph must have non-negative edge weights

    if(node1 >= size() || node2 >= size())
        return std::vector<std::size_t>();
    if(node1 == node2)
        return std::vector<std::size_t>({node1});

    typedef std::pair<W, std::size_t> p;
    std::priority_queue<p, std::vector<p>, std::greater<p> > pq;

    W* dist = new W[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++){
        //dist[i] = W();
        parent[i] = -1;
    }
    dist[node1] = W();

    pq.push(std::make_pair(dist[node1], node1));
    while(!pq.empty()){
        std::size_t v = pq.top().second;
        W d = pq.top().first;
        pq.pop();

        if(dist[v] < d)
            continue;
        if(v == node2)
            break;

        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
            if(dist[v] + it->weight < dist[it->node] || parent[it->node] == -1 && it->node != node1){
                dist[it->node] = dist[v] + it->weight;
                parent[it->node] = v;
                pq.push(std::make_pair(dist[it->node], it->node));
            }
    }
    delete[] dist;

    // construct path
    std::vector<std::size_t> result;
    if(parent[node2] != -1){
        std::size_t v = node2;
        while(v != -1){
            result.push_back(v);
            v = parent[v];
        }
        std::reverse(result.begin(), result.end());
    }

    delete[] parent;
    return result;
}

template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::Dijkstra3(std::size_t node1, std::size_t node2){
    // version with indexed priority queue

    // graph must have non-negative edge weights

    if(node1 >= size() || node2 >= size())
        return std::vector<std::size_t>();
    if(node1 == node2)
        return std::vector<std::size_t>({node1});

    struct indexed_pq{ // indexed min priority queue
        std::size_t size;
        std::size_t* h;     // heap containing graph vertices
        std::size_t* hp;    // position of graph vertex in heap
        W* dist;            // key (priority)

        indexed_pq(std::size_t s, W* d){
            size = 0;
            h = new std::size_t[s];
            hp = new std::size_t[s];
            for(std::size_t i=0; i<s; i++)
                hp[i] = -1;
            dist = d;
        }
        ~indexed_pq(){
            delete[] h;
            delete[] hp;
        }
        void push(std::size_t v){
            h[size] = v;
            hp[v] = size;
            size++;
            std::size_t child = hp[v];
            std::size_t parent = (child-1)/2;
            while(child != 0 && dist[h[parent]] > dist[v]){
                std::swap(hp[v], hp[h[parent]]);
                std::swap(h[child], h[parent]);
                child = parent;
                parent = (child-1)/2;
            }
        }
        std::size_t pop(){
            if(size > 0){
                std::size_t t = h[0];
                hp[h[0]] = -1;
                --size;
                if(size > 0){
                    h[0] = h[size];
                    hp[h[size]] = 0;
                    std::size_t pos = 0;
                    do{
                        std::size_t left = 2*pos+1;
                        std::size_t right = left+1;
                        if(left < size && dist[h[left]] < dist[h[pos]]){
                            std::swap(hp[h[left]], hp[h[pos]]);
                            std::swap(h[left], h[pos]);
                            pos = left;
                        }
                        else if(right < size && dist[h[right]] < dist[h[pos]]){
                            std::swap(hp[h[right]], hp[h[pos]]);
                            std::swap(h[right], h[pos]);
                            pos = right;
                        }
                        else
                            break;
                    }while(true);
                }
                return t;
            }
            return -1;
        }
        void decrease_key(std::size_t v){
            std::size_t child = hp[v];
            std::size_t parent = (child-1)/2;
            while(child != 0 && dist[h[parent]] > dist[v]){
                std::swap(hp[v], hp[h[parent]]);
                std::swap(h[child], h[parent]);
                child = parent;
                parent = (child-1)/2;
            }
        }
        bool contains(std::size_t v){
            return (hp[v] != -1);
        }
        bool empty(){
            return (size == 0);
        }
    };


    W* dist = new W[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++){
        //dist[i] = W();
        parent[i] = -1;
    }
    dist[node1] = W();

    indexed_pq ipq(size(), dist);

    ipq.push(node1);
    while(!ipq.empty()){
        std::size_t v = ipq.pop();

        if(v == node2)
            break;

        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
            if(dist[v] + it->weight < dist[it->node] || parent[it->node] == -1 && it->node != node1){
                dist[it->node] = dist[v] + it->weight;
                parent[it->node] = v;

                if(ipq.contains(it->node))
                    ipq.decrease_key(it->node);
                else
                    ipq.push(it->node);
            }
    }
    delete[] dist;

    // construct path
    std::vector<std::size_t> result;
    if(parent[node2] != -1){
        std::size_t v = node2;
        while(v != -1){
            result.push_back(v);
            v = parent[v];
        }
        std::reverse(result.begin(), result.end());
    }

    delete[] parent;
    return result;
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::BellmanFord(std::size_t node1, std::size_t node2){
    if(node1 >= size() || node2 >= size())
        return std::vector<std::size_t>();

    W* dist = new W[size()];
    std::size_t* parent = new std::size_t[size()];
    bool* is_inf = new bool[size()];
    bool* is_neg_inf = new bool[size()];
    for(std::size_t i=0; i<size(); i++){
        parent[i] = -1;
        is_inf[i] = true;
        is_neg_inf[i] = false;
    }
    dist[node1] = W();
    is_inf[node1] = false;

    for(std::size_t i=0; i < size()-1; i++){
        bool changed = false;
        for(std::size_t v=0; v < size(); v++)
            for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
                if(!is_inf[v] && (dist[v] + it->weight < dist[it->node] || is_inf[it->node])){
                    dist[it->node] = dist[v] + it->weight;
                    parent[it->node] = v;
                    is_inf[it->node] = false;
                    changed = true;
                }
        if(!changed)
            break;
    }

    // find all nodes reachable by negative cycles and set their dist to negative inf
    for(std::size_t i=0; i < size()-1; i++){
        bool changed = false;
        for(std::size_t v=0; v < size(); v++)
            for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
                if(!is_neg_inf[it->node] && (is_neg_inf[v] || !is_inf[v] && dist[v] + it->weight < dist[it->node])){
                    dist[it->node] = dist[v] + it->weight;
                    is_neg_inf[it->node] = true;
                    changed = true;
                }
        if(!changed)
            break;
    }

    // construct path
    std::vector<std::size_t> result;
    if(node1 == node2 && is_neg_inf[node1] == false)
        result.push_back(node1);
    else if(parent[node2] != -1 && is_neg_inf[node2] == false){
        std::size_t v = node2;
        while(v != -1){
            result.push_back(v);
            v = parent[v];
        }
        std::reverse(result.begin(), result.end());
    }

    delete[] dist;
    delete[] parent;
    delete[] is_inf;
    delete[] is_neg_inf;
    return result;
}


template<class T, class W>
std::pair<Matrix<W>, Matrix<int> > WeightedGraph<T,W>::FloydWarshall(){
    // returns:
    // matrix of distances between each pair of nodes
    // matrix containing info whether distance is infinite or finite

    Matrix<W> dist(size(), size(), W());
    Matrix<int> inf(size(), size(), 1);
    // inf matrix:
    // 1 - +inf
    // 0 - finite
    // -1 - -inf

    for(std::size_t i=0; i<size(); i++){
        dist.at(i,i) = W();
        inf.at(i,i) = 0;

        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            if(i != it->node){
                dist.at(i,it->node) = it->weight;
                inf.at(i,it->node) = 0;
            }
    }

    for(std::size_t k=0; k < size(); k++)
        for(std::size_t v=0; v < size(); v++)
            for(std::size_t u=0; u < size(); u++)
                if(inf.at(v,k) == 0 && inf.at(k,u) == 0)
                    if(dist.at(v,k) + dist.at(k,u) < dist.at(v,u) || inf.at(v,u) == 1){
                        dist.at(v,u) = dist.at(v,k) + dist.at(k,u);
                        inf.at(v,u) = 0;
                    }

    // detect negative cycle
    bool neg_cycle = false;
    for(std::size_t i=0; i < size(); i++)
        if(dist.at(i,i) < W()){
            neg_cycle = true;
            break;
        }

    if(neg_cycle){
        // find all nodes reachable by negative cycles and set their dist to negative inf
        for(std::size_t k=0; k < size(); k++)
            for(std::size_t v=0; v < size(); v++)
                for(std::size_t u=0; u < size(); u++)
                    if(inf.at(v,k) == 0 && inf.at(k,u) == 0 && inf.at(v,u) == 0){
                        if(dist.at(v,k) + dist.at(k,u) < dist.at(v,u))
                            inf.at(v,u) = -1;
                    }
                    else if(inf.at(v,k) != 1 && inf.at(k,u) != 1 && inf.at(v,u) != 1){
                        if(inf.at(v,k) == -1 || inf.at(k,u) == -1)
                            inf.at(v,u) = -1;
                    }
    }

    return std::make_pair(dist, inf);
}
template<class T, class W>
std::vector<std::vector<std::size_t> > WeightedGraph<T,W>::FloydWarshallPaths(){
    // returns paths with finite distance

    Matrix<W> dist(size(), size(), W());
    Matrix<std::size_t> parent(size(), size(), -1);
    Matrix<int> inf(size(), size(), 1);
    // inf matrix:
    // 1 - +inf
    // 0 - finite
    // -1 - -inf

    for(std::size_t i=0; i<size(); i++){
        dist.at(i,i) = W();
        inf.at(i,i) = 0;

        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            if(i != it->node){
                dist.at(i,it->node) = it->weight;
                inf.at(i,it->node) = 0;
                parent.at(i,it->node) = i;
            }
    }

    for(std::size_t k=0; k < size(); k++)
        for(std::size_t v=0; v < size(); v++)
            for(std::size_t u=0; u < size(); u++)
                if(inf.at(v,k) == 0 && inf.at(k,u) == 0)
                    if(dist.at(v,k) + dist.at(k,u) < dist.at(v,u) || inf.at(v,u) == 1){
                        dist.at(v,u) = dist.at(v,k) + dist.at(k,u);
                        inf.at(v,u) = 0;
                        parent.at(v,u) = parent.at(k,u);
                    }

    // detect negative cycle
    bool neg_cycle = false;
    for(std::size_t i=0; i < size(); i++)
        if(dist.at(i,i) < W()){
            neg_cycle = true;
            break;
        }
    if(neg_cycle){
        // find all nodes reachable by negative cycles and set their dist to negative inf
        for(std::size_t k=0; k < size(); k++)
            for(std::size_t v=0; v < size(); v++)
                for(std::size_t u=0; u < size(); u++)
                    if(inf.at(v,k) == 0 && inf.at(k,u) == 0 && inf.at(v,u) == 0){
                        if(dist.at(v,k) + dist.at(k,u) < dist.at(v,u))
                            inf.at(v,u) = -1;
                    }
                    else if(inf.at(v,k) != 1 && inf.at(k,u) != 1 && inf.at(v,u) != 1){
                        if(inf.at(v,k) == -1 || inf.at(k,u) == -1)
                            inf.at(v,u) = -1;
                    }
    }

    std::vector<std::vector<std::size_t> > result;
    // construct paths
    for(std::size_t v=0; v < size(); v++)
        for(std::size_t u=0; u < size(); u++){
            if(inf.at(v,u) == 0){
                std::vector<std::size_t> path;
                std::size_t i=v, j=u;
                while(i != j){
                    path.push_back(j);
                    j = parent.at(i,j);
                }
                path.push_back(j);
                std::reverse(path.begin(), path.end());
                result.push_back(path);
            }
        }

    return result;
}


template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::travellingSalesmanProblem(std::size_t start){
    // shortest Hamiltonian cycle

    std::vector<std::size_t> result;
    if(size() > 0){
        bool* visited = new bool[size()];
        for(std::size_t i=0; i<size(); i++)
            visited[i] = false;

        std::vector<std::size_t> nodes;
        W dist = W(), min_dist = W();
        bool found_sth = false;
        innerTravellingSalesmanProblem(start, start, visited, 1, dist, min_dist, found_sth, nodes, result);

        delete[] visited;
    }
    return result;
}
template<class T, class W>
void WeightedGraph<T,W>::innerTravellingSalesmanProblem(std::size_t node, std::size_t start,
                                     bool* visited, std::size_t counter,
                                     W& dist, W& min_dist, bool& found_sth,
                                     std::vector<std::size_t>& nodes,
                                     std::vector<std::size_t>& result){
    visited[node] = true;
    nodes.push_back(node);

    if(counter < size()){
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(visited[it->node] == false){
                W temp = dist;
                dist = dist + it->weight;
                innerTravellingSalesmanProblem(it->node, start, visited, counter+1, dist, min_dist, found_sth, nodes, result);
                dist = temp;
            }
    }
    else{
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(it->node == start){ // cycle
                W temp = dist;
                dist = dist + it->weight;
                if(dist < min_dist || found_sth == false){
                    min_dist = dist;
                    found_sth = true;

                    nodes.push_back(start);
                    result = nodes;
                    nodes.pop_back();
                }
                dist = temp;
                break;
            }
    }

    visited[node] = false;
    nodes.pop_back();
}

template<class T, class W>
std::vector<std::size_t> WeightedGraph<T,W>::shortestHamiltonianPath(std::size_t start){
    std::vector<std::size_t> result;

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    std::vector<std::size_t> nodes;
    W dist = W(), min_dist = W();
    bool found_sth = false;
    if(start == -1){
        for(std::size_t i=0; i<size(); i++)
            innerShortestHamiltonianPath(i, visited, 1, dist, min_dist, found_sth, nodes, result);
    }
    else
        innerShortestHamiltonianPath(start, visited, 1, dist, min_dist, found_sth, nodes, result);

    delete[] visited;
    return result;
}
template<class T, class W>
void WeightedGraph<T,W>::innerShortestHamiltonianPath(std::size_t node,
                                     bool* visited, std::size_t counter,
                                     W& dist, W& min_dist, bool& found_sth,
                                     std::vector<std::size_t>& nodes,
                                     std::vector<std::size_t>& result){
    visited[node] = true;
    nodes.push_back(node);

    if(counter < size()){
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(visited[it->node] == false){
                W temp = dist;
                dist = dist + it->weight;
                innerShortestHamiltonianPath(it->node, visited, counter+1, dist, min_dist, found_sth, nodes, result);
                dist = temp;
            }
    }
    else{ // path
        if(dist < min_dist || found_sth == false){
            min_dist = dist;
            found_sth = true;

            result = nodes;
        }
    }
    visited[node] = false;
    nodes.pop_back();
}


template<class T, class W>
std::pair<std::vector<std::size_t>,std::vector<std::size_t> > WeightedGraph<T,W>::bipartiteSets(){
    // graph must be undirected

    std::pair<std::vector<std::size_t>,std::vector<std::size_t> > result;

    char* color = new char[size()];
    for(std::size_t i=0; i < size(); i++)
        color[i] = 0;

    std::queue<std::size_t> q;
    for(std::size_t i=0; i < size(); i++)
        if(color[i] == 0){
            q.push(i);
            color[i] = 'r';
            result.first.push_back(i);

            while(!q.empty()){
                std::size_t v = q.front();
                q.pop();

                for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                    if(color[it->node] == 0){
                        if(color[v] == 'r'){
                            color[it->node] = 'b';
                            result.second.push_back(it->node);
                        }
                        else{
                            color[it->node] = 'r';
                            result.first.push_back(it->node);
                        }
                        q.push(it->node);
                    }
                    else if(color[v] == color[it->node]){
                        delete[] color;
                        return std::pair<std::vector<std::size_t>,std::vector<std::size_t> >();
                    }
                }
            }
        }
    delete[] color;
    return result;
}

template<class T, class W>
std::vector<std::pair<std::size_t,std::size_t> > WeightedGraph<T,W>::maxWeightHungarianAlgorithm(){
    // max-weight max-cardinality bipartite matching
    // graph must be undirected and bipartite
    // W type must be signed type

    std::pair<std::vector<std::size_t>, std::vector<std::size_t> > bs = bipartiteSets();

    std::vector<std::pair<std::size_t,std::size_t> > result;
    if(bs.first.size() > 0 && bs.second.size() > 0){
        WeightedGraph<T,W> completeB(*this);

        // add dummy nodes
        while(bs.first.size() < bs.second.size()){
            bs.first.push_back(completeB.size());
            completeB.addNode(T());
        }
        while(bs.second.size() < bs.first.size()){
            bs.second.push_back(completeB.size());
            completeB.addNode(T());
        }

        // calculate lower bound for weight of dummy edges
        // -sum(abs(w)) - 1
        W dummy_weight = W();
        for(auto it = bs.first.begin(); it != bs.first.end(); it++)
            for(auto itn = nodes.at(*it).neighbours.begin(); itn != nodes.at(*it).neighbours.end(); itn++){
                if(itn->weight > W())
                    dummy_weight = dummy_weight - itn->weight;
                else
                    dummy_weight = dummy_weight + itn->weight;
            }
        --dummy_weight;

        // add missing edges for making completeB graph complete bipartite
        for(auto it = bs.first.begin(); it != bs.first.end(); it++)
            for(auto it2 = bs.second.begin(); it2 != bs.second.end(); it2++)
                if(!completeB.existsDirectedEdge(*it, *it2))
                    completeB.addEdge(*it, *it2, dummy_weight);


        // set initial labels
        W* label = new W[completeB.size()];
        for(auto it = bs.first.begin(); it != bs.first.end(); it++){
            W max = nodes.at(*it).neighbours.front().weight;
            for(auto it2 = completeB.nodes.at(*it).neighbours.begin(); it2 != completeB.nodes.at(*it).neighbours.end(); it2++)
                if(it2->weight > max)
                    max = it2->weight;
            label[*it] = max;
        }
        for(auto it = bs.second.begin(); it != bs.second.end(); it++)
            label[*it] = W();


        std::size_t* match = new std::size_t[completeB.size()];
        std::size_t* parent = new std::size_t[completeB.size()];
        for(std::size_t i=0; i<completeB.size(); i++)
            match[i] = -1;

        for(auto it = bs.first.begin(); it != bs.first.end();){
            std::queue<std::size_t> q;
            q.push(*it);
            bool found = false;
            for(std::size_t i=0; i < completeB.size(); i++)
                parent[i] = -1;

            // find augmenting path
            while(!q.empty()){
                std::size_t v = q.front();
                q.pop();

                for(auto it2 = completeB.nodes.at(v).neighbours.begin(); it2 != completeB.nodes.at(v).neighbours.end(); it2++)
                    if(parent[it2->node] == -1 && parent[v] != it2->node &&
                       label[v] + label[it2->node] == it2->weight){ // tight edge
                        parent[it2->node] = v;
                        if(match[it2->node] == -1){
                            // augment
                            std::size_t u = it2->node;
                            while(u != -1){
                                match[u] = parent[u];
                                match[parent[u]] = u;
                                u = parent[parent[u]];
                            }
                            found = true;
                            break;
                        }
                        else{
                            std::size_t u = match[it2->node];
                            parent[u] = it2->node;
                            q.push(u);
                        }
                    }
                if(found){
                    it++;
                    break;
                }
            }
            // not found - update labels
            if(!found){
                // calculate delta
                // delta = min{l(s) + l(y) - w(s,y)}
                W delta;
                bool initialized = false;

                for(auto itf = bs.first.begin(); itf != bs.first.end(); itf++)
                    for(auto itn = completeB.nodes.at(*itf).neighbours.begin(); itn != completeB.nodes.at(*itf).neighbours.end(); itn++)
                        if((parent[*itf] != -1 || *itf == *it) && parent[itn->node] == -1){ // visited from first and not visited from second
                            W new_delta = label[*itf] + label[itn->node] - itn->weight;
                            if(new_delta < delta || !initialized){
                                delta = new_delta;
                                initialized = true;
                            }
                        }

                // update labels
                for(auto itf = bs.first.begin(); itf != bs.first.end(); itf++)
                    if(parent[*itf] != -1 || *itf == *it)
                        label[*itf] = label[*itf] - delta;
                for(auto its = bs.second.begin(); its != bs.second.end(); its++)
                    if(parent[*its] != -1)
                        label[*its] = label[*its] + delta;
            }
        }

        // collect matching
        for(auto it = bs.first.begin(); it != bs.first.end(); it++)
            if(*it < size() && match[*it] < size() && match[*it] != -1 && existsDirectedEdge(*it,match[*it]))
                result.push_back(std::make_pair(*it, match[*it]));

        delete[] label;
        delete[] match;
        delete[] parent;
    }
    return result;
}
template<class T, class W>
std::vector<std::pair<std::size_t,std::size_t> > WeightedGraph<T,W>::minWeightHungarianAlgorithm(){
    // min-weight max-cardinality bipartite matching
    // graph must be undirected and bipartite
    // W type must be signed type

    // set all weights opposite and run max-weight HA
    WeightedGraph<T,W> temp(*this);
    for(std::size_t i=0; i<size(); i++)
        for(auto it = temp.nodes.at(i).neighbours.begin(); it != temp.nodes.at(i).neighbours.end(); it++)
            it->weight = -it->weight;
    return temp.maxWeightHungarianAlgorithm();
}


template<class T, class W>
WeightedGraph<T,W> WeightedGraph<T,W>::KruskalMST(){
    // Minimum Spanning Tree/Forest
    // graph must be undirected

    WeightedGraph<T,W> mst(size(), T());
    for(std::size_t i=0; i<size(); i++)
        mst.nodes.at(i).value = nodes.at(i).value;

    typedef std::pair<std::size_t, std::size_t> Edge;
    typedef std::pair<W, Edge> WEdge;
    std::priority_queue<WEdge, std::vector<WEdge>, std::greater<WEdge> > pq;
    for(std::size_t v=0; v<size(); v++)
        for(auto itn = nodes.at(v).neighbours.begin(); itn != nodes.at(v).neighbours.end(); itn++)
            pq.push(WEdge(itn->weight, Edge(v,itn->node)));

    DisjointSets<std::size_t> ds;
    for(std::size_t i=0; i < size(); i++)
        ds.makeSet(i);

    while(!pq.empty()){
        WEdge wedge = pq.top();
        pq.pop();

        W w = wedge.first;
        std::size_t u = wedge.second.first;
        std::size_t v = wedge.second.second;

        if(ds.findSet(ds.getElement(u)) != ds.findSet(ds.getElement(v))){
            ds.unionSets(ds.getElement(u), ds.getElement(v));
            mst.addEdge(u,v, w);
        }
    }

    return mst;
}
template<class T, class W>
WeightedGraph<T,W> WeightedGraph<T,W>::PrimMST(){
    // Minimum Spanning Tree/Forest
    // graph must be undirected

    WeightedGraph<T,W> mst(size(), T());
    for(std::size_t i=0; i<size(); i++)
        mst.nodes.at(i).value = nodes.at(i).value;

    typedef std::pair<std::size_t, std::size_t> Edge;
    typedef std::pair<W, Edge> WEdge;
    std::priority_queue<WEdge, std::vector<WEdge>, std::greater<WEdge> > pq;

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == false){
            for(auto itn = nodes.at(i).neighbours.begin(); itn != nodes.at(i).neighbours.end(); itn++)
                pq.push(WEdge(itn->weight, Edge(i,itn->node)));
            visited[i] = true;

            while(!pq.empty()){
                WEdge wedge = pq.top();
                pq.pop();

                W w = wedge.first;
                std::size_t u = wedge.second.first;
                std::size_t v = wedge.second.second;

                if(visited[v] == false){
                    mst.addEdge(u,v, w);
                    visited[v] = true;

                    for(auto itn = nodes.at(v).neighbours.begin(); itn != nodes.at(v).neighbours.end(); itn++)
                        if(visited[itn->node] == false)
                            pq.push(WEdge(itn->weight, Edge(v,itn->node)));
                }
            }
        }

    delete[] visited;
    return mst;
}


template<class T, class W>
bool WeightedGraph<T,W>::operator==(const WeightedGraph<T,W>& other){
    return (nodes == other.nodes);
}
template<class T, class W>
bool WeightedGraph<T,W>::operator!=(const WeightedGraph<T,W>& other){
    return !(nodes == other.nodes);
}



// ============================================

template<class T, class W>
void WeightedGraph<T,W>::printNodes(){
    std::size_t i = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++){
        std::cout << i << ": " << it->value << "      neighbours: ";
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            std::cout << it2->node << "(w: " << it2->weight << ") ";
        std::cout << std::endl;
    }
}
template<class T, class W>
void WeightedGraph<T,W>::printValues(){
    std::size_t i = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++){
        std::cout << i << ": " << it->value << std::endl;
    }
}


