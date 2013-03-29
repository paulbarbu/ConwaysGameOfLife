#include <string>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "ConwaysGameOfLife.h"
#include "Game.h"
#include "helpers.h" //positions_t

int main(int argc, char **argv){
    std::string tilemap;
    unsigned int width, height;

    po::options_description desc("Program options");
    desc.add_options()
        ("help", "show this help message")
        ("width,w", po::value<unsigned int>(&width)->default_value(10),
         "the number of cell columns")
        ("height,h", po::value<unsigned int>(&height)->default_value(10),
         "the number of cell rows")
        //TODO: this should be the default
        ("file,f", po::value<std::string>(&tilemap)->default_value("tilemap.txt"),
         "the tilemap to be loaded as starting grid for the game");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")){
        std::cout<<desc<<"\n";
        return 0;
    }

    //TODO: if I can find width and height in the tilemap, overwrite these
    //TODO: remove these
    std::cout<<vm["file"].as<std::string>()<<"\n"
             <<vm["width"].as<unsigned int>()<<"\n"
             <<vm["height"].as<unsigned int>()<<"\n";

    positions_t pos(get_positions(tilemap));

    if(pos.size() == 0){
        std::cout<<"Could not get positions in order to start the game\n";
        return 1;
    }

    for(auto it=pos.begin(); it != pos.end(); ++it){
        std::cout<<it->first<<" "<<it->second<<"\n";
    }

    ConwaysGameOfLife cgol(width, height, pos);
    cgol.showBoard();

    try{
        Game g(width, height, pos);
        g.run();
    }
    catch(std::exception &e){
        std::cout<<e.what()<<"\nExiting...\n";
    }

    return 0;
}
