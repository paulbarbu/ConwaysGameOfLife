#ifndef H_CGOL
#define H_CGOL

#include <vector>

#include "helpers.h" // positions_t

typedef std::pair<unsigned int, unsigned int> neighbours_t;

class ConwaysGameOfLife{
    public:
        ConwaysGameOfLife(int rows, int cols, positions_t pos);
        void showBoard();
        std::pair<positions_t, positions_t> getGenerationChanges();
        std::pair<positions_t, positions_t> evolve();
    private:
        neighbours_t getNeighboursStatus(int line, int col);
        std::vector<std::vector<int>> board;
        int no_rows, no_columns;
};

#endif
