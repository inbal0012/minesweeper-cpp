//Cell.h
#define IS_EMPTY value == 0
#define IS_BOMB value == -1
#define IS_OPEN state == State::open
#define IS_CLOSE state == State::close
#define IS_FLAG state == State::flag

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
