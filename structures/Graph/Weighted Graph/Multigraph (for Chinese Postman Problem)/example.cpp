#include <iostream>

#include "WeightedMultigraph.h"

using namespace std;

template<class T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec){
    for(auto it = vec.begin(); it != vec.end(); it++)
        os << *it << ' ';
    return os;
}

template<class T, class W>
void CPP(WeightedMultigraph<T,W>& mg, size_t start=0){
    if(!mg.empty()){
        auto res = mg.ChinesePostmanProblemDirected(start);
        if(res.first.size() > 0)
            cout << "CPP cycle: " << res.first << "   dist: " << res.second << endl;
        else
            cout << "no CPP cycle (graph is disconnected or not strongly connected)" << endl;
    }
    else
        cout << "empty graph" << endl;
}

int main(){
    cout << "Chinese Postman Problem in directed graph" << endl << endl;

    // euler cycle
    WeightedMultigraph<int,int> g({0,1,2,3,4,5,6,7,8, 9});
    g.addDirectedEdge(0,1, 1);
    g.addDirectedEdge(1,3, 2);
    g.addDirectedEdge(1,4, 3);
    g.addDirectedEdge(2,1, 4);
    g.addDirectedEdge(2,5, 1);
    g.addDirectedEdge(3,0, 8);
    g.addDirectedEdge(3,2, 6);
    g.addDirectedEdge(3,7, 8);
    g.addDirectedEdge(4,2, 3);
    g.addDirectedEdge(4,3, 5);
    g.addDirectedEdge(4,6, 2);
    g.addDirectedEdge(5,4, 1);
    g.addDirectedEdge(5,7, 6);
    g.addDirectedEdge(6,3, 7);
    g.addDirectedEdge(7,4, 5);
    g.addDirectedEdge(7,8, 2);
    g.addDirectedEdge(8,5, 7);

    CPP(g);
    CPP(g, 4);

    cout << "======================================================================" << endl;

    // euler path
    WeightedMultigraph<int,int> g2({0,1,2,3,4,5,6,7,8, 9});
    g2.addDirectedEdge(0,1, 1);
    g2.addDirectedEdge(0,7, 2);
    g2.addDirectedEdge(1,2, 3);
    g2.addDirectedEdge(1,5, 5);
    g2.addDirectedEdge(2,3, 9);
    g2.addDirectedEdge(2,4, 4);
    g2.addDirectedEdge(3,0, 7);
    g2.addDirectedEdge(3,7, 3);
    g2.addDirectedEdge(4,5, 8);
    g2.addDirectedEdge(4,8, 6);
    g2.addDirectedEdge(5,2, 4);
    g2.addDirectedEdge(5,7, 1);
    g2.addDirectedEdge(6,3, 5);
    g2.addDirectedEdge(7,4, 9);
    g2.addDirectedEdge(7,6, 4);
    g2.addDirectedEdge(7,8, 2);
    g2.addDirectedEdge(8,1, 8);

    CPP(g2);

    cout << "======================================================================" << endl;

    // disconnected
    WeightedMultigraph<int> g3({0,1,2,3,4,5,6,7,8});
    g3.addDirectedEdge(0,4, 6);
    g3.addDirectedEdge(1,5, 4);
    g3.addDirectedEdge(1,6, 2);
    g3.addDirectedEdge(2,7, 7);
    g3.addDirectedEdge(3,1, 9);
    g3.addDirectedEdge(4,2, 1);
    g3.addDirectedEdge(5,8, 5);
    g3.addDirectedEdge(6,3, 3);
    g3.addDirectedEdge(7,0, 8);
    g3.addDirectedEdge(8,1, 3);

    CPP(g3);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g4({0,1,2,3,4});
    g4.addDirectedEdge(0,1, 2);
    g4.addDirectedEdge(0,2, 4);
    g4.addDirectedEdge(0,3, 5);
    g4.addDirectedEdge(1,3, 7);
    g4.addDirectedEdge(2,4, 2);
    g4.addDirectedEdge(3,4, 2);

    CPP(g4);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g5(6,0);
    g5.addDirectedEdge(0,1, 10);
    g5.addDirectedEdge(0,2, 20);
    g5.addDirectedEdge(1,3, 50);
    g5.addDirectedEdge(1,4, 10);
    g5.addDirectedEdge(2,3, 20);
    g5.addDirectedEdge(2,4, 33);
    g5.addDirectedEdge(3,4, 5);
    g5.addDirectedEdge(3,5, 12);
    g5.addDirectedEdge(4,0, 12);
    g5.addDirectedEdge(4,5, 1);
    g5.addDirectedEdge(5,2, 22);

    CPP(g5);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g6(6,0);
    g6.addDirectedEdge(0,1, 10);
    g6.addDirectedEdge(0,2, 20);
    g6.addDirectedEdge(1,3, 50);
    g6.addDirectedEdge(1,4, 10);
    g6.addDirectedEdge(2,3, 20);
    g6.addDirectedEdge(2,4, 33);
    g6.addDirectedEdge(3,4, 20);
    g6.addDirectedEdge(3,5, 2);
    g6.addDirectedEdge(4,5, 1);

    CPP(g6);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g7(2,0);
    g7.addDirectedEdge(0,1, 10);

    CPP(g7);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g8(4,0);
    g8.addDirectedEdge(0,1, 6);
    g8.addDirectedEdge(1,2, 12);
    g8.addDirectedEdge(1,3, 3);
    g8.addDirectedEdge(2,0, 8);
    g8.addDirectedEdge(3,0, 20);
    g8.addDirectedEdge(3,2, 34);

    CPP(g8);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g9(2,0);
    g9.addDirectedEdge(0,1, 2);
    g9.addDirectedEdge(0,1, 1);
    g9.addDirectedEdge(0,1, 1);
    g9.addDirectedEdge(1,0, 1);

    CPP(g9);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int> g10(4,0);
    g10.addDirectedEdge(0,1, 21);
    g10.addDirectedEdge(1,2, 8);
    g10.addDirectedEdge(2,0, 5);
    g10.addDirectedEdge(2,3, 20);
    g10.addDirectedEdge(3,1, 2);
    g10.addDirectedEdge(3,1, 12);

    CPP(g10);

    cout << "======================================================================" << endl;

    WeightedMultigraph<int, float> gf(4,0);
    gf.addDirectedEdge(0,1, 2.3);
    gf.addDirectedEdge(1,2, 1.4);
    gf.addDirectedEdge(1,3, 9.4);
    gf.addDirectedEdge(2,0, 8);
    gf.addDirectedEdge(3,0, 0.7);
    gf.addDirectedEdge(3,2, 1.1);

    CPP(gf);

    cout << "======================================================================" << endl;

    // loop
    WeightedMultigraph<int> gl(2,0);
    gl.addDirectedEdge(0,0, 2);
    gl.addDirectedEdge(0,1, 3);
    gl.addDirectedEdge(1,0, 4);
    gl.addDirectedEdge(1,1, 1);

    CPP(gl);

    return 0;
}
