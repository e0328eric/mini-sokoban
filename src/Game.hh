#ifndef _SOKOBAN_GAME_HH_
#define _SOKOBAN_GAME_HH_

#include "Board.hh"
#include "Render.hh"
#include "SatSize.hh"
#include "Terminal.hh"

namespace sokoban
{
    enum class GameState
    {
        GameOver,
        StartGame,
        Running,
        NextLevel,
    };

    class Game
    {
     public:
        explicit Game(const char* bluePrints[], int maxLevel);
        ~Game();

        void run();

        Pair<size_t, size_t>& getPlayerPos();
        Element& operator[](Pair<size_t, size_t> pos);
        void renderBoard() const;

        void movePlayer(int key);

     private:
        void resetGame();

     public:
        Terminal mTerm;

     private:
        const char** mMaps;
        Board mBoard;
        Render mRender;
        GameState mState;
        int mLevel;
        int mMaxLevel;
        SatSize mTotalGoalCount;
        SatSize mGoalCount;
        bool mIsStandOnGoal;
    };
}// namespace sokoban

#endif// _SOKOBAN_GAME_HH_
