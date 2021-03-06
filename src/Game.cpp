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
 * A nice feature for this would be to highlight the cell under the and only
 * set it if the user clicks on it
 */
Game::Game(int rows, int cols, unsigned int i, SDL_Color acolor,
           SDL_Color dcolor, ConwaysGameOfLife *cgol, positions_t pos)
        : no_rows(rows), no_columns(cols), interval(i), life(cgol){

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

    alive_color = SDL_MapRGB(vinfo->vfmt, acolor.r, acolor.g, acolor.b);
    dead_color = SDL_MapRGB(vinfo->vfmt, dcolor.r, dcolor.g, dcolor.b);

    std::vector<SDL_Rect> rects = setCells(pos, alive_color);

    SDL_UpdateRects(screen, rects.size(), rects.data());

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

        std::vector<SDL_Rect> cell_rects(setCells(positions.first, alive_color));
        std::vector<SDL_Rect> dead_cell_rects(
            setCells(positions.second, dead_color));

        cell_rects.insert(cell_rects.end(), dead_cell_rects.begin(),
            dead_cell_rects.end());

        SDL_UpdateRects(screen, cell_rects.size(), cell_rects.data());

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
 * @return a SDL_Rect that represents the area that needs updating in order to
 * actually view the new cell's color
 *
 * @throws SDLException in case that SDL_FillRect has failed
 */
SDL_Rect Game::setCell(int row, int col, Uint32 color){
    SDL_Rect cell_rect;
    if(row < 0 || col < 0 || row >= no_rows || col >= no_columns){
        return cell_rect;
    }

    cell_rect.w = cell_side_length;
    cell_rect.h = cell_side_length;

    cell_rect.x = cell_side_length * col;
    cell_rect.y = cell_side_length * row;

    int err = SDL_FillRect(screen, &cell_rect, color);
    if(err == -1){
        throw SDLException("Couldn't draw to screen!");
    }

    return cell_rect;
}

/**
 * Set the color of several cells
 *
 * @param positions_t pos the positions where the cells are located
 * @param Uint32 color the color the cells should be filled with
 *
 * @return a std::vector<SDL_Rect> that represents the areas that need updating
 * in order to actually view the new cells' color
 *
 * @see{
 *  Game::setCell
 * }
 */
std::vector<SDL_Rect> Game::setCells(positions_t pos, Uint32 color){
    std::vector<SDL_Rect> rects;
    for(auto it=pos.begin(); it != pos.end(); ++it){
        rects.push_back(setCell(it->first, it->second, color));
    }

    return rects;
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
