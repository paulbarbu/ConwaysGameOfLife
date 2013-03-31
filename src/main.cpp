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

    po::options_description desc("Program options");
    desc.add_options()
        ("help,h", "show this help message")
        ("columns,c", po::value<unsigned int>(&no_columns)->default_value(10),
         "the number of columns (number of cells on the X axis)")
        ("rows,r", po::value<unsigned int>(&no_rows)->default_value(10),
         "the number of rows (number of cells on the Y axis)")
        //TODO: this should be the default
        ("file,f", po::value<std::string>(&filename)->default_value("blinker.txt"),
         "the starting generation of cells to be loaded");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")){
        std::cout<<desc<<"\n";
        return 0;
    }

    //TODO: if I can find width and height in the file, overwrite these
    //TODO: remove these
    std::cout<<vm["file"].as<std::string>()<<"\n"
             <<vm["columns"].as<unsigned int>()<<"\n"
             <<vm["rows"].as<unsigned int>()<<"\n";

    positions_t pos(get_positions(filename));

    if(pos.size() == 0){
        std::cout<<"Could not get positions in order to start the game\n";
        return 1;
    }

    for(auto it=pos.begin(); it != pos.end(); ++it){
        std::cout<<it->first<<" "<<it->second<<"\n";
    }

    ConwaysGameOfLife cgol(no_rows, no_columns, pos);
    cgol.showBoard();

    //for(int i=0; i<3; i++){
        //std::cout<<"\n";
        //cgol.evolve();
        //cgol.showBoard();
    //}

    try{
        Game g(no_rows, no_columns, pos, &cgol);
        g.run();
    }
    catch(std::exception &e){
        std::cout<<e.what()<<"\nExiting...\n";
        return 1;
    }

    return 0;
}
