#include "mines.h"

Mines::Mines():
    board((tile_t *)(::operator new(sizeof(tile_t) * MINES_ROWS_DEFAULT * MINES_COLUMNS_DEFAULT))),
    rows(MINES_ROWS_DEFAULT),
    columns(MINES_COLUMNS_DEFAULT),
    mines(MINES_MINES_DEFAULT)
{ }

Mines::Mines(std::size_t new_rows,
              std::size_t new_columns,
              std::size_t new_mines):
    rows((new_rows < MINES_ROWS_MAX) ? new_rows : MINES_ROWS_MAX),
    columns((new_columns < MINES_COLUMNS_MAX) ? new_columns : MINES_COLUMNS_MAX),
    mines((new_mines < new_rows * new_columns - 1) ? new_mines : new_rows * new_columns - 1)
{
    mines = (new_mines < rows * columns - 1) ? new_mines : rows * columns - 1;
    board = (tile_t *)(::operator new(sizeof(tile_t) * rows * columns));
}

void Mines::play()
{
    srand(time(NULL));

    insertMines(0, 0);
    print();
/*
    floodfill(0, 0);

    print();
*/
}

void Mines::insertMines(std::size_t start_row, std::size_t start_column)
{
    std::size_t mine_count;
    std::size_t i;
    std::size_t j;

    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < columns; ++j)
        {
            board[i * columns + j].tile = '-';
        }
    }

    while (mine_count < mines)
    {
        i = rand() % rows;
        j = rand() % columns;

        if (i != start_row || j != start_column || board[i * columns + j].tile != '*')
        {
            ++mine_count;
            board[i * columns + j].tile = '*';
        }
    }
}

bool Mines::sweep(std::size_t i, std::size_t j)
{
    if (board[i * columns + j].flag == true)
        return true;

    board[i * columns + j].view = true;

    if (board[i * columns + j].tile == '*')
        return false;

/*
    if (board[i * columns + j].tile == '-')
        floodfill(i, j);
*/
    return true;
}

void Mines::print()
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
/*
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
*/
                putchar(' ');
                putchar(board[i * columns + j].tile);
                putchar(' ');
           // }
        }

        printf("\n");
    }
}

Mines::~Mines()
{
    delete board;
}
