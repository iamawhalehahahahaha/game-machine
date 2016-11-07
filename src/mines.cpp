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
    std::size_t row = 0;
    std::size_t column = 0;

    srand(time(NULL));

    print();
    getInput(&row, &column);
    insertMines(row, column);
    sweep(row, column);
}

void Mines::insertMines(std::size_t start_row, std::size_t start_column)
{
    std::size_t mine_count;
    std::size_t row;
    std::size_t column;

    for (row = 0; row < rows; ++row)
    {
        for (column = 0; column < columns; ++column)
        {
            board[row * columns + column].tile = '-';
            board[row * columns + column].flag = false;
            board[row * columns + column].view = false;
        }
    }

    while (mine_count < mines)
    {
        row = rand() % rows;
        column = rand() % columns;

        if ((row != start_row || column != start_column) && board[row * columns + column].tile != '*')
        {
            ++mine_count;
            board[row * columns + column].tile = '*';

            updateTile(row - 1, column - 1);
            updateTile(row - 1, column);
            updateTile(row - 1, column + 1);
            updateTile(row, column - 1);
            updateTile(row, column + 1);
            updateTile(row + 1, column - 1);
            updateTile(row + 1, column);
            updateTile(row + 1, column + 1);
        }
    }
}

void Mines::updateTile(std::size_t row, std::size_t column)
{
    if (row >= rows || column >= columns)
        return;

    if (board[row * columns + column].tile == '*')
        return;

    if (board[row * columns + column].tile == '-')
    {
        board[row * columns + column].tile = '1';
    }
    else if (board[row * columns + column]. tile >= '1' && board[row * columns + column]. tile < '8')
    {
        ++board[row * columns + column].tile;
    }
    else
        puts("error: invalid tile\n");
}

bool Mines::sweep(std::size_t row, std::size_t column)
{
    if (board[row * columns + column].flag == true)
        return true;

    floodfill(row, column);

    return ! (board[row * columns + column].tile == '*');
}

void Mines::flag(std::size_t row, std::size_t column)
{
    if (board[row * columns + column].view == false)
    {
        board[row * columns + column].flag = !board[row * columns + column].flag;
    }
}

void Mines::floodfill(std::size_t row, std::size_t column)
{
    if (row >= rows || column >= columns)
        return;

    if (board[row * columns + column].view == true)
        return;

    board[row * columns + column].view = true;

    if (board[row * columns + column].tile != '-')
        return;

    floodfill(row - 1, column - 1);
    floodfill(row - 1, column);
    floodfill(row - 1, column + 1);
    floodfill(row, column - 1);
    floodfill(row, column + 1);
    floodfill(row + 1, column - 1);
    floodfill(row + 1, column);
    floodfill(row + 1, column + 1);
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
                putchar(' ');
                putchar(board[i * columns + j].tile);
                putchar(' ');
            }
        }

        printf("\n");
    }
}

bool Mines::getInput(std::size_t *row, std::size_t *column)
{
    char flag = 0;

    printf("Input row column: ");

    while (scanf("%lu %lu %c", row, column, &flag) < 2)
    {
        printf("Invalid input: expeceted: row column [f]\n"
               "Input row column: ");

        cleanStdin();
    }

    return flag == 'f';
}

void Mines::cleanStdin()
{
    int c;

    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

Mines::~Mines()
{
    delete board;
}
