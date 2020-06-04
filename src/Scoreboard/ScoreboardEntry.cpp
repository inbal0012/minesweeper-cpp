

#ifndef _ScoreboardEntry
#define _ScoreboardEntry

#include <iostream>

using namespace std;

struct ScoreboardEntry
{
    /* data */
    string name, board, mines;
    int timeInt;
};

const string parseTime(int time)
{
    int min = time / 60;
    int sec = time % 60;
    string secStr = "";
    if (sec < 10)
        secStr = '0' + to_string(sec);
    else
        secStr = to_string(sec);

    return to_string(min) + ":" + secStr;
}

static const string ScoreboardEntryToSting(const ScoreboardEntry &score)
{
    return parseTime(score.timeInt) + " " + score.name + " " + score.board + " " + score.mines;
}

#endif // _ScoreboardEntry
