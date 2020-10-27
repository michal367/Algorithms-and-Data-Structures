#pragma once

#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>

#include "IndexedPQ.h"

#include <iostream>


template<class T, class W = int>
class WeightedMultigraph{
    // undirected/directed weighted multigraph with loops (pseudograph)

    struct Edges{
        std::size_t node;
        std::vector<W> weights;

        Edges(std::size_t node) : node(node) {}
        Edges(std::size_t node, const W& weight) : node(node), weights({weight}) {}
        Edges(std::size_t node, const std::vector<W>& weights) : node(node), weights(weights) {}
        bool operator==(const Edges& other) const{
            return (node == other.node && weights == other.weights);
        }
    };

    std::vector<std::list<Edges> > neighbours;
    std::vector<T> data;

public:
    WeightedMultigraph();
    WeightedMultigraph(std::size_t size, const T& value);
    WeightedMultigraph(std::initializer_list<T> il);
    WeightedMultigraph(const WeightedMultigraph<T,W>& other);
    WeightedMultigraph<T,W>& operator=(const WeightedMultigraph<T,W>& other);

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

    std::list<std::pair<std::size_t, std::vector<W> > > getNeighbours(std::size_t node);

    void addNode(const T& value);
    void addDirectedEdge(std::size_t node1, std::size_t node2, const W& weight);
    void addDirectedEdges(std::size_t node1, std::size_t node2, const std::vector<W>& weights);
    void addEdge(std::size_t node1, std::size_t node2, const W& weight);

    void removeNode(T value);
    void removeNodeByIndex(std::size_t index);
    void removeDirectedEdges(std::size_t node1, std::size_t node2);
    void removeEdges(std::size_t node1, std::size_t node2);
    void removeDirectedEdge(std::size_t node1, std::size_t node2, std::size_t index);

    std::vector<W> getWeights(std::size_t node1, std::size_t node2);
    void setWeightsDirected(std::size_t node1, std::size_t node2, const std::vector<W>& weight);
    void setWeights(std::size_t node1, std::size_t node2, const std::vector<W>& weight);
    void setWeightDirected(std::size_t node1, std::size_t node2, std::size_t weight_index, const W& weight);

    WeightedMultigraph<T,W> subgraph(const std::vector<std::size_t>& nodes);
    WeightedMultigraph<T,W> convertToUndirectedMultigraph();


    std::pair<std::vector<std::size_t>, W> ChinesePostmanProblemDirected(std::size_t start=0);


    bool operator==(const WeightedMultigraph<T,W>& other);
    bool operator!=(const WeightedMultigraph<T,W>& other);

    void printNodes();
    void printValues();

private:
    std::pair<std::vector<std::size_t>, W> EulerianDirected(std::size_t start=0);
    void innerEulerianDirected(std::size_t node, std::vector<std::size_t>& result, W& dist);

    bool CPPstronglyConnectedDirected();
    bool innerCPPstronglyConnectedDirected(std::size_t node,
                              std::size_t& node_number, std::size_t* nodes_order, std::size_t* low,
                              bool* on_stack, std::stack<std::size_t>& s,
                              std::size_t& scc_counter);
    std::pair<std::vector<std::size_t>, std::vector<std::size_t> > CPPdifferentDegreeNodesDirected();

    std::vector<W> DijkstraDistances(std::size_t node);
    std::vector<std::size_t> DijkstraPath(std::size_t node1, std::size_t node2);

    std::pair<std::vector<std::size_t>,std::vector<std::size_t> > bipartiteSets();

    std::vector<std::pair<std::size_t,std::size_t> > maxWeightHungarianAlgorithm();
    std::vector<std::pair<std::size_t,std::size_t> > minWeightHungarianAlgorithm();
};



template<class T, class W>
WeightedMultigraph<T,W>::WeightedMultigraph() {}
template<class T, class W>
WeightedMultigraph<T,W>::WeightedMultigraph(std::size_t size, const T& value){
    for(std::size_t i=0; i<size; i++){
        data.push_back(value);
        neighbours.push_back(std::list<Edges>());
    }
}
template<class T, class W>
WeightedMultigraph<T,W>::WeightedMultigraph(std::initializer_list<T> il){
    for(auto it = il.begin(); it != il.end(); it++){
        data.push_back(*it);
        neighbours.push_back(std::list<Edges>());
    }
}
template<class T, class W>
WeightedMultigraph<T,W>::WeightedMultigraph(const WeightedMultigraph<T,W>& other){
    data = other.data;
    neighbours = other.neighbours;
}
template<class T, class W>
WeightedMultigraph<T,W>& WeightedMultigraph<T,W>::operator=(const WeightedMultigraph<T,W>& other){
    if(this != &other){
        data = other.data;
        neighbours = other.neighbours;
    }
    return *this;
}



template<class T, class W>
std::size_t WeightedMultigraph<T,W>::size(){
    return data.size();
}
template<class T, class W>
std::size_t WeightedMultigraph<T,W>::nodesAmount(){
    return size();
}
template<class T, class W>
std::size_t WeightedMultigraph<T,W>::directedEdgesAmount(){
    std::size_t amount = 0;
    for(auto it = neighbours.begin(); it != neighbours.end(); it++)
        for(auto it2 = it->begin(); it2 != it->end(); it2++)
            amount += it2->weights.size();
    return amount;
}
template<class T, class W>
std::size_t WeightedMultigraph<T,W>::edgesAmount(){
    std::list<std::pair<std::pair<std::size_t,std::size_t>, W> > edges;

    for(std::size_t i=0; i<neighbours.size(); i++)
        for(auto it = neighbours.at(i).begin(); it != neighbours.at(i).end(); it++)
            for(auto itw = it->weights.begin(); itw != it->weights.end(); itw++)
                if(std::find(edges.begin(),edges.end(), std::make_pair(std::make_pair(it->node, i), *itw)) == edges.end())
                    edges.push_back(std::make_pair(std::make_pair(i, it->node), *itw));

    return edges.size();
}
template<class T, class W>
bool WeightedMultigraph<T,W>::empty(){
    return (size() == 0);
}
template<class T, class W>
void WeightedMultigraph<T,W>::clear(){
    data.clear();
    neighbours.clear();
}


template<class T, class W>
T WeightedMultigraph<T,W>::getData(std::size_t node){
    return data.at(node);
}
template<class T, class W>
T& WeightedMultigraph<T,W>::at(std::size_t node){
    return data.at(node);
}
template<class T, class W>
void WeightedMultigraph<T,W>::setData(std::size_t node, const T& value){
    data.at(node) = value;
}
template<class T, class W>
bool WeightedMultigraph<T,W>::existsDirectedEdge(std::size_t node1, std::size_t node2){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2)
            return true;
    return false;
}
template<class T, class W>
std::list<std::pair<std::size_t, std::vector<W> > > WeightedMultigraph<T,W>::getNeighbours(std::size_t node){
    std::list<std::pair<std::size_t, std::vector<W> > > result;
    for(auto it = neighbours.at(node).begin(); it != neighbours.at(node).end(); it++)
        result.push_back(std::make_pair(it->node, it->weights));
    return result;
}


template<class T, class W>
void WeightedMultigraph<T,W>::addNode(const T& value){
    data.push_back(value);
    neighbours.push_back(std::list<Edges>());
}
template<class T, class W>
void WeightedMultigraph<T,W>::addDirectedEdge(std::size_t node1, std::size_t node2, const W& weight){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            it->weights.push_back(weight);
            return;
        }
    neighbours.at(node1).push_back(Edges(node2, weight));
}
template<class T, class W>
void WeightedMultigraph<T,W>::addDirectedEdges(std::size_t node1, std::size_t node2, const std::vector<W>& weights){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            it->weights.insert(it->weights.end(), weights.begin(),weights.end());
            return;
        }
    neighbours.at(node1).push_back(Edges(node2, weights));
}
template<class T, class W>
void WeightedMultigraph<T,W>::addEdge(std::size_t node1, std::size_t node2, const W& weight){
    addDirectedEdge(node1, node2, weight);
    addDirectedEdge(node2, node1, weight);
}


template<class T, class W>
void WeightedMultigraph<T,W>::removeNode(T value){
    for(std::size_t i=0; i<data.size(); i++)
        if(data.at(i) == value){
            data.erase(data.begin()+i);
            neighbours.erase(neighbours.begin()+i);

            for(auto it = neighbours.begin(); it != neighbours.end(); it++)
                for(auto it2 = it->begin(); it2 != it->end();)
                    if(it2->node == i){
                        auto temp = it2;
                        it2++;
                        it->erase(temp);
                    }
                    else{
                        if(it2->node > i)
                            it2->node--;
                        it2++;
                    }
            break;
        }
}
template<class T, class W>
void WeightedMultigraph<T,W>::removeNodeByIndex(std::size_t index){
    data.erase(data.begin()+index);
    neighbours.erase(neighbours.begin()+index);

    for(auto it = neighbours.begin(); it != neighbours.end(); it++)
        for(auto it2 = it->begin(); it2 != it->end();)
            if(it2->node == index){
                auto temp = it2;
                it2++;
                it->erase(temp);
            }
            else{
                if(it2->node > index)
                    it2->node--;
                it2++;
            }
}
template<class T, class W>
void WeightedMultigraph<T,W>::removeDirectedEdges(std::size_t node1, std::size_t node2){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end();)
        if(it->node == node2){
            auto temp = it;
            it++;
            neighbours.at(node1).erase(temp);
        }
        else
            it++;
}
template<class T, class W>
void WeightedMultigraph<T,W>::removeEdges(std::size_t node1, std::size_t node2){
    removeDirectedEdges(node1, node2);
    removeDirectedEdges(node2, node1);
}

template<class T, class W>
void WeightedMultigraph<T,W>::removeDirectedEdge(std::size_t node1, std::size_t node2, std::size_t index){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            if(index < it->weights.size()){
                it->weights.erase(it->weights.begin()+index);
                if(it->weights.size() == 0)
                    neighbours.at(node1).erase(it);
            }
            break;
        }
}


template<class T, class W>
std::vector<W> WeightedMultigraph<T,W>::getWeights(std::size_t node1, std::size_t node2){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2)
            return it->weights;
    return std::vector<W>();
}
template<class T, class W>
void WeightedMultigraph<T,W>::setWeightsDirected(std::size_t node1, std::size_t node2, const std::vector<W>& weights){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            it->weights = weights;
            break;
        }
}
template<class T, class W>
void WeightedMultigraph<T,W>::setWeights(std::size_t node1, std::size_t node2, const std::vector<W>& weights){
    setWeightDirected(node1, node2, weights);
    setWeightDirected(node2, node1, weights);
}
template<class T, class W>
void WeightedMultigraph<T,W>::setWeightDirected(std::size_t node1, std::size_t node2, std::size_t weight_index, const W& weight){
    for(auto it = neighbours.at(node1).begin(); it != neighbours.at(node1).end(); it++)
        if(it->node == node2){
            if(weight_index < it->weights.size())
                it->weights.at(weight_index) = weight;
            break;
        }
}


template<class T, class W>
WeightedMultigraph<T,W> WeightedMultigraph<T,W>::subgraph(const std::vector<std::size_t>& nodes){
    WeightedMultigraph<T,W> sg;
    std::map<std::size_t, std::size_t> m;

    std::size_t i=0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        sg.addNode(data.at(*it));
        m.insert(std::pair<std::size_t,std::size_t>(*it, i++));
    }

    for(auto it = nodes.begin(); it != nodes.end(); it++){
        for(auto it2 = neighbours.at(*it).begin(); it2 != neighbours.at(*it).end(); it2++){
            auto mit = m.find(it2->node);
            if(mit != m.end()){
                sg.addDirectedEdges(m.find(*it)->second, mit->second, it2->weights);
            }
        }
    }

    return sg;
}
template<class T, class W>
WeightedMultigraph<T,W> WeightedMultigraph<T,W>::convertToUndirectedMultigraph(){
    WeightedMultigraph<T,W> undig;
    undig.data.insert(undig.data.end(), data.begin(), data.end());
    undig.neighbours.insert(undig.neighbours.begin(), size(), std::list<Edges>());

    std::list<std::pair<std::pair<std::size_t,std::size_t>, W> > edges;
    for(std::size_t i=0; i<neighbours.size(); i++)
        for(auto it = neighbours.at(i).begin(); it != neighbours.at(i).end(); it++)
            for(auto itw = it->weights.begin(); itw != it->weights.end(); itw++)
                if(std::find(edges.begin(),edges.end(), std::make_pair(std::make_pair(it->node, i), *itw)) == edges.end())
                    edges.push_back(std::make_pair(std::make_pair(i, it->node), *itw));

    for(auto it = edges.begin(); it != edges.end(); it++)
        undig.addEdge(it->first.first, it->first.second, it->second);

    return undig;
}


template<class T, class W>
std::pair<std::vector<std::size_t>, W> WeightedMultigraph<T,W>::EulerianDirected(std::size_t start){
    std::vector<std::size_t> result;
    W dist = W();
    if(start < size()){
        WeightedMultigraph<T,W> clone(*this);
        clone.innerEulerianDirected(start, result, dist);
        std::reverse(result.begin(), result.end());
    }
    return std::make_pair(result, dist);
}
template<class T, class W>
void WeightedMultigraph<T,W>::innerEulerianDirected(std::size_t node, std::vector<std::size_t>& result, W& dist){
    while(neighbours.at(node).size() > 0){
        if(neighbours.at(node).front().weights.size() > 0){
            // get first neighbour
            std::size_t v = neighbours.at(node).front().node;
            dist = dist + neighbours.at(node).front().weights.front();
            // delete first neighbour
            neighbours.at(node).front().weights.erase(neighbours.at(node).front().weights.begin());

            innerEulerianDirected(v, result, dist);
        }
        else
            neighbours.at(node).pop_front();
    }
    result.push_back(node);
}


template<class T, class W>
std::pair<std::vector<std::size_t>, W> WeightedMultigraph<T,W>::ChinesePostmanProblemDirected(std::size_t start){
    // graph cannot have negative weights
    // W type must be signed type (for hungarian algorithm)
    // returns
    // CPP cycle
    // distance of cycle

    std::vector<std::size_t> path;
    W dist = W();

    if(start < size() && CPPstronglyConnectedDirected()){
        auto imbalanced = CPPdifferentDegreeNodesDirected();
        if(imbalanced.first.size() == 0){ // graph has Eulerian cycle
            return EulerianDirected(start);
        }
        else{
            // creating complete bipartite graph with imbalanced vertices
            // weights of edges are distances of min-dist path
            WeightedMultigraph<T,W> missingPaths(imbalanced.first.size() + imbalanced.second.size(), W());
            for(std::size_t i=0; i<imbalanced.first.size(); i++){
                std::vector<W> dist = DijkstraDistances(imbalanced.first.at(i));
                for(std::size_t j=0; j<imbalanced.second.size(); j++)
                    missingPaths.addEdge(i, imbalanced.first.size() + j, dist.at(imbalanced.second.at(j)));
            }

            // find min-weight max-cardinality matching
            auto matching = missingPaths.minWeightHungarianAlgorithm();

            // add min-weight paths to graph
            WeightedMultigraph<T,W> temp(*this);
            for(auto itm = matching.begin(); itm != matching.end(); itm++){
                std::size_t first_node = imbalanced.first.at(itm->first);
                std::size_t second_node = imbalanced.second.at(itm->second - imbalanced.first.size());
                std::vector<std::size_t> path = DijkstraPath(first_node, second_node);

                for(auto itp = path.begin(); itp+1 != path.end(); itp++){
                    std::vector<W> weights = getWeights(*itp, *(itp+1));
                    W min_weight = *std::min_element(weights.begin(), weights.end());
                    temp.addDirectedEdge(*itp, *(itp+1), min_weight);
                }
            }
            // find Eulerian Cycle
            return temp.EulerianDirected(start);
        }
    }
    return std::make_pair(path, dist);
}

template<class T, class W>
bool WeightedMultigraph<T,W>::CPPstronglyConnectedDirected(){
    // returns: does directed graph has all edges in one strongly connected component
    std::size_t big_components = 0;
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
        if(nodes_order[i] == 0){
            big_components++;

            if(neighbours.at(i).size() == 0)
                big_components--;
            else if(big_components > 1){
                delete[] nodes_order;
                delete[] low;
                delete[] on_stack;
                return false;
            }

            std::size_t scc_counter = 0;
            if(innerCPPstronglyConnectedDirected(i, node_number, nodes_order, low, on_stack, s, scc_counter) == false){
                delete[] nodes_order;
                delete[] low;
                delete[] on_stack;
                return false;
            }
        }
    }
    delete[] nodes_order;
    delete[] low;
    delete[] on_stack;
    return true;
}
template<class T, class W>
bool WeightedMultigraph<T,W>::innerCPPstronglyConnectedDirected(std::size_t node,
                              std::size_t& node_number, std::size_t* nodes_order, std::size_t* low,
                              bool* on_stack, std::stack<std::size_t>& s,
                              std::size_t& scc_counter){
    // checks if all reachable vertices are in one strongly connected component

    node_number++;
    nodes_order[node] = node_number;
    low[node] = node_number;
    s.push(node);
    on_stack[node] = true;

    for(auto it = neighbours.at(node).begin(); it != neighbours.at(node).end(); it++){
        if(nodes_order[it->node] == 0){
            innerCPPstronglyConnectedDirected(it->node, node_number, nodes_order, low, on_stack, s, scc_counter);
            low[node] = std::min(low[node], low[it->node]);
        }
        else if(on_stack[it->node] == true)
            low[node] = std::min(low[node], nodes_order[it->node]);
    }

    if(low[node] == nodes_order[node]){
        while(!s.empty()){
            std::size_t v = s.top();
            s.pop();
            on_stack[v] = false;
            if(v == node)
                break;
        }
        scc_counter++;
        return (scc_counter == 1);
    }
    return false;
}

template<class T, class W>
std::pair<std::vector<std::size_t>, std::vector<std::size_t> > WeightedMultigraph<T,W>::CPPdifferentDegreeNodesDirected(){
    // returns
    // vertices with  indegree - outdegree > 0
    // vertices with  outdegree - indegree > 0

    std::vector<std::size_t> in, out;

    int* indegree = new int[size()];
    int* outdegree = new int[size()];
    for(std::size_t i=0; i<size(); i++){
        indegree[i] = 0;
        outdegree[i] = 0;
    }
    for(std::size_t i=0; i<size(); i++){
        for(auto it = neighbours.at(i).begin(); it != neighbours.at(i).end(); it++){
            outdegree[i] += it->weights.size();
            indegree[it->node] += it->weights.size();
        }
    }

    for(std::size_t node = 0; node < size(); node++){
        if(indegree[node] != outdegree[node]){
            if(indegree[node] - outdegree[node] > 0)
                in.insert(in.end(), indegree[node] - outdegree[node], node);
            else if(outdegree[node] - indegree[node] > 0)
                out.insert(out.end(), outdegree[node] - indegree[node], node);
        }
    }
    delete[] indegree;
    delete[] outdegree;
    return std::make_pair(in,out);
}


template<class T, class W>
std::vector<W> WeightedMultigraph<T,W>::DijkstraDistances(std::size_t node){
    // graph must have non-negative edge weights

    if(node >= size())
        return std::vector<W>();

    std::vector<W> dist(size(), W());
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++){
        //dist[i] = W();
        parent[i] = -1;
    }
    dist[node] = W();

    IndexedPQ<W> ipq(size());
    ipq.push(node, dist[node]);
    while(!ipq.empty()){
        std::size_t v = ipq.pop();

        for(auto it = neighbours.at(v).begin(); it != neighbours.at(v).end(); it++){
            W min_weight = *std::min_element(it->weights.begin(), it->weights.end());
            if(dist[v] + min_weight < dist[it->node] || parent[it->node] == -1 && it->node != node){
                dist[it->node] = dist[v] + min_weight;
                parent[it->node] = v;

                if(ipq.contains(it->node))
                    ipq.decrease_key(it->node, dist[it->node]);
                else
                    ipq.push(it->node, dist[it->node]);
            }
        }
    }
    delete[] parent;
    return dist;
}
template<class T, class W>
std::vector<std::size_t> WeightedMultigraph<T,W>::DijkstraPath(std::size_t node1, std::size_t node2){
    // graph must have non-negative edge weights

    if(node1 >= size() || node2 >= size())
        return std::vector<std::size_t>();
    if(node1 == node2)
        return std::vector<std::size_t>({node1});

    W* dist = new W[size()];
    std::size_t* parent = new std::size_t[size()];
    for(std::size_t i=0; i<size(); i++){
        //dist[i] = W();
        parent[i] = -1;
    }
    dist[node1] = W();

    IndexedPQ<W> ipq(size());
    ipq.push(node1, dist[node1]);
    while(!ipq.empty()){
        std::size_t v = ipq.pop();

        if(v == node2)
            break;

        for(auto it = neighbours.at(v).begin(); it != neighbours.at(v).end(); it++){
            W min_weight = *std::min_element(it->weights.begin(), it->weights.end());
            if(dist[v] + min_weight < dist[it->node] || parent[it->node] == -1 && it->node != node1){
                dist[it->node] = dist[v] + min_weight;
                parent[it->node] = v;

                if(ipq.contains(it->node))
                    ipq.decrease_key(it->node, dist[it->node]);
                else
                    ipq.push(it->node, dist[it->node]);
            }
        }
    }

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
std::pair<std::vector<std::size_t>,std::vector<std::size_t> > WeightedMultigraph<T,W>::bipartiteSets(){
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

                for(auto it = neighbours.at(v).begin(); it != neighbours.at(v).end(); it++){
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
std::vector<std::pair<std::size_t,std::size_t> > WeightedMultigraph<T,W>::maxWeightHungarianAlgorithm(){
    // max-weight max-cardinality bipartite matching
    // graph must be undirected and bipartite
    // W type must be signed type

    std::pair<std::vector<std::size_t>, std::vector<std::size_t> > bs = bipartiteSets();

    std::vector<std::pair<std::size_t,std::size_t> > result;
    if(bs.first.size() > 0 && bs.second.size() > 0){
        WeightedMultigraph<T,W> completeB(*this);

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
            for(auto itn = neighbours.at(*it).begin(); itn != neighbours.at(*it).end(); itn++){
                W max_weight = *std::max_element(itn->weights.begin(), itn->weights.end());
                if(max_weight > W())
                    dummy_weight = dummy_weight - max_weight;
                else
                    dummy_weight = dummy_weight + max_weight;
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
            W max = neighbours.at(*it).front().weights.front();
            for(auto it2 = completeB.neighbours.at(*it).begin(); it2 != completeB.neighbours.at(*it).end(); it2++){
                W max_weight = *std::max_element(it2->weights.begin(), it2->weights.end());
                if(max_weight > max)
                    max = max_weight;
                }
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

                for(auto it2 = completeB.neighbours.at(v).begin(); it2 != completeB.neighbours.at(v).end(); it2++){
                    W max_weight = *std::max_element(it2->weights.begin(), it2->weights.end());
                    if(parent[it2->node] == -1 && parent[v] != it2->node &&
                       label[v] + label[it2->node] == max_weight){ // tight edge
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
                    for(auto itn = completeB.neighbours.at(*itf).begin(); itn != completeB.neighbours.at(*itf).end(); itn++)
                        if((parent[*itf] != -1 || *itf == *it) && parent[itn->node] == -1){ // visited from first and not visited from second
                            W max_weight = *std::max_element(itn->weights.begin(), itn->weights.end());
                            W new_delta = label[*itf] + label[itn->node] - max_weight;
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
std::vector<std::pair<std::size_t,std::size_t> > WeightedMultigraph<T,W>::minWeightHungarianAlgorithm(){
    // min-weight max-cardinality bipartite matching
    // graph must be undirected and bipartite
    // W type must be signed type

    // set all weights opposite and run max-weight HA
    WeightedMultigraph<T,W> temp(*this);
    for(std::size_t i=0; i<size(); i++)
        for(auto it = temp.neighbours.at(i).begin(); it != temp.neighbours.at(i).end(); it++)
            for(auto itw = it->weights.begin(); itw != it->weights.end(); itw++)
                *itw = -*itw;
    return temp.maxWeightHungarianAlgorithm();
}


template<class T, class W>
bool WeightedMultigraph<T,W>::operator==(const WeightedMultigraph<T,W>& other){
    return (data == other.data && neighbours == other.neighbours);
}
template<class T, class W>
bool WeightedMultigraph<T,W>::operator!=(const WeightedMultigraph<T,W>& other){
    return !(*this == other);
}


// ============================================

template<class T, class W>
void WeightedMultigraph<T,W>::printNodes(){
    std::size_t i = 0;
    for(auto it = data.begin(); it != data.end(); it++, i++){
        std::cout << i << ": " << *it << "      neighbours: ";
        for(auto it2 = neighbours.at(i).begin(); it2 != neighbours.at(i).end(); it2++){
            std::cout << it2->node << "(w:";
            for(auto itw = it2->weights.begin(); itw != it2->weights.end()-1; itw++)
                std::cout << *itw << ",";
            std::cout << it2->weights.back();
            std::cout << ")  ";
        }
        std::cout << std::endl;
    }
}
template<class T, class W>
void WeightedMultigraph<T,W>::printValues(){
    std::size_t i = 0;
    for(auto it = data.begin(); it != data.end(); it++, i++){
        std::cout << i << ": " << *it << std::endl;
    }
}

