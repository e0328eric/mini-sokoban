#include <cassert>
#include <cstring>

#include "Game.hh"
#include "Game_Macro.hh"
#include "Pair.hh"

using namespace sokoban;

constexpr int leftKey = 0x445b1b;
constexpr int rightKey = 0x435b1b;
constexpr int upKey = 0x415b1b;
constexpr int downKey = 0x425b1b;

constexpr const char* nextLevelMsg = "Press any key to goto the next level...";
constexpr const char* quitMsg = "Press any key to quit...";
constexpr const char* msgFmt = "\x1b[1m\x1b[4m%s\x1b[0m";

Game::Game(const char* bluePrints[], int maxLevel)
    : mTerm()
    , mMaps(bluePrints)
    , mBoard(mMaps[0])
    , mRender(&mTerm, &mBoard)
    , mState(GameState::StartGame)
    , mLevel(0)
    , mMaxLevel(maxLevel)
    , mTotalGoalCount(mBoard.getTotalGoalCount())
    , mGoalCount(mBoard.getGoalCount())
    , mIsStandOnGoal(mBoard.getIsPlayerOnGoal())
{
}

Game::~Game()
{
    mTerm.refreshScreen();
}

void Game::run()
{
    int c;

    mTerm.refreshScreen();

    while (true)
    {
        switch (mState)
        {
        case GameState::GameOver:
            return;

        case GameState::StartGame:
            mTerm.refreshScreen();
            mState = GameState::Running;
            [[fallthrough]];

        case GameState::Running:
            renderBoard();
            if (mGoalCount >= mTotalGoalCount)
            {
                mState = GameState::NextLevel;
                [[fallthrough]];
            }
            else
                break;

        case GameState::NextLevel: {
            auto termSizeInfo = mTerm.getScreenSize();
            auto mapSizeInfo = mBoard.getMapSize();
            size_t msgRowLocation = (termSizeInfo.snd + mapSizeInfo.snd) >> 1;

            ++mLevel;
            if (mLevel >= mMaxLevel)
            {
                mState = GameState::GameOver;
                mTerm.drawf((termSizeInfo.fst - strlen(quitMsg)) >> 1, msgRowLocation + 1, msgFmt, quitMsg);
                mTerm.flush();
            }
            else
            {
                mTerm.drawf((termSizeInfo.fst - strlen(nextLevelMsg)) >> 1, msgRowLocation + 1, msgFmt, nextLevelMsg);
                mTerm.flush();
                resetGame();
            }
            break;
        }
        }

        while ((c = mTerm.readKey()) <= 0)
            if (mTerm.isScreenSizeChanges())
            {
                mTerm.updateScreenSize();
                mTerm.refreshScreen();
                renderBoard();
            }

        if (mTerm.isExit(c)) break;
        if (c == 'r')
        {
            resetGame();
            continue;
        }

        movePlayer(c);
    }
}

Pair<size_t, size_t>& Game::getPlayerPos()
{
    return mBoard.getPlayerPos();
}

Element& Game::operator[](Pair<size_t, size_t> pos)
{
    return mBoard[pos];
}

void Game::renderBoard() const
{
    mRender.renderBoard(mLevel);
}

void Game::resetGame()
{
    mState = GameState::StartGame;
    mBoard.changeMap(mMaps[mLevel]);
    mTotalGoalCount = mBoard.getTotalGoalCount();
    mGoalCount = mBoard.getGoalCount();
    mIsStandOnGoal = mBoard.getIsPlayerOnGoal();
}

void Game::movePlayer(int key)
{
    Element nextBlock = Element::Air;
    auto& pos = mBoard.getPlayerPos();

    switch (key)
    {
    case leftKey:
        MOVE_PLAYER(subf);
        break;
    case rightKey:
        MOVE_PLAYER(addf);
        break;
    case upKey:
        MOVE_PLAYER(subs);
        break;
    case downKey:
        MOVE_PLAYER(adds);
        break;
    default:
        break;
    }
}
