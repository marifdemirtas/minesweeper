#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
    int** board;
    char** mask;
    int row_count;
    int col_count;
    int safe_squares;
public:
    Board(int row_count, int col_count);
    ~Board();
    void showBoard(bool bombs=false);
    void placeBomb(int x, int y);
    void incrementCell(int x, int y);
    bool revealClick(int x, int y);
    void reveal(int x, int y);
    void markBomb(int x, int y);
    int getSafe(){
        return safe_squares;
    }
};

#endif