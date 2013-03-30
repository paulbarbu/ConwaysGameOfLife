#include "Game.h"

/**
 * Initialize SDL
 *
 * @param int rows the number of rows that will be displayed
 * @param int cols the number of columns that will be displayed
 * @param positions_t positions the first generation of cells to be displayed
 */
Game::Game(int rows, int cols, positions_t positions)
    : no_rows(rows), no_columns(cols) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw SDLException("Couldn't initialize SDL!");
    }

    const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();

    screen = SDL_SetVideoMode(400, 400, vinfo->vfmt->BitsPerPixel, SDL_SWSURFACE|SDL_DOUBLEBUF);

    if(screen == nullptr){
        throw SDLException("Couldn't set SDL video mode!");
    }

    running = true;
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
