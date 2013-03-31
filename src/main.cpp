#include <string>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "ConwaysGameOfLife.h"
#include "Game.h"
#include "helpers.h" //positions_t

int main(int argc, char **argv){
    std::string filename;
    unsigned int no_columns, no_rows;
    int interval;

    po::options_description desc("Program options");
    desc.add_options()
        ("help,h", "show this help message")
        ("columns,c", po::value<unsigned int>(&no_columns)->default_value(10),
         "the number of columns (number of cells on the X axis)")
        ("rows,r", po::value<unsigned int>(&no_rows)->default_value(10),
         "the number of rows (number of cells on the Y axis)")
        ("file,f", po::value<std::string>(&filename)->default_value("blinker.txt"),
         "the starting generation of cells to be loaded, this option is a positional one")
        ("interval,i", po::value<int>(&interval)->default_value(500),
         "the interval at which new generations are generated and drawn, in milliseconds");

    po::positional_options_description positional_opts;
    positional_opts.add("file", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc)
                .positional(positional_opts).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        std::cout<<desc<<"\n";
        return 0;
    }

    if(interval <= 0){
        std::cout<<"Please pass a strictly positive interval\n";
        return 1;
    }

    positions_t pos = read_config(filename, no_rows, no_columns);

    if(pos.size() == 0){
        std::cout<<"Invalid configuration file provided!\n"
            "Check the number of rows and columns you provided and the initial\n"
            "size of the generation of cells, the generation may not fit in\n"
            "the screen size.\n";
        return 1;
    }

    ConwaysGameOfLife cgol(no_rows, no_columns, pos);

    SDL_Color alive_cell_color;
    alive_cell_color.r = 255;
    alive_cell_color.g = 255;
    alive_cell_color.b = 255;

    SDL_Color dead_cell_color;
    dead_cell_color.r = 0;
    dead_cell_color.g = 0;
    dead_cell_color.b = 0;

    try{
        Game g(no_rows, no_columns, interval, alive_cell_color, dead_cell_color,
               &cgol, pos);
        g.run();
    }
    catch(std::exception &e){
        std::cout<<e.what()<<"\nExiting...\n";
        return 1;
    }

    return 0;
}
