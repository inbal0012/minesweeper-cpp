#
#ifndef _Board
#define _Board

#include "../Cell.h"
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace std;

#define SIZE 8
#define cells(row, col) (cells[make_pair(row, col)])

typedef std::pair<int, int> point;
typedef std::map<point, Cell> matrix;

class Board
{
private:
    int height, width, mines, flags = 0, openCells = 0;
    std::map<point, Cell> cells;
    bool lose = false, win = false;

    bool createBoard();
    void genereteNumbers(int row, int col);
    Board(int height = SIZE, int width = SIZE, int mines = 10);

public:
    static Board *CreateBoard(int height, int width, int mines);
    ~Board();
    //Getters
    int getMines();
    int getFlags();
    int getWidth();
    int getHeight();
    bool getLose();
    bool getWin();
    int getOpenCells();
    Cell &getCellAt(int row, int col);
    std::vector<pair<point, Cell *>> getAllNeighbors(int row, int col);
    //Change Cell/s
    void openCell(int row, int col);
    void openNeighbors(int row, int col);
    void flagCell(Cell *cell);
    void unflagCell(Cell *cell);
    void flagNeighbors(int row, int col);
    //game
    bool inBoard(int row, int col);
    void seeEnough(int row, int col);
    void checkBoard();
};

#endif // _Board
