#include <iostream>

#include "ConwaysGameOfLife.h"

/**
 * Create a board of the right dimensions and fill it with the cells of the
 * first generation
 *
 * @param int rows the number of rows the game will have at its disposal
 * @param int cols the number of columns the game will have at its disposal
 * @param positions_t pos the cells' positions in the first generation
 */
ConwaysGameOfLife::ConwaysGameOfLife(int rows, int cols, positions_t pos)
        : no_rows(rows), no_columns(cols) {

    board.resize(no_rows);

    for(auto it=board.begin(); it != board.end(); ++it){
        it->resize(no_columns);
    }

    for(auto it=pos.begin(); it != pos.end(); ++it){
        board[it->first][it->second] = 1;
    }
}

void ConwaysGameOfLife::showBoard(){
    for(auto it=board.begin(); it != board.end(); ++it){
        for(auto jt=it->begin(); jt != it->end(); ++jt){
            std::cout<<*jt<<" ";
        }
        std::cout<<"\n";
    }
}

/**
 * Advance to the next generation of cells by setting the alive cells and dead
 * cells
 *
 * @return a pair of positions_t where the first member of the pair is the
 * structure that holds the alive cells and the second member is a position_t
 * that holds the cells that should be dead in the next generation
 *
 * @see{
 *  ConwaysGameOfLife::getGenerationChanges
 *}
 */
std::pair<positions_t, positions_t> ConwaysGameOfLife::evolve(){
    std::pair<positions_t, positions_t> pos = getGenerationChanges();

    // set the living cells
    //std::cout<<"Lives: ";
    for(auto it=pos.first.begin(); it != pos.first.end(); ++it){
        //std::cout<<"("<<it->first<<" "<<it->second<<") ";
        board[it->first][it->second] = 1;
    }

    // set the dead cells
    //std::cout<<"\nDies: ";
    for(auto it=pos.second.begin(); it != pos.second.end(); ++it){
        //std::cout<<"("<<it->first<<" "<<it->second<<") ";
        board[it->first][it->second] = 0;
    }

    //std::cout<<"\n";

    return pos;
}

/**
 * Given the current generation stored on the board, get the cells that get to
 * live to the next generation and the ones that die
 *
 * @return a pair of positions_t where the first member of the pair is the
 * structure that holds the alive cells and the second member is a position_t
 * that holds the cells that should be dead in the next generation
 *
 * @see{
 *  ConwaysGameOfLife::getNeighboursStatus
 * }
 */
std::pair<positions_t, positions_t> ConwaysGameOfLife::getGenerationChanges(){
    positions_t lives, dies;

    for(unsigned int i=0; i<no_rows; ++i){
        for(unsigned int j=0; j<no_columns; ++j){
            neighbours_t status = getNeighboursStatus(i, j);

            if(board[i][j] == 1){ //alive
                if(status.first < 2 || status.first > 3){
                    dies.push_back(std::make_pair(i, j));
                }
            }
            else{ //dead
                if(status.first == 3){
                    lives.push_back(std::make_pair(i, j));
                }
            }
        }
    }

    return std::make_pair(lives, dies);
}

/**
 * Get the number of alive and dead cells surrounding another cell
 *
 * @param int row the row of the cell whose neighbours should be checked
 * @param int col the column of the cell whose neighbours should be checked
 *
 * @return a neighbours_t type that holds the number of alive and dead
 * neighbours
 */
neighbours_t ConwaysGameOfLife::getNeighboursStatus(int row, int col){
    unsigned int alive=0, dead=0;
    int drow[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int dcol[]  = { 0,  1, 1, 1, 0, -1, -1, -1};

    for(int i=0; i<8; ++i){
        int n_row = row+drow[i];
        int n_col = col+dcol[i];

        if(n_row < 0 || n_row >= no_rows || n_col < 0 || n_col >= no_columns){
            ++dead;
            continue;
        }

        if(board[n_row][n_col] == 1){
            ++alive;
        }
        else{
            ++dead;
        }
    }

    return std::make_pair(alive, dead);
}
