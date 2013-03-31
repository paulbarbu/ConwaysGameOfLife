#ifndef H_GAME_GRID
#define H_GAME_GRID

#include <vector>
#include <exception>

#include "SDL/SDL.h"

#include "ConwaysGameOfLife.h"
#include "helpers.h" // positions_t

class SDLException : public std::exception{
    public:
        SDLException(const char* m) : msg(m) {}

        virtual const char* what() const throw(){
            return msg.c_str();
        }

    private:
        std::string msg;
};

class Game{
    public:
        Game(int rows, int cols, unsigned int interval, ConwaysGameOfLife *cgol, positions_t pos);
        ~Game();
        void run();
    private:
        int getWindowSize(SDL_PixelFormat *format);
        void processEvent(SDL_Event *event);
        void setCell(int row, int col, Uint32 color);
        void setCells(positions_t pos, Uint32 color);
        SDL_Surface *screen;
        int no_rows, no_columns;
        bool running = false;
        Uint32 flags = SDL_SWSURFACE|SDL_DOUBLEBUF;
        double cell_width, cell_height;
        Uint32 alive_color, dead_color;
        unsigned int interval;
        ConwaysGameOfLife *life;
};

#endif
