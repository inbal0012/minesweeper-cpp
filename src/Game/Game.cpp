#include "Game.h"

Game::Game(/* args */)
{
}
Game::~Game()
{
}

void Game::Play()
{
    settings();
    PrintBoard();
    clickHandler();
    startTime = time(NULL);
    do
    {
        SPACE(10);
        PrintBoard();
    } while (clickHandler());
    PrintBoard(true);
}

//prints
void Game::printHorizontalLine()
{
    std::cout << "--+"; // the left bar

    for (int i = 0; i < b->getWidth(); ++i)
        std::cout << "---+";
    std::cout << "\n";
}
void Game::PrintBoard(bool showAll)
{
    std::cout << "0 ";
    for (int i = 0; i < b->getWidth(); ++i)
        std::cout
            << "| " << (i + 1) % 10 << " ";

    std::cout << "|"; // the right bar
    std::cout << "\n";

    printHorizontalLine();
    for (int i = 0; i < b->getHeight(); i++)
    {
        std::cout << (i + 1) % 10 << " ";
        for (int j = 0; j < b->getWidth(); ++j)
        {
            Cell &cell = b->getCellAt(i, j);
            char v = CLOSE_CELL_CHAR;
            if (cell.IS_OPEN || showAll)
                v = char(cell.value < 0 ? BOMB_CELL_CHAR : cell.IS_EMPTY ? EMPTY_CELL_CHAR : cell.value + '0'); //nested lamda. if bomb - x, if empty -> ' ', else show num
            else if (cell.IS_FLAG)
                v = FLAG_CELL_CHAR;

            std::cout << "| " << char(v) << " ";
        }
        std::cout << "|" << endl;
        printHorizontalLine();
    }
}
void Game::printTime()
{
    if (startTime != 0)
    {
        int t = time(NULL) - startTime;
        int min = t / 60;
        int sec = t % 60;
        cout << min << ":" << sec << endl;
    }
}
void Game::printSymbleIndexAndGameInstructions()
{
    cout << "Game Symbols: \n"
         << CLOSE_CELL_CHAR << " represent a closed cell\n"
         << BOMB_CELL_CHAR << " represent a bomb!! be carfull \n"
         << FLAG_CELL_CHAR << " represent a flaged cell\n"
         << EMPTY_CELL_CHAR << " represent an empty cell\n"
         << endl;
    //TODO Game Instructions
}

//Validation
bool Game::inputValidation(char commend, int row, int col)
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
    if (b->inBoard(row - 1, col - 1))
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
bool Game::settingsValidation(int row, int col, int mines)
{
    auto SIZE_CHECK = [](int n) -> bool { return n >= 5 && n <= 50; };
    auto MINES_CHECK = [](int mines) -> bool { return mines > 0 && mines <= 500; };

    if (!SIZE_CHECK(row) || !SIZE_CHECK(col))
    {
        cout << SORRY
             << row << "," << col << SIZE_ERROR << BOARD_SIZE_RECOMMENDATIONS << endl;
        return false;
    }
    if (MINES_CHECK(mines))
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

void Game::settings()
{
    int row = -1, col = -1, mines = -1;
    bool boardCreated = false;
    do
    {
        cout << "\nhello and welcome\n"
             << "please select board size (height first then width)\n"
             << endl;
        cin >> row >> col >> mines;
        boardCreated = settingsValidation(row, col, mines);
        // if (boardCreated) {
        //     char ass;
        //     cout << "do you want to able the assistant mode? Y/N";
        //     cin >> ass;
        //     toupper(ass);
        //     if (ass=='Y' || ass == 'N') {

        //     }
        // }
    } while (!boardCreated);

    b = Board::CreateBoard(row, col, mines);
    //return Board::CreateBoreturnard(row, col, mines);
}

bool Game::clickHandler()
{
    int row = -1, col = -1;
    char commend = 'O';
    do
    {
        printTime();
        cout
            << "You have " << b->getMines() << " mines left\n"
            << "Enter commend and ROW and COL (Example: \"O 1 5\" OR \"P 6 3\"): ";
        cin >> commend >> row >> col;
    } while (!inputValidation(commend, row, col));

    click(row - 1, col - 1, commend); //user will NOT work starting with 0

    return !isGameOver();
}

bool Game::click(int row, int col, char commend)
{
    char upCommend = toupper(commend);
    Cell &cell = b->getCellAt(row, col);

    switch (upCommend)
    {
    case 'O':
        if (cell.IS_OPEN)
        {
            b->seeEnough(row, col);
            checkWin();
            return true;
        }
        else if (cell.IS_FLAG)
        {
            return true;
        }
        b->openCell(row, col);
        return b->getLose();

    case 'P':
        if (cell.IS_FLAG)
        {
            b->unflagCell(&cell);
            return true;
        }
        else if (cell.IS_OPEN)
        {
            checkAmbiguity(row, col);
            checkWin();
            return true;
        }
        else
        {
            b->flagCell(&cell);
            checkWin();
            return true;
        }

    default:
        return true;
    }
}

bool Game::checkAmbiguity(int row, int col)
{
    cout << "checkAmbiguity" << endl;
    auto nbrs = b->getAllNeighbors(row, col);
    int flags = 0, close = 0;

    for (auto &entry : nbrs)
    {
        auto cell = entry.second;
        if (cell->IS_FLAG)
        {
            flags++;
        }
        if (cell->state == State::close)
        {
            close++;
        }
    }

    if (b->getCellAt(row, col).value == flags)
    {
        b->openNeighbors(row, col);
    }
    else if (b->getCellAt(row, col).value == flags + close)
    {
        b->flagNeighbors(row, col);
    }

    cout << "checkAmbiguity END" << endl;
}

bool Game::checkWin()
{
    if (b->getMines() == 0)
    {
        b->checkBoard();
    }
}

bool Game::isGameOver()
{
    if (b->getLose())
    {
        cout << LOSE_STRING << endl;
        return true;
    }
    else if (b->getWin())
    {
        cout << WON_STRING << endl;
        return true;
    }
    return false;
}
