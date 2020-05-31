#include <iostream>
#include "src/Board.cpp"

using namespace std;

int main()
{
    Board b(8, 8, 10);
    b.PrintBoard();
    return 0;
}