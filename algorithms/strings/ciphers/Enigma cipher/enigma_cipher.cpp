#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;


bool isnumber(string str)
{
    for(int i=0; i<str.size(); ++i)
        if(!isdigit(str[i]))
            return false;
    return true;
}
bool isalphabetic(string str)
{
    for(int i=0; i<str.size(); ++i)
        if(!isalpha(str[i]))
            return false;
    return true;
}
string strtoupper(string str)
{
    for(int i=0; i<str.size(); ++i)
        str[i] = toupper(str[i]);
    return str;
}


int main()
{
    cout << "Enigma cipher" << endl
         << "rings_conf - configuration of 3 rotors in the form of a three-digit number 111...555" << endl
         << "start_chars - initial position of the rotors in the form of a three-character string AAA...ZZZ" << endl
         << "plugboard - state of plugboard in the form of a string made of pairs of letters e.g. AXDSFE - A with X, D with S and F with E" << endl
         << "str - text to encrypt (use X instead of spaces)" << endl << endl;


    string rings_conf, start_chars, plugboard = "", str;

    cout << "rings_conf: ";
    do{
        cin >> rings_conf;
    }while(rings_conf.size() != 3 || !isnumber(rings_conf) || rings_conf < "111" || rings_conf > "555");
    cout << "start_chars: ";
    do{
        cin >> start_chars;
        cin.ignore();
    }while(start_chars.size() != 3 || !isalphabetic(start_chars));
    cout << "plugboard: ";
    do{
        getline(cin, plugboard);
    }while(!isalphabetic(plugboard) || plugboard.size() % 2 == 1 && plugboard.size() != 0);
    cout << "str: ";
    getline(cin, str);
    cout << endl;

    start_chars = strtoupper(start_chars);
    plugboard = strtoupper(plugboard);
    str = strtoupper(str);



    // ========================================
    // machine configuration

    string ciphers[5] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
                        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
                        "VZBRGITYUPSDNHLXAWMJQOFECK"};
    char ring_change[5] = {'R', 'F', 'W', 'K', 'A'};
    string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    string plugboard_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    int rings[3] = {rings_conf[2]-'0' -1,
                    rings_conf[1]-'0' -1,
                    rings_conf[0]-'0' -1};
    int rings_position[3] = {start_chars[2]-'A',
                            start_chars[1]-'A',
                            start_chars[0]-'A'};
    for(int i=0; i<plugboard.size(); i += 2)
    {
        plugboard_str[plugboard[i]-'A'] = plugboard[i+1];
        plugboard_str[plugboard[i+1]-'A'] = plugboard[i];
    }


    // ========================================
    // encryption

    for(int i=0; i<str.size(); ++i)
    {
        bool move = true;
        for(int j=0; move && j<3; ++j)
        {
            move = ('A' + rings_position[j] == ring_change[rings[j]]);
            rings_position[j] = (rings_position[j] + 1) % 26;
        }

        char ch = str[i];

        ch = plugboard_str[ch-'A'];

        for(int j=0; j<3; ++j)
        {
            ch = ciphers[rings[j]][(ch-'A' + rings_position[j]) % 26];
            ch = 'A' + (ch-'A' - rings_position[j] + 26) % 26;
        }

        ch = reflector[ch-'A'];

        for(int j=2; j>=0; --j)
        {
            ch = 'A' + (ch-'A' + rings_position[j]) % 26;
            ch = 'A' + (ciphers[rings[j]].find(ch) - rings_position[j] + 26) % 26;
        }

        ch = plugboard_str[ch-'A'];

        str[i] = ch;
    }


    cout << "Encrypted text: " << str << endl;


    // ========================================
    // decryption

    rings_position[0] = start_chars[2]-'A';
    rings_position[1] = start_chars[1]-'A';
    rings_position[2] = start_chars[0]-'A';

    for(int i=0; i<str.size(); ++i)
    {
        bool move = true;
        for(int j=0; move && j<3; ++j)
        {
            move = ('A' + rings_position[j] == ring_change[rings[j]]);
            rings_position[j] = (rings_position[j] + 1) % 26;
        }

        char ch = str[i];

        ch = plugboard_str[ch-'A'];

        for(int j=0; j<3; ++j)
        {
            ch = ciphers[rings[j]][(ch-'A' + rings_position[j]) % 26];
            ch = 'A' + (ch-'A' - rings_position[j] + 26) % 26;
        }

        ch = reflector[ch-'A'];

        for(int j=2; j>=0; --j)
        {
            ch = 'A' + (ch-'A' + rings_position[j]) % 26;
            ch = 'A' + (ciphers[rings[j]].find(ch) - rings_position[j] + 26) % 26;
        }

        ch = plugboard_str[ch-'A'];

        str[i] = ch;
    }

    cout << "Decrypted text: " << str << endl;

    cout << endl;
    system("pause");
    return 0;
}





