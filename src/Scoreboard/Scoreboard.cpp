
#ifndef _Scoreboard
#define _Scoreboard

#include <vector>
#include <fstream> //file managment
#include <string>  //getline
#include <sstream> // std::stringstream

#include "ScoreboardEntry.cpp"

class Scoreboard
{
private:
    vector<ScoreboardEntry> scores;

public:
    Scoreboard(/* args */);
    ~Scoreboard();
    void getScoreboard();
    bool isOnScoreboard(int newTime);
    void addToScoreboard(const ScoreboardEntry &);
    void saveScoreboard();
    void printScoreboard();
};

Scoreboard::Scoreboard(/* args */)
{
}

Scoreboard::~Scoreboard()
{
}

void Scoreboard::getScoreboard()
{
    string line;
    string part;
    ifstream fScoreboard("scoreboard.txt");
    if (fScoreboard.is_open())
    {
        while (getline(fScoreboard, line))
        {
            stringstream lineStrm(line);

            string time, name, board, mines;
            lineStrm >> time >> name >> board >> mines;

            string timeDelimiter = ":";
            auto timeSplitPos = time.find(timeDelimiter);
            if (timeSplitPos == string::npos)
            {
                // ERROR
            }
            string tMin = time.substr(0, timeSplitPos), tSec = time.substr(timeSplitPos + timeDelimiter.length()); //split the time string into min & sec String
            int cTime = stoi(tMin) * 60 + stoi(tSec);
            ScoreboardEntry score;
            score.timeInt = cTime;
            score.name = name;
            score.board = board;
            score.mines = mines;
            scores.push_back(score);
        }
        fScoreboard.close();
    }
    else
        cout << "Unable to open file";
}

bool Scoreboard::isOnScoreboard(int newTime)
{
    for (ScoreboardEntry score : scores)
    {
        if (newTime < score.timeInt)
        {
            return true;
        }
    }

    return false;
}

void Scoreboard::addToScoreboard(const ScoreboardEntry &newScore)
{
    int i = 0;
    for (const ScoreboardEntry &score : scores)
    {
        if (newScore.timeInt < score.timeInt)
        {
            scores.insert(scores.begin() + i, newScore);
            break;
        }
        i++;
    }
}

void Scoreboard::saveScoreboard()
{
    ofstream fScoreboard;
    fScoreboard.open("scoreboard.txt");
    if (fScoreboard.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            fScoreboard << ScoreboardEntryToSting(scores[i]) << endl;
        }
        fScoreboard.close();
    }
}

void Scoreboard::printScoreboard()
{

    int i = 1;
    for (const ScoreboardEntry &entry : scores)
    {
        cout << i++ << ". " << ScoreboardEntryToSting(entry) << endl;
    }
}

#endif // _Scoreboard
