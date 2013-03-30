#include <iostream>
#include <algorithm>

#include "Game.h"

/**
 * Initialize SDL
 *
 * @param int rows the number of rows that will be displayed
 * @param int cols the number of columns that will be displayed
 * @param positions_t positions the first generation of cells to be displayed
 *
 * @throws SDLException if SDL coudn't be initialized
 */
Game::Game(int rows, int cols, positions_t positions)
    : no_rows(rows), no_columns(cols) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw SDLException("Couldn't initialize SDL!");
    }

    const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();

    int size = getWindowSize(vinfo->vfmt);

    screen = SDL_SetVideoMode(size, size, vinfo->vfmt->BitsPerPixel, flags);

    if(screen == nullptr){
        throw SDLException("Couldn't set SDL video mode!");
    }

    running = true;
}


/**
 * Determine the best size for the window
 *
 * @param SDL_PixelFormat *format the pixel's format as present in
 * the SDL_VideoInfo struct
 *
 * @return an int that represents both the width and the height of the window
 * considering that a grid looks best when it's made of squares
 *
 * TODO: note that I currently use the highest resolution available which is not
 * necessarily the current one, change this
 */
int Game::getWindowSize(SDL_PixelFormat *format){
    SDL_Rect **modes = SDL_ListModes(format, flags|SDL_FULLSCREEN);

    if(modes != (SDL_Rect**) -1){
        //for(int i=0; modes[i]; ++i){
            //std::cout<<modes[i]->w<<" "<<modes[i]->h<<"\n";
        //}

        return std::min(modes[0]->w, modes[0]->h) - 50;
    }

    return 400; //sane defaults?
}

/**
 * Actually run the game:
 * Process events
 * Advance through generations
 */
void Game::run(){
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            processEvent(&event);
        }
    }
}

/**
 * Process an event
 *
 * @param SDL_Event *event the event that should be processed
 */
void Game::processEvent(SDL_Event *event){
    switch(event->type){
        case SDL_QUIT:
            running = false;
            break;
    }
}

/**
 * Cleanup SDL
 */
Game::~Game(){
    SDL_Quit();
}
