#ifndef H_HELPERS
#define H_HELPERS

#include <vector>
#include <string>

typedef std::vector<std::pair<unsigned int, unsigned int>> positions_t;

positions_t read_config(std::string fname, unsigned int &no_rows,
                        unsigned int &no_columns);

#endif
