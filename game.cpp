#include <cstdlib>
#include <ctime>
#include <iostream>

#include "game.h"

using namespace std;

Game::Game(int row_count, int col_count, int bomb_count)
{
    if (row_count * col_count < bomb_count){
        throw logic_error("Too many bombs!");
    }
    srand(time(NULL));
    b = new Board(row_count, col_count);
    for (int i = 0; i < bomb_count; i++)
    {
        try{
            b->placeBomb(rand() % row_count, rand() % col_count);
        }catch(const exception& e){
            i--;
        }
    }
    moveCount = 0;
    timer = 0;
    cout << "Game is ready!" << endl;
}

Game::~Game()
{
    delete b;
}

bool Game::play()
{
    cout << "Game starts now!" << endl;

    timer = time(NULL);
    while(b->getSafe() > 0)
    {
        b->showBoard();
        cout << "Enter coordinates to reveal: " << endl;
        int x = 0, y = 0;
        while(!(cin >> x >> y)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter coordinates as integers, seperated by space: ";
        }
        moveCount++;
        try{
            if(b->revealClick(x-1, y-1)){
                break;
            }
        }catch(const out_of_range& e){
            cout << "Please enter values inside the board coordinates." << endl;
        }catch(const domain_error& e){
            cout << "Given coordinates are already revealed." << endl;
        }
    }
    if (b->getSafe() == 0){
        b->showBoard();
        cout << "All squares found!" << endl;
        outcome = true;
    } else {
        b->showBoard(true);
        cout << "BOMB FOUND!" << endl;
        outcome = false;
    }
    timer = time(NULL) - timer;
    return outcome;
}

void Game::showResults(){
    if (outcome){
        cout << "Congratulations!" << endl;
    }
    cout << "You spend " << timer << " seconds." << endl;
    cout << "You made " << moveCount << " moves." << endl;
}