#include <iostream>
#include "src/Board.cpp"

using namespace std;

#define SPACE(n)                 \
    for (int i = 0; i < 10; i++) \
    cout << endl

bool play(Board &b)
{
    int row = -1, col = -1;
    char commend = 'O';
    do
    {
        cout << "You have " << b.getMines() << " mines left\n"
             << "Enter ROW and COL and command (Example: \"O 1 5\" OR \"P 6 3\"): ";
        cin >> commend >> row >> col;
    } while (!b.inputValidation(commend, row, col));

    b.click(row - 1, col - 1, commend); //user will NOT work starting with 0

    return !b.hasLost();
}
int main()
{
    Board b(8, 8, 10);
    do
    {
        SPACE(10);
        b.PrintBoard();
    } while (play(b));
    b.PrintBoard();
    return 0;
}