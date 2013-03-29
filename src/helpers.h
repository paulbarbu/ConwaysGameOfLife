#ifndef H_HELPERS
#define H_HELPERS

#include <vector>
#include <string>

typedef std::vector<std::pair<unsigned int, unsigned int>> positions_t;

positions_t get_positions(std::string fname);

#endif
