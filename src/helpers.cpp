#include <fstream>
#include <tuple>

#include "helpers.h"

positions_t get_positions(std::string fname){
    positions_t retval;
    std::string line;

    std::ifstream fh(fname);

    int line_no=0, col_no=1;

    while(fh.good()){
        line_no++;
        col_no = 1;

        std::getline(fh, line);

        for(int i=0; i<line.length(); i++){
            if(line[i] == '*'){
                retval.push_back(std::make_pair(line_no, col_no));
            }
            col_no++;
        }
    }

    fh.close();

    return retval;
}
