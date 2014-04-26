#ifndef SPN_H
#define SPN_H 1

/* auxiliar bit operations macros */
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

/* constants */
#define BYTE_SIZE 8
#define ITERATIONS 4 // 4 for linear cryptanalysis
#define PBOX_SIZE 24
#define BLOCK_SIZE 3

#define KEY_SIZE 21
#define SBOX_SIZE 6
#define SBOX_LOOKUP_SIZE 64 // 2 ^ SBOX_SIZE
#define PBOX_SIZE 24

/* defining byte type as unsigned char (8-bit) */
typedef unsigned char byte;

/*********/

byte * box_inv(byte * sbox, unsigned int size);
byte * key_inv(byte * key, unsigned int size, byte * pbox_i);

inline void keyxor(byte * message, byte * key, unsigned int block, unsigned int iteration);
void substitution(byte * message, unsigned int block, byte * sbox);
void permute(byte * message, unsigned int block, byte * pbox);
void spn(byte * message, unsigned int size, byte * key, byte * sbox, byte * pbox);

#endif