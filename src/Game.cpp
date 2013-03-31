#include <iostream>
#include <algorithm>
#include <cmath>

#include "Game.h"

/**
 * Initialize SDL
 *
 * @param int rows the number of rows that will be displayed
 * @param int cols the number of columns that will be displayed
 * @param int i the time interval in milliseconds after which the next
 * generation is drawn
 * @param ConwaysGameOfLife *cgol pointer to the object that encapsulates the
 * game's actual logic
 * @param positions_t positions the first generation of cells to be displayed
 *
 * @throws SDLException if SDL coudn't be initialized
 *
 * @see{
 *  game::getWindowSize
 * }
 *
 * TODO: allow the user to draw his own pattern using the mouse at the start
 */
Game::Game(int rows, int cols, unsigned int i, ConwaysGameOfLife *cgol, positions_t pos)
    : no_rows(rows), no_columns(cols), interval(i), life(cgol) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw SDLException("Couldn't initialize SDL!");
    }

    const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();

    unsigned int length = std::min(vinfo->current_w, vinfo->current_h) - 50;
    setCellSideLength(length);

    SDL_Rect size = getWindowSize(length);

    screen = SDL_SetVideoMode(size.w, size.h, vinfo->vfmt->BitsPerPixel, flags);

    if(screen == nullptr){
        throw SDLException("Couldn't set SDL video mode!");
    }

    // TODO: these should be supplied by the user
    alive_color = SDL_MapRGB(vinfo->vfmt, 255, 255, 255);
    dead_color = SDL_MapRGB(vinfo->vfmt, 0, 0, 0);

    setCells(pos, alive_color);
    running = true;
}


/**
 * Determine the best size for the window
 *
 * @param unsigned int length the smallest of the width and height of the window
 *
 * @return a SDL_Rect that has its .h and .w members set as the best width and
 * height for the window
 */
SDL_Rect Game::getWindowSize(unsigned int length){
    SDL_Rect size;

    if(no_rows == no_columns){ //the user requested a square window
        size.w = length;
        size.h = length;
    }
    else{ //the window won't be a square
        size.w = cell_side_length * no_columns;
        size.h = cell_side_length * no_rows;
    }

    return size;
}

/**
 * Set the cell side length, because it's a square
 *
 * @param unsigned int length the smallest of the width and height of the window
 */
void Game::setCellSideLength(unsigned int length){
    double cell_w = (double)length/no_columns;
    double cell_h = (double)length/no_rows;

    // use the minimum value of the two since a cell should be a square
    cell_side_length = ceil(std::min(cell_w, cell_h));
}

/**
 * Actually run the game:
 * process events, advance through generations and draw the cells
 *
 * @see{
 *  Game::setCell
 *  Game::setCells
 *  Game::processEvent
 * }
 */
void Game::run(){
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            processEvent(&event);
        }

        std::pair<positions_t, positions_t> positions = life->evolve();

        setCells(positions.first, alive_color);
        setCells(positions.second, dead_color);

        SDL_Delay(interval);
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
    cell_rect.w = cell_side_length;
    cell_rect.h = cell_side_length;

    cell_rect.x = cell_side_length * col;
    cell_rect.y = cell_side_length * row;

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
