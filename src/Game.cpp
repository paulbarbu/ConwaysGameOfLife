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

    int size = getWindowSize(vinfo->vfmt);

    cell_width = ceil((double)size/no_columns);
    cell_height = ceil((double)size/no_rows);

    // TODO: these should be supplied by the user
    alive_color = SDL_MapRGB(vinfo->vfmt, 255, 255, 255);
    dead_color = SDL_MapRGB(vinfo->vfmt, 0, 0, 0);

    //std::cout<<"Window size, Cell width and height: "<<size<<", "<<cell_width<<" "<<cell_height<<"\n";

    screen = SDL_SetVideoMode(size, size, vinfo->vfmt->BitsPerPixel, flags);

    if(screen == nullptr){
        throw SDLException("Couldn't set SDL video mode!");
    }

    setCells(pos, alive_color);
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
    //TODO: run ./conway gosper_glider_gun.txt with 10 and 37 as the size and it
    //will look awful, this should be changed so the window can take different
    //dimenstions on the X and Y axis in order to keep the square aspect ratio
    //of the cells, ie: if the user doesn't provide a square screen by default
    ////set this size on one axis, then set the min(cell_width, cell_height)*size
    //as the other axis
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
