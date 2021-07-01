#include <cassert>
#include <cstddef>

#include "Render.hh"

using namespace sokoban;

constexpr const char* airBlock = "  ";
constexpr const char* wallBlock = "\x1b[47m  \x1b[0m";
constexpr const char* rockBlock = "\x1b[104m  \x1b[0m";
constexpr const char* goalBlock = "\x1b[103m  \x1b[0m";
constexpr const char* filledGoalBlock = "\x1b[105m  \x1b[0m";
constexpr const char* playerBlock = "\x1b[46m  \x1b[0m";

typedef Pair<size_t, size_t> Coordinate;

Render::Render(Terminal* term, Board* board)
    : mTerm(term)
    , mBoard(board)
{
    mTerm->refreshScreen();
    mTerm->hideCursor();
}

void Render::setBoard(Board* board)
{
    mBoard = board;
}

void Render::renderBoard() const
{
    auto termSizeInfo = mTerm->getScreenSize();
    auto mapSizeInfo = mBoard->getMapSize();
    size_t paddingCol = (termSizeInfo.fst - (mapSizeInfo.fst << 1)) >> 1;
    size_t paddingRow = (termSizeInfo.snd - mapSizeInfo.snd) >> 1;
    size_t i, j;
    size_t totalLength = mapSizeInfo.fst * mapSizeInfo.snd;

    for (size_t k = 0; k < totalLength; ++k)
    {
        i = k % mapSizeInfo.fst;
        j = k / mapSizeInfo.fst;
        switch ((*mBoard)[{i, j}])
        {
        case Element::Air:
            mTerm->draw(paddingCol + i * 2, paddingRow + j, airBlock);
            break;
        case Element::Wall:
            mTerm->draw(paddingCol + i * 2, paddingRow + j, wallBlock);
            break;
        case Element::Rock:
            mTerm->draw(paddingCol + i * 2, paddingRow + j, rockBlock);
            break;
        case Element::Goal:
            mTerm->draw(paddingCol + i * 2, paddingRow + j, goalBlock);
            break;
        case Element::FilledGoal:
            mTerm->draw(paddingCol + i * 2, paddingRow + j, filledGoalBlock);
            break;
        case Element::Player:
            mTerm->draw(paddingCol + i * 2, paddingRow + j, playerBlock);
            break;
        default:
            assert(0 && "unreachable");
        }
    }

    mTerm->moveCursor(0, 0);
    mTerm->flush();
}
