#ifndef H_GAME_GRID
#define H_GAME_GRID

#include <vector>

#include "helpers.h" // positions_t

class Game{
    public:
        Game(int w, int h, positions_t positions);
    private:
        int width, height;
};

#endif
