#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "spn.h"


void print_expression_html(byte i, byte k, char bias) {
    printf("<tr><td>");
    if (i & 0x01) printf("X0 + ");
    if (i & 0x02) printf("X1 + ");
    if (i & 0x04) printf("X2 + ");
    if (i & 0x08) printf("X3 + ");
    if (i & 0x10) printf("X4 + ");
    if (i & 0x20) printf("X5 + ");

    printf("</td><td>");

    if (k & 0x01) printf("Y0 + ");
    if (k & 0x02) printf("Y1 + ");
    if (k & 0x04) printf("Y2 + ");
    if (k & 0x08) printf("Y3 + ");
    if (k & 0x10) printf("Y4 + ");
    if (k & 0x20) printf("Y5 + ");

    printf("</td><td>%hhd</td></tr>\n", bias);
}

int main() {
    byte KEY[21] = {78, 231, 58, 170, 218, 181, 240, 150, 252, 10, 22, 1, 253, 130, 97, 26, 142, 64, 232, 242, 87};

    // default sbox provided
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

    // default b provided
    byte PBOX[24] = {
        0, 6, 12, 18,
        1, 7, 13, 19,
        2, 8, 14, 20,
        3, 9, 15, 21,
        4, 10, 16, 22,
        5, 11, 17, 23
    };

    byte i, k;
    char sbox_linear_approx[64][64];

    byte input, mask_input, mask_output;
    byte output, masked_input, masked_output;

    // zeroing sbox_linear_approx
    memset(sbox_linear_approx, -32, 64*64);

    for (input=0; input < 64; input++) {
        output = SBOX[input];
        for (mask_input=0; mask_input < 64; mask_input++) {
            masked_input = input & mask_input;
            for (mask_output=0; mask_output < 64; mask_output++) {
                masked_output = output & mask_output;
                if (!get_parity(masked_input ^ masked_output))
                    sbox_linear_approx[mask_input][mask_output]++;
            }
        }
    }


    printf("<table border='1'><tr><th>X</th><th>Y</th><th>Bias</th></tr>");
    for (i=0; i<64; i++) {
        for (k=0; k<64; k++) {
            if ((sbox_linear_approx[i][k] >= 8) || (sbox_linear_approx[i][k] <= -8)) {
                print_expression_html(i, k, sbox_linear_approx[i][k]);
            }
        }
    }
    printf("</table>");

    return;
}
