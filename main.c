#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "parser.h"

int main()
{
    char input[100];
    char c;
    int _;

    while (1)
    {
        printf("$> ");
        _ = scanf("%[^\n]%c", input, &c);

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

    return 0;
}
