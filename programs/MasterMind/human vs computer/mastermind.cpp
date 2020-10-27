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
    cout << endl;



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
            // delete all containing any letters of code
            if(key.size() == 0)
            {
                int i2 = 0;
                for(int i=0; i<codes_size; ++i)
                {
                    string code_quess_copy = code_quess;
                    int number_code = codes[i];
                    bool increase_array = true;

                    for(int j=0; j<4; ++j)
                    {
                        char letter = alphabet[number_code%6];
                        number_code /= 6;

                        for(int k=0; k<4; ++k)
                            if(letter == code_quess_copy[k])
                            {
                                increase_array = false;
                                break;
                            }
                        if(!increase_array)
                            break;
                    }

                    // good value
                    if(increase_array)
                    {
                        codes[i2] = codes[i];
                        ++i2;
                    }
                }
                codes_size = i2;
            }
            // removing all permutations
            // delete all not containing some code letter
            else if(key.size() < 4)
            {
                int i2 = 0;
                for(int i=0; i<codes_size; ++i)
                {
                    string code_quess_copy = code_quess;
                    int number_code = codes[i];
                    bool increase_array = true;

                    int good_letters_counter = 0;
                    for(int j=0; j<4; ++j)
                    {
                        char letter = alphabet[number_code%6];
                        number_code /= 6;

                        for(int k=0; k<4; ++k)
                            if(letter == code_quess_copy[k])
                            {
                                code_quess_copy[k] = '.';
                                ++good_letters_counter;
                                break;
                            }
                    }

                    // good value
                    if(good_letters_counter >= key.size() && good_letters_counter < 4)
                    {
                        codes[i2] = codes[i];
                        ++i2;
                    }
                }
                codes_size = i2;
            }
            // delete all not containing every letter of code
            else if(key.size() == 4 && key != "xxxx")
            {
                int i2 = 0;
                for(int i=0; i<codes_size; ++i)
                {
                    string code_quess_copy = code_quess;
                    int number_code = codes[i];
                    bool increase_array = true;

                    int good_letters_counter = 0;
                    for(int j=0; j<4; ++j)
                    {
                        char letter = alphabet[number_code%6];
                        number_code /= 6;

                        for(int k=0; k<4; ++k)
                            if(letter == code_quess_copy[k])
                            {
                                code_quess_copy[k] = '.';
                                ++good_letters_counter;
                                break;
                            }
                    }

                    // good value
                    if(good_letters_counter == 4)
                    {
                        codes[i2] = codes[i];
                        ++i2;
                    }
                }
                codes_size = i2;
            }
        }


        for(int i=0; i<codes_size; ++i)
        {
            string code_2 = "";
            int number_code = codes[i];
            for(int j=0; j<4; ++j)
            {
                code_2 += alphabet[number_code%6];
                number_code /= 6;
            }

            //cout << code_2 << endl;
        }
        //cout << codes_size << endl << endl;



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


        cout << round_counter << ". " << endl << code_quess << endl;


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
        cout << endl;


    }while(round_counter < 6 && key != "xxxx");

    cout << endl;
    if(key == "xxxx")
        cout << "The computer managed to crack your code" << endl
             << code << endl;
    else
        cout << "The computer failed to crack your code" << endl
             << code << endl;



    cout << endl;
    system("pause");
    return 0;
}


