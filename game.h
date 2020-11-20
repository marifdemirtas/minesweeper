#include "board.h"

class Game
{
private:
    Board* b;
    int timer;
    int moveCount;
    bool outcome;
public:
    Game(int row_count, int col_count, int bomb_count);
    ~Game();
    bool play();
    void showResults();
};
