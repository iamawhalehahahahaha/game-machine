#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <ctime>

#include "../hdr/minesweeper.h"

Msweep::Msweep():
    board((unsigned char *)(::operator new(MSWEEP_ROWS_DEFAULT_NEW * MSWEEP_COLUMNS_DEFAULT_NEW))),
    rows(MSWEEP_ROWS_DEFAULT_NEW),
    columns(MSWEEP_COLUMNS_DEFAULT_NEW),
    mines(MSWEEP_MINES_DEFAULT_NEW)
{ }

Msweep::Msweep(std::size_t new_rows,
               std::size_t new_columns,
               std::size_t new_mines):
    board((unsigned char *)(::operator new(new_rows * new_columns))),
    rows((new_rows < MSWEEP_ROWS_MAX) ? new_rows : MSWEEP_ROWS_DEFAULT_NEW),
    columns((new_columns < MSWEEP_COLUMNS_MAX) ? new_columns : MSWEEP_ROWS_DEFAULT_NEW),
    mines((new_mines < new_rows * new_columns - 1) ? new_mines : new_rows * new_columns - 1)
{ }

void Msweep::play()
{
    srand(time(NULL));

    print();

    insertMines(0, 0);

    floodfill(0, 0);

    print();
}

void Msweep::floodfill(std::size_t row, std::size_t column)
{
    if (row >= rows || column >= columns)
        return;

    if (board[(row * columns) + column] > 0)
        return;

    board[(row * columns) + column] |= 0x80;

    floodfill(row - 1, column - 1);
    floodfill(row - 1, column);
    floodfill(row - 1, column + 1);
    floodfill(row, column - 1);
    floodfill(row, column + 1);
    floodfill(row + 1, column - 1);
    floodfill(row + 1, column);
    floodfill(row + 1, column + 1);
}

void Msweep::insertMines(std::size_t start_row, std::size_t start_column)
{
    std::size_t current_mines;
    std::size_t current_row;
    std::size_t current_column;

    while (current_mines < mines)
    {
        current_row = rand() % rows;
        current_column = rand() % columns;

        if (current_row == start_row || current_column == start_column ||
           (board[(current_row * columns) + current_column] & 0x3f) >= 9)
            continue;

        board[(current_row * columns) + current_column] |= 0x1f;
        ++current_mines;

        updateMine(current_row - 1, current_column - 1);
        updateMine(current_row - 1, current_column);
        updateMine(current_row - 1, current_column + 1);
        updateMine(current_row, current_column - 1);
        updateMine(current_row, current_column + 1);
        updateMine(current_row + 1, current_column - 1);
        updateMine(current_row + 1, current_column);
        updateMine(current_row + 1, current_column + 1);
    }
}

void Msweep::updateMine(std::size_t row, std::size_t column)
{
    if (row >= rows || column >= columns)
        return;

    if ((board[(row * columns) + column] & 0x3f) >= 9)
        return;

    ++board[(row * columns) + column];
}

void Msweep::print()
{
    std::size_t i;
    std::size_t j;

    printf("   ");

    for (i = 0; i < columns; ++i)
    {
        printf(" %2d", i + 1);
    }

    printf("\n  +-");

    for (i = 0; i < columns; ++i)
    {
        printf("---");
    }

    printf("\n");

    for (i = 0; i < rows; ++i)
    {
        printf("%2d| ", i + 1);

        for (j = 0; j < columns; ++j)
        {
            if ((board[(i * columns) + j] & 0x40) > 0)
            {
                printf(" ? ");
            }
            else if (!(board[(i * columns) + j] & 0x80))
            {
                printf(" # ");
            }
            else if ((board[(i * columns) + j] & 0x1f) == 0)
            {
                printf(" - ");
            }
            else if ((board[(i * columns) + j] & 0x3f) < 9)
            {
                printf(" %d ", (board[(i * columns) + j] & 0x3f));
            }
            else
            {
                printf(" * ");
            }
        }

        printf("\n");
    }
}

Msweep::~Msweep()
{
    delete(board);
}
