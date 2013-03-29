#include <iostream>

#include "ConwaysGameOfLife.h"

ConwaysGameOfLife::ConwaysGameOfLife(int w, int h, positions_t pos)
    : width(w), height(h){

    board.resize(height);

    for(auto it=board.begin(); it != board.end(); it++){
        it->resize(width);
    }

    for(auto it=pos.begin(); it != pos.end(); it++){
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

void ConwaysGameOfLife::evolve(){
    std::pair<positions_t, positions_t> pos = getGenerationChanges();

    // set the living cells
    std::cout<<"Lives: ";
    for(auto it=pos.first.begin(); it != pos.first.end(); ++it){
        std::cout<<"("<<it->first<<" "<<it->second<<") ";
        board[it->first][it->second] = 1;
    }

    // set the dead cells
    std::cout<<"\nDies: ";
    for(auto it=pos.second.begin(); it != pos.second.end(); ++it){
        std::cout<<"("<<it->first<<" "<<it->second<<") ";
        board[it->first][it->second] = 0;
    }

    std::cout<<"\n";
}

std::pair<positions_t, positions_t> ConwaysGameOfLife::getGenerationChanges(){
    positions_t lives, dies;

    for(unsigned int i=0; i<height; i++){
        for(unsigned int j=0; j<width; j++){
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

neighbours_t ConwaysGameOfLife::getNeighboursStatus(int line, int col){
    unsigned int alive=0, dead=0;
    int dline[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int dcol[]  = { 0,  1, 1, 1, 0, -1, -1, -1};

    for(int i=0; i<8; i++){
        int n_line = line+dline[i];
        int n_col = col+dcol[i];

        if(n_line < 0 || n_line >= height || n_col < 0 || n_col >= width){
            ++dead;
            continue;
        }

        if(board[n_line][n_col] == 1){
            ++alive;
        }
        else{
            ++dead;
        }
    }

    return std::make_pair(alive, dead);
}
