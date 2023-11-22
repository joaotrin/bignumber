
// interface

#ifndef BIGNUMBER_H
#define BIGNUMBER_H

// structs and function names

typedef struct bignumber_struct
{
    char sign;
    char* digits;
    int size;
}
* bignumber;

// adds chars to array with 'realloc':
char* read_string();

// reads single char (and reads '\n' after char and discards it):
char* read_char();

// uses 'read_string' to get bignumber->digits as arrays of chars and stores its length in bignumber->size:
bignumber init_bignumber();

// frees bignumber->digits and bignumber itself:
void free_bignumber(bignumber n);

// to get bignumber->digits backwards (recursively):
void reverse_string(char* s, int ini, int len);

// to use 'reverse_string' and add a leading zero to it (INCLUDED in 'bignumber->size'):
void reverse_and_add_zero(bignumber n);

// symbol '0' is equal to 48 in the ASCII Table, so 48 is subtracted of each digit to get its corresponding decimal value
// we keep using char data type to manipulate ints since we only need values from 0 to 9:
void get_char_decimals(bignumber n);

// prints bignumber->digits one by one (prints ints or chars' decimal values) and skips leading zero:
void print_reversed_bignumber(bignumber n);

// compares 'n1' and 'n2' according to their sizes (number of digits):
void compare_sizes(bignumber n1, bignumber n2, bignumber* nLonger, bignumber* nShorter);

// compares 'n1' and 'n2' according to their values:
void compare_values(bignumber n1, bignumber n2, bignumber* nBigger, bignumber* nSmaller);

// adds two bignumbers, with 'n1' being the longest (has more digits), and replaces 'n1' with the result:
void add_bignumbers(bignumber nLonger, bignumber nShorter, bignumber* RESULT);

// subtracts two bignumbers, with 'n1' being the first to appear, and replaces 'n1' with the result:
void subtract_bignumbers(bignumber n1, bignumber n2, bignumber* RESULT);

// multiplies two bignumbers:
void multiply_bignumbers(bignumber n1, bignumber n2, bignumber* RESULT);

// chooses which operation to do (some subtractions are easier to be calculated as additions of the modules of the numbers and vice versa):
void choose_operation(char op, bignumber n1, bignumber n2, bignumber* nLonger, bignumber* nShorter, bignumber* nBigger, bignumber* nSmaller, bignumber* RESULT);

#endif

