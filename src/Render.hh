#ifndef _SOKOBAN_RENDER_HH_
#define _SOKOBAN_RENDER_HH_

#include "Board.hh"
#include "Terminal.hh"

namespace sokoban
{
    class Render
    {
     public:
        explicit Render(Terminal* term, Board* mBoard);

        void setBoard(Board* board);
        void renderBoard(int level) const;

     private:
        Terminal* mTerm;
        Board* mBoard;
    };
}// namespace sokoban

#endif// _SOKOBAN_RENDER_HH_
