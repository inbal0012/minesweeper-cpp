
#define IS_EMPTY value == 0
#define IS_BOMB value == -1

enum class State : int
{
    close,
    flag,
    open
};

struct Cell
{
    int value = 0;
    State state = State::close;
};