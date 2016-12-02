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
    bool sweep_status;
    bool flag_status;

    srand(time(NULL));
    system("clear");

    printf(
        "Welcome to Mines!  This is a game similar to Minesweeper! (except worse)\n"
        "The goal is to sweep the board without hitting any mines.\n"
        "So you have to reveal all the spaces that are not mines.\n\n"
        "You have to give input each turn that determines where you sweep for mines.\n"
        "If you hit a mine, then you lose.\n"
        "You can flag a mine so you don't have to worry about it.\n\n"
        "Input is handled by the user giving:\n"
        "    integer as a row,\n"
        "    integer as a column,\n"
        "    character (s or f) which determines whether or not to sweep or place a flag\n\n"
        "Each tile is represented with a character.\n"
        "The tiles are:\n"
        "    (1 - 8): the number of mines adjacent to the tile\n"
        "    #: an unrevealed tile\n"
        "    ?: a flag\n"
        "    *: a mine (if you see this, then you lost)\n\n"
        "press enter to continue.\n");

    getchar();

    print();
    getInput(&row, &column);
    insertMines(row, column);
    sweep(row, column);
    print();

    do
    {
        flag_status = getInput(&row, &column);
        if (flag_status == true)
        {
            flag(row, column);
        }
        else
        {
            sweep_status = sweep(row, column);
            if (sweep_status == false)
            {
                print();
                puts("OH NO YOU HIT A MINE!");
                puts("BOOM BOOM AAAHHHHH!");
                break;
            }
        }
        print();
        printf("Sweep status: %s\n", (sweep_status) ? "true" : "false");
    } while (victory() == false);
    if (victory() == true)
    {
        puts("\nYou win!\n");
    }
    puts("Game over.");
}

void Mines::insertMines(std::size_t start_row, std::size_t start_column)
{
    std::size_t mine_count = 0;
    std::size_t row = 0;
    std::size_t column = 0;
    std::size_t i = 0;

    for (i = 0; i < rows * columns; ++i)
    {
        board[i].tile = '-';
        board[i].flag = false;
        board[i].view = false;
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

bool Mines::victory()
{
    std::size_t i;

    for (i = 0; i < rows * columns; ++i)
    {
        if (board[i].tile != '*' && board[i].view == false)
        {
            return false;
        }
    }

    return true;
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

    printf("Input row column flag: ");

    while (scanf("%lu %lu %c", row, column, &flag) < 3 || *row == 0 || *column == 0 || *row > rows || *column > columns)
    {
        printf("Invalid input: expeceted: row column flag\n"
               "Input row column: ");

        cleanStdin();
    }

    --(*row);
    --(*column);

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
