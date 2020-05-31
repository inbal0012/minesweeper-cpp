
#include "Board.h"
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace std;
#define cells(row, col) (cells[make_pair(row, col)])
#define SIZE_CHECK(n) (n >= 5 && n <= 50)
#define CHECK_MINES(mines) (mines > 0 && mines <= 500)

//strings
//print
#define CLOSE_CELL_CHAR '#'
#define BOMB_CELL_CHAR 'X'
#define FLAG_CELL_CHAR 'p'
#define EMPTY_CELL_CHAR ' '

//input validation
#define INVALID_COMMEND "invalid commend. please select o to open OR p to flag"
#define INVALID_POINT "invalid point.   please select a point on the board"

//settings validation
#define SORRY "\nSORRY\n"
#define SIZE_ERROR " is an incompatible size\n please choose size between 5 - 50 "
#define MINES_RATIO_ERROR "please create a bigger board or place less mines"
#define MINES_COUNT_ERROR " is an incompatible mines amount\n please choose size between 1 - 500 (not more then half the cells)"
#define BOARD_SIZE_RECOMMENDATIONS "\nOur recommendations:\nBegginers: 8 8 10\nInter: 16 16 40\nExpert: 16 30 99\nInsain: 50 50 500\n"

#define WON_STRING "\n\ncongratulations! you've WON!!!"
#define LOSE_STRING "Loooooseerrrrrr"

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
            Cell &cell = cells(i, j);
            char v = CLOSE_CELL_CHAR;
            if (cell.state == State::open || showAll)
                v = char(cell.value < 0 ? BOMB_CELL_CHAR : cell.IS_EMPTY ? EMPTY_CELL_CHAR : cell.value + '0'); //nested lamda. if bomb - x, if empty -> ' ', else show num
            else if (cell.state == State::flag)
                v = FLAG_CELL_CHAR;

            std::cout << "| " << char(v) << " ";
        }
        std::cout << "|" << endl;
        printHorizontalLine();
    }
}

Board::Board(int height, int width, int mines)
{
    if (!settingsValidation(height, width, mines))
    {
        return;
    }

    this->height = height;
    this->width = width;
    this->mines = mines;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Cell cell;
            cells.insert(make_pair(make_pair(i, j), cell));
        }
    }

    createBoard();
}
Board::~Board()
{
}

//Setters
int Board::getMines()
{
    return mines;
}
int Board::getWidth()
{
    return width;
}
int Board::getHeight()
{
    return height;
}

//Setters END

//Validation
bool Board::inputValidation(char commend, int row, int col)
{
    bool valid = false;
    bool comValid = false;
    char upCom = toupper(commend);
    if (upCom == 'O' || upCom == 'P')
    {
        comValid = true;
    }
    else
    {
        cout << INVALID_COMMEND << endl;
    }
    if (inBoard(row - 1, col - 1))
    {
        valid = true;
    }
    else
    {
        cout << INVALID_POINT << endl;
    }

    bool res = valid && comValid;
    return res;
}
bool Board::settingsValidation(int row, int col, int mines)
{
    if (!SIZE_CHECK(row) || !SIZE_CHECK(col))
    {
        cout << SORRY
             << row << "," << col << SIZE_ERROR << BOARD_SIZE_RECOMMENDATIONS << endl;
        return false;
    }
    if (CHECK_MINES(mines))
    {
        if (mines > row * col / 2)
        {
            cout << SORRY
                 << MINES_RATIO_ERROR << BOARD_SIZE_RECOMMENDATIONS << endl;
            return false;
        }
    }
    else
    {
        cout << SORRY
             << mines << MINES_COUNT_ERROR << BOARD_SIZE_RECOMMENDATIONS << endl;
        return false;
    }
    return true;
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
        if (cells(row, col).IS_BOMB)
        {
            continue;
        }

        cells(row, col).value = -1;
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
                nbrs.push_back(&cells(row + j, col + i));
            }
        }
    }
    return nbrs;
}

bool Board::click(int row, int col, char commend)
{
    char upCommend = toupper(commend);
    Cell &cell = cells(row, col);

    if (cell.IS_OPEN)
    {
        seeEnough(row, col);
        checkWin();
        return true;
    }
    switch (upCommend)
    {
    case 'O':
        if (cell.IS_OPEN)
        {
            seeEnough(row, col);
            checkWin();
            return true;
        }
        if (cell.IS_FLAG)
        {
            return true;
        }
        openCell(row, col);
        return lose;

    case 'P':
        if (cell.IS_FLAG)
        {
            cell.state = State::close;
            mines++;
            return true;
        }
        else
        {
            cell.state = State::flag;
            mines--;
            checkWin();
            return true;
        }

    default:
        return true;
    }
}

void Board::openCell(int row, int col)
{
    Cell &cell = cells(row, col);

    if (cell.IS_FLAG)
    {
        return;
    }
    cell.state = State::open;
    if (cell.IS_BOMB)
    {
        std::cout << LOSE_STRING << endl;
        lose = true;
        return;
    }
    seeEnough(row, col);
    if (cell.IS_EMPTY)
    {
        openNeighbors(row, col);
    }
}

void Board::openNeighbors(int row, int col)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            else if (inBoard(row + j, col + i))
            {
                if (!(cells(row + j, col + i).IS_OPEN))
                {
                    openCell(row + j, col + i);
                }
                else
                    continue;
            }
        }
    }
}

void Board::seeEnough(int row, int col)
{
    auto nbrs = getAllNeighbors(row, col);
    flags = 0;

    for (auto &cell : nbrs)
    {
        if (cell->IS_FLAG)
        {
            flags++;
        }
    }

    if (cells(row, col).value == flags)
    {
        openNeighbors(row, col);
    }
}

bool Board::checkWin()
{
    if (mines == 0)
    {
        checkBoard();
    }
}

void Board::checkBoard()
{
    for (const auto &entry : cells)
    {
        auto key_pair = entry.first;
        Cell cell = entry.second;
        if (cell.state == State::close)
        {
            openCell(key_pair.first, key_pair.second);
        }
    }

    if (!lose)
    {
        win = true;
        cout << WON_STRING << endl;
    }
}

bool Board::isGameOver()
{
    return !(lose || win);
}
