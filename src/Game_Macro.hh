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
