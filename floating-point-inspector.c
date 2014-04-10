#include <stdio.h>
#include <stdlib.h>

// report whether machine is big or small endian
void bigOrSmallEndian()
{
    int     test_int = 1;

    printf("byte order: ");

    // endian type: check rightmost byte
    // (note: this method of finding endian type depends on
    //   char and int being different lengths)
    // for more info, see references:
    //   - http://ndevilla.free.fr/endian/
    //   - http://vijayinterviewquestions.blogspot.com/2007/07/
    //       what-little-endian-and-big-endian-how.html
    
    if (*(char *)&test_int == 1)
        printf("little-endian\n\n");
    else
        printf("big-endian\n\n");
}

// get next int (entered in hex) using scanf()
// returns 1 (success) or 0 (failure)
// if call succeeded, return int value via i pointer
int getNextHexInt(int *i)
{
    int     result = 0;

    if (scanf("%x", i) == 1)
        result = 1;
    return result;
}

// print requested data for the given number
void printNumberData(int i)
{
    int     sign_bit        = 0;
    int     exponent_bits   = 0;
    int     fraction_bits   = 0;
    int     normalized      = 1;
    
    if (i < 0)
        sign_bit = 1;                       // "1" means sign bit is negative
    exponent_bits = i & 0x7F800000;         // mask 0x7F800000 is for bits 30-23
    exponent_bits = exponent_bits >> 23;    // get exponent bits
    fraction_bits = i & 0x007FFFFF;         // mask 0x007FFFFF is for bits 22-0

    printf("signBit %d, expBits %3d, fractBits 0x%08X\n",
            sign_bit, exponent_bits, fraction_bits);

    // check normalization
    if (exponent_bits == 0) {
        if (fraction_bits != 0) {
            normalized = 0;                 // not normalized
            printf("denormalized: exp = %d", (exponent_bits - 126));
        } else {
            // check zero
            normalized = 0;                 // not normalized
            if (sign_bit == 0) {
                printf("+zero");
            } else {
                printf("-zero");
            }
        }
    } else {
        // check infinity
        if (exponent_bits == 0xff && fraction_bits == 0) {
            normalized = 0;                 // not normalized
            if (sign_bit == 0) {
                printf("+infinity");
            } else {
                printf("-infinity");
            }
        }

        // check NaN
        if (exponent_bits == 0xff && fraction_bits > 0) {
            // 0x00400000 mask hint for NaN type found in this reference:
            // http://www.c-jump.com/CIS77/reference/Intel/CIS77_24319002/pg_0342.htm
            if (fraction_bits & 0x00400000) {
                normalized = 0;             // not normalized
                printf("QNaN");
            } else {
                normalized = 0;             // not normalized
                printf("SNaN");
            }
        }

        if (normalized) {
            printf("normalized:   exp =  %d", (exponent_bits - 127));
        }
    }
    
    printf("\n\n");
}

int main(int argc, char **argv)
{
    int     i;                              // number currently being analyzed
    int     nValues;                        // number of values successfully parsed by scanf

    printf("Floating Point Inspector\n\n");
    bigOrSmallEndian();
    for (;;) {
        if (argc == 1)                      // allow grading script to control ...
            printf("> ");                   // ... whether prompt character is printed
        nValues = getNextHexInt(&i);
        printf("0x%08X\n", i);
        if (! nValues) {                    // encountered bad input
            printf("bad input\n");
            while (getchar() != '\n') ;     // flush bad line from input buffer
            continue;
        }
        printNumberData(i);
        if (i == 0)
            break;
    }
    printf("\n");
    return 0;
}
