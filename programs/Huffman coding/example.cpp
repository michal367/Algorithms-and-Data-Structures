#include <iostream>
#include <cstdlib>
#include <map>

#include "HuffmanCoding.h"

using namespace std;

int main()
{
    cout << "Huffman coding" << endl << endl;

    string data[] = {"ABCDEF", "AAAABBBBDDD", "ACBECAHCADFEGAFAGACBBADAAFAAEAGACAFABEFBCCFA", "FSUIDHFUIERHADDFDHSIDFHSDUIFHSI"};
    size_t data_s = 4;

    for(int i=0; i<data_s; ++i)
    {
        cout << "text: " << data[i] << endl;

        HuffmanCoding hc;
        string encoded = hc.encode(data[i]);
        cout << "encoded: " << encoded << endl;

        cout << endl << "Huffman coding:" << endl;
        hc.PRINT();
        cout << endl;

        string decoded = hc.decode();
        cout << "decoded: " << decoded << endl;

        cout << "correct: " << bool(data[i] == hc.decode()) << endl;
        std::cout << "======================================================================================" << std::endl;
    }


    cout << endl;
    return 0;
}
