#ifndef H_GAME_GRID
#define H_GAME_GRID

#include <vector>
#include <exception>

#include "SDL/SDL.h"

#include "helpers.h" // positions_t

class SDLException : public std::exception{
    public:
        SDLException(const char* m) : msg(m) {
        }

        virtual const char* what() const throw(){
            return msg.c_str();
        }

    private:
        std::string msg;
};

class Game{
    public:
        Game();
        Game(int w, int h, positions_t positions);
        ~Game();
        void run();
    private:
        void processEvent(SDL_Event *event);
        SDL_Surface *screen;
        int width, height;
        bool running = false;
};

#endif
