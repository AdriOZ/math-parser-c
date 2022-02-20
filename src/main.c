#include <stdio.h>

#include "parser.h"

int main()
{
    char input[100];
    char clear;
    int run = 1;
    int ignore;
    FILE *log = fopen("log.txt", "a");

    while (run)
    {
        printf("$> ");
        ignore = scanf("%99[^\n]", input);
        ignore = scanf("%c", &clear);

        if (run = (input[0] != 'q' && input[0] != 'Q' && input[0] != 'e' && input[0] != 'E'))
        {
            ParserResult result = parser_parse(input);

            if (result.error == NULL)
            {
                printf("\n%.2f\n\n", result.result);
                fprintf(log, "%s = %.2f\n", input, result.result);
            }
            else
            {
                printf("\n%s\n\n", result.error);
                fprintf(log, "%s = %s\n", input, result.error);
            }
        }
    }

    fclose(log);

    return 0;
}
