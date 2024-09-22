/**
 * @file b64.c
 * @author aicdev
 * @date 2023-01-06
 */
#include <string.h>
#include "b64.h"

static const char b64_encoding_table[B_TABLE_SIZE] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'};

static const unsigned char b64_decoding_table[ASCII_RANGE] = {
    [0 ... (ASCII_RANGE - 1)] = 64, 
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,
    ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,
    ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11,
    ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15,
    ['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19,
    ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24, ['Z'] = 25, ['a'] = 26, ['b'] = 27,
    ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31,
    ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35,
    ['k'] = 36, ['l'] = 37, ['m'] = 38, ['n'] = 39,
    ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43,
    ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47,
    ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51,
    ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55,
    ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59,
    ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63
};

b64_encoding_padding_t get_encoding_offset(size_t input_len) {
    switch (input_len % 3) {
        case 1: return 2;
        case 2: return 1;
        default: return 0;
    }
}

b64_decoded_t* decode_base64(const char *input) {

    size_t input_len = strlen(input);
    if (input_len % 4 != 0) {
        return NULL;
    }

    b64_required_storage_size_t r_storage = calc_b64_decoding_size(input_len);
    b64_decoded_t *b_out = (b64_decoded_t*)calloc(r_storage, sizeof(b64_decoded_t));
    if (!b_out) return NULL;

    for (size_t i = 0, c = 0; i < input_len; i += 4) {
        unsigned int block = 0;

        for (int a = 0; a < 4; a++) {
            unsigned char decoded_val = b64_decoding_table[(unsigned char)input[i + a]];
            block |= decoded_val << ((3 - a) * 6);
        }

        b_out[c++] = (block >> 16) & 0xFF;
        if (input[i + 2] != B64_PAD_CHAR) b_out[c++] = (block >> 8) & 0xFF;
        if (input[i + 3] != B64_PAD_CHAR) b_out[c++] = block & 0xFF;
    }


    return b_out;
    
}

b64_encoded_t* encode_base_64(const char *input) {

    size_t input_len = strlen(input);
    b64_encoding_padding_t padding = get_encoding_offset(input_len);
    b64_required_storage_size_t r_storage = calc_b64_encoding_size(input_len);
    b64_encoded_t *b_out = (b64_encoded_t*)calloc(r_storage + 1, sizeof(b64_encoded_t));
    if (!b_out) return NULL;

    for(int i = 0, c =0; i < (input_len); i+= 3) {

        unsigned int block = 0;

        for (int a = 0; a < 3; a++) {
            if (i + a < input_len) {
                block |= (unsigned char)input[i + a] << ((2 - a) * 8);
            }
        }

        for (int x = 3; x > -1; x--) {

            if ( (r_storage - (r_storage - c)) >= (r_storage - padding - 1)) {
                b_out[c] = 0x3D;
            } else {
                b_out[c] = b64_encoding_table[(block >> (x * 6)) & 0x3F];
            }

            c++;
        }

    }

    b_out[r_storage] = '\0';
    return b_out;
}