#include <string>
#include <iostream>
#include <exception>

#include "board.h"
#include "game.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 4){
        cout << "This program should be called with three integer arguments: row_count, col_count, bomb_count" << endl;        
        return 1;
    }
    Game g(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    g.play();
    cout << "Game over." << endl;
    g.showResults();
    return 0;
}