#include <iostream>

#include "src/Game/Game.cpp"
#include "src/Scoreboard/ScoreboardEntry.cpp"
#include "src/Scoreboard/Scoreboard.cpp"

using namespace std;

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

    + win if width*hight - openCells (int) == mines

    + Strings.cpp 
    File in out
    add To Scoreboard()
    Show scoreboard()
    + Time StartTime //TODO learn to calculate 
    + Show time()

    scoreboard per standart board (Begginers, Inter, Expert, Insane) 
    selectBoard OR customize board  
     */

    Scoreboard SB;
    // SB.getScoreboard();
    // SB.printScoreboard();
    // SB.isOnScoreboard(150);

    Game g = Game();
    g.Play();

    // int newTime = 125;

    // int times[10] = {0};
    // int i = 0;
    // vector<ScoreboardEntry> scores;

    // string line;
    // string part;
    // ifstream scoreboard("scoreboard.txt");
    // if (scoreboard.is_open())
    // {
    //     while (getline(scoreboard, line))
    //     {
    //         stringstream lineStrm(line);

    //         string time, name, board, mines;
    //         lineStrm >> time >> name >> board >> mines;

    //         string timeDelimiter = ":";
    //         auto timeSplitPos = time.find(timeDelimiter);
    //         if (timeSplitPos == string::npos)
    //         {
    //             // ERROR
    //         }
    //         string tMin = time.substr(0, timeSplitPos), tSec = time.substr(timeSplitPos + timeDelimiter.length());
    //         int cTime = stoi(tMin) * 60 + stoi(tSec);
    //         times[i++] = cTime;
    //         ScoreboardEntry score;
    //         score.timeInt = cTime;
    //         score.name = name;
    //         score.board = board;
    //         score.mines = mines;
    //         scores.push_back(score);
    //     }
    //     scoreboard.close();

    //     cout << "times:" << endl;
    // }
    // else
    //     cout << "Unable to open file";

    return 0;
}
