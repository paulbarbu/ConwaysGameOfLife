#ifndef H_GAME_GRID
#define H_GAME_GRID

#include <vector>
#include <exception>

#include "SDL/SDL.h"

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
        Game(int rows, int cols, positions_t positions);
        ~Game();
        void run();
    private:
        int getWindowSize(SDL_PixelFormat *format);
        void processEvent(SDL_Event *event);
        SDL_Surface *screen;
        int no_rows, no_columns;
        bool running = false;
        Uint32 flags = SDL_SWSURFACE|SDL_DOUBLEBUF;
};

#endif
