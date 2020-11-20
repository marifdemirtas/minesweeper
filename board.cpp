#include <iostream>
#include "board.h"

using namespace std;

/**
 * Constructor
*/
Board::Board(int row_count, int col_count)
{
    board = new int*[row_count];
    for (int i = 0; i < row_count; i++){
        board[i] = new int[col_count];
        for (int j = 0; j < col_count; j++){
            board[i][j] = 0;
        }
    }

    mask = new char*[row_count];
    for (int i = 0; i < row_count; i++){
        mask[i] = new char[col_count];
        for (int j = 0; j < col_count; j++){
            mask[i][j] = '-';
        }
    }

    this->row_count = row_count;
    this->col_count = col_count;
    this->safe_squares = row_count * col_count;
}

Board::~Board()
{
    for (int i = 0; i < row_count; i++)
    {
        delete[] board[i];
        delete[] mask[i];
    }
   delete[] board;
   delete[] mask;
}

/**
 * Shows the board under the mask.
 * Shows value of square if mask is opened, else the symbol on the mask.
*/
void Board::showBoard(bool bombs)
{
    for (int i = 0; i < row_count; i++){
        for (int j = 0; j < col_count; j++){
            if (mask[i][j] == '.'){
                cout << board[i][j] << " ";
            } else {
                if (board[i][j] == 9 && bombs){
                    cout << board[i][j] << " ";
                } else {
                    cout << mask[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

/**
 * Places bomb at given coordinate 
 *
 */
void Board::placeBomb(int x, int y)
{
    if (x >= row_count || y >= col_count || x < 0 || y < 0){
        throw out_of_range("Given coordinate is out of board");
    }
    if (board[x][y] == 9){
        throw domain_error("Already placed a bomb there");
    }
    board[x][y] = 9;
    safe_squares--;

    incrementCell(x-1, y-1);
    incrementCell(x  , y-1);
    incrementCell(x+1, y-1);
    incrementCell(x-1, y  );
    incrementCell(x+1, y  );
    incrementCell(x-1, y+1);
    incrementCell(x  , y+1);
    incrementCell(x+1, y+1);
}

void Board::incrementCell(int x, int y){
    if (x < row_count && y < col_count && (x >= 0 && y >= 0) && board[x][y] < 8){    
        board[x][y]++;
    }
}

bool Board::revealClick(int x, int y){
    if (x >= row_count || y >= col_count || x < 0 || y < 0){
        throw out_of_range("Given coordinate is out of board");
    }
    if (mask[x][y] != '-'){
        throw domain_error("Given coordinate is already revealed");
    }
    if (board[x][y] == 9){
        return true;
    } else {
        mask[x][y] = '.';
        safe_squares--;
        if (board[x][y] == 0){
            reveal(x-1, y-1);
            reveal(x  , y-1);
            reveal(x+1, y-1);
            reveal(x-1, y  );
            reveal(x+1, y  );
            reveal(x-1, y+1);
            reveal(x  , y+1);
            reveal(x+1, y+1);    
        }
        return false;
    }

}

void Board::reveal(int x, int y){
    if ((x < row_count && y < col_count) && (x >= 0 && y >= 0)){
        if (mask[x][y] == '-'){
            mask[x][y] = '.';
            safe_squares--;
            if (board[x][y] == 0){
                reveal(x-1, y-1);
                reveal(x  , y-1);
                reveal(x+1, y-1);
                reveal(x-1, y  );
                reveal(x+1, y  );
                reveal(x-1, y+1);
                reveal(x  , y+1);
                reveal(x+1, y+1);    
            }
        }
    }
}

void Board::markBomb(int x, int y){
    if (x >= row_count || y >= col_count || x < 0 || y < 0){
        throw out_of_range("Given coordinate is out of board");
    }
    if (mask[x][y] != '-'){
        throw domain_error("Given coordinate is not hidden");
    }
    if (mask[x][y] == '!')
    {
        mask[x][y] == '-';
    } else {
        mask[x][y] = '!';        
    }
    
}
