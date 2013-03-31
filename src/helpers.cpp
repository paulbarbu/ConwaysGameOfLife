#include <fstream>
#include <tuple>
#include <string>
#include <sstream>

#include "helpers.h"

/**
 * Get the initial positions from a file
 *
 * @param string fname the name of the configuration file
 * @param unsigned int &no_rows the number of rows to be displayed on the
 * screen, this number will be modified if the configuration file specifies one
 * @param unsigned int &no_columns the number of columns to be displayed on the
 * screen, this number will be modified if the configuration file specifies one
 *
 * @return a vector of pairs of unsigned ints representing the line and the
 * column position of the alive cells in the first generation, an empty vector
 * (ie: v.size() == 0) will be returned if the config is invalid (ie: the
 * provided generation is bigger than the provided number of rows and columns to
 * be displayed or if there is no starting generation in the file)
 */
positions_t read_config(std::string fname, unsigned int &no_rows,
                        unsigned int &no_columns){
    positions_t retval;
    std::string line;
    bool first_line = true;

    std::ifstream fh(fname);

    int cur_row=0, cur_col=1;

    while(fh.good()){
        std::getline(fh, line);

        if(first_line && line[0] != '*' && line[0] != '.' &&
           line.find(" ") != std::string::npos){
            first_line = false;

            std::istringstream iss(line);

            iss>>no_rows;
            iss>>no_columns;
        }
        else{
            ++cur_row;
            cur_col = 1;


            for(int i=0; i<line.length(); ++i){
                if(line[i] == '*'){
                    retval.push_back(std::make_pair(cur_row, cur_col));
                }
                ++cur_col;
            }
        }
    }

    fh.close();

    if(cur_row > no_rows || cur_col > no_columns){
        positions_t empty;
        return empty;
    }

    return retval;
}
