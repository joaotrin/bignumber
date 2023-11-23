
// implementation

#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functions develpment

char* read_string()
{
    char* s = malloc(sizeof(char));

    int prev_is_leading_zero = 1;
    unsigned long long int i = 0;
    while (1)
    {
        char c = getchar();
        if (c != '\n')
        {
            if (c == '0' && prev_is_leading_zero)
                continue;
            else
            {
                prev_is_leading_zero = 0;
                s = realloc(s, sizeof(char) * (i+1));
                s[i] = c;
            }
        }
        else
        {
            s = realloc(s, sizeof(char) * (i+1));
            s[i] = '\0';
            break;
        }
        i++;
    }

    return s;
}

char* read_char()
{
    char* c = malloc(sizeof(char));
    *c = getchar();
    getchar();
    return c;
}

bignumber init_bignumber()
{
    bignumber n = malloc(sizeof(struct bignumber_struct));

    char sign_char = getchar();
    if (sign_char == '+' || sign_char == '-')
        n->sign = sign_char;

    else
    {
        n->sign = '+';
        ungetc(sign_char, stdin);
    }

    n->digits = read_string();
    n->size = strlen(n->digits);

    return n;
}

void free_bignumber(bignumber n)
{
    free(n->digits);
    free(n);
}

void reverse_string(char* s, int ini, int len)
{
    if (len - ini > 1)
    {
        char t = s[ini];
        s[ini] = s[len-1];
        s[len-1] = t;

        if (len - ini > 2)
            reverse_string(s, ini + 1, len - 1); 
    }
}

void reverse_and_add_zero(bignumber n)
{
    reverse_string(n->digits, 0, n->size);

    n->digits = realloc(n->digits, sizeof(char) * (n->size + 1));
    n->digits[n->size] = '0';
    n->size++;
}

void get_char_decimals(bignumber n)
{
    for (int i = 0; i < n->size; i++)
        n->digits[i] -= '0'; // or "-= 48"
}

void print_reversed_bignumber(bignumber n)
{
    int all_zeros = 1;
    for (int i = 0; i < n->size; i++)
    {
        if (n->digits[i] != 0)
        {
            all_zeros = 0;
            break;
        }
    }
    if (all_zeros)
    {
        printf("0\n");
        return;
    }

    if (n->sign == '-')
        printf("-");

    int prev_is_leading_zero = 1;
    for (int i = n->size - 1; i >= 0; i--)
    {
        if (prev_is_leading_zero && n->digits[i] == 0)
            continue;
        else
        {
            prev_is_leading_zero = 0;
            printf("%d", n->digits[i]);
        }            
    }

    printf("\n");
}

void compare_sizes(bignumber n1, bignumber n2, bignumber* nLonger, bignumber* nShorter)
{
    if (n1->size >= n2->size)
    {
        *nLonger = n1;
        *nShorter = n2;
    }
    else
    {
        *nLonger = n2;
        *nShorter = n1;
    }
}

void compare_values(bignumber n1, bignumber n2, bignumber* nBigger, bignumber* nSmaller)
{
    int d = 0;

    if (n1->sign != n2->sign)
    {
        if (n1->sign == '+')
        {
            *nBigger = n1;
            *nSmaller = n2;
        }
        else
        {
            *nBigger = n2;
            *nSmaller = n1;
        }
    }

    else if (n1->sign == '+')
    {
        if (n1->size != n2->size)
        {
            if (n1->size > n2->size)
            {
                *nBigger = n1;
                *nSmaller = n2;
            }
            else
            {
                *nBigger = n2;
                *nSmaller = n1;
            }
        }
        else
        {
            
            for (int i = n1->size - 1; i >= 0; i--)
            {
                if (n1->digits[i] != n2->digits[i])
                {
                    if (n1->digits[i] > n2->digits[i])
                    {
                        *nBigger = n1;
                        *nSmaller = n2;
                        d = 1;
                        break;
                    }
                    else
                    {
                        *nBigger = n2;
                        *nSmaller = n1;
                        d = 1;
                        break;
                    }
                }
            }
            if (d == 0)
                *nBigger = *nSmaller = n1;
        }
    }

    else
    {
        if (n1->size != n2->size)
        {
            if (n1->size > n2->size)
            {
                *nBigger = n2;
                *nSmaller = n1;
            }
            else
            {
                *nBigger = n1;
                *nSmaller = n2;
            }
        }
        else
        {
            for (int i = n1->size - 1; i >= 0; i--)
            {
                if (n1->digits[i] != n2->digits[i])
                {
                    if (n1->digits[i] > n2->digits[i])
                    {
                        *nBigger = n2;
                        *nSmaller = n1;
                        d = 1;
                        break;
                    }
                    else
                    {
                        *nBigger = n1;
                        *nSmaller = n2;
                        d = 1;
                        break;
                    }
                }
            }
            if (d == 0)
                *nBigger = *nSmaller = n1;
        }
    }
}

void add_bignumbers(bignumber nLonger, bignumber nShorter, bignumber* RESULT)
{
    nShorter->digits = realloc(nShorter->digits, sizeof(char) * nLonger->size);
    for (int i = nShorter->size; i < nLonger->size; i++)
    {
        nShorter->digits[i] = 0;
        // nShorter->size++;
    }

    int sum;
    int carry = 0;
    for (int i = 0; i < nLonger->size; i++)
    {
        sum = nLonger->digits[i] + nShorter->digits[i] + carry;
        nLonger->digits[i] = sum % 10;
        carry = sum / 10;
    }

    *RESULT = nLonger;
}

void subtract_bignumbers(bignumber n1, bignumber n2, bignumber* RESULT)
{
    n2->digits = realloc(n2->digits, sizeof(char) * n1->size);
    for (int i = n2->size; i < n1->size; i++)
    {
        n2->digits[i] = 0;
        // n2->size++;
    }

    int result;
    int borrow = 0;
    for (int i = 0; i < n1->size; i++)
    {
        result = n1->digits[i] - n2->digits[i] - borrow;

        if (result < 0)
        {
            result += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        n1->digits[i] = result;
    }

    *RESULT = n1;
}

void multiply_bignumbers(bignumber n1, bignumber n2, bignumber* RESULT)
{
    bignumber product = malloc(sizeof(struct bignumber_struct));

    if (n1->sign == n2->sign)
        product->sign = '+';
    else
        product->sign = '-';

    product->size = n1->size * n2->size;
    product->digits = malloc(sizeof(char) * product->size);

    for (int i = 0; i < product->size; i++)
        product->digits[i] = 0;

    int sum;
    for (int i = 0; i < n1->size; i++)
    {
        int carry = 0;
        for (int j = 0; j < n2->size; j++)
        {
            sum = product->digits[i+j] + (n1->digits[i] * n2->digits[j]) + carry;
            product->digits[i+j] = sum % 10;
            carry = sum / 10;
        }
    }

    *RESULT = product;
}

void choose_operation(char op, bignumber n1, bignumber n2, bignumber* nLonger, bignumber* nShorter, bignumber* nBigger, bignumber* nSmaller, bignumber* RESULT)
{
    switch (op)
    {
        case '+':
            
            if ((*nLonger)->sign == (*nShorter)->sign)
            {
                if ((*nLonger)->sign == '+')
                {
                    add_bignumbers(*nLonger, *nShorter, RESULT);
                }
                else
                {
                    (*nLonger)->sign = '+';
                    (*nShorter)->sign = '+';
                    add_bignumbers(*nLonger, *nShorter, RESULT);
                    (*RESULT)->sign = '-';
                }
            }
            else
            {
                (*nSmaller)->sign = '+';

                bignumber moduleBigger, moduleSmaller;
                compare_values(n1, n2, &moduleBigger, &moduleSmaller);

                subtract_bignumbers(moduleBigger, moduleSmaller, RESULT);

                if (moduleBigger == *nBigger)
                    (*RESULT)->sign = '+';
                else
                    (*RESULT)->sign = '-';
            }

            break;
        
        case '-':

            if (n1->sign == n2->sign)
            {
                if (n1->sign == '+')
                {
                    subtract_bignumbers(*nBigger, *nSmaller, RESULT);

                    if (*nBigger == n1)
                        (*RESULT)->sign = '+';
                    else
                        (*RESULT)->sign = '-';
                }
                else
                {
                    n1->sign = '+';
                    n2->sign = '+';
                    compare_values(n1, n2, nBigger, nSmaller);

                    subtract_bignumbers(*nBigger, *nSmaller, RESULT);

                    if (*nBigger == n2)
                        (*RESULT)->sign = '+';
                    else
                        (*RESULT)->sign = '-';
                }
            }
            else
            {
                if (n1->sign == '+')
                {
                    n2->sign = '+';
                    compare_sizes(n1, n2, nLonger, nShorter);
                    add_bignumbers(*nLonger, *nShorter, RESULT);
                }
                else
                {
                    n1->sign = '+';
                    compare_sizes(n1, n2, nLonger, nShorter);
                    add_bignumbers(*nLonger, *nShorter, RESULT);
                    (*RESULT)->sign = '-';
                }
            }

            break;
        
        case '*':

            multiply_bignumbers(n1, n2, RESULT);

            break;
    }
}

