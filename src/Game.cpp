#include "Game.h"

Game::Game(){}

Game::Game(int w, int h, positions_t positions)
    : width(w), height(h) {

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

void Game::run(){
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            processEvent(&event);
        }
    }
}

void Game::processEvent(SDL_Event *event){
    switch(event->type){
        case SDL_QUIT:
            running = false;
            break;
    }
}

Game::~Game(){
    SDL_Quit();
}
