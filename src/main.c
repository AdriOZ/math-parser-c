#include <stdio.h>

#include "util.h"
#include "parser.h"

int main()
{
    char input[256];
    char clear;
    i32 run = 1;
    FILE *log = fopen("log.txt", "a");

    while (run)
    {
        printf("$> ");
        scanf_s("%255[^\n]", input, 255);
        scanf_s("%c", &clear, 1);

        run = (input[0] != 'q' &&
               input[0] != 'Q' &&
               input[0] != 'e' &&
               input[0] != 'E');

        if (run)
        {
            ParserResult result = parser_parse(input);

            if (result.error == NULL)
            {
                printf("\n%.2Lf\n\n", result.result);
                fprintf(log, "%s = %.2Lf\n", input, result.result);
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
