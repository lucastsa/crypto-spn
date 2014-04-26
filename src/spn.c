#include <stdio.h>
#include <stdlib.h>
#include "spn.h"

/**
    Implements a SPN cipher.
        @message is a pointer to the plaintext. The result will replace this value.
        @size is the size of the message in bits
        @key is a pointer to the key
        @sbox is a substitution box lookup table to be used
        @pbox is a permutation lookup table to be used

*/
void spn(byte * message, unsigned int size, byte * key, byte * sbox, byte * pbox) {
    unsigned int size_in_bytes = size / BYTE_SIZE;
    int i = 0, b; // iteration, blocks

    /* Iterate over several blocks */
    for (b = 0; b < size_in_bytes; b+=BLOCK_SIZE) {
        // initial rounds
        for (i=1; i <= ITERATIONS-1; i++) {
            keyxor(message, key, b, i);
            substitution(message, b, sbox);
            permute(message, b, pbox);
        }

        // last round
        keyxor(message, key, b, i);
        substitution(message, b, sbox);

        // last key xor-ing
        keyxor(message, key, b, i+1);
    }
}

/**
    Permutes a given message at some block using a given permutation lookup table
*/
void permute(byte * message, unsigned int block, byte * pbox) {
    // using mask and shifts to convert the 3 8-bits chunks to uint (32-bit) while casting
    unsigned int word = ((0x000000FF & message[block]) << 16) +
                        ((0x000000FF & message[block+1]) << 8) +
                         (0x000000FF & message[block+2]);
    unsigned int new_word = 0x00000000; // initialize with 32 bits with 0
    int i;

    // setting bits in word2
	for (i = 0; i < PBOX_SIZE; i++)
        if (BIT_CHECK(word, pbox[i]))
            BIT_SET(new_word, i);

    // spliting new word in 3 8-bit chunks and putting in original message
    message[block+2] = new_word & 0x000000FF;
    message[block+1] = ((new_word & 0x0000FF00) >> 8);
    message[block] = ((new_word & 0x00FF0000) >> 16);
}

/**
    Perform a block XOR operation on a given message with a given key at some
    block. The iteration will generate the subkey.
*/
inline void keyxor(byte * message, byte * key, unsigned int block, unsigned int iteration) {
    int k = (iteration-1) * BLOCK_SIZE;

    message[block] ^= key[k];
    message[block+1] ^= key[k+1];
    message[block+2] ^= key[k+2];
}

/**
    Perform a simple Substitution with a 6-bit lookup table values. A initial 3-byte block
    is converted into 4 6-bit strings that will be passed to the 4 S-boxes. The result are
    concatenated again in a 3-byte block.
*/
void substitution(byte * message, unsigned int block, byte * sbox) {
    byte box1, box2, box3, box4; // 8-bit vars

    // spliting messages in six bits chunks
    box1 = (message[block] & 0xFC) >> 2; // upper six bits from msg[0]
    box2 = ((message[block] & 0x03) << 4) | (message[block+1] >> 4); // lower 2 bits from msg[0] + 4 upper bits of msg[1]
    box3 = ((message[block+1] & 0x0F) << 2) | ((message[block+2] & 0xC0) >> 6); // lower 4 bits from msg[1] + 2 upper bits of msg[2]
    box4 = message[block+2] & 0x3F; // lower six bits from msg[2]

    // basic lookup substitution
    box1 = sbox[box1];
    box2 = sbox[box2];
    box3 = sbox[box3];
    box4 = sbox[box4];

    // concatenating 6-bit chunks to form message
    message[block] = (box1 << 2) | ((box2 & 0x30 ) >> 4);
    message[block+1] = (box2 << 4) | ((box3 & 0x3C ) >> 2);
    message[block+2] = (box3 << 6) | (box4 & 0x3F);
}

/************************ Auxiliar functions **********************************/

/**
    Auxiliar to invert box (s-box or p-box)
*/
byte * box_inv(byte * box, unsigned int size) {
    int i;
    byte * box_i = malloc(size * sizeof(byte));

    for (i=0; i<size; i++)
        box_i[box[i]] = i;

    return box_i;
}

/**
    Auxiliar to invert key schedule (i.e. inverting and permuting to be
    used in decryption).
*/
byte * key_inv(byte * key, unsigned int size, byte * pbox_i) {
    int i, j;
    byte * key_i = malloc(size * sizeof(byte));

    for (i=0; i<size; i+=BLOCK_SIZE) {
        for (j=0; j<BLOCK_SIZE; j++)
            key_i[i+j] = key[size - i - BLOCK_SIZE + j];

        if ((i > 0) && (i < size-BLOCK_SIZE))
            permute(key_i, i, pbox_i);
    }

    return key_i;
}