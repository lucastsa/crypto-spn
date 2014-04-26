#ifndef LINEAR_H
#define LINEAR_H 1

#include "spn.h"    // S-Box implementation was modified to have only 4 rounds

// Substitution box provided in Homework 2
byte SBOX[64] = {
    60, 12, 9, 11, 39, 52, 1, 36,
    41, 50, 53, 26, 28, 33, 8, 42,
    19, 45, 35, 46, 62, 59, 4, 13,
    6, 14, 40, 49, 58, 38, 47, 63,
    24, 22, 43, 55, 18, 48, 2, 23,
    25, 31, 16, 10, 5, 27, 15, 61,
    44, 3, 29, 7, 21, 20, 54, 57,
    32, 17, 30, 56, 34, 51, 37, 0
};

// Permutation box provided in Homework 2
byte PBOX[24] = {
    0, 6, 12, 18,
    1, 7, 13, 19,
    2, 8, 14, 20,
    3, 9, 15, 21,
    4, 10, 16, 22,
    5, 11, 17, 23
};

void generate_approx_table();
void generate_pairs();
void attack();

/*
    Generates a 32-bit pseudo random number
*/
int random_number() {
    static char seeded = 0;

    if (!seeded) {
        srand(time(NULL)); // seeding with current time
        seeded = 1;
    }

    return rand();
}

/*
    Returns the parity of a bitstring
*/
inline unsigned char get_parity(unsigned int word) {
    unsigned char parity = 0;

    while (word) {
      parity = !parity;
      word = word & (word - 1);
    }

    return parity;
}

/* Auxiliar to print linear approx table as html */
void print_table_html(char sbox_linear_approx[64][64]) {
    unsigned int j,k;

    printf("<table border='1'><tr><th>&nbsp;</th>");
    for (k=0; k < 64; k++) {
        printf("<th>%02hhX</th>", k);
    }
    printf("</tr>\n");

    for (j=0; j < 64; j++) {
        printf("<tr><th>%02hhX</th>", j);
        for (k=0; k < 64; k++) {
            printf("<td>%hhi</td>", sbox_linear_approx[j][k]);
        }
        printf("</tr>\n");
    }
    printf("</table>\n");
}

/* Auxiliar to print linear approx table as LaTeX */
void print_table_latex(char sbox_linear_approx[64][64]) {
    unsigned int j,k;

    printf("\\begin{tabular}{|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|}\n");
    printf(" & ");
    for (k=0; k < 63; k++) {
        printf("%02hhX & ", k);
    }
    printf("%02hhX \\\\ \\hline\n", k);

    for (j=0; j < 64; j++) {
        printf("%02hhX & ", j);
        for (k=0; k < 63; k++) {
            printf("%hhi & ", sbox_linear_approx[j][k]);
        }
        printf("%hhi \\\\ \\hline\n", sbox_linear_approx[j][k]);
    }
    printf("\\end{tabular}\n");
}

#endif