#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include "Terminal.hh"

using namespace sokoban;

constexpr unsigned int STDIN = 0;
constexpr unsigned int STDOUT = 1;

void die(const char* msg)
{
    write(STDOUT, "\x1b[2J", 4);
    write(STDOUT, "\x1b[H", 3);
    write(STDOUT, "\x1b[?25h", 6);

    std::cerr << msg << std::endl;
    std::exit(1);
}

int getCursorPosition(size_t* rows, size_t* cols)
{
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT, "\x1b[6n", 4) != 4) return -1;
    while (i < sizeof(buf) - 1)
    {
        if (read(STDIN, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%zd;%zd", rows, cols) != 2) return -1;
    return 0;
}

Terminal::Terminal()
    : mScreenSize(Pair{0ul, 0ul})
{
    if (tcgetattr(STDIN, &mOrigTerm) == -1)
        die("Terminal::Terminal (tcgetattr)");

    mTerm = mOrigTerm;

    mTerm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    mTerm.c_oflag &= ~(OPOST);
    mTerm.c_cflag |= (CS8);
    mTerm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    mTerm.c_cc[VMIN] = 0;
    mTerm.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN, TCSAFLUSH, &mTerm) == -1)
        die("Terminal::Terminal (tcsetattr)");

    if (write(STDOUT, "\x1b[999C\x1b[999B", 12) != 12)
        die("Terminal::Terminal (write)");

    if (getCursorPosition(&mScreenSize.snd, &mScreenSize.fst) == -1)
        die("Terminal::Terminal (getCursorPosition)");

    setbuf(stdout, NULL);
}

Terminal::~Terminal()
{
    write(STDOUT, "\x1b[?25h", 6);
    if (tcsetattr(STDIN, TCSAFLUSH, &mOrigTerm) == -1)
        die("tcsetattr");
}

ScreenSize Terminal::getScreenSize() const
{
    return mScreenSize;
}

int Terminal::readKey() const
{
    int nread;
    int ch = 0;

    nread = read(STDIN, &ch, 4);
    if (nread == -1 && errno != EAGAIN) die("read");
    if (nread == 0) return 0;

    return ch;
}

void Terminal::refreshScreen() const
{
    write(STDOUT, "\x1b[2J", 4);
    write(STDOUT, "\x1b[H", 3);
    hideCursor();
}

void Terminal::cleanLine() const
{
    write(STDOUT, "\x1b[K", 3);
}

void Terminal::hideCursor() const
{
    write(STDOUT, "\x1b[?25l", 6);
}

void Terminal::showCursor() const
{
    write(STDOUT, "\x1b[?25h", 6);
}

void Terminal::moveCursor(int col, int row) const
{
    char buffer[32];
    size_t n;
    n = sprintf(buffer, "\x1b[%d;%dH", row + 1, col + 1);
    buffer[n] = '\0';
    write(STDOUT, buffer, n);
}

void Terminal::draw(int col, int row, const char* s) const
{
    moveCursor(col, row);
    printf("%s", s);
}

void Terminal::drawf(int col, int row, const char* fmt, ...) const
{
    va_list args;

    moveCursor(col, row);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void Terminal::flush() const
{
    size_t col, row;
    getCursorPosition(&row, &col);

    if (row == mScreenSize.snd)
        write(STDOUT, "\r", 1);
    else
        write(STDOUT, "\r\n", 2);
}
