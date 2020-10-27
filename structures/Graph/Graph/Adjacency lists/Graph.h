#pragma once

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include "DisjointSets.h"

#include <iostream>

template<class T>
class Graph{
    // simple undirected/directed graph with loops

    struct Node{
        T value;
        std::list<std::size_t> neighbours;

        Node(const T& value){
            this->value = value;
        }
        bool operator==(const Node& other) const{
            return (value == other.value && neighbours == other.neighbours);
        }
    };

    std::vector<Node> nodes;

public:
    Graph();
    Graph(std::size_t size, const T& value);
    Graph(std::initializer_list<T> il);
    Graph(const Graph<T>& other);
    Graph<T>& operator=(const Graph<T>& other);


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

    std::vector<std::size_t> getNeighbours(std::size_t node);

    Graph<T> convertToUndirectedGraph();
    Graph<T> subgraph(const std::vector<std::size_t>& nodes);


    std::size_t degree();
    std::size_t degree2();
    std::size_t degree(std::size_t node);
    std::size_t indegree(std::size_t node);
    std::size_t outdegree(std::size_t node);


    void addNode(const T& value);
    void addDirectedEdge(std::size_t node1, std::size_t node2);
    void addEdge(std::size_t node1, std::size_t node2);

    void removeNode(std::size_t node);
    void removeDirectedEdge(std::size_t node1, std::size_t node2);
    void removeEdge(std::size_t node1, std::size_t node2);


    std::vector<std::size_t> DFS();
    std::vector<std::size_t> DFSstack();
    std::vector<std::size_t> BFS();

    void transpose();
    void square();

    Graph<T> lineGraph();

    std::vector<std::size_t> DFSpath(std::size_t start, std::size_t end);
    std::vector<std::size_t> DFSpath2(std::size_t start, std::size_t end);
    std::vector<std::size_t> BFSpath(std::size_t start, std::size_t end);
    bool existsDFSpath(std::size_t start, std::size_t end);

    bool connectedUndirected();
    bool connectedDirected();
    std::size_t countConnectedComponentsUndirected();
    std::size_t countConnectedComponentsDirected();
    std::vector<Graph<T> > connectedComponentsUndirected();
    std::vector<Graph<T> > connectedComponentsDirected();
    std::vector<Graph<T> > connectedComponents();
    std::vector<Graph<T> > stronglyConnectedComponents();
    std::vector<Graph<T> > KosarajuSCC();
    std::vector<Graph<T> > TarjanSCC();

    Graph<T> DFspanningTrees(std::size_t start=0);
    Graph<T> BFspanningTrees(std::size_t start=0);

    std::vector<std::pair<std::size_t,std::size_t> > bridgesUndirected();
    std::vector<std::pair<std::size_t,std::size_t> > bridgesDirected();
    std::vector<std::pair<std::size_t,std::size_t> > TarjanBridgesUndirected();

    std::vector<std::size_t> articulationPointsUndirected();
    std::vector<std::size_t> articulationPointsDirected();
    std::vector<std::size_t> TarjanArticulationPointsUndirected();

    bool bipartite();
    std::pair<std::vector<std::size_t>,std::vector<std::size_t> > bipartiteSets();

    std::vector<std::pair<std::size_t,std::size_t> > maximumBipartiteMatching();

    bool hasCycleUndirected();
    bool hasCycleDirected();

    std::vector<std::vector<std::size_t> > cyclesUndirected();
    std::vector<std::vector<std::size_t> > cyclesDirected();

    std::pair<bool, std::pair<std::size_t,std::size_t> > hasEulerianPathUndirected();
    std::pair<bool, std::size_t> hasEulerianCycleUndirected();
    std::pair<bool, std::pair<std::size_t,std::size_t> > hasEulerianPathDirected();
    std::pair<bool, std::size_t> hasEulerianCycleDirected();

    std::vector<std::size_t> EulerianPathUndirected();
    std::vector<std::size_t> EulerianCycleUndirected();
    std::vector<std::size_t> EulerianPathDirected();
    std::vector<std::size_t> EulerianCycleDirected();
    std::vector<std::size_t> FleuryEulerianPathUndirected();
    std::vector<std::size_t> FleuryEulerianCycleUndirected();
    std::list<std::size_t> HierholzerEulerianPathUndirected();
    std::list<std::size_t> HierholzerEulerianCycleUndirected();
    std::list<std::size_t> HierholzerEulerianPathDirected();
    std::list<std::size_t> HierholzerEulerianCycleDirected();

    std::vector<std::size_t> HamiltonianPath(std::size_t start=-1);
    std::vector<std::size_t> HamiltonianCycle(std::size_t start=0);
    std::vector<std::vector<std::size_t> > HamiltonianPathsCycles();

    std::vector<std::size_t> topologicalSort();
    std::vector<std::size_t> topologicalSortDFS();

    std::vector<std::pair<std::size_t,std::size_t> > EdmondsBlossom();

    std::vector<std::vector<std::size_t> > vertexColoring();
    std::vector<std::vector<std::size_t> > vertexColoringGreedy();
    std::vector<std::vector<std::size_t> > vertexColoringGreedyLF();
    std::vector<std::vector<std::pair<std::size_t,std::size_t> > > edgeColoring();
    std::vector<std::vector<std::pair<std::size_t,std::size_t> > > edgeColoringGreedyLF();

    std::vector<std::vector<std::size_t> > cliques();
    std::vector<std::vector<std::size_t> > cliques2();
    std::vector<std::size_t> maxClique();


    bool operator==(const Graph<T>& other);
    bool operator!=(const Graph<T>& other);

    void printNodes();
    void printValues();

private:
    void innerDFS(std::size_t node, bool* visited, std::vector<std::size_t>& result);

    std::size_t lineGraphMapHelper(std::map<std::set<std::size_t>, std::size_t>& indexes,
                                    std::size_t v, std::size_t u,
                                    std::size_t& i,
                                    Graph<T>& graph);

    void innerDFSpath(std::size_t start, std::size_t end, bool* visited, std::size_t* path);
    bool innerDFSpath2(std::size_t start, std::size_t end, bool* visited, std::vector<std::size_t>& path);

    void innerConnectedUndirectedDFS(std::size_t node, bool* visited, int& counter);
    void innerCountConnectedComponentsUndirectedDFS(std::size_t node, bool* visited);
    void innerConnectedComponentsUndirected(std::size_t node, bool* visited, std::vector<std::size_t>& nodes);
    void innerStronglyConnectedComponents(std::size_t node, bool* visited, std::vector<std::size_t>& nodes);
    void innerKosarajuSCCDFS1(std::size_t node, bool* visited, std::stack<std::size_t>& nodes_order);
    void innerTarjanSCCDFS(std::size_t node,
                      std::size_t& node_number, std::size_t* nodes_order, std::size_t* low,
                      bool* on_stack, std::stack<std::size_t>& s,
                      std::vector<Graph<T> >& nodes);

    void innerDFspanningTrees(std::size_t node, bool* visited, Graph<T>& tree);

    void innerTarjanBridgesDFS(std::size_t node,
                              std::size_t& node_number, std::size_t* disc, std::size_t* low,
                              std::size_t* parent,
                              std::vector<std::pair<std::size_t,std::size_t> >& result);

    void innerArticulationPointsUndirected(std::size_t node, std::size_t skip_node, bool* visited);
    void innerTarjanArticulationPointsDFS(std::size_t node,
                                      std::size_t node_number, std::size_t* disc, std::size_t* low,
                                      std::size_t* parent, std::vector<std::size_t>& result);


    bool innerCyclesDirected(const std::vector<std::size_t>& scc,
                                   std::size_t node, std::size_t start,
                                   bool* blocked, std::size_t* blocked_map,
                                   std::vector<std::size_t>& path,
                                   std::vector<std::vector<std::size_t> >& result);
    template<class ForwardIt>
    std::list<std::vector<std::size_t> > JohnsonTarjanSCC(ForwardIt begin, ForwardIt end);
    template<class ForwardIt>
    void innerJohnsonTarjanSCCDFS(ForwardIt begin, ForwardIt end, std::size_t node,
                              std::size_t& node_number, std::size_t* nodes_order, std::size_t* low,
                              bool* on_stack, std::stack<std::size_t>& s,
                              std::list<std::vector<std::size_t> >& result);


    void innerEulerianUndirected(std::size_t node, std::vector<std::size_t>& result);
    void innerEulerianDirected(std::size_t node, std::vector<std::size_t>& result);

    void innerFleuryEulerianUndirected(std::size_t v, std::vector<std::size_t>& result);
    void innerFleuryEulerianUndirectedBridges(std::size_t node, std::size_t parent,
                                             std::size_t& node_number, std::size_t* disc, std::size_t* low,
                                             std::vector<std::size_t>& nodes);

    bool innerHierholzerEulerianUndirected(std::size_t node, std::size_t parent, std::size_t start, bool* visited,
                                                      std::list<std::size_t>& result, std::list<std::size_t>::iterator it);
    bool innerHierholzerEulerianDirected(std::size_t node, std::size_t start, bool* visited,
                                                      std::list<std::size_t>& result, std::list<std::size_t>::iterator it);


    bool innerHamiltonianPath(std::size_t node, bool* visited, std::size_t counter, std::vector<std::size_t>& nodes);
    bool innerHamiltonianCycle(std::size_t node, std::size_t start, bool* visited, std::size_t counter, std::vector<std::size_t>& nodes);
    void innerHamiltonianPathsCycles(std::size_t node, std::size_t start, bool* visited, std::size_t counter,
                                 std::vector<std::size_t>& nodes, std::vector<std::vector<std::size_t> >& result);

    bool innerTopologicalSortDFS(std::size_t node, char* visited, std::vector<std::size_t>& result);

    std::size_t EdmondsBlossomFindAugmentingPath(std::size_t start,
                                                       std::size_t* match, std::size_t* parent, std::size_t* base);
    void EdmondsBlossomContractBlossom(std::size_t start, std::size_t u, std::size_t v,
                                             std::size_t* match, std::size_t* parent, std::size_t* base,
                                             std::queue<std::size_t>& q, bool* in_queue);
    void EdmondsBlossomMarkBlossom(std::size_t blossom_base, std::size_t u, bool* in_blossom,
                                         std::size_t* match, std::size_t* parent, std::size_t* base);
    std::size_t EdmondsBlossomLCA(std::size_t u, std::size_t v,
                                std::size_t* match, std::size_t* parent, std::size_t* base);

    Graph<T> edgeColoringLineGraph(std::map<std::size_t, std::pair<std::size_t,std::size_t> >& node_edge_map);
    std::vector<std::vector<std::size_t> > vertexEdgesColoring(std::size_t delta);

    void innerCliques(bool* P, bool* R, bool* X, std::vector<std::vector<std::size_t> >& result);
    void innerCliques2(bool* P, bool* R, bool* X, std::vector<std::vector<std::size_t> >& result);
};



template<class T>
Graph<T>::Graph() {}
template<class T>
Graph<T>::Graph(std::size_t size, const T& value){
    for(std::size_t i=0; i<size; i++){
        nodes.push_back(Node(value));
    }
}
template<class T>
Graph<T>::Graph(std::initializer_list<T> il){
    for(auto it = il.begin(); it != il.end(); it++){
        nodes.push_back(Node(*it));
    }
}
template<class T>
Graph<T>::Graph(const Graph<T>& other){
    nodes = other.nodes;
}
template<class T>
Graph<T>& Graph<T>::operator=(const Graph<T>& other){
    if(this != &other){
        nodes = other.nodes;
    }
    return *this;
}



template<class T>
std::size_t Graph<T>::size(){
    return nodes.size();
}
template<class T>
std::size_t Graph<T>::nodesAmount(){
    return size();
}
template<class T>
std::size_t Graph<T>::directedEdgesAmount(){
    std::size_t amount = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        amount += it->neighbours.size();
    return amount;
}
template<class T>
std::size_t Graph<T>::edgesAmount(){
    std::set<std::set<std::size_t>> edges;

    for(std::size_t i=0; i<nodes.size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            edges.insert(std::set<std::size_t>({i, *it}));

    return edges.size();
}
template<class T>
bool Graph<T>::empty(){
    return (size() == 0);
}
template<class T>
void Graph<T>::clear(){
    nodes.clear();
}


template<class T>
T Graph<T>::getData(std::size_t node){
    return nodes.at(node).value;
}
template<class T>
T& Graph<T>::at(std::size_t node){
    return nodes.at(node).value;
}
template<class T>
void Graph<T>::setData(std::size_t node, const T& value){
    nodes.at(node) = value;
}
template<class T>
bool Graph<T>::existsDirectedEdge(std::size_t node1, std::size_t node2){
    auto it = nodes.at(node1).neighbours.begin();
    auto end = nodes.at(node1).neighbours.end();
    for(; it != end; it++)
        if(*it == node2)
            return true;
    return false;
}

template<class T>
std::vector<std::size_t> Graph<T>::getNeighbours(std::size_t node){
    std::vector<std::size_t> neighbours;
    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
        neighbours.push_back(*it);
    return neighbours;
}

template<class T>
Graph<T> Graph<T>::convertToUndirectedGraph(){
    Graph<T> undig;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        undig.nodes.push_back(Node(it->value));

    int i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++)
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            undig.addEdge(i, *it2);

    return undig;
}

template<class T>
Graph<T> Graph<T>::subgraph(const std::vector<std::size_t>& nodes){
    Graph<T> sg;
    std::map<std::size_t, std::size_t> m;

    std::size_t i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        sg.addNode(this->nodes.at(*it).value);
        m.insert(std::pair<std::size_t,std::size_t>(*it, i++));
    }

    for(auto it = nodes.begin(); it != nodes.end(); it++){
        for(auto it2 = this->nodes.at(*it).neighbours.begin(); it2 != this->nodes.at(*it).neighbours.end(); it2++){
            auto mit = m.find(*it2);
            if(mit != m.end()){
                sg.addDirectedEdge(m.find(*it)->second, mit->second);
            }
        }
    }

    return sg;
}


template<class T>
std::size_t Graph<T>::degree(){
    std::size_t max = 0;
    for(std::size_t i=0; i < size(); i++){
        std::size_t deg = degree(i);
        if(deg > max)
            max = deg;
    }
    return max;
}

template<class T>
std::size_t Graph<T>::degree2(){
    std::size_t* degrees = new std::size_t[size()];
    for(int i=0; i<size(); i++)
        degrees[i] = 0;

    for(int i=0; i<nodes.size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++){
            degrees[i]++;
            degrees[*it]++;
        }

    std::size_t max = 0;
    for(std::size_t i=0; i < size(); i++)
        if(degrees[i] > max)
            max = degrees[i];

    delete[] degrees;
    return max;
}
template<class T>
std::size_t Graph<T>::degree(std::size_t node){
    return indegree(node) + outdegree(node);
}
template<class T>
std::size_t Graph<T>::indegree(std::size_t node){
    std::size_t amount = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            if(*it2 == node)
                amount++;
    }
    return amount;
}
template<class T>
std::size_t Graph<T>::outdegree(std::size_t node){
    return nodes.at(node).neighbours.size();
}




template<class T>
void Graph<T>::addNode(const T& value){
    Node n(value);
    nodes.push_back(n);
}
template<class T>
void Graph<T>::addDirectedEdge(std::size_t node1, std::size_t node2){
    if(!existsDirectedEdge(node1, node2))
        nodes.at(node1).neighbours.push_back(node2);
}
template<class T>
void Graph<T>::addEdge(std::size_t node1, std::size_t node2){
    addDirectedEdge(node1, node2);
    addDirectedEdge(node2, node1);
}


template<class T>
void Graph<T>::removeNode(std::size_t node){
    nodes.erase(nodes.begin() + node);

    for(auto it2 = nodes.begin(); it2 != nodes.end(); it2++)
        for(auto it3 = it2->neighbours.begin(); it3 != it2->neighbours.end();)
            if(*it3 == node){
                auto temp = it3;
                it3++;
                it2->neighbours.erase(temp);
            }
            else{
                if(*it3 > node)
                    (*it3)--;
                it3++;
            }
}
template<class T>
void Graph<T>::removeDirectedEdge(std::size_t node1, std::size_t node2){
    for(auto it = nodes.at(node1).neighbours.begin(); it != nodes.at(node1).neighbours.end();)
        if(*it == node2){
            auto temp = it;
            it++;
            nodes.at(node1).neighbours.erase(temp);
        }
        else
            it++;
}
template<class T>
void Graph<T>::removeEdge(std::size_t node1, std::size_t node2){
    removeDirectedEdge(node1, node2);
    removeDirectedEdge(node2, node1);
}


template<class T>
std::vector<std::size_t> Graph<T>::DFS(){
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
template<class T>
void Graph<T>::innerDFS(std::size_t node, bool* visited, std::vector<std::size_t>& result){
    if(visited[node] == false){
        visited[node] = true;
        result.push_back(node);

        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            innerDFS(*it, visited, result);
    }
}


template<class T>
std::vector<std::size_t> Graph<T>::DFSstack(){
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
                        if(visited[*it] == false)
                            s.push(*it);
                }
            }
        }
    }


    delete[] visited;
    return result;
}

template<class T>
std::vector<std::size_t> Graph<T>::BFS(){
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
                    if(visited[*it] == false){
                        visited[*it] = true;
                        q.push(*it);
                    }
                }
            }
        }
    }

    delete[] visited;
    return result;
}


template<class T>
void Graph<T>::transpose(){
    std::size_t g_size = size();
    std::list<std::size_t>* new_lists = new std::list<std::size_t>[g_size];

    for(int i=0; i<g_size; i++){
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++){
            new_lists[*it].push_back(i);
        }
    }

    for(int i=0; i<g_size; i++)
        nodes.at(i).neighbours = new_lists[i];
    delete[] new_lists;
}

template<class T>
void Graph<T>::square(){
    std::size_t g_size = size();
    std::list<std::size_t>* new_lists = new std::list<std::size_t>[g_size];
    for(int i=0; i<g_size; i++)
        new_lists[i] = nodes.at(i).neighbours;

    for(int i=0; i<g_size; i++){
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++){
            for(auto it2 = nodes.at(*it).neighbours.begin(); it2 != nodes.at(*it).neighbours.end(); it2++){
                // check if new list already contains new neighbour
                bool contains = false;
                for(auto contains_it = new_lists[i].begin(); contains_it != new_lists[i].end(); contains_it++)
                    if(*contains_it == *it2){
                        contains = true;
                        break;
                    }
                if(!contains)
                    new_lists[i].push_back(*it2);
            }
        }
    }

    for(int i=0; i<g_size; i++)
        nodes.at(i).neighbours = new_lists[i];
    delete[] new_lists;
}


template<class T>
Graph<T> Graph<T>::lineGraph(){
    Graph<T> result(edgesAmount(), T());

    std::map<std::set<std::size_t>, std::size_t> indexes;

    std::size_t i=0;

    for(int v=0; v<nodes.size(); v++){
        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
            std::size_t index1 = lineGraphMapHelper(indexes, v,*it, i, result);
            for(auto it2 = nodes.at(*it).neighbours.begin(); it2 != nodes.at(*it).neighbours.end(); it2++){
                if(*it2 != v){
                    std::size_t index2 = lineGraphMapHelper(indexes, *it,*it2, i, result);
                    result.addDirectedEdge(index1, index2);
                }
            }
        }
    }

    return result;
}

template<class T>
std::size_t Graph<T>::lineGraphMapHelper(
                std::map<std::set<std::size_t>, std::size_t>& indexes,
                std::size_t v, std::size_t u,
                std::size_t& i,
                Graph<T>& graph){

    typedef std::set<std::size_t> Edge;

    auto it = indexes.find(Edge({v,u}));
    if(it == indexes.end()){
        it = indexes.insert(indexes.begin(), std::pair<Edge,std::size_t>(Edge({v,u}), i++));
        //graph.setData(i-1, v*10+u); // sets index1'th node value to concat vu to know from what nodes of starting graph it is defined
    }
    return it->second;
}


template<class T>
std::vector<std::size_t> Graph<T>::DFSpath(std::size_t start, std::size_t end){
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

template<class T>
void Graph<T>::innerDFSpath(std::size_t start, std::size_t end, bool* visited, std::size_t* path){
    visited[start] = true;
    if(start != end){
        for(auto it = nodes.at(start).neighbours.begin(); it != nodes.at(start).neighbours.end(); it++){
            if(visited[*it] == false){
                path[*it] = start;
                innerDFSpath(*it, end, visited, path);
            }
        }
    }
}

template<class T>
std::vector<std::size_t> Graph<T>::DFSpath2(std::size_t start, std::size_t end){
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

template<class T>
bool Graph<T>::innerDFSpath2(std::size_t start, std::size_t end, bool* visited, std::vector<std::size_t>& path){
    visited[start] = true;
    path.push_back(start);
    if(start != end){
        bool found = false;
        for(auto it = nodes.at(start).neighbours.begin(); it != nodes.at(start).neighbours.end(); it++){
            if(visited[*it] == false){
                found = found || innerDFSpath2(*it, end, visited, path);
            }
        }
        if(found == false)
            path.pop_back();
        return found;
    }
    return true;
}


template<class T>
std::vector<std::size_t> Graph<T>::BFSpath(std::size_t start, std::size_t end){
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
            if(visited[*it] == false){
                path[*it] = v;
                q.push(*it);
                visited[*it] = true;
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

template<class T>
bool Graph<T>::existsDFSpath(std::size_t start, std::size_t end){
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
                if(visited[*it] == false)
                    s.push(*it);
        }
    }

    delete[] visited;
    return false;
}


template<class T>
bool Graph<T>::connectedUndirected(){
    if(size() > 1){
        int counter = 0;

        bool* visited = new bool[size()];
        for(int i=0; i<size(); i++)
            visited[i] = false;

        innerConnectedUndirectedDFS(0, visited, counter);

        delete[] visited;
        return (counter == size());
    }
    else
        return true;
}
template<class T>
void Graph<T>::innerConnectedUndirectedDFS(std::size_t node, bool* visited, int& counter){
    if(visited[node] == false){
        visited[node] = true;
        counter++;

        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            innerConnectedUndirectedDFS(*it, visited, counter);
    }
}


template<class T>
bool Graph<T>::connectedDirected(){
    if(size() > 1){
        Graph<T> undig = convertToUndirectedGraph();
        return undig.connectedUndirected();
    }
    else
        return true;
}

template<class T>
std::size_t Graph<T>::countConnectedComponentsUndirected(){
    if(size() > 1){
        int counter = 0;

        bool* visited = new bool[size()];
        for(int i=0; i<size(); i++)
            visited[i] = false;

        for(std::size_t i=0; i < size(); i++){
            if(visited[i] == false){
                innerCountConnectedComponentsUndirectedDFS(i, visited);
                counter++;
            }
        }

        delete[] visited;
        return counter;
    }
    else if(size() == 1)
        return 1;
    else
        return 0;
}
template<class T>
void Graph<T>::innerCountConnectedComponentsUndirectedDFS(std::size_t node, bool* visited){
    if(visited[node] == false){
        visited[node] = true;

        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            innerCountConnectedComponentsUndirectedDFS(*it, visited);
    }
}

template<class T>
std::size_t Graph<T>::countConnectedComponentsDirected(){
    if(size() > 1){
        Graph<T> undig = convertToUndirectedGraph();
        return undig.countConnectedComponentsUndirected();
    }
    else if(size() == 1)
        return 1;
    else
        return 0;
}


template<class T>
std::vector<Graph<T> > Graph<T>::connectedComponentsUndirected(){
    if(size() > 0){
        std::vector<Graph<T> > result;

        std::vector<std::size_t> nodes;
        bool* visited = new bool[size()];
        for(int i=0; i<size(); i++)
            visited[i] = false;

        for(std::size_t i=0; i < size(); i++){
            if(visited[i] == false){
                innerConnectedComponentsUndirected(i, visited, nodes);

                std::sort(nodes.begin(), nodes.end());
                result.push_back(subgraph(nodes));
                nodes.clear();
            }
        }

        delete[] visited;
        return result;
    }
    else
        return std::vector<Graph<T> >();
}
template<class T>
void Graph<T>::innerConnectedComponentsUndirected(std::size_t node, bool* visited, std::vector<std::size_t>& nodes){
    if(visited[node] == false){
        visited[node] = true;
        nodes.push_back(node);

        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            innerConnectedComponentsUndirected(*it, visited, nodes);
    }
}

template<class T>
std::vector<Graph<T> > Graph<T>::connectedComponentsDirected(){
    if(size() > 0){
        Graph<T> undig = convertToUndirectedGraph();

        std::vector<Graph<T> > result;

        std::vector<std::size_t> nodes;
        bool* visited = new bool[size()];
        for(int i=0; i<size(); i++)
            visited[i] = false;

        for(std::size_t i=0; i < size(); i++){
            if(visited[i] == false){
                undig.innerConnectedComponentsUndirected(i, visited, nodes);

                std::sort(nodes.begin(), nodes.end());
                result.push_back(subgraph(nodes));
                nodes.clear();
            }
        }

        delete[] visited;
        return result;
    }
    else
        return std::vector<Graph<T> >();
}


template<class T>
std::vector<Graph<T> > Graph<T>::connectedComponents(){
    if(size() > 0){
        std::vector<Graph<T> > result;

        DisjointSets<std::size_t> ds;
        for(std::size_t i=0; i < size(); i++)
            ds.makeSet(i);

        int i=0;
        for(auto it = nodes.begin(); it != nodes.end(); it++, i++)
            for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
                ds.unionSets(ds.getElement(i), ds.getElement(*it2));

        std::vector<std::vector<std::size_t> > nodes;
        std::map<std::size_t, int> m;

        int counter = 0;
        for(std::size_t i=0; i < size(); i++){
            std::size_t node = *ds.findSet(ds.getElement(i));

            auto mit = m.find(node);
            if(mit == m.end()){
                mit = m.insert(std::pair<std::size_t, int>(node, counter++)).first;
                nodes.push_back(std::vector<std::size_t>());
            }
            nodes.at(mit->second).push_back(i);
        }

        for(auto it = nodes.begin(); it != nodes.end(); it++){
            std::sort(it->begin(), it->end());
            result.push_back(subgraph(*it));
        }

        return result;
    }
    else
        return std::vector<Graph<T> >();
}


template<class T>
std::vector<Graph<T> > Graph<T>::stronglyConnectedComponents(){
    if(size() > 0){
        std::vector<Graph<T> > result;

        std::vector<std::size_t> nodes;
        bool* visited = new bool[size()];
        for(int i=0; i<size(); i++)
            visited[i] = false;

        for(std::size_t i=0; i < size(); i++){
            if(visited[i] == false){
                innerStronglyConnectedComponents(i, visited, nodes);

                std::sort(nodes.begin(), nodes.end());
                result.push_back(subgraph(nodes));
                nodes.clear();
            }
        }

        delete[] visited;
        return result;
    }
    else
        return std::vector<Graph<T> >();
}

template<class T>
void Graph<T>::innerStronglyConnectedComponents(std::size_t node, bool* visited, std::vector<std::size_t>& nodes){
    if(visited[node] == false){
        visited[node] = true;
        nodes.push_back(node);

        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(existsDFSpath(*it, node))
                innerStronglyConnectedComponents(*it, visited, nodes);
    }
}

template<class T>
std::vector<Graph<T> > Graph<T>::KosarajuSCC(){
    if(size() > 0){
        std::vector<Graph<T> > result;

        std::vector<std::size_t> nodes;
        bool* visited = new bool[size()];
        for(std::size_t i=0; i < size(); i++)
            visited[i] = false;

        std::stack<std::size_t> nodes_order;

        for(std::size_t i=0; i < size(); i++)
            innerKosarajuSCCDFS1(i, visited, nodes_order);


        Graph<T> transposed(*this);
        transposed.transpose();

        for(std::size_t i=0; i < size(); i++)
            visited[i] = false;

        while(!nodes_order.empty()){
            std::size_t node = nodes_order.top();
            nodes_order.pop();
            if(visited[node] == false){
                transposed.innerConnectedComponentsUndirected(node, visited, nodes);

                std::sort(nodes.begin(), nodes.end());
                result.push_back(subgraph(nodes));
                nodes.clear();
            }
        }

        delete[] visited;
        return result;
    }
    else
        return std::vector<Graph<T> >();
}
template<class T>
void Graph<T>::innerKosarajuSCCDFS1(std::size_t node, bool* visited, std::stack<std::size_t>& nodes_order){
    if(visited[node] == false){
        visited[node] = true;
        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            innerKosarajuSCCDFS1(*it, visited, nodes_order);
        nodes_order.push(node);
    }
}

template<class T>
std::vector<Graph<T> > Graph<T>::TarjanSCC(){
    if(size() > 0){
        std::vector<Graph<T> > result;

        std::size_t* nodes_order = new std::size_t[size()];
        std::size_t* low = new std::size_t[size()];
        bool* on_stack = new bool[size()];
        std::stack<std::size_t> s;
        for(std::size_t i=0; i<size(); i++){
            nodes_order[i] = 0;
            on_stack[i] = false;
        }

        std::size_t node_number = 0;
        for(std::size_t i=0; i < size(); i++){
            if(nodes_order[i] == 0)
                innerTarjanSCCDFS(i, node_number, nodes_order, low, on_stack, s, result);
        }

        delete[] nodes_order;
        delete[] low;
        delete[] on_stack;
        return result;
    }
    else
        return std::vector<Graph<T> >();
}

template<class T>
void Graph<T>::innerTarjanSCCDFS(std::size_t node,
                              std::size_t& node_number, std::size_t* nodes_order, std::size_t* low,
                              bool* on_stack, std::stack<std::size_t>& s,
                              std::vector<Graph<T> >& result){
    node_number++;
    nodes_order[node] = node_number;
    low[node] = node_number;
    s.push(node);
    on_stack[node] = true;

    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++){
        if(nodes_order[*it] == 0){
            innerTarjanSCCDFS(*it, node_number, nodes_order, low, on_stack, s, result);
            low[node] = std::min(low[node], low[*it]);
        }
        else if(on_stack[*it] == true)
            low[node] = std::min(low[node], nodes_order[*it]);
    }

    if(low[node] == nodes_order[node]){
        std::vector<std::size_t> nodes;
        while(!s.empty()){
            std::size_t v = s.top();
            s.pop();
            on_stack[v] = false;
            nodes.push_back(v);
            if(v == node)
                break;
        }
        std::sort(nodes.begin(), nodes.end());
        result.push_back(subgraph(nodes));
    }
}


template<class T>
Graph<T> Graph<T>::DFspanningTrees(std::size_t start){
    Graph<T> trees;
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
template<class T>
void Graph<T>::innerDFspanningTrees(std::size_t node, bool* visited, Graph<T>& trees){
    visited[node] = true;
    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
        if(visited[*it] == false){
            trees.addDirectedEdge(node, *it);
            innerDFspanningTrees(*it, visited, trees);
        }
}

template<class T>
Graph<T> Graph<T>::BFspanningTrees(std::size_t start){
    Graph<T> trees;
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
            if(visited[*it] == false){
                q.push(*it);
                visited[*it] = true;
                trees.addDirectedEdge(v,*it);
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
                    if(visited[*it] == false){
                        q.push(*it);
                        visited[*it] = true;
                        trees.addDirectedEdge(v,*it);
                    }
            }
        }
    }

    return trees;
}


template<class T>
std::vector<std::pair<std::size_t,std::size_t> > Graph<T>::bridgesUndirected(){
    std::size_t cc_amount = countConnectedComponentsUndirected();

    std::vector<std::pair<std::size_t,std::size_t> > result;

    Graph<T> temp(*this);
    std::size_t i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++)
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            if(i < *it2){
                temp.removeEdge(i,*it2);

                std::size_t cc_amount2 = temp.countConnectedComponentsUndirected();
                if(cc_amount2 > cc_amount)
                    result.push_back(std::pair<std::size_t,std::size_t>(i,*it2));

                temp.addEdge(i,*it2);
            }

    return result;
}
template<class T>
std::vector<std::pair<std::size_t,std::size_t> > Graph<T>::bridgesDirected(){
    std::size_t cc_amount = countConnectedComponentsDirected();

    std::vector<std::pair<std::size_t,std::size_t> > result;

    Graph<T> temp(*this);
    std::size_t i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++)
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++){
            temp.removeDirectedEdge(i,*it2);

            std::size_t cc_amount2 = temp.countConnectedComponentsDirected();
            if(cc_amount2 > cc_amount)
                result.push_back(std::pair<std::size_t,std::size_t>(i,*it2));

            temp.addDirectedEdge(i,*it2);
        }

    return result;
}

template<class T>
std::vector<std::pair<std::size_t,std::size_t> > Graph<T>::TarjanBridgesUndirected(){
    if(size() > 0){
        std::vector<std::pair<std::size_t,std::size_t> > result;

        std::size_t* disc = new std::size_t[size()];
        std::size_t* low = new std::size_t[size()];
        std::size_t* parent = new std::size_t[size()];
        for(std::size_t i=0; i<size(); i++){
            disc[i] = 0;
            parent[i] = -1;
        }

        std::size_t node_number = 0;
        for(std::size_t i=0; i < size(); i++){
            if(disc[i] == 0)
                innerTarjanBridgesDFS(i, node_number, disc, low, parent, result);
        }

        delete[] disc;
        delete[] low;
        delete[] parent;
        return result;
    }
    else
        return std::vector<std::pair<std::size_t,std::size_t> >();
}
template<class T>
void Graph<T>::innerTarjanBridgesDFS(std::size_t node,
                              std::size_t& node_number, std::size_t* disc, std::size_t* low,
                              std::size_t* parent,
                              std::vector<std::pair<std::size_t,std::size_t> >& result){
    node_number++;
    disc[node] = node_number;
    low[node] = node_number;

    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++){
        if(disc[*it] == 0){
            parent[*it] = node;
            innerTarjanBridgesDFS(*it, node_number, disc, low, parent, result);
            low[node] = std::min(low[node], low[*it]);
        }
        else if(parent[node] != *it)
            low[node] = std::min(low[node], disc[*it]);
    }

    if(low[node] == disc[node] && parent[node] != -1){
        result.push_back(std::pair<std::size_t,std::size_t>(parent[node], node));
    }
}


template<class T>
std::vector<std::size_t> Graph<T>::articulationPointsUndirected(){
    std::vector<std::size_t> result;

    if(size() > 0){
        std::size_t cc_amount = countConnectedComponentsUndirected();
        bool* visited = new bool[size()];

        for(std::size_t skip_node=0; skip_node < size(); skip_node++){
            for(std::size_t i=0; i < size(); i++)
                visited[i] = false;

            std::size_t cc_amount2 = 0;
            for(std::size_t i=0; i < size(); i++){
                if(i != skip_node && visited[i] == false){
                    innerArticulationPointsUndirected(i, skip_node, visited);
                    cc_amount2++;
                }
            }

            if(cc_amount2 > cc_amount)
                result.push_back(skip_node);
        }
        delete[] visited;
    }
    return result;
}
template<class T>
void Graph<T>::innerArticulationPointsUndirected(std::size_t node, std::size_t skip_node, bool* visited){
    if(visited[node] == false){
        visited[node] = true;

        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            if(*it != skip_node)
                innerArticulationPointsUndirected(*it, skip_node, visited);
    }
}

template<class T>
std::vector<std::size_t> Graph<T>::articulationPointsDirected(){
    std::vector<std::size_t> result;

    if(size() > 0){
        Graph<T> undig = convertToUndirectedGraph();
        std::size_t cc_amount = undig.countConnectedComponentsUndirected();
        bool* visited = new bool[size()];

        for(std::size_t skip_node=0; skip_node < size(); skip_node++){
            for(std::size_t i=0; i < size(); i++)
                visited[i] = false;

            std::size_t cc_amount2 = 0;
            for(std::size_t i=0; i < size(); i++){
                if(i != skip_node && visited[i] == false){
                    undig.innerArticulationPointsUndirected(i, skip_node, visited);
                    cc_amount2++;
                }
            }

            if(cc_amount2 > cc_amount)
                result.push_back(skip_node);
        }
        delete[] visited;
    }
    return result;
}

template<class T>
std::vector<std::size_t> Graph<T>::TarjanArticulationPointsUndirected(){
    if(size() > 0){
        std::vector<std::size_t> result;

        std::size_t* disc = new std::size_t[size()];
        std::size_t* low = new std::size_t[size()];
        std::size_t* parent = new std::size_t[size()];
        for(std::size_t i=0; i<size(); i++){
            disc[i] = 0;
            parent[i] = -1;
        }

        std::size_t node_number = 0;
        for(std::size_t i=0; i < size(); i++){
            if(disc[i] == 0)
                innerTarjanArticulationPointsDFS(i, node_number, disc, low, parent, result);
        }

        delete[] disc;
        delete[] low;
        delete[] parent;

        return result;
    }
    else
        return std::vector<std::size_t>();
}
template<class T>
void Graph<T>::innerTarjanArticulationPointsDFS(std::size_t node,
                                      std::size_t node_number, std::size_t* disc, std::size_t* low,
                                      std::size_t* parent, std::vector<std::size_t>& result){
    node_number++;
    disc[node] = node_number;
    low[node] = node_number;

    bool found_artp = false;
    std::size_t children = 0;
    for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++){
        if(disc[*it] == 0){
            children++;
            parent[*it] = node;
            innerTarjanArticulationPointsDFS(*it, node_number, disc, low, parent, result);
            low[node] = std::min(low[node], low[*it]);

            if(!found_artp){
                // non root
                if(parent[node] != -1 && disc[node] <= low[*it]){
                    result.push_back(node);
                    found_artp = true;
                }
                // root
                else if(parent[node] == -1 && children > 1){
                    result.push_back(node);
                    found_artp = true;
                }
            }
        }
        else if(parent[node] != *it)
            low[node] = std::min(low[node], disc[*it]);
    }
}


template<class T>
bool Graph<T>::bipartite(){
    // graph must be undirected

    char* color = new char[size()];
    for(std::size_t i=0; i < size(); i++)
        color[i] = 0;

    std::queue<std::size_t> q;

    for(std::size_t i=0; i < size(); i++)
        if(color[i] == 0){
            q.push(i);
            color[i] = 'r';

            while(!q.empty()){
                std::size_t v = q.front();
                q.pop();

                for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                    if(color[*it] == 0){
                        if(color[v] == 'r')
                            color[*it] = 'b';
                        else
                            color[*it] = 'r';
                        q.push(*it);
                    }
                    else if(color[v] == color[*it]){
                        delete[] color;
                        return false;
                    }
                }
            }
        }
    delete[] color;
    return true;
}
template<class T>
std::pair<std::vector<std::size_t>,std::vector<std::size_t> > Graph<T>::bipartiteSets(){
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
                    if(color[*it] == 0){
                        if(color[v] == 'r'){
                            color[*it] = 'b';
                            result.second.push_back(*it);
                        }
                        else{
                            color[*it] = 'r';
                            result.first.push_back(*it);
                        }
                        q.push(*it);
                    }
                    else if(color[v] == color[*it]){
                        delete[] color;
                        return std::pair<std::vector<std::size_t>,std::vector<std::size_t> >();
                    }
                }
            }
        }
    delete[] color;
    return result;
}


template<class T>
std::vector<std::pair<std::size_t,std::size_t> > Graph<T>::maximumBipartiteMatching(){
    std::vector<std::pair<std::size_t,std::size_t> > result;

    auto bv = bipartiteSets();
    if(bv == std::pair<std::vector<std::size_t>,std::vector<std::size_t> >())
        return result;

    std::size_t* pair = new std::size_t[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i < size(); i++)
        pair[i] = -1;

    for(auto it = bv.first.begin(); it != bv.first.end(); it++){
        std::queue<std::size_t> q;
        q.push(*it);
        bool found = false;
        for(std::size_t i=0; i < size(); i++)
            parent[i] = -1;

        while(!q.empty()){
            std::size_t v = q.front();
            q.pop();

            for(auto it2 = nodes.at(v).neighbours.begin(); it2 != nodes.at(v).neighbours.end(); it2++)
                if(parent[*it2] == -1 && parent[v] != *it2){
                    parent[*it2] = v;
                    if(pair[*it2] == -1){
                        std::size_t u = *it2;
                        while(u != -1){
                            pair[u] = parent[u];
                            pair[parent[u]] = u;
                            u = parent[parent[u]];
                        }
                        found = true;
                        break;
                    }
                    else{
                        std::size_t u = pair[*it2];
                        parent[u] = *it2;
                        q.push(u);
                    }
                }
            if(found)
                break;
        }
    }

    for(auto it = bv.first.begin(); it != bv.first.end(); it++)
        if(pair[*it] != -1)
            result.push_back(std::pair<std::size_t,std::size_t>(*it, pair[*it]));

    delete[] pair;
    delete[] parent;
    return result;
}

template<class T>
bool Graph<T>::hasCycleUndirected(){
    bool* visited = new bool[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    std::stack<std::size_t> s;
    for(int i=0; i < size(); i++){
        if(visited[i] == false){
            s.push(i);
            parent[i] = -1;

            while(!s.empty()){
                std::size_t v = s.top();
                s.pop();

                if(visited[v] == false){
                    visited[v] = true;

                    for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
                        if(*it != parent[v])
                            if(visited[*it] == false){
                                s.push(*it);
                                parent[*it] = v;
                            }
                            else{
                                delete[] visited;
                                delete[] parent;
                                return true;
                            }
                }
            }
        }
    }
    delete[] visited;
    delete[] parent;
    return false;
}
template<class T>
bool Graph<T>::hasCycleDirected(){
    // 'w' (white) - not visited
    // 'g' (gray) - processing
    // 'b' (black) - done
    char* visited = new char[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = 'w';

    std::stack<std::size_t> s;
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == 'w'){
            s.push(i);

            while(!s.empty()){
                std::size_t v = s.top();

                if(visited[v] == 'w'){
                    visited[v] = 'g';
                    for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                        if(visited[*it] == 'w'){
                            s.push(*it);
                        }
                        else if(visited[*it] == 'g'){
                            delete[] visited;
                            return true;
                        }
                    }
                }
                else{
                    visited[v] = 'b';
                    s.pop();
                }
            }
        }
    delete[] visited;
    return false;
}


template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::cyclesUndirected(){
    // this method finds cycle basis

    std::vector<std::vector<std::size_t> > result;

    bool* visited = new bool[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    std::stack<std::size_t> s;
    for(int i=0; i < size(); i++){

        // if you want all cycles (not only cycle basis)
        // (there will be some duplicates)
        // uncomment 2 lines below
        // for(std::size_t j=0; j<size(); j++)
        //    visited[j] = false;

        if(visited[i] == false){
            s.push(i);
            parent[i] = -1;

            while(!s.empty()){
                std::size_t v = s.top();
                s.pop();

                if(visited[v] == false){
                    visited[v] = true;

                    for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++)
                        if(*it != parent[v])
                            if(visited[*it] == false){
                                s.push(*it);
                                parent[*it] = v;
                            }
                            else{
                                result.push_back(std::vector<std::size_t>());
                                result.back().push_back(*it);
                                std::size_t u = v;
                                while(u != *it){
                                    result.back().push_back(u);
                                    u = parent[u];
                                }
                            }
                }
            }
        }
    }
    delete[] visited;
    delete[] parent;
    return result;
}

template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::cyclesDirected(){
    // Johnson's algorithm for finding all simple cycles in directed graph

    std::vector<std::vector<std::size_t> > result;

    bool* blocked = new bool[size()];
    std::size_t* blocked_map = new std::size_t[size()];
    for(std::size_t i=0; i < size(); i++){
        blocked[i] = false;
        blocked_map[i] = -1;
    }

    std::vector<std::size_t> nodes(size());
    for(std::size_t i=0; i<size(); i++)
        nodes.push_back(i);
    auto sccs = JohnsonTarjanSCC(nodes.begin(), nodes.end()); // SCCs with at least 2 elements

    std::vector<std::size_t> path;

    for(auto scc_nodes = sccs.begin(); scc_nodes != sccs.end(); scc_nodes++){
        // find cycles starting and ending at first node of each SCC
        auto node = scc_nodes->begin();
        innerCyclesDirected(*scc_nodes, *node, *node, blocked, blocked_map, path, result);

        // insert SCCs created from actual SCC without first node
        auto new_sccs = JohnsonTarjanSCC(scc_nodes->begin()+1, scc_nodes->end());
        sccs.insert(sccs.end(), new_sccs.begin(), new_sccs.end());
    }

    delete[] blocked;
    delete[] blocked_map;

    // loops
    for(std::size_t i=0; i < size(); i++)
        if(existsDirectedEdge(i,i))
            result.push_back(std::vector<std::size_t>({i}));

    return result;
}

template<class T>
bool Graph<T>::innerCyclesDirected(const std::vector<std::size_t>& scc,
                                   std::size_t node, std::size_t start,
                                   bool* blocked, std::size_t* blocked_map,
                                   std::vector<std::size_t>& path,
                                   std::vector<std::vector<std::size_t> >& result){
    bool found = false;
    blocked[node] = true;
    path.push_back(node);

    for(auto it = scc.begin(); it != scc.end(); it++)
        if(existsDirectedEdge(node, *it)){
            if(*it != start){
                if(blocked[*it] == false)
                    if(innerCyclesDirected(scc, *it, start, blocked, blocked_map, path, result))
                        found = true;
            }
            else{
                // found cycle
                result.push_back(path);
                found = true;
            }
        }
    if(found){
        // unblock
        blocked[node] = false;
        std::size_t u = node;
        while(blocked_map[u] != -1){
            std::size_t temp = u;
            u = blocked_map[u];
            blocked[u] = false;
            blocked_map[temp] = -1;
        }
    }
    else{
        // add to blocked_map
        for(auto it = scc.begin(); it != scc.end(); it++)
            if(existsDirectedEdge(node, *it))
                blocked_map[*it] = node;
    }
    path.pop_back();
    return found;
}
template<class T>
template<class ForwardIt>
std::list<std::vector<std::size_t> > Graph<T>::JohnsonTarjanSCC(ForwardIt begin, ForwardIt end){
    if(size() > 0){
        std::list<std::vector<std::size_t> > result;

        std::size_t* nodes_order = new std::size_t[size()];
        std::size_t* low = new std::size_t[size()];
        bool* on_stack = new bool[size()];
        std::stack<std::size_t> s;
        for(std::size_t i=0; i<size(); i++){
            nodes_order[i] = 0;
            on_stack[i] = false;
        }

        std::size_t node_number = 0;
        for(auto it = begin; it != end; it++){
            if(nodes_order[*it] == 0)
                innerJohnsonTarjanSCCDFS(begin, end, *it, node_number, nodes_order, low, on_stack, s, result);
        }

        delete[] nodes_order;
        delete[] low;
        delete[] on_stack;
        return result;
    }
    else
        return std::list<std::vector<std::size_t> >();
}

template<class T>
template<class ForwardIt>
void Graph<T>::innerJohnsonTarjanSCCDFS(ForwardIt begin, ForwardIt end, std::size_t node,
                              std::size_t& node_number, std::size_t* nodes_order, std::size_t* low,
                              bool* on_stack, std::stack<std::size_t>& s,
                              std::list<std::vector<std::size_t> >& result){
    node_number++;
    nodes_order[node] = node_number;
    low[node] = node_number;
    s.push(node);
    on_stack[node] = true;

    for(auto it = begin; it != end; it++)
        if(existsDirectedEdge(node, *it)){
            if(nodes_order[*it] == 0){
                innerJohnsonTarjanSCCDFS(begin,end, *it, node_number, nodes_order, low, on_stack, s, result);
                low[node] = std::min(low[node], low[*it]);
            }
            else if(on_stack[*it] == true)
                low[node] = std::min(low[node], nodes_order[*it]);
        }

    if(low[node] == nodes_order[node]){
        std::vector<std::size_t> scc_nodes;
        while(!s.empty()){
            std::size_t v = s.top();
            s.pop();
            on_stack[v] = false;
            scc_nodes.push_back(v);
            if(v == node)
                break;
        }
        if(scc_nodes.size() > 1) // Johnson's algorithm doesn't use SCCs with 1 element
            result.push_back(scc_nodes);
    }
}


template<class T>
std::pair<bool, std::pair<std::size_t,std::size_t> > Graph<T>::hasEulerianPathUndirected(){
    // returns
    // if graph has Eulerian path
    // starting vertices

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    int odd_counter = 0;
    std::size_t big_components = 0; // components with at least 2 vertices

    std::pair<std::size_t,std::size_t> odds(-1,-1);

    std::stack<std::size_t> s;
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == false){
            s.push(i);
            big_components++;

            while(!s.empty()){
                std::size_t v = s.top();
                s.pop();

                if(visited[v] == false){
                    visited[v] = true;

                    std::size_t neighbours = 0;
                    for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                        if(visited[*it] == false)
                            s.push(*it);
                        if(v != *it)
                            neighbours++;
                        else // loop
                            neighbours += 2;
                    }
                    if(neighbours == 0)
                        big_components--;
                    else{
                        if(neighbours % 2 != 0){
                            odd_counter++;
                            if(odd_counter == 1)
                                odds.first = v;
                            else if(odd_counter == 2)
                                odds.second = v;
                            else if(odd_counter > 2){
                                delete[] visited;
                                std::pair<std::size_t,std::size_t> none(-1,-1);
                                return std::pair<bool, std::pair<std::size_t,std::size_t> >(false, none);
                            }
                        }
                        if(big_components > 1){
                            delete[] visited;
                            std::pair<std::size_t,std::size_t> none(-1,-1);
                            return std::pair<bool, std::pair<std::size_t,std::size_t> >(false, none);
                        }
                    }
                }
            }
        }

    delete[] visited;
    if(odd_counter == 2)
        return std::pair<bool, std::pair<std::size_t,std::size_t> >(true, odds);
    else{
        std::pair<std::size_t,std::size_t> none(-1,-1);
        return std::pair<bool, std::pair<std::size_t,std::size_t> >(false, none);
    }
}

template<class T>
std::pair<bool, std::size_t> Graph<T>::hasEulerianCycleUndirected(){
    // returns
    // if graph has Eulerian cycle
    // one of possible vertex to start

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    std::size_t big_components = 0; // components with at least 2 vertices

    std::size_t start_vertex = -1;

    std::stack<std::size_t> s;
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == false){
            s.push(i);
            big_components++;

            while(!s.empty()){
                std::size_t v = s.top();
                s.pop();

                if(visited[v] == false){
                    visited[v] = true;

                    std::size_t neighbours = 0;
                    for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                        if(visited[*it] == false)
                            s.push(*it);
                        if(v != *it)
                            neighbours++;
                        else // loop
                            neighbours += 2;
                    }
                    if(neighbours == 0)
                        big_components--;
                    else if(neighbours % 2 != 0 || big_components > 1){
                        delete[] visited;
                        return std::pair<bool, std::size_t>(false, -1);
                    }
                    else if(start_vertex == -1)
                        start_vertex = v;
                }
            }
        }

    delete[] visited;
    return std::pair<bool, std::size_t>(true, start_vertex);
}


template<class T>
std::pair<bool, std::pair<std::size_t,std::size_t> > Graph<T>::hasEulerianPathDirected(){
    // directed graph has Eulerian path if:
    // all edges are in one weakly connected component
    // there is exactly one vertex with outdegree - indegree = 1
    // there is exactly one vertex with indegree - outdegree = 1
    // all other vertices have outdegree = indegree

    // returns
    // if directed graph has Eulerian path
    // start and end vertex

    std::size_t* indegree = new std::size_t[size()];
    std::size_t* outdegree = new std::size_t[size()];
    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++){
        indegree[i] = 0;
        outdegree[i] = 0;
        visited[i] = false;
    }

    Graph<T> undig = convertToUndirectedGraph();

    std::size_t big_components = 0;
    std::stack<std::size_t> s;
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == false){
            s.push(i);
            big_components++;

            while(!s.empty()){
                std::size_t v = s.top();
                s.pop();

                if(visited[v] == false){
                    visited[v] = true;

                    for(auto it = undig.nodes.at(v).neighbours.begin(); it != undig.nodes.at(v).neighbours.end(); it++){
                        if(visited[*it] == false)
                            s.push(*it);
                    }
                    if(undig.nodes.at(v).neighbours.size() == 0)
                        big_components--;
                    else if(big_components > 1){
                        delete[] indegree;
                        delete[] outdegree;
                        delete[] visited;
                        std::pair<std::size_t,std::size_t> none(-1,-1);
                        return std::pair<bool, std::pair<std::size_t,std::size_t> >(false, none);
                    }
                }
            }
        }

    for(std::size_t i=0; i<size(); i++){
        outdegree[i] = nodes.at(i).neighbours.size();
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            indegree[*it]++;
    }

    bool has = true;
    std::size_t inout_counter = 0;
    std::size_t outin_counter = 0;

    std::pair<std::size_t, std::size_t> vertices(-1,-1);

    for(std::size_t node = 0; node < size(); node++){
        if(indegree[node] != outdegree[node]){
            if(indegree[node] - outdegree[node] == 1){
                inout_counter++;
                if(inout_counter > 1){
                    has = false;
                    break;
                }
                vertices.second = node;
            }
            else if(outdegree[node] - indegree[node] == 1){
                outin_counter++;
                if(outin_counter > 1){
                    has = false;
                    break;
                }
                vertices.first = node;
            }
            else{
                has = false;
                break;
            }
        }
    }
    delete[] indegree;
    delete[] outdegree;
    delete[] visited;
    if(has && inout_counter == 1)
        return std::pair<bool, std::pair<std::size_t,std::size_t> >(true, vertices);
    else{
        std::pair<std::size_t,std::size_t> none(-1,-1);
        return std::pair<bool, std::pair<std::size_t,std::size_t> >(false, none);
    }
}


template<class T>
std::pair<bool, std::size_t> Graph<T>::hasEulerianCycleDirected(){
    // directed graph has Eulerian cycle if:
    // all edges are in one strongly connected component
    // (weakly connected component + each vertex in that component has indegree equal outdegre  ->  strongly connected component)
    // all vertices have outdegree = indegree

    // returns
    // if directed graph has Eulerian cycle
    // one of possible vertex to start

    std::size_t* indegree = new std::size_t[size()];
    std::size_t* outdegree = new std::size_t[size()];
    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++){
        indegree[i] = 0;
        outdegree[i] = 0;
        visited[i] = false;
    }

    Graph<T> undig = convertToUndirectedGraph();

    std::size_t start_vertex = -1;

    std::size_t big_components = 0;
    std::stack<std::size_t> s;
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == false){
            s.push(i);
            big_components++;

            while(!s.empty()){
                std::size_t v = s.top();
                s.pop();

                if(visited[v] == false){
                    visited[v] = true;

                    for(auto it = undig.nodes.at(v).neighbours.begin(); it != undig.nodes.at(v).neighbours.end(); it++){
                        if(visited[*it] == false)
                            s.push(*it);
                    }
                    if(undig.nodes.at(v).neighbours.size() == 0)
                        big_components--;
                    else if(big_components > 1){
                        delete[] indegree;
                        delete[] outdegree;
                        delete[] visited;
                        return std::pair<bool, std::size_t>(false, -1);
                    }
                }
            }
        }

    for(std::size_t i=0; i<size(); i++){
        outdegree[i] = nodes.at(i).neighbours.size();
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            indegree[*it]++;
    }

    for(std::size_t node = 0; node < size(); node++){
        if(indegree[node] != outdegree[node]){
            delete[] indegree;
            delete[] outdegree;
            delete[] visited;
            return std::pair<bool, std::size_t>(false, -1);
        }
        else if(start_vertex == -1)
            start_vertex = node;
    }

    delete[] indegree;
    delete[] outdegree;
    delete[] visited;
    return std::pair<bool, std::size_t>(true, start_vertex);
}

template<class T>
std::vector<std::size_t> Graph<T>::EulerianPathUndirected(){
    std::vector<std::size_t> result;

    auto info = hasEulerianPathUndirected();
    if(info.first == true && info.second.first != -1){
        Graph<T> clone(*this);
        clone.innerEulerianUndirected(info.second.first, result);
    }
    return result;
}
template<class T>
std::vector<std::size_t> Graph<T>::EulerianCycleUndirected(){
    std::vector<std::size_t> result;

    auto info = hasEulerianCycleUndirected();
    if(info.first == true && info.second != -1){
        Graph<T> clone(*this);
        clone.innerEulerianUndirected(info.second, result);
    }
    return result;
}
template<class T>
void Graph<T>::innerEulerianUndirected(std::size_t node, std::vector<std::size_t>& result){
    while(nodes.at(node).neighbours.size() > 0){
        std::size_t v = nodes.at(node).neighbours.front();
        nodes.at(node).neighbours.pop_front();
        removeDirectedEdge(v, node);
        innerEulerianUndirected(v, result);
    }
    result.push_back(node);
}

template<class T>
std::vector<std::size_t> Graph<T>::EulerianPathDirected(){
    std::vector<std::size_t> result;

    auto info = hasEulerianPathDirected();
    if(info.first == true && info.second.first != -1){
        Graph<T> clone(*this);
        clone.innerEulerianDirected(info.second.first, result);
        std::reverse(result.begin(), result.end());
    }
    return result;
}
template<class T>
std::vector<std::size_t> Graph<T>::EulerianCycleDirected(){
    std::vector<std::size_t> result;

    auto info = hasEulerianCycleDirected();
    if(info.first == true && info.second != -1){
        Graph<T> clone(*this);
        clone.innerEulerianDirected(info.second, result);
        std::reverse(result.begin(), result.end());
    }
    return result;
}
template<class T>
void Graph<T>::innerEulerianDirected(std::size_t node, std::vector<std::size_t>& result){
    while(nodes.at(node).neighbours.size() > 0){
        std::size_t v = nodes.at(node).neighbours.front();
        nodes.at(node).neighbours.pop_front();
        innerEulerianDirected(v, result);
    }
    result.push_back(node);
}


template<class T>
std::vector<std::size_t> Graph<T>::FleuryEulerianPathUndirected(){
    std::vector<std::size_t> result;

    auto info = hasEulerianPathUndirected();
    if(info.first == true && info.second.first != -1)
        innerFleuryEulerianUndirected(info.second.first, result);
    return result;
}
template<class T>
std::vector<std::size_t> Graph<T>::FleuryEulerianCycleUndirected(){
    std::vector<std::size_t> result;

    auto info = hasEulerianCycleUndirected();
    if(info.first == true && info.second != -1)
        innerFleuryEulerianUndirected(info.second, result);
    return result;
}

template<class T>
void Graph<T>::innerFleuryEulerianUndirected(std::size_t v, std::vector<std::size_t>& result){
    Graph<T> clone(*this);

    std::size_t* disc = new std::size_t[size()];
    std::size_t* low = new std::size_t[size()];

    std::size_t prev = -1;

    while(true){
        result.push_back(v);

        std::size_t node_number = 0;
        for(std::size_t i=0; i<size(); i++)
            disc[i] = 0;

        std::vector<std::size_t> bridges_nodes;
        clone.innerFleuryEulerianUndirectedBridges(v, prev, node_number, disc, low, bridges_nodes);

        std::size_t edges_counter = 0;
        std::size_t next = -1;
        for(auto it = clone.nodes.at(v).neighbours.begin(); it != clone.nodes.at(v).neighbours.end(); it++){
            edges_counter++;
            if(std::find(bridges_nodes.begin(), bridges_nodes.end(), *it) == bridges_nodes.end()){
                next = *it;
                break;
            }
        }
        if(edges_counter != 0){
            if(next != -1){ // exists incident edge that is not bridge
                clone.removeEdge(v, next);
                prev = v;
                v = next;
            }
            else{ // all incident edges are bridges
                for(auto it = clone.nodes.at(v).neighbours.begin(); it != clone.nodes.at(v).neighbours.end(); it++){
                    clone.removeEdge(v, *it);
                    prev = v;
                    v = *it;
                    break;
                }
            }
        }
        else
            break;
    }

    delete[] disc;
    delete[] low;
}
template<class T>
void Graph<T>::innerFleuryEulerianUndirectedBridges(std::size_t node, std::size_t parent,
                                             std::size_t& node_number, std::size_t* disc, std::size_t* low,
                                             std::vector<std::size_t>& nodes){
    node_number++;
    disc[node] = node_number;
    low[node] = node_number;

    for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++){
        if(disc[*it] == 0){
            innerFleuryEulerianUndirectedBridges(*it, node, node_number, disc, low, nodes);
            low[node] = std::min(low[node], low[*it]);
        }
        else if(parent != *it)
            low[node] = std::min(low[node], disc[*it]);
    }

    if(low[node] == disc[node] && parent != -1)
        nodes.push_back(node);
}


// Hierholzer algorithm version with finding simple cycles
// simple cycle is found and then all of its edges are removed
// then algorithm finds next simple cycle starting from one of the nodes of prev cycles and so on
template<class T>
std::list<std::size_t> Graph<T>::HierholzerEulerianPathUndirected(){
    std::list<std::size_t> result;

    auto info = hasEulerianPathUndirected();
    if(info.first == true && info.second.first != -1){
        Graph<T> clone(*this);
        // add new edge
        clone.addEdge(info.second.second, info.second.first);

        bool* visited = new bool[size()];

        // find Eulerian cycle
        result.push_back(info.second.first);
        for(auto it = result.begin(); it != result.end(); it++)
            while(clone.nodes.at(*it).neighbours.size() > 0){
                for(std::size_t i=0; i<size(); i++)
                    visited[i] = false;

                std::size_t v = clone.nodes.at(*it).neighbours.front();
                if(!clone.innerHierholzerEulerianUndirected(v, *it, *it, visited, result, std::next(it))){
                    delete[] visited;
                    return std::list<std::size_t>();
                }
            }
        delete[] visited;

        // convert Eulerian cycle to path
        // erase last element and move all elements from middle of new added edge to front
        result.pop_back();
        auto it = result.begin();
        auto it2 = result.begin();
        it2++;
        for(; it2 != result.end(); it++, it2++)
            if(*it == info.second.second && *it2 == info.second.first ||
               *it == info.second.first && *it2 == info.second.second)
                break;
        result.splice(result.begin(), result, it2, result.end());
    }
    return result;
}
template<class T>
std::list<std::size_t> Graph<T>::HierholzerEulerianCycleUndirected(){
    std::list<std::size_t> result;

    auto info = hasEulerianCycleUndirected();
    if(info.first == true && info.second != -1){
        Graph<T> clone(*this);

        bool* visited = new bool[size()];

        result.push_back(info.second);
        for(auto it = result.begin(); it != result.end(); it++)
            while(clone.nodes.at(*it).neighbours.size() > 0){
                for(std::size_t i=0; i<size(); i++)
                    visited[i] = false;

                std::size_t v = clone.nodes.at(*it).neighbours.front();
                if(!clone.innerHierholzerEulerianUndirected(v, *it, *it, visited, result, std::next(it))){
                    delete[] visited;
                    return std::list<std::size_t>();
                }
            }
        delete[] visited;
    }
    return result;
}
template<class T>
bool Graph<T>::innerHierholzerEulerianUndirected(std::size_t node, std::size_t parent, std::size_t start, bool* visited,
                                                std::list<std::size_t>& result, std::list<std::size_t>::iterator it){
    visited[node] = true;
    result.insert(it, node);

    if(node == start){ // loop
        removeEdge(node, node);
        return true;
    }
    for(auto itn = nodes.at(node).neighbours.begin(); itn != nodes.at(node).neighbours.end(); itn++)
        if(*itn != parent){
            if(*itn == start){
                result.insert(it, *itn);

                auto it2 = --it;
                --it;
                removeEdge(*it, *it2);
                while(*it != start){
                    --it2;
                    --it;
                    removeEdge(*it, *it2);
                }
                return true;
            }
            else if(visited[*itn] == false){
                if(innerHierholzerEulerianUndirected(*itn, node, start, visited, result, it))
                    return true;
            }
        }
    result.erase(--it);
    return false;
}

template<class T>
std::list<std::size_t> Graph<T>::HierholzerEulerianPathDirected(){
    std::list<std::size_t> result;

    auto info = hasEulerianPathDirected();
    if(info.first == true && info.second.first != -1){
        Graph<T> clone(*this);
        // add new edge
        clone.addDirectedEdge(info.second.second, info.second.first);

        bool* visited = new bool[size()];

        // find Eulerian cycle
        result.push_back(info.second.first);
        for(auto it = result.begin(); it != result.end(); it++)
            while(clone.nodes.at(*it).neighbours.size() > 0){
                for(std::size_t i=0; i<size(); i++)
                    visited[i] = false;

                std::size_t v = clone.nodes.at(*it).neighbours.front();
                if(!clone.innerHierholzerEulerianDirected(v, *it, visited, result, std::next(it))){
                    delete[] visited;
                    return std::list<std::size_t>();
                }
            }
        delete[] visited;

        // convert Eulerian cycle to path
        // erase last element and move all elements from middle of new added edge to front
        result.pop_back();
        auto it = result.begin();
        auto it2 = result.begin();
        it2++;
        for(; it2 != result.end(); it++, it2++)
            if(*it == info.second.second && *it2 == info.second.first)
                break;
        result.splice(result.begin(), result, it2, result.end());
    }
    return result;
}
template<class T>
std::list<std::size_t> Graph<T>::HierholzerEulerianCycleDirected(){
    std::list<std::size_t> result;

    auto info = hasEulerianCycleDirected();
    if(info.first == true && info.second != -1){
        Graph<T> clone(*this);

        bool* visited = new bool[size()];

        result.push_back(info.second);
        for(auto it = result.begin(); it != result.end(); it++)
            while(clone.nodes.at(*it).neighbours.size() > 0){
                for(std::size_t i=0; i<size(); i++)
                    visited[i] = false;

                std::size_t v = clone.nodes.at(*it).neighbours.front();
                if(!clone.innerHierholzerEulerianDirected(v, *it, visited, result, std::next(it))){
                    delete[] visited;
                    return std::list<std::size_t>();
                }
            }
        delete[] visited;
    }
    return result;
}
template<class T>
bool Graph<T>::innerHierholzerEulerianDirected(std::size_t node, std::size_t start, bool* visited,
                                                std::list<std::size_t>& result, std::list<std::size_t>::iterator it){
    visited[node] = true;
    result.insert(it, node);

    if(node == start){ // loop
        removeEdge(node, node);
        return true;
    }
    for(auto itn = nodes.at(node).neighbours.begin(); itn != nodes.at(node).neighbours.end(); itn++){
        if(*itn == start){
            result.insert(it, *itn);

            auto it2 = --it;
            --it;
            removeDirectedEdge(*it, *it2);
            while(*it != start){
                --it2;
                --it;
                removeDirectedEdge(*it, *it2);
            }
            return true;
        }
        else if(visited[*itn] == false){
            if(innerHierholzerEulerianDirected(*itn, start, visited, result, it))
                return true;
        }
    }
    result.erase(--it);
    return false;
}


template<class T>
std::vector<std::size_t> Graph<T>::HamiltonianPath(std::size_t start){
    std::vector<std::size_t> nodes;

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    if(start == -1){
        for(std::size_t i=0; i<size(); i++)
            if(innerHamiltonianPath(i, visited, 1, nodes))
                break;
    }
    else
        innerHamiltonianPath(start, visited, 1, nodes);

    delete[] visited;
    return nodes;
}
template<class T>
bool Graph<T>::innerHamiltonianPath(std::size_t node, bool* visited, std::size_t counter, std::vector<std::size_t>& nodes){
    visited[node] = true;
    nodes.push_back(node);

    if(counter < size()){
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(visited[*it] == false)
                if(innerHamiltonianPath(*it, visited, counter+1, nodes))
                    return true;
    }
    else // path
        return true;
    visited[node] = false;
    nodes.pop_back();
    return false;
}
template<class T>
std::vector<std::size_t> Graph<T>::HamiltonianCycle(std::size_t start){
    std::vector<std::size_t> nodes;

    if(size() > 0){
        bool* visited = new bool[size()];
        for(std::size_t i=0; i<size(); i++)
            visited[i] = false;

        innerHamiltonianCycle(start, start, visited, 1, nodes);

        delete[] visited;
    }
    return nodes;
}
template<class T>
bool Graph<T>::innerHamiltonianCycle(std::size_t node, std::size_t start, bool* visited, std::size_t counter, std::vector<std::size_t>& nodes){
    visited[node] = true;
    nodes.push_back(node);

    if(counter < size()){
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(visited[*it] == false)
                if(innerHamiltonianCycle(*it, start, visited, counter+1, nodes))
                    return true;
    }
    else{
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(*it == start){ // cycle
                nodes.push_back(start);
                return true;
            }
    }

    visited[node] = false;
    nodes.pop_back();
    return false;
}

template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::HamiltonianPathsCycles(){
    std::vector<std::vector<std::size_t> > result;

    bool* visited = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = false;

    std::vector<std::size_t> nodes;
    for(std::size_t i=0; i<size(); i++)
        innerHamiltonianPathsCycles(i, i, visited, 1, nodes, result);

    delete[] visited;
    return result;
}
template<class T>
void Graph<T>::innerHamiltonianPathsCycles(std::size_t node, std::size_t start, bool* visited, std::size_t counter,
                                 std::vector<std::size_t>& nodes, std::vector<std::vector<std::size_t> >& result){
    visited[node] = true;
    nodes.push_back(node);

    if(counter < size()){
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(visited[*it] == false)
                innerHamiltonianPathsCycles(*it, start, visited, counter+1, nodes, result);
    }
    else{
        for(auto it = this->nodes.at(node).neighbours.begin(); it != this->nodes.at(node).neighbours.end(); it++)
            if(*it == start){ // cycle
                nodes.push_back(start);
                result.push_back(nodes);
                nodes.pop_back();
                break;
            }
        // path
        result.push_back(nodes);
    }
    visited[node] = false;
    nodes.pop_back();
}


template<class T>
std::vector<std::size_t> Graph<T>::topologicalSort(){
    // Kahn's algorithm
    // graph must be DAG (Directed Acyclic Graph)
    // if graph is cyclic then only part of nodes will be returned

    std::size_t* indegree = new std::size_t[size()];
    for(std::size_t i=0; i < size(); i++)
        indegree[i] = 0;

    for(std::size_t i=0; i < size(); i++)
        for(auto it = nodes.at(i).neighbours.begin(); it != nodes.at(i).neighbours.end(); it++)
            indegree[*it]++;

    std::vector<std::size_t> result;

    std::queue<std::size_t> q;
    for(std::size_t i=0; i < size(); i++)
        if(indegree[i] == 0)
            q.push(i);
    while(!q.empty()){
        std::size_t v = q.front();
        q.pop();
        result.push_back(v);
        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
            indegree[*it]--;
            if(indegree[*it] == 0)
                q.push(*it);
        }
    }

    delete[] indegree;
    return result;
}

template<class T>
std::vector<std::size_t> Graph<T>::topologicalSortDFS(){
    // graph must be DAG (Directed Acyclic Graph)
    // if graph is cyclic then no nodes will be returned

    // 'w' (white) - not visited
    // 'g' (gray) - processing
    // 'b' (black) - done

    char* visited = new char[size()];
    for(std::size_t i=0; i<size(); i++)
        visited[i] = 'w';

    std::vector<std::size_t> result;
    for(std::size_t i=0; i<size(); i++)
        if(visited[i] == 'w')
            if(!innerTopologicalSortDFS(i, visited, result)){
                delete[] visited;
                return std::vector<std::size_t>();
            }

    delete[] visited;
    std::reverse(result.begin(), result.end());
    return result;
}
template<class T>
bool Graph<T>::innerTopologicalSortDFS(std::size_t node, char* visited, std::vector<std::size_t>& result){
    if(visited[node] == 'w'){
        visited[node] = 'g';

        for(auto it = nodes.at(node).neighbours.begin(); it != nodes.at(node).neighbours.end(); it++)
            if(!innerTopologicalSortDFS(*it, visited, result))
                return false;

        visited[node] = 'b';
        result.push_back(node);
    }
    else if(visited[node] == 'g')
        return false;
    return true;
}


template<class T>
std::vector<std::pair<std::size_t,std::size_t> > Graph<T>::EdmondsBlossom(){
    // maximum matching in undirected graph

    std::size_t* match = new std::size_t[size()];
    std::size_t* parent = new std::size_t[size()];
    std::size_t* base = new std::size_t[size()]; // base of blossom
    for(std::size_t i=0; i < size(); i++)
        match[i] = -1;

    for(std::size_t i=0; i<size(); i++)
        if(match[i] == -1){ // exposed vertex
            // clear vars
            for(std::size_t i=0; i<size(); i++){
                parent[i] = -1;
                base[i] = i;
            }

            // find augmenting path
            std::size_t j = EdmondsBlossomFindAugmentingPath(i, match, parent, base);

            // augment
            // each augmentation adds one match (in other words - matches 2 exposed vertices)
            while(j != -1){
                match[j] = parent[j];
                std::size_t temp = match[parent[j]];
                match[parent[j]] = j;
                j = temp;
            }
        }

    // collect matching
    std::vector<std::pair<std::size_t,std::size_t> > result;
    for(std::size_t i=0; i<size(); i++)
        if(match[i] != -1 && i < match[i])
            result.push_back(std::make_pair(i, match[i]));

    delete[] match;
    delete[] parent;
    delete[] base;
    return result;
}
template<class T>
std::size_t Graph<T>::EdmondsBlossomFindAugmentingPath(std::size_t start,
                                                       std::size_t* match, std::size_t* parent, std::size_t* base){
    bool* in_queue = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        in_queue[i] = false;
    std::queue<std::size_t> q;
    q.push(start);

    while(!q.empty()){
        std::size_t u = q.front();
        q.pop();

        for(auto it = nodes.at(u).neighbours.begin(); it != nodes.at(u).neighbours.end(); it++){
            if(base[u] != base[*it] && match[u] != *it){ // u and v can't be in the same blossom and v can't be predecessor of u
                if(*it == start || match[*it] != -1 && parent[match[*it]] != -1) // visited and odd-cycle - found blossom
                    EdmondsBlossomContractBlossom(start, u,*it, match,parent,base, q,in_queue);
                else if(parent[*it] == -1){ // not visited
                    parent[*it] = u;
                    if(match[*it] == -1){ // v is exposed vertex
                        delete[] in_queue;
                        return *it;
                    }
                    else if(!in_queue[match[*it]]){
                        // add to queue match of v
                        in_queue[match[*it]] = true;
                        q.push(match[*it]);
                    }
                }
            }
        }
    }
    delete[] in_queue;
    return -1;
}
template<class T>
void Graph<T>::EdmondsBlossomContractBlossom(std::size_t start, std::size_t u, std::size_t v,
                                             std::size_t* match, std::size_t* parent, std::size_t* base,
                                             std::queue<std::size_t>& q, bool* in_queue){
    std::size_t blossom_base = EdmondsBlossomLCA(u,v, match,parent,base);

    bool* in_blossom = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        in_blossom[i] = false;

    EdmondsBlossomMarkBlossom(blossom_base, u, in_blossom,match,parent,base);
    EdmondsBlossomMarkBlossom(blossom_base, v, in_blossom,match,parent,base);

    if(base[u] != blossom_base)
        parent[u] = v;
    if(base[v] != blossom_base)
        parent[v] = u;

    // set base of all vertices in blossom to blossom base
    for(std::size_t i=0; i<size(); i++)
        if(in_blossom[base[i]] == true){
            base[i] = blossom_base;

            if(!in_queue[i]){
                // adding to queue vertices from blossom that have not been added yet
                in_queue[i] = true;
                q.push(i);
            }
        }
    delete[] in_blossom;
}
template<class T>
void Graph<T>::EdmondsBlossomMarkBlossom(std::size_t blossom_base, std::size_t u, bool* in_blossom,
                                         std::size_t* match, std::size_t* parent, std::size_t* base){
    while(base[u] != blossom_base){
        std::size_t v = match[u];

        in_blossom[base[u]] = true;
        in_blossom[base[v]] = true;

        u = parent[v];
        if(base[u] != blossom_base)
            parent[u] = v;
    }
}
template<class T>
std::size_t Graph<T>::EdmondsBlossomLCA(std::size_t u, std::size_t v,
                  std::size_t* match, std::size_t* parent, std::size_t* base){
    // lowest common ancestor

    bool* contains = new bool[size()];
    for(std::size_t i=0; i<size(); i++)
        contains[i] = false;

    while(true){
        u = base[u];
        contains[u] = true;
        if(match[u] == -1) // root
            break;
        u = parent[match[u]];
    }
    while(true){
        v = base[v];
        if(contains[v]){
            delete[] contains;
            return v;
        }
        v = parent[match[v]];
    }

    delete[] contains;
    return -1;
}


template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::vertexColoring(){
    std::vector<std::vector<std::size_t> > result;
    if(size() > 0){
        Graph<T> undig = convertToUndirectedGraph();

        std::size_t n = size();
        std::size_t b = 1; // base
        std::size_t* color = new std::size_t[n];

        bool found = false;
        while(!found){
            for(std::size_t i=0; i < n; i++)
                color[i] = 0;

            std::size_t counter = 0;
            bool done = false;
            while(!done){
                for(std::size_t i=0; i<n; i++)
                    if(color[i] == b-1)
                        counter++;
                if(counter > 0){
                    // check colors
                    bool collision = false;
                    for(std::size_t i=0; i < n; i++){
                        for(auto itn = undig.nodes.at(i).neighbours.begin(); itn != undig.nodes.at(i).neighbours.end(); itn++){
                            if(i == *itn){ // loop
                                delete[] color;
                                return result;
                            }
                            else if(color[i] == color[*itn]){
                                collision = true;
                                break;
                            }
                        }
                        if(collision)
                            break;
                    }
                    if(collision == false){
                        found = true;
                        break;
                    }
                }
                counter = 0;

                // generate next color combination
                color[n-1]++;
                size_t k = n-1;
                while(color[k] > b-1){
                    color[k] = 0;
                    k--;
                    if(k > n){
                        done = true;
                        break;
                    }
                    color[k]++;
                }
            }
            // increase base
            b++;
        }

        // collect colors to sets
        for(std::size_t i=0; i<n; i++){
            while(result.size() <= color[i])
                result.push_back(std::vector<std::size_t>());
            result.at(color[i]).push_back(i);
        }

        delete[] color;
    }
    return result;
}
template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::vertexColoringGreedy(){
    // result can be not optimal

    std::vector<std::vector<std::size_t> > result;
    if(size() > 0){
        Graph<T> undig = convertToUndirectedGraph();
        std::size_t n = size();

        bool* used_color = new bool[n];
        std::size_t* color = new std::size_t[n];
        for(std::size_t i=0; i<n; i++)
            color[i] = -1;

        for(std::size_t v=0; v < n; v++){
            for(std::size_t i=0; i<n; i++)
                used_color[i] = false;

            for(auto itn = undig.nodes.at(v).neighbours.begin(); itn != undig.nodes.at(v).neighbours.end(); itn++){
                if(v == *itn){ // loop
                    delete[] used_color;
                    delete[] color;
                    return result;
                }
                if(color[*itn] != -1)
                    used_color[color[*itn]] = true;
            }

            std::size_t free_color = 0;
            while(used_color[free_color] == true)
                free_color++;

            color[v] = free_color;
        }

        // collect colors to sets
        for(std::size_t i=0; i<n; i++){
            while(result.size() <= color[i])
                result.push_back(std::vector<std::size_t>());
            result.at(color[i]).push_back(i);
        }

        delete[] used_color;
        delete[] color;
    }
    return result;
}
template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::vertexColoringGreedyLF(){
    // heuristic method - Largest First
    // greedy algorithm coloring in order of descending degrees
    // result can be not optimal

    std::vector<std::vector<std::size_t> > result;
    if(size() > 0){
        Graph<T> undig = convertToUndirectedGraph();
        std::size_t n = size();

        std::size_t* degree = new std::size_t[n];
        for(std::size_t i=0; i<n; i++)
            degree[i] = undig.nodes.at(i).neighbours.size();

        std::priority_queue<std::pair<std::size_t,std::size_t> > pq;
        for(std::size_t i=0; i<n; i++)
            pq.push(std::make_pair(degree[i], i));
        delete[] degree;


        bool* used_color = new bool[n];
        std::size_t* color = new std::size_t[n];
        for(std::size_t i=0; i<n; i++)
            color[i] = -1;

        while(!pq.empty()){
            std::size_t v = pq.top().second;
            pq.pop();

            for(std::size_t i=0; i<n; i++)
                used_color[i] = false;

            for(auto itn = undig.nodes.at(v).neighbours.begin(); itn != undig.nodes.at(v).neighbours.end(); itn++){
                if(v == *itn){ // loop
                    delete[] used_color;
                    delete[] color;
                    return result;
                }
                if(color[*itn] != -1)
                    used_color[color[*itn]] = true;
            }

            std::size_t free_color = 0;
            while(used_color[free_color] == true)
                free_color++;

            color[v] = free_color;
        }

        // collect colors to sets
        for(std::size_t i=0; i<n; i++){
            while(result.size() <= color[i])
                result.push_back(std::vector<std::size_t>());
            result.at(color[i]).push_back(i);
        }

        delete[] used_color;
        delete[] color;
    }
    return result;
}

template<class T>
std::vector<std::vector<std::pair<std::size_t,std::size_t> > > Graph<T>::edgeColoring(){
    std::vector<std::vector<std::pair<std::size_t,std::size_t> > > result;
    if(size() > 0){
        // convert to undirected
        Graph<T> undig = convertToUndirectedGraph();

        // convert undirected to line graph
        std::map<std::size_t, std::pair<std::size_t,std::size_t> > node_edge_map;
        Graph<T> lineGraph = undig.edgeColoringLineGraph(node_edge_map);

        // get max degree
        std::size_t* degree = new std::size_t[size()];
        for(std::size_t i=0; i<size(); i++)
            degree[i] = undig.nodes.at(i).neighbours.size();
        std::size_t delta = *std::max_element(degree, degree+size()); // amount of colors must be delta or delta+1
        delete[] degree;

        // color vertices
        auto cs = lineGraph.vertexEdgesColoring(delta);

        // convert colored vertices to edges
        for(std::size_t i=0; i<cs.size(); i++){
            result.push_back(std::vector<std::pair<std::size_t,std::size_t> >());
            for(auto itc = cs.at(i).begin(); itc != cs.at(i).end(); itc++)
                result.at(i).push_back(node_edge_map.find(*itc)->second);
        }
    }
    return result;
}
template<class T>
Graph<T> Graph<T>::edgeColoringLineGraph(std::map<std::size_t, std::pair<std::size_t,std::size_t> >& node_edge_map){
    Graph<T> lineGraph(edgesAmount(), T());
    typedef std::set<std::size_t> Edge;
    std::map<Edge, std::size_t> edge_node_map;

    std::size_t i=0;
    for(std::size_t v=0; v<nodes.size(); v++){
        for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
            auto itm = edge_node_map.find(Edge({v,*it}));
            if(itm == edge_node_map.end()){
                itm = edge_node_map.insert(edge_node_map.begin(), std::make_pair(Edge({v,*it}), i));
                node_edge_map.insert(node_edge_map.begin(), std::make_pair(i, std::make_pair(v,*it)));
                i++;
            }
            std::size_t index1 = itm->second;

            for(auto it2 = nodes.at(*it).neighbours.begin(); it2 != nodes.at(*it).neighbours.end(); it2++){
                if(*it2 != v){
                    auto itm = edge_node_map.find(Edge({*it,*it2}));
                    if(itm == edge_node_map.end()){
                        itm = edge_node_map.insert(edge_node_map.begin(), std::make_pair(Edge({*it,*it2}), i));
                        node_edge_map.insert(node_edge_map.begin(), std::make_pair(i, std::make_pair(*it,*it2)));
                        i++;
                    }
                    std::size_t index2 = itm->second;
                    lineGraph.addDirectedEdge(index1, index2);
                }
            }
        }
    }
    return lineGraph;
}
template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::vertexEdgesColoring(std::size_t delta){
    // graph is colored by delta or delta+1 colors (Vizing's theorem)

    std::vector<std::vector<std::size_t> > result;
    if(size() > 0){
        Graph<T> undig = convertToUndirectedGraph();
        size_t n = size();
        std::size_t* color = new std::size_t[n];
        bool* color_occur = new bool[delta+1];

        bool found = false;
        for(std::size_t b = delta; b <= delta+1 && !found; b++){
            for(std::size_t i=0; i < n; i++)
                color[i] = 0;

            size_t counter = 0;
            bool done = false;
            while(!done){
                for(std::size_t i=0; i<n; i++)
                    color_occur[i] = false;
                for(std::size_t i=0; i<n; i++)
                    if(color_occur[color[i]] == false){
                        color_occur[color[i]] = true;
                        counter++;
                    }

                if(counter == b){
                    // check colors
                    bool collision = false;
                    for(std::size_t i=0; i < n; i++){
                        for(auto itn = undig.nodes.at(i).neighbours.begin(); itn != undig.nodes.at(i).neighbours.end(); itn++){
                            if(i == *itn){ // loop
                                delete[] color;
                                delete[] color_occur;
                                return result;
                            }
                            else if(color[i] == color[*itn]){
                                collision = true;
                                break;
                            }
                        }
                        if(collision)
                            break;
                    }
                    if(collision == false){
                        found = true;
                        break;
                    }
                }
                counter = 0;

                // generate next color combination
                color[n-1]++;
                size_t k = n-1;
                while(color[k] > b-1){
                    color[k] = 0;
                    k--;
                    if(k > n){
                        done = true;
                        break;
                    }
                    color[k]++;
                }
            }
        }

        // collect colors to sets
        for(std::size_t i=0; i<n; i++){
            while(result.size() <= color[i])
                result.push_back(std::vector<std::size_t>());
            result.at(color[i]).push_back(i);
        }

        delete[] color;
        delete[] color_occur;
    }
    return result;
}

template<class T>
std::vector<std::vector<std::pair<std::size_t,std::size_t> > > Graph<T>::edgeColoringGreedyLF(){
    // result can be not optimal

    std::vector<std::vector<std::pair<std::size_t,std::size_t> > > result;
    if(size() > 0){
        // convert to undirected
        Graph<T> undig = convertToUndirectedGraph();

        // convert undirected to line graph
        std::map<std::size_t, std::pair<std::size_t,std::size_t> > node_edge_map;
        Graph<T> lineGraph = undig.edgeColoringLineGraph(node_edge_map);

        // color vertices
        auto cs = lineGraph.vertexColoringGreedyLF();

        // convert colored vertices to edges
        for(std::size_t i=0; i<cs.size(); i++){
            result.push_back(std::vector<std::pair<std::size_t,std::size_t> >());
            for(auto itc = cs.at(i).begin(); itc != cs.at(i).end(); itc++)
                result.at(i).push_back(node_edge_map.find(*itc)->second);
        }
    }
    return result;
}


template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::cliques(){
    // Bron-Kerbosch algorithm for maximal cliques

    std::vector<std::vector<std::size_t> > result;
    if(size() > 0){
        bool* P = new bool[size()];
        bool* R = new bool[size()];
        bool* X = new bool[size()];
        for(std::size_t i=0; i<size(); i++){
            P[i] = true;
            R[i] = false;
            X[i] = false;
        }

        innerCliques(P,R,X, result);

        delete[] P;
        delete[] R;
        delete[] X;
    }
    return result;
}
template<class T>
void Graph<T>::innerCliques(bool* P, bool* R, bool* X, std::vector<std::vector<std::size_t> >& result){
    std::size_t P_size = 0, X_size = 0;
    for(std::size_t i=0; i<size(); i++){
        P_size += P[i];
        X_size += X[i];
    }

    if(P_size == 0 && X_size == 0){ // found clique
        std::vector<std::size_t> clique;
        for(std::size_t i=0; i<size(); i++)
            if(R[i] == true)
                clique.push_back(i);
        result.push_back(clique);
    }
    else if(P_size != 0){
        bool* P2 = new bool[size()];
        bool* R2 = new bool[size()];
        bool* X2 = new bool[size()];

        for(std::size_t v=0; v<size(); v++)
            if(P[v] == true){
                for(std::size_t i=0; i<size(); i++){
                    R2[i] = R[i];
                    P2[i] = false;
                    X2[i] = false;
                }
                R2[v] = true;
                for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                    if(v != *it){
                        P2[*it] = P[*it];
                        X2[*it] = X[*it];
                    }
                }

                innerCliques(P2,R2,X2, result);

                P[v] = false;
                X[v] = true;
            }

        delete[] P2;
        delete[] R2;
        delete[] X2;
    }
}

template<class T>
std::vector<std::vector<std::size_t> > Graph<T>::cliques2(){
    // Bron-Kerbosch algorithm with pivoting for maximal cliques

    std::vector<std::vector<std::size_t> > result;
    if(size() > 0){
        bool* P = new bool[size()];
        bool* R = new bool[size()];
        bool* X = new bool[size()];
        for(std::size_t i=0; i<size(); i++){
            P[i] = true;
            R[i] = false;
            X[i] = false;
        }

        innerCliques2(P,R,X, result);

        delete[] P;
        delete[] R;
        delete[] X;
    }
    return result;
}
template<class T>
void Graph<T>::innerCliques2(bool* P, bool* R, bool* X, std::vector<std::vector<std::size_t> >& result){
    std::size_t P_size = 0, X_size = 0;
    for(std::size_t i=0; i<size(); i++){
        P_size += P[i];
        X_size += X[i];
    }

    if(P_size == 0 && X_size == 0){ // found clique
        std::vector<std::size_t> clique;
        for(std::size_t i=0; i<size(); i++)
            if(R[i] == true)
                clique.push_back(i);
        result.push_back(clique);
    }
    else if(P_size != 0){

        std::size_t N_counter_max = 0;
        std::size_t u_max = 0;
        for(std::size_t u=0; u<size(); u++)
            if(P[u] || X[u]){
                std::size_t N_counter = 0;
                for(auto it = nodes.at(u).neighbours.begin(); it != nodes.at(u).neighbours.end(); it++)
                    if(u != *it && P[*it])
                        N_counter++;

                if(N_counter >= N_counter_max){
                    N_counter_max = N_counter;
                    u_max = u;
                }
            }

        bool* N = new bool[size()];
        for(std::size_t i=0; i<size(); i++)
            N[i] = false;
        for(auto it = nodes.at(u_max).neighbours.begin(); it != nodes.at(u_max).neighbours.end(); it++)
            N[*it] = true;
        N[u_max] = false;

        bool* P2 = new bool[size()];
        bool* R2 = new bool[size()];
        bool* X2 = new bool[size()];

        for(std::size_t v=0; v<size(); v++)
            if(P[v] && !N[v]){
                for(std::size_t i=0; i<size(); i++){
                    R2[i] = R[i];
                    P2[i] = false;
                    X2[i] = false;
                }
                R2[v] = true;
                for(auto it = nodes.at(v).neighbours.begin(); it != nodes.at(v).neighbours.end(); it++){
                    if(v != *it){
                        P2[*it] = P[*it];
                        X2[*it] = X[*it];
                    }
                }

                innerCliques2(P2,R2,X2, result);

                P[v] = false;
                X[v] = true;
            }

        delete[] P2;
        delete[] R2;
        delete[] X2;
        delete[] N;
    }
}

template<class T>
std::vector<std::size_t> Graph<T>::maxClique(){
    // maximum clique

    std::vector<std::size_t> result;
    if(size() > 0){
        auto cliques = cliques2();

        for(auto clique_it = cliques.begin(); clique_it != cliques.end(); clique_it++)
            if(clique_it->size() > result.size())
                result = *clique_it;
    }
    return result;
}


template<class T>
bool Graph<T>::operator==(const Graph<T>& other){
    return (nodes == other.nodes);
}
template<class T>
bool Graph<T>::operator!=(const Graph<T>& other){
    return !(nodes == other.nodes);
}



// ============================================

template<class T>
void Graph<T>::printNodes(){
    std::size_t i = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++){
        std::cout << i << ": " << it->value << "      neighbours: ";
        for(auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
            std::cout << *it2 << ' ';
        std::cout << std::endl;
    }
}
template<class T>
void Graph<T>::printValues(){
    std::size_t i = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++, i++){
        std::cout << i << ": " << it->value << std::endl;
    }
}


