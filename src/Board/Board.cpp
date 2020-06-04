
#include "Board.h"

Board::Board(int height, int width, int mines)
{
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

Board *Board::CreateBoard(int height, int width, int mines)
{
    // if (!settingsValidation(height, width, mines))
    // {
    //     return nullptr;
    // }

    return new Board(height, width, mines);
}
bool Board::createBoard()
{
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

    return true;
}

void Board::genereteNumbers(int row, int col)
{
    auto nbrs = getAllNeighbors(row, col);
    for (auto &entry : nbrs)
    {
        auto cell = entry.second;
        if (cell->IS_BOMB)
            continue;

        cell->value++;
    }
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
bool Board::getLose()
{
    return lose;
}
bool Board::getWin()
{
    return win;
}
Cell &Board::getCellAt(int row, int col)
{
    if (inBoard(row, col))
    {
        return cells(row, col);
    }
}
std::vector<pair<point, Cell *>> Board::getAllNeighbors(int row, int col)
{
    vector<pair<point, Cell *>> nbrs;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            else if (inBoard(row + j, col + i))
            {
                point p = make_pair(row + j, col + i);
                nbrs.push_back(make_pair(p, &cells(row + j, col + i)));
            }
        }
    }
    return nbrs;
}
//Setters END

//Change Cell/s
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
    auto nbrs = getAllNeighbors(row, col);
    for (auto &entry : nbrs)
    {
        auto nbr = entry.second;
        if (!(nbr->IS_OPEN))
        {
            int row = entry.first.first;
            int col = entry.first.second;
            openCell(row, col);
        }
    }
}

void Board::flagCell(Cell *cell)
{
    if (cell->IS_CLOSE)
    {
        cell->state = State::flag;
        mines--;
    }
}
void Board::unflagCell(Cell *cell)
{
    if (cell->IS_FLAG)
    {
        cell->state = State::close;
        mines++;
    }
}
void Board::flagNeighbors(int row, int col)
{
    auto nbrs = getAllNeighbors(row, col);
    for (auto &entry : nbrs)
    {
        auto nbr = entry.second;
        flagCell(nbr);
    }
}

bool Board::inBoard(int row, int col)
{
    if (col < 0 || col >= width || row < 0 || row >= height)
    {
        return false;
    }

    return true;
}
void Board::seeEnough(int row, int col)
{
    auto nbrs = getAllNeighbors(row, col);
    int flags = 0;

    for (auto &entry : nbrs)
    {
        auto cell = entry.second;
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
    }
}
