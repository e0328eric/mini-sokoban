// Map Encoding lists
// use the format described in sokoban wiki
// Reference: http://sokobano.de/wiki/index.php?title=Level_format
//
//      Level Element        Character
// ------------------------- -----------
//  Wall                      #
//  Player                    @
//  Player on goal square     +
//  Box                       $
//  Box on goal square        *
//  Goal square               .
//  Floor                     (Space)

constexpr const char* map1 =
    "##########\n"
    "#@       #\n"
    "#  $     #\n"
    "# $ $   .#\n"
    "#      ..#\n"
    "##########\n";

constexpr const char* map2 =
    "##########   \n"
    "#........####\n"
    "# $$$$$$$#  #\n"
    "#.$......#  #\n"
    "# $$$$$$ #  #\n"
    "#......$+#  #\n"
    "#$$$$$$$ #  #\n"
    "#        ####\n"
    "##########   \n";

// Reference: http://sokoban-jd.blogspot.com/2014/04/sokoban-lessons-storage-one-entrance.html
constexpr const char* map3 =
    "      ####           \n"
    "      #  ########### \n"
    "      #            # \n"
    "      #.###### #$# # \n"
    "      # #   ## # @ # \n"
    "####### #    # ##### \n"
    "#    .# ###  #    ## \n"
    "#   ..# # #$$ $$$$ # \n"
    "#  ...# # #  #     ##\n"
    "# ....# ### ## $$$$ #\n"
    "#         ...##     #\n"
    "#  ############ $$$ #\n"
    "####          ##    #\n"
    "               ######\n";

const char* maps[3] = {map1, map2, map3};
