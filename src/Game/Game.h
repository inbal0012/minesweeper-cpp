
#ifndef _Game
#define _Game

#include <iostream>
#include "../Board/Board.cpp"
#include "../Strings.cpp"

#define SPACE(n)                 \
    for (int i = 0; i < 10; i++) \
    cout << endl

class Game
{
private:
    /* data */
    Board *b;

    //prints
    void printHorizontalLine();
    void PrintBoard(bool showAll = false);
    void printSymbleIndexAndGameInstructions();

    //Validation
    bool inputValidation(char commend, int row, int col);
    bool settingsValidation(int row, int col, int mines);

    void settings();
    bool clickHandler();
    bool click(int row, int col, char commend);
    bool checkAmbiguity(int row, int col);
    bool checkWin();
    bool isGameOver();

public:
    Game(/* args */);
    ~Game();
    void Play();
};

#endif // _Game
