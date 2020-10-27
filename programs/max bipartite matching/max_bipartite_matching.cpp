#include <iostream>

#include "FlowNetwork.h"


int main(){
    // maximum bipartite matching using max flow algorithm in flow network

    std::cout << "Maximum bipartite matching" << std::endl;

    // get sizes of sets
    int x=0,y=0;
    std::cout << "Number of elements of first set: ";
    do{
        std::cin >> x;
    }while(x <= 0);
    std::cout << "Number of elements of second set: ";
    do{
        std::cin >> y;
    }while(y <= 0);
    std::cin.ignore();


    // get data for sets
    std::vector<std::string> vertices_data;
    std::string line;
    std::cout << "First set:" << std::endl;
    for(int i=1; i <= x; i++){
        std::cout << i << ": ";
        std::getline(std::cin, line);
        vertices_data.push_back(line);
    }
    std::cout << "Second set:" << std::endl;
    for(int i=1; i <= y; i++){
        std::cout << x+i << ": ";
        std::getline(std::cin, line);
        vertices_data.push_back(line);
    }

    // create flow network
    FlowNetwork<std::string, int> fn(x+y);
    for(int i=0; i<vertices_data.size(); i++)
        fn.setData(i+1, vertices_data.at(i));


    // get edges and add them to flow network
    int m;
    std::cout << std::endl << "Number of edges: ";
    do{
        std::cin >> m;
    }while(m <= 0);
    std::cout << "Edges:" << std::endl;
    for(int i=0; i<m;){
        int a,b;
        std::cin >> a >> b;
        if(a <= 0 || b <= 0 || a > x || b <= x || b > x+y || a == b)
            std::cout << "wrong edge" << std::endl;
        else{
            fn.addDirectedEdge(a,b, 1);
            i++;
        }
    }

    int s = fn.sourceNode(), t = fn.sinkNode();
    // connect first set with source
    for(int i=1; i <= x; i++)
        fn.addDirectedEdge(s, i, 1);
    // connect second set with sink
    for(int j=1; j <= y; j++)
        fn.addDirectedEdge(x+j, t, 1);


    // run Dinic's algorithm to find max flow
    fn.Dinic();

    std::cout << std::endl << std::endl << "Maximum bipartite matching:" << std::endl;
    for(int i=1; i <= x; i++)
        for(int j=x+1; j <= x+y; j++)
            if(fn.getFlow(i,j) == 1){
                std::cout << fn.getData(i) << "-" << fn.getData(j) << std::endl;
                break;
            }

    return 0;
}
