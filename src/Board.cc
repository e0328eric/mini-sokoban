#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Board.hh"

using namespace sokoban;

Board::Board(const char* bluePrint)
    : mBoard(nullptr)
    , mColSize(0)
    , mRowSize(0)
    , mPlayerPos(Pair{0ul, 0ul})
    , mTotalGoalCount(0)
    , mGoalCount(0)
    , mIsPlayerOnGoal(false)
{
    const char* firstNewline = strchr(bluePrint, '\n');
    mColSize = firstNewline - bluePrint;
    size_t i, j;

    for (i = 0; bluePrint[i]; ++i)
        if (bluePrint[i] == '\n')
            ++mRowSize;

    mBoard = new Element[mColSize * mRowSize];

    // blueprint actually has (mColSize + 1) chars in a row including '\n' character
    for (i = 0, j = 0; i < (mColSize + 1) * mRowSize; ++i)
    {
        switch (bluePrint[i])
        {
        case ' ':
            mBoard[j++] = Element::Air;
            break;
        case '#':
            mBoard[j++] = Element::Wall;
            break;
        case '$':
            mBoard[j++] = Element::Rock;
            break;
        case '.':
            mBoard[j++] = Element::Goal;
            ++mTotalGoalCount;
            break;
        case '*':
            mBoard[j++] = Element::FilledGoal;
            ++mTotalGoalCount;
            ++mGoalCount;
            break;
        case '@':
            mBoard[j] = Element::Player;
            mPlayerPos = Pair{j % mColSize, j / mColSize};
            ++j;
            break;
        case '+':
            mBoard[j] = Element::Player;
            mPlayerPos = Pair{j % mColSize, j / mColSize};
            mIsPlayerOnGoal = true;
            ++j;
            break;
        default:
            break;
        }
    }

    if (j != mColSize * mRowSize)
    {
        std::cerr << "ERROR: failed to parsing map blueprint" << std::endl;
        delete[] mBoard;
        mBoard = nullptr;
    }
}

Board::~Board()
{
    delete[] mBoard;
}

Board& Board::operator=(Board&& board)
{
    mBoard = board.mBoard;
    mColSize = board.mColSize;
    mRowSize = board.mRowSize;
    mPlayerPos = board.mPlayerPos;
    mTotalGoalCount = board.mTotalGoalCount;
    board.mBoard = nullptr;

    return *this;
}

Pair<size_t, size_t> Board::getMapSize() const
{
    return Pair{mColSize, mRowSize};
}

Coordinate& Board::getPlayerPos()
{
    return mPlayerPos;
}

size_t Board::getTotalGoalCount() const
{
    return mTotalGoalCount;
}

size_t Board::getGoalCount() const
{
    return mGoalCount;
}

bool Board::getIsPlayerOnGoal() const
{
    return mIsPlayerOnGoal;
}

void Board::changeMap(const char* bluePrint)
{
    delete[] mBoard;
    Board tmp(bluePrint);

    mBoard = tmp.mBoard;
    mColSize = tmp.mColSize;
    mRowSize = tmp.mRowSize;
    mPlayerPos = tmp.mPlayerPos;
    mTotalGoalCount = tmp.mTotalGoalCount;
    mGoalCount = tmp.mGoalCount;
    mIsPlayerOnGoal = tmp.mIsPlayerOnGoal;

    tmp.mBoard = nullptr;
}

Element& Board::operator[](Coordinate pos)
{
    return mBoard[pos.snd * mColSize + pos.fst];
}
