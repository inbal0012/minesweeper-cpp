
#include "Board.h"
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace std;
#define cells2(row, col) (cells2[make_pair(row, col)])

//prints
void Board::printHorizontalLine()
{
    std::cout << "--+"; // the left bar

    for (int i = 0; i < width; ++i)
        std::cout << "---+";
    std::cout << "\n";
}
void Board::PrintBoard(bool showAll)
{
    std::cout << "0 ";
    for (int i = 0; i < width; ++i)
        std::cout
            << "| " << (i + 1) % 10 << " ";

    std::cout << "|"; // the right bar
    std::cout << "\n";

    printHorizontalLine();
    for (int i = 0; i < height; i++)
    {
        std::cout << (i + 1) % 10 << " ";
        for (int j = 0; j < width; ++j)
        {
            //Cell &cell = cells[i][j];
            Cell &cell = cells2(i, j);
            char v = '#';
            if (cell.state == State::open || showAll)
                v = char(cell.value < 0 ? 'X' : cell.IS_EMPTY ? ' ' : cell.value + '0'); //nested lamda. if bomb - x, if empty -> ' ', else show num
            else if (cell.state == State::flag)
                v = 'P';

            std::cout << "| " << char(v) << " ";
        }
        std::cout << "|" << endl;
        printHorizontalLine();
    }
}

Board::Board(int height, int width, int mines)
{
    this->height = height;
    this->width = width;
    this->mines = mines;

    cells = (Cell **)(calloc(height, sizeof(Cell *)));
    for (int i = 0; i < height; i++)
    {
        cells[i] = (Cell *)(calloc(width, sizeof(Cell)));
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Cell cell;
            cells2.insert(make_pair(make_pair(i, j), cell));
        }
    }

    createBoard();
}
Board::~Board()
{
}

bool Board::createBoard()
{
    std::cout << "createBoard" << endl;

    /* initialize random seed: */
    srand(time(NULL));

    int placedMines = 0;
    while (placedMines < mines)
    {
        int num = rand() % (height * width);
        int col = num % width;
        int row = num / width;

        if (!inBoard(row, col))
        {
            continue;
        }
        if (cells2(row, col).IS_BOMB)
        {
            continue;
        }

        //cells[row][col].value = -1;
        cells2(row, col).value = -1;
        placedMines++;
        genereteNumbers(row, col);
    }

    std::cout << "createBoard END" << endl;

    return true;
}

bool Board::inBoard(int row, int col)
{
    if (col < 0 || col >= width || row < 0 || row >= height)
    {
        return false;
    }

    return true;
}

void Board::genereteNumbers(int row, int col)
{
    auto nbrs = getAllNeighbors(row, col);
    for (auto &cell : nbrs)
    {
        if (cell->IS_BOMB)
            continue;

        cell->value++;
    }
}

vector<Cell *> Board::getAllNeighbors(int row, int col)
{
    vector<Cell *> nbrs;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            else if (inBoard(row + j, col + i))
            {
                //nbrs.push_back(&cells[row + j][col + i]);
                nbrs.push_back(&cells2(row + j, col + i));
            }
        }
    }
    return nbrs;
}

bool Board::click(int row, int col, char commend)
{
    char upCommend = toupper(commend);
    //Cell &cell = cells[row][col];
    Cell &cell = cells2(row, col);

    if (cell.IS_OPEN)
    {
        return true;
    }
    switch (upCommend)
    {
    case 'O':
        if (cell.IS_FLAG)
        {
            return true;
        }
        openCell(row, col);
        return lose;

    case 'P':
        cell.state = State::flag;
        mines--;
        return true;

    default:
        return true;
    }
}

void Board::openCell(int row, int col)
{
    //Cell &cell = cells[row][col];
    Cell &cell = cells2(row, col);

    if (cell.IS_FLAG)
    {
        return;
    }
    cell.state = State::open;
    if (cell.IS_BOMB)
    {
        std::cout << "Loooooseerrrrrr" << endl;
        lose = true;
        return;
    }
    if (cell.IS_EMPTY)
    {
        // TODO openNeighbors(row, col);
    }
}
