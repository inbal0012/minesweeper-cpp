#include "Cell.h"
#include <vector>

#define SIZE 8

class Board
{
private:
    int height, width, mines, flags = 0;
    Cell **cells;

    void printHorizontalLine();
    bool createBoard();
    bool inBoard(int row, int col);
    void genereteNumbers(int row, int col);
    std::vector<Cell *> getAllNeighbors(int row, int col);

public:
    Board(int height = SIZE, int width = SIZE, int mines = 10);
    ~Board();
    void PrintBoard(bool showAll = false);
};