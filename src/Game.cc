#include <cassert>
#include <cstring>

#include "Game.hh"
#include "Pair.hh"

#define MOVE_PLAYER(_fnt_)                                                   \
    do                                                                       \
    {                                                                        \
        auto nextPos = pos._fnt_(1);                                         \
        nextBlock = mBoard[nextPos];                                         \
        switch (nextBlock)                                                   \
        {                                                                    \
        case Element::Wall:                                                  \
            break;                                                           \
        case Element::Air:                                                   \
            if (mIsStandOnGoal)                                              \
            {                                                                \
                mBoard[nextPos] = Element::Player;                           \
                mBoard[pos] = Element::Goal;                                 \
                pos = nextPos;                                               \
                mIsStandOnGoal = false;                                      \
            }                                                                \
            else                                                             \
            {                                                                \
                mBoard[nextPos] = mBoard[pos];                               \
                mBoard[pos] = nextBlock;                                     \
                pos = nextPos;                                               \
            }                                                                \
            break;                                                           \
        case Element::Goal:                                                  \
            mBoard[nextPos] = Element::Player;                               \
            mBoard[pos] = mIsStandOnGoal ? Element::Goal : Element::Air;     \
            pos = nextPos;                                                   \
            mIsStandOnGoal = true;                                           \
            break;                                                           \
        case Element::FilledGoal: {                                          \
            auto nextnextPos = nextPos._fnt_(1);                             \
            auto nextnextBlock = mBoard[nextnextPos];                        \
            switch (nextnextBlock)                                           \
            {                                                                \
            case Element::Air:                                               \
                mBoard[nextnextPos] = Element::Rock;                         \
                mBoard[nextPos] = Element::Player;                           \
                mBoard[pos] = mIsStandOnGoal ? Element::Goal : Element::Air; \
                pos = nextPos;                                               \
                mIsStandOnGoal = true;                                       \
                --mGoalCount;                                                \
                break;                                                       \
            case Element::Goal:                                              \
                mBoard[nextnextPos] = Element::FilledGoal;                   \
                mBoard[nextPos] = Element::Player;                           \
                mBoard[pos] = mIsStandOnGoal ? Element::Goal : Element::Air; \
                pos = nextPos;                                               \
                mIsStandOnGoal = true;                                       \
                break;                                                       \
            default:                                                         \
                break;                                                       \
            }                                                                \
            break;                                                           \
        }                                                                    \
        case Element::Rock: {                                                \
            auto nextnextPos = nextPos._fnt_(1);                             \
            auto nextnextBlock = mBoard[nextnextPos];                        \
            switch (nextnextBlock)                                           \
            {                                                                \
            case Element::Air:                                               \
                if (mIsStandOnGoal)                                          \
                {                                                            \
                    mBoard[nextnextPos] = Element::Rock;                     \
                    mBoard[nextPos] = Element::Player;                       \
                    mBoard[pos] = Element::Goal;                             \
                    pos = nextPos;                                           \
                    mIsStandOnGoal = false;                                  \
                }                                                            \
                else                                                         \
                {                                                            \
                    mBoard[nextnextPos] = mBoard[nextPos];                   \
                    mBoard[nextPos] = mBoard[pos];                           \
                    mBoard[pos] = nextnextBlock;                             \
                    pos = nextPos;                                           \
                }                                                            \
                break;                                                       \
            case Element::Goal:                                              \
                mBoard[nextnextPos] = Element::FilledGoal;                   \
                mBoard[nextPos] = Element::Player;                           \
                if (mIsStandOnGoal)                                          \
                {                                                            \
                    mIsStandOnGoal = false;                                  \
                    mBoard[pos] = Element::Goal;                             \
                }                                                            \
                else                                                         \
                    mBoard[pos] = Element::Air;                              \
                pos = nextPos;                                               \
                ++mGoalCount;                                                \
                break;                                                       \
            default:                                                         \
                break;                                                       \
            }                                                                \
            break;                                                           \
        }                                                                    \
        case Element::Player:                                                \
            assert(0 && "unreatchable");                                     \
            break;                                                           \
        }                                                                    \
    } while (false)

using namespace sokoban;

constexpr int leftKey = 0x445b1b;
constexpr int rightKey = 0x435b1b;
constexpr int upKey = 0x415b1b;
constexpr int downKey = 0x425b1b;

constexpr const char* nextLevelMsg = "Press any key to goto the next level...";
constexpr const char* quitMsg = "Press any key to quit...";

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
    , mIsStandOnGoal(false)
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
                mTerm.drawf((termSizeInfo.fst - strlen(quitMsg)) >> 1, msgRowLocation + 1, "\x1b[1m\x1b[4m%s\x1b[0m", quitMsg);
                mTerm.flush();
            }
            else
            {
                mState = GameState::StartGame;
                mTerm.drawf((termSizeInfo.fst - strlen(nextLevelMsg)) >> 1, msgRowLocation + 1, "\x1b[1m\x1b[4m%s\x1b[0m", nextLevelMsg);
                mTerm.flush();
                mBoard.changeMap(mMaps[mLevel]);
                mTotalGoalCount = mBoard.getTotalGoalCount();
                mGoalCount = mBoard.getGoalCount();
                mIsStandOnGoal = false;
            }
            break;
        }
        }

        while ((c = mTerm.readKey()) <= 0) {}
        if (mTerm.isExit(c)) break;

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
    mRender.renderBoard();
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
