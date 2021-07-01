#include "Board.hh"
#include "Game.hh"
#include "Pair.hh"
#include "Render.hh"
#include "SatSize.hh"
#include "Terminal.hh"

#include "map.hh"

int main()
{

    // TODO(#1): remove the second parameter if it is possible
    sokoban::Game game(static_cast<const char**>(maps), 3);
    game.run();

    return 0;
}
