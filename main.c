#include <stdio.h>

#include "parser.h"

int main()
{
    char input[100];
    char clear;
    int run = 1;
    int ignore;

    while (run)
    {
        printf("$> ");
        ignore = scanf("%99[^\n]", input);
        ignore = scanf("%c", &clear);

        if (run = (input[0] != 'q' && input[0] != 'Q'))
        {
            ParserResult result = parser_parse(input);

            if (result.error == NULL)
            {
                printf("\n%f\n\n", result.result);
            }
            else
            {
                printf("\n%s\n\n", result.error);
            }
        }
    }

    return 0;
}
