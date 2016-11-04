#ifndef MSWEEP_H_
#define MSWEEP_H_

#define MSWEEP_ROWS_DEFAULT_NEW (10)
#define MSWEEP_COLUMNS_DEFAULT_NEW (10)
#define MSWEEP_MINES_DEFAULT_NEW (10)

#define MSWEEP_ROWS_MAX (30)
#define MSWEEP_COLUMNS_MAX (26)
#define MSWEEP_MINES_MAX (MSWEEP_ROWS_MAX * MSWEEP_COLUMNS_MAX - 1)

#include <cstddef>

class Msweep
{
public:
    void play();
    Msweep();
    Msweep(std::size_t rows, std::size_t columns, std::size_t mines);
    ~Msweep();
private:
    void insertMines(std::size_t start_row, std::size_t start_column);
    void updateMine(std::size_t start_row, std::size_t start_column);
    void floodfill(std::size_t start_row, std::size_t start_column);
    bool sweep(std::size_t test_row, std::size_t test_column);
    bool flag(std::size_t flag_row, std::size_t flag_column);
    void end(bool win);
    void print();

    unsigned char* board;
    std::size_t rows;
    std::size_t columns;
    std::size_t mines;
};

#endif /* MSWEEP_H_ */