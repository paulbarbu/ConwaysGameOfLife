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

    cell_width = size/no_columns;
    cell_height = size/no_rows;

    // TODO: these should be supplied by the user
    alive_color = SDL_MapRGB(vinfo->vfmt, 255, 255, 255);
    dead_color = SDL_MapRGB(vinfo->vfmt, 0, 0, 0);

    std::cout<<"Window size, Cell width and height: "<<size<<", "<<cell_width<<" "<<cell_height<<"\n";

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
 * necessarily the current one, change this, see: http://sdl.beuc.net/sdl.wiki/SDL_VideoInfo
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
 * process events, advance through generations and draw the cells
 */
void Game::run(){
    SDL_Event event;
    setCell(1, 1, alive_color);
    setCell(1, 2, alive_color);
    setCell(1, 3, alive_color);
    setCell(1, 3, dead_color);
    setCell(9, 9, alive_color);
    setCell(0, 0, alive_color);
    setCell(10, 10, alive_color);
    setCell(100, 100, alive_color);

    while(running){
        while(SDL_PollEvent(&event)){
            processEvent(&event);
        }
    }
}

/**
 * Set a cell's color
 *
 * @param int row the row where the cell is located
 * @param int col the column where the cell is located
 * @param Uint32 color the color the cell should be set to
 *
 * @throws SDLException in case that SDL_FillRect has failed
 *
 * TODO: for optimization purposes I can return a rect to be SDL_UpdateRect'ed
 * and then in setCells I would return an array of rects to be updated.
 * The updating would then be done in run()
 */
void Game::setCell(int row, int col, Uint32 color){
    if(row < 0 || col < 0 || row >= no_rows || col >= no_columns){
        return;
    }

    SDL_Rect cell_rect;
    cell_rect.w = cell_width;
    cell_rect.h = cell_height;

    cell_rect.x = cell_width * col;
    cell_rect.y = cell_height * row;

    int err = SDL_FillRect(screen, &cell_rect, color);
    if(err == -1){
        throw SDLException("Couldn't draw to screen!");
    }

    SDL_UpdateRect(screen, cell_rect.x, cell_rect.y, cell_rect.w, cell_rect.h);
}

/**
 * Set the color of several cells
 *
 * @param positions_t pos the positions where the cells are located
 * @param Uint32 color the color the cells should be filled with
 *
 * @see{
 *  Game::setCell
 * }
 */
void Game::setCells(positions_t pos, Uint32 color){
    for(auto it=pos.begin(); it != pos.end(); ++it){
        setCell(it->first, it->second, color);
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
