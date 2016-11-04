#include "minesweeper.h"

Msweep::Msweep():
    board((tile_t *)(::operator new(sizeof(tile_t) * MSWEEP_ROWS_DEFAULT * MSWEEP_COLUMNS_DEFAULT))),
    rows(MSWEEP_ROWS_DEFAULT),
    columns(MSWEEP_COLUMNS_DEFAULT),
    mines(MSWEEP_MINES_DEFAULT)
{ }

Msweep::Msweep(std::size_t new_rows,
               std::size_t new_columns,
               std::size_t new_mines):
    rows((new_rows < MSWEEP_ROWS_MAX) ? new_rows : MSWEEP_ROWS_MAX),
    columns((new_columns < MSWEEP_COLUMNS_MAX) ? new_columns : MSWEEP_COLUMNS_MAX),
    mines((new_mines < new_rows * new_columns - 1) ? new_mines : new_rows * new_columns - 1)
{
    mines = (new_mines < rows * columns - 1) ? new_mines : rows * columns - 1;
    board = (tile_t *)(::operator new(sizeof(tile_t) * rows * columns));
}

void Msweep::play()
{
    srand(time(NULL));

    print();

    /*
    insertMines(0, 0);

    floodfill(0, 0);

    print();
    */
}

bool Msweep::sweep(std::size_t row, std::size_t column)
{
    
}

void Msweep::print()
{

    std::size_t i;
    std::size_t j;

    system("clear");

    printf("   ");

    for (i = 0; i < columns; ++i)
    {
        printf(" %2lu", i + 1);
    }

    printf("\n  +-");

    for (i = 0; i < columns; ++i)
    {
        printf("---");
    }

    printf("\n");

    for (i = 0; i < rows; ++i)
    {
        printf("%2lu| ", i + 1);

        for (j = 0; j < columns; ++j)
        {
            //flags
            if (board[i * columns + j].flag == true)
            {
                printf(" ? ");
            }
            else if (board[i * columns + j].view == false)
            {
                printf(" # ");
            }
            else
            {
                printf(" %c ", board[i * columns + j].tile);
            }
        }

        printf("\n");
    }
}

Msweep::~Msweep()
{
    delete board;
}
