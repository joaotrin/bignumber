
// client

#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// main() script

int main()
{
    char temp_char;
    while ((temp_char = getchar()) != -1) // while there is input from stdin (until 'Ctrl + D')
    {
        ungetc(temp_char, stdin); // returns analized char ('temp_char') to be read again

        bignumber n1 = init_bignumber();
        bignumber n2 = init_bignumber();
        char* op = read_char();

        reverse_and_add_zero(n1);
        reverse_and_add_zero(n2);

        get_char_decimals(n1);
        get_char_decimals(n2);

        bignumber nLonger, nShorter, nBigger, nSmaller, RESULT;
        compare_sizes(n1, n2, &nLonger, &nShorter);
        compare_values(n1, n2, &nBigger, &nSmaller);

        choose_operation(*op, n1, n2, &nLonger, &nShorter, &nBigger, &nSmaller, &RESULT);

        print_reversed_bignumber(RESULT);

        free_bignumber(n1);
        free_bignumber(n2);
        if (*op == '*')
            free_bignumber(RESULT);
        free(op);
    }

    return 0;
}

