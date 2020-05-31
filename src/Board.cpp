
#include "Board.h"
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace std;
#define cells2(row, col) (cells2[make_pair(row, col)])
#define SIZE_CHECK(n) (n >= 5 && n <= 50)
#define CHECK_MINES(mines) (mines > 0 && mines <= 500)
#define BOARD_SIZE_RECOMMENDATIONS "\nOur recommendations:\nBegginers: 8 8 10\nInter: 16 16 40\nExpert: 16 30 99\nInsain: 50 50 500\n"

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
    if (!settingsValidation(height, width, mines))
    {
        return;
    }

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
        cout << "invalid commend. please select o to open OR p to flag" << endl;
    }
    if (inBoard(row - 1, col - 1))
    {
        valid = true;
    }
    else
    {
        cout << "invalid point.   please select a point on the board" << endl;
    }

    bool res = valid && comValid;
    return res;
}
bool Board::settingsValidation(int row, int col, int mines)
{
    if (!SIZE_CHECK(row) || !SIZE_CHECK(col))
    {
        cout << "\nSORRY\n"
             << row << "," << col << " is an incompatible size\n please choose size between 5 - 50 " << BOARD_SIZE_RECOMMENDATIONS << endl;
        return false;
    }
    if (CHECK_MINES(mines))
    {
        if (mines > row * col / 2)
        {
            cout << "\nSORRY\n"
                 << "please create a bigger board or place less mines" << BOARD_SIZE_RECOMMENDATIONS << endl;
            return false;
        }
    }
    else
    {
        cout << "\nSORRY\n"
             << mines << " is an incompatible mines amount\n please choose size between 1 - 500 (not more then half the cells)" << endl;
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
                if (!(cells2(row + j, col + i).IS_OPEN))
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

    if (cells2(row, col).value == flags)
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
    for (const auto &entry : cells2)
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
        cout << "\n\ncongratulations! you've WON!!!" << endl;
    }
}

bool Board::isGameOver()
{
    return !(lose || win);
}
