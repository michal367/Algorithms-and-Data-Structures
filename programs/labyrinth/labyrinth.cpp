#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <fstream>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace std;

enum sign{
    wall = '#',
    start = 'S',
    path = ' ',
    good_path = '.',
    end = 'E'
};
enum direction{
    none = '-',
    left = 'l',
    right = 'r',
    top = 't',
    bottom = 'b'
};


// x is the column, y is the row. The origin (0,0) is top-left.
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void setConsoleColour(unsigned short colour)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


void print_labyrinth(const vector<std::vector<char>>& labyrinth){
    for(size_t i=0; i < labyrinth.size(); i++){
        for(size_t j=0; j < labyrinth[i].size(); j++){
            if(labyrinth[i][j] == sign::wall)
                cout << char(177);
            else
                cout << labyrinth[i][j];
        }
        cout << endl;
    }
}

pair<int,int> find_sign(const vector<std::vector<char>>& labyrinth, sign s){
    for(size_t i=0; i < labyrinth.size(); i++){
        for(size_t j=0; j < labyrinth[i].size(); j++)
            if(labyrinth[i][j] == s)
                return pair<int,int>(i,j);
    }
    return pair<int,int>(-1,-1);
}




int main(int argc, char** argv){

    // read labyrinth
    vector<std::vector<char>> labyrinth;

    string filename;
    if(argc == 2)
        filename = argv[1];
    else
        filename = "labyrinth.txt";

    ifstream file(filename);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            vector<char> v(line.begin(), line.end());
            labyrinth.push_back(v);
        }
        file.close();
    }
    else{
        cout << "Unable to open file " << filename << endl;
        return -1;
    }


    print_labyrinth(labyrinth);

    cout << endl;
    system("pause");
    system("cls");


    pair<int,int> start = find_sign(labyrinth, sign::start);
    pair<int,int> end = find_sign(labyrinth, sign::end);
    if(start.first == -1){
        cout << "No S sign (start)" << endl;
        return 0;
    }
    if(end.first == -1){
        cout << "No E sign (end)" << endl;
        return 0;
    }


    // create visited matrix
    int rows = labyrinth.size();
    int cols = labyrinth[0].size();
    vector<std::vector<char>> visited(rows, std::vector<char>(cols, '-'));



    labyrinth[end.first][end.second] = sign::path;

    // BFS
    queue<pair<int,int> > q;
    q.push(start);
    visited[start.first][start.second] = sign::start;
    bool found = false;
    while(!q.empty()){
        pair<int,int> p = q.front();
        q.pop();

        if(p == end){
            found = true;
            break;
        }

        int y = p.first;
        int x = p.second;

        if(labyrinth[y][x-1] == sign::path && visited[y][x-1] == direction::none){
            q.push(pair<int,int>(y,x-1));
            visited[y][x-1] = direction::right;
        }
        if(labyrinth[y+1][x] == sign::path && visited[y+1][x] == direction::none){
            q.push(pair<int,int>(y+1,x));
            visited[y+1][x] = direction::top;
        }
        if(labyrinth[y][x+1] == sign::path && visited[y][x+1] == direction::none){
            q.push(pair<int,int>(y,x+1));
            visited[y][x+1] = direction::left;
        }
        if(labyrinth[y-1][x] == sign::path && visited[y-1][x] == direction::none){
            q.push(pair<int,int>(y-1,x));
            visited[y-1][x] = direction::bottom;
        }
    }

    labyrinth[end.first][end.second] = sign::end;
    print_labyrinth(labyrinth);

    if(found == true){
        // recreating correct path
        vector<pair<int,int> > path;

        int y = end.first;
        int x = end.second;
        char way = visited[y][x];
        while(way != sign::start){
            path.push_back(pair<int,int>(y,x));

            if(way == direction::top)
                y--;
            else if(way == direction::right)
                x++;
            else if(way == direction::bottom)
                y++;
            else if(way == direction::left)
                x--;
            way = visited[y][x];
        }


        ShowConsoleCursor(false);

        for(auto it = path.rbegin(); it != path.rend()-1; it++){
            char act = visited[(it)->first][(it)->second];
            char next = visited[(it+1)->first][(it+1)->second];

            if(act == direction::left && next == direction::left ||
               act == direction::right && next == direction::right)
                labyrinth[it->first][it->second] = char(196);
            else if(act == direction::top && next == direction::top ||
               act == direction::bottom && next == direction::bottom)
                labyrinth[it->first][it->second] = char(179);
            else if(act == direction::left && next == direction::top ||
               act == direction::bottom && next == direction::right)
                labyrinth[it->first][it->second] = char(191);
            else if(act == direction::top && next == direction::left ||
               act == direction::right && next == direction::bottom)
                labyrinth[it->first][it->second] = char(192);
            else if(act == direction::left && next == direction::bottom ||
               act == direction::top && next == direction::right)
                labyrinth[it->first][it->second] = char(217);
            else if(act == direction::bottom && next == direction::left ||
               act == direction::right && next == direction::top)
                labyrinth[it->first][it->second] = char(218);

            //system("cls");
            //print_labyrinth(labyrinth);
            //Sleep(150);

            setConsoleColour(FOREGROUND_RED);
            setCursorPosition(it->second, it->first);
            cout << labyrinth[it->first][it->second];
            Sleep(100);
        }

        //system("cls");
        //print_labyrinth(labyrinth);
        setCursorPosition(0, rows);
        setConsoleColour(0x7);
        cout << endl << "Done" << endl;
        ShowConsoleCursor(true);
    }
    else{
        cout << endl << "There is no path from S to E" << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}
