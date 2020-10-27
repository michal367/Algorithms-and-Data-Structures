#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{
    srand(time(NULL));

    cout << "MasterMind" << endl
         << "Think of a 4-letter code to be guessed by the computer in 6 tries" << endl
         << "The 4-letter code can be made up of letters: A,B,C,D,E,F" << endl
         << "If the relevant factors agree, write a letter:" << endl
         << "- letter and position - x" << endl
         << "- letter - o" << endl
         << "First write xs then ys (e.g. xoo, oo, xxoo)" << endl << endl;


    string alphabet = "ABCDEF";
    string code = "";


    cout << "Code: ";
    bool is_good;
    do{
        is_good = true;
        getline(cin, code);
        if(code.size() == 4)
        {
            for(int i=0; i<4; ++i)
                if(alphabet.find(code[i]) == string::npos)
                {
                    is_good = false;
                    break;
                }
        }
        else
            is_good = false;
    }while(!is_good);



    int codes_size = 1296;
    int codes[codes_size];
    for(int i=0; i<6; ++i)
        for(int j=0; j<6; ++j)
            for(int k=0; k<6; ++k)
                for(int l=0; l<6; ++l)
                    codes[i*216 + j*36 + k*6 + l] = (((l*6 +k)*6 +j)*6 +i);


    int round_counter = 0;
    string code_quess;
    string key;
    do{
        ++round_counter;

        // decreasing the set with possible codes
        if(round_counter > 1)
        {
            int i2 = 0;
            for(int i=0; i < codes_size; ++i)
            {
                string code_quess_copy = code_quess;
                string code_quess2 = "";
                int number_code = codes[i];
                for(int i=0; i<4; ++i)
                {
                    code_quess2 += alphabet[number_code%6];
                    number_code /= 6;
                }

                string key2 = "";
                for(int i=0; i<4; ++i)
                    if(code_quess2[i] == code_quess_copy[i])
                    {
                        key2 += 'x';
                        code_quess2[i] = '.';
                        code_quess_copy[i] = ',';
                    }
                for(int i=0; i<4; ++i)
                    for(int j=0; j<4; ++j)
                        if(code_quess2[i] == code_quess_copy[j])
                        {
                            key2 += 'o';
                            code_quess2[i] = '.';
                            code_quess_copy[j] = ',';
                            break;
                        }
                if(key2 == key)
                {
                    codes[i2] = codes[i];
                    ++i2;
                }
            }
            codes_size = i2;
        }

        if(codes_size == 0)
            break;

        // get random value from set
        code_quess = "";
        int random_number = rand()%codes_size;
        int number_code = codes[random_number];
        for(int i=0; i<4; ++i)
        {
            code_quess += alphabet[number_code%6];
            number_code /= 6;
        }
        // remove drawn value
        for(int i=random_number; i < codes_size-1; ++i)
            codes[i] = codes[i+1];
        --codes_size;

        // displaying an attempt to break the code
        cout << endl << round_counter << ". " << endl << code_quess << endl;


        // key input
        key = "";
        do{
            is_good = true;
            getline(cin, key);
            if(key.size() <= 4)
            {
                for(int i=0; i<key.size(); ++i)
                    if(key[i] != 'x' && key[i] != 'o')
                    {
                        is_good = false;
                        break;
                    }
            }
            else
                is_good = false;
        }while(!is_good);


    }while(round_counter < 6 && key != "xxxx");


    // results
    cout << endl;
    if(key == "xxxx")
    {
        if(key == "xxxx")
            cout << "The computer managed to crack your code" << endl;
        else
            cout << "The computer failed to crack your code" << endl;
    }
    else if(codes_size == 0)
    {
        cout << "You cheated!!!" << endl;
    }
    else
    {
        cout << "Other possibilities:" << endl;
        for(int i=0; i<codes_size; ++i)
        {
            string code_temp = "";
            int number_code = codes[i];
            for(int j=0; j<4; ++j)
            {
                code_temp += alphabet[number_code%6];
                number_code /= 6;
            }

            cout << code_temp << endl;
        }
        cout << endl << "Remaining quantity: " << codes_size << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}



