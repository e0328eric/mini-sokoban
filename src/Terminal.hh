#ifndef _SOKOBAN_TERMINAL_HH_
#define _SOKOBAN_TERMINAL_HH_

#include <cstddef>
#include <termios.h>

#include "Pair.hh"

typedef Pair<size_t, size_t> ScreenSize;

namespace sokoban
{
    class Terminal
    {
     public:
        Terminal();
        ~Terminal();

        constexpr char ctrlKey(char ch)
        {
            return ch & 0x1F;
        }

        constexpr bool isExit(char ch)
        {
            return ch == ctrlKey('c') || ch == ctrlKey('d') || ch == ctrlKey('q');
        }

        ScreenSize getScreenSize() const;

        int readKey() const;

        void refreshScreen() const;
        void cleanLine() const;

        void hideCursor() const;
        void showCursor() const;
        // The coordinate of the top left corner is (0,0)
        // +---------------------
        // | (0,0) (1,0) (2,0) ..
        // | (0,1) (1,1) (2,1) ..
        // | (0,2) (1,2) (2,2) ..
        // |   :     :     :
        void moveCursor(int col, int row) const;

        void draw(int col, int row, const char* s) const;
        void drawf(int col, int row, const char* fmt, ...) const;
        void flush() const;

     private:
        struct termios mOrigTerm;
        struct termios mTerm;
        ScreenSize mScreenSize;
    };
}// namespace sokoban

#endif// _SOKOBAN_TERMINAL_HH_
