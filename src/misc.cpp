#include "misc.h"

getInput(std::size_t row, std::size_t column, char *prompt, char *error)
{
    printf("%s\n", prompt);

    while (scanf("%lu %lu", &row, &column) != 2)
    {
        printf("%s\n", error);
        cleanStdin();
    }
}

cleanStdin()
{
    char c;

    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}
