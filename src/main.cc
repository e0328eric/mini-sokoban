#include "Board.hh"
#include "Game.hh"
#include "Pair.hh"
#include "Render.hh"
#include "SatSize.hh"
#include "Terminal.hh"

// Map Encoding lists
// # : Wall
// P : Start position of the player
// O : Rocks to move
// G : Goal Place
// . : Blank Position
constexpr const char* simpleMap =
    "#####\n"
    "#POG#\n"
    "#####\n";

constexpr const char* map1 =
    ".....................................\n"
    ".#############...........#####.......\n"
    ".#........####...........#...#.......\n"
    ".#........################...#.......\n"
    ".#.....G..#..........O.......#.......\n"
    ".#....G.G.#..........O.......#.......\n"
    ".#.....G..#..........O...P...#.......\n"
    ".#...................O.......#.......\n"
    ".#...........................#.......\n"
    ".#############################.......\n"
    ".....................................\n"
    ".....................................\n";

const char* maps[2] = {simpleMap, map1};

int main()
{

    sokoban::Game game(static_cast<const char**>(maps), 2);

    game.run();

    return 0;
}
