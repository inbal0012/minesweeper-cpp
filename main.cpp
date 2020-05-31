#include <iostream>
#include "src/Board.cpp"

using namespace std;

int main()
{
    Board b(8, 8, 10);
    b.click(2, 2, 'O');
    b.PrintBoard();
    return 0;
}