//UI
void printHorizontalLine();
void PrintBoard(); //map<point, char> ?
inputHandler();
setGame();

//Game  Singelon?
void printSymbleIndexAndGameInstructions();
void play();
bool clickHandler(Board &b);
bool inputValidation(char commend, int row, int col);
parseBoardToPrint();
void PrintBoard(bool showAll = false);
static bool settingsValidation(int row, int col, int mines);

//Board     hide ctor (find DP name)
Board(int height = SIZE, int width = SIZE, int mines = 10);
~Board();
bool click(int row, int col, char commend);
Board settings();
bool isGameOver();
bool inBoard(int row, int col);
void genereteNumbers(int row, int col);
std::vector<pair<point, Cell *>> getAllNeighbors(int row, int col);
void openCell(int row, int col);
void flagCell(Cell *cell);
void openNeighbors(int row, int col);
void flagNeighbors(int row, int col);
bool checkAmbiguity(int row, int col);
void seeEnough(int row, int col);
//Getters
int getMines();
int getWidth();
int getHeight();

//___________________________________________________
int height, width, mines;
std::map<point, Cell> cells;
bool lose = false, win = false;
bool createBoard();
bool checkWin();
void checkBoard();
bool click(int row, int col, char commend);
bool inputValidation(char commend, int row, int col);
bool isGameOver();
static bool settingsValidation(int row, int col, int mines);