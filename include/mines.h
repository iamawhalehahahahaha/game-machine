#ifndef MINES_H_
#define MINES_H_

#define MINES_ROWS_DEFAULT (10)
#define MINES_COLUMNS_DEFAULT (10)
#define MINES_MINES_DEFAULT (10)

#define MINES_ROWS_MAX (30)
#define MINES_COLUMNS_MAX (26)
#define MINES_MINES_MAX (MINES_ROWS_MAX * MINES_COLUMNS_MAX - 1)

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstddef>

class Mines
{
public:
    void play();
    Mines();
    Mines(std::size_t rows, std::size_t columns, std::size_t mines);
    ~Mines();

private:
    void insertMines(std::size_t row, std::size_t column);
    void updateMine(std::size_t row, std::size_t column);
    void floodfill(std::size_t row, std::size_t column);
    bool sweep(std::size_t test_row, std::size_t test_column);
    bool flag(std::size_t flag_row, std::size_t flag_column);
    void end(bool win);
    void print();

    typedef struct tile_s
    {
        char tile;
        bool view;
        bool flag;
    } tile_t;

    tile_t *board;
    std::size_t rows;
    std::size_t columns;
    std::size_t mines;
};

#endif /* MINES_H_ */
