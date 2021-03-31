#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main()
{
    char *input = malloc(sizeof(char) * 100);
    char c;
    int _;

    while (1)
    {
        printf("$> ");
        _ = scanf("%2000[^\n]", input);
        _ = scanf("%c", &c);

        ParserResult *result = parser_parse(input);

        if (result->error == NULL)
        {
            printf("\n%f\n\n", result->result);
        }
        else
        {
            printf("\n%s\n\n", result->error);
        }
        free(result);
    }

    return 0;
}
