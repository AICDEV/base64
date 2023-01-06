/**
 * @file b64.c
 * @author aicdev
 * @date 2023-01-06
 */
#include <string.h>
#include <stdio.h>
#include "b64.h"

static const char b64_encoding_table[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'};


unsigned short get_b64_table_index(char el) {
    unsigned short index = 0;
    for(; index < 64; index++) {
        if(b64_encoding_table[index] == el) {
            break;
        }
    }

    return index;
}

b64_encoding_padding_t get_encoding_offset(size_t input_len) {
    b64_encoding_padding_t padding = input_len % B_BASE;

    if (padding == 1) {
        return 2;
    } else if (padding == 2) {
        return 1;
    } else {
        return padding;
    }
}

b64_decoded_t* decode_base64(char *input) {

    size_t input_l = strlen(input);
    b64_required_storage_size_t r_storage = calc_b64_decoding_size(input_l);
    b64_decoded_t *b_out = (b64_decoded_t*)calloc(r_storage, sizeof(b64_decoded_t));

    if(input_l % 4 != 0) {
        return "";
    }

    for(int i = 0, c = 0; i < input_l; i += 4) {
        int block = 0;

        for(int a = 0; a < 4; a++) {
            unsigned short test = get_b64_table_index(input[(i+a)]);

            if(test == 64) {
                test = 0;
            }

            block |= test;
            
            if((a + 1) < 4) {
                block <<= 6;
            }
        }

        for (int x = 2; x >= 0; x--) {
            b_out[c] = (char)(block >> (x * 8)) & 0xFF;
            c++;
        }
    }

    return b_out;
    
}

b64_encoded_t* encode_base_64(char *input) {

    size_t input_l = strlen(input);
    b64_encoding_padding_t padding = get_encoding_offset(input_l);
    b64_required_storage_size_t r_storage = calc_b64_encoding_size(input_l);
    b64_encoded_t *b_out = (b64_encoded_t*)calloc(r_storage, sizeof(b64_encoded_t));  

    for(int i = 0, c =0; i < (input_l); i+= 3) {

        int block = 0;

        for(int a = 0; a < 3; a++) {
            
            if((i + a) <= input_l) {
            
                block |= (char)input[i+a];
            
                if(a != 2) {
                    block <<= 8;
                }
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

    return b_out;
}