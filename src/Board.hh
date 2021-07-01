#ifndef _SOKOBAN_BOARD_HH_
#define _SOKOBAN_BOARD_HH_

#include "Pair.hh"
#include <cstddef>

typedef Pair<size_t, size_t> Coordinate;

namespace sokoban
{
    enum class Element
    {
        Air = 0,
        Wall,
        Rock,
        Goal,
        FilledGoal,
        Player,
    };

    class Board
    {
     public:
        Board(const char* bluePrint);
        ~Board();

        Board& operator=(Board&& board);

        Pair<size_t, size_t> getMapSize() const;
        Coordinate& getPlayerPos();
        size_t getTotalGoalCount() const;
        size_t getGoalCount() const;

        void changeMap(const char* bluePrint);

        Element& operator[](Coordinate pos);

     public:
        Element* mBoard;
        size_t mColSize;
        size_t mRowSize;
        Coordinate mPlayerPos;
        size_t mTotalGoalCount;
        size_t mGoalCount;
    };
}// namespace sokoban

#endif// _SOKOBAN_BOARD_HH_
