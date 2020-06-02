#include <iostream>
#include "src/Board.cpp"

using namespace std;

#define SPACE(n)                 \
    for (int i = 0; i < 10; i++) \
    cout << endl

bool clickHandler(Board &b)
{
    int row = -1, col = -1;
    char commend = 'O';
    do
    {
        cout << "You have " << b.getMines() << " mines left\n"
             << "Enter commend and ROW and COL (Example: \"O 1 5\" OR \"P 6 3\"): ";
        cin >> commend >> row >> col;
    } while (!b.inputValidation(commend, row, col));

    b.click(row - 1, col - 1, commend); //user will NOT work starting with 0

    return !b.isGameOver();
}

void play()
{
    Board b = settings();
    b.PrintBoard(true);
    do
    {
        SPACE(10);
        b.PrintBoard();
    } while (clickHandler(b));
    b.PrintBoard(true);
}

Board settings()
{
    int row = -1, col = -1, mines = -1;
    bool boardCreated = false;
    do
    {
        cout << "\nhello and welcome\n"
             << "please select board size (height first then width)\n"
             << endl;
        cin >> row >> col >> mines;
        boardCreated = Board::settingsValidation(row, col, mines);
        // if (boardCreated) {
        //     char ass;
        //     cout << "do you want to able the assistant mode? Y/N";
        //     cin >> ass;
        //     toupper(ass);
        //     if (ass=='Y' || ass == 'N') {

        //     }
        // }
    } while (!boardCreated);

    return Board(row, col, mines);
}

int main()
{
    /*todo: 
    Ass mood - cB(r, c) -> if cell != empty then try again (spinner?)
    If clsNbrs+flags == value then flagNbrs.

    strategy -> code duplications
    factory -> getNewBoard 
    files -> score board
    timer -> threads?
    last action -> color?
    symble index + game instructions
     */
    play();

    return 0;
}