#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{
    srand(time(NULL));

    cout << "MasterMind" << endl
         << "You have 6 tries to guess your opponent's code" << endl
         << "The four-letter code can be made up of letters: A,B,C,D,E,F" << endl
         << "If the relevant factors match, a letter will be printed:" << endl
         << "- letter and position - x" << endl
         << "- letter - o" << endl << endl;


    string alphabet = "ABCDEF";
    string code = "";

    for(int i=0; i<4; ++i)
        code += alphabet[rand()%6];


    int round_counter = 0;
    string code_quess;
    string key;
    do{
        key = "";
        ++round_counter;
        bool is_good;

        cout << endl << round_counter << ". " << endl;

        do{
            is_good = true;
            getline(cin, code_quess);
            if(code_quess.size() == 4)
            {
                for(int i=0; i<4; ++i)
                    if(alphabet.find(code_quess[i]) == string::npos)
                    {
                        is_good = false;
                        break;
                    }
            }
            else
                is_good = false;
        }while(!is_good);

        string code_copy = code;
        for(int i=0; i<4; ++i)
            if(code_quess[i] == code_copy[i])
            {
                key += 'x';
                code_quess[i] = '.';
                code_copy[i] = ',';
            }
        for(int i=0; i<4; ++i)
            for(int j=0; j<4; ++j)
                if(code_quess[i] == code_copy[j])
                {
                    key += 'o';
                    code_quess[i] = '.';
                    code_copy[j] = ',';
                    break;
                }

        cout << key << endl;

    }while(round_counter < 6 && key != "xxxx");

    cout << endl;
    if(key == "xxxx")
        cout << "You've cracked the code!" << endl
             << code << endl;
    else
        cout << "Unfortunately, you failed to crack the code" << endl
             << code << endl;



    cout << endl;
    system("pause");
    return 0;
}

