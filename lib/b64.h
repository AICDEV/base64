/**
 * @file b64.h
 * @author aicdev
 * @date 2023-01-06
 */
#ifndef B64_H
#define B64_H

#include <stdlib.h>

#define B_FACTOR 4
#define B_BASE 3
#define calc_b64_encoding_size(l) (((B_FACTOR * l / B_BASE) + B_BASE) & ~B_BASE) + 1
#define calc_b64_decoding_size(l) (((B_BASE * l / B_FACTOR) + B_BASE) & ~B_BASE) + 1


typedef char b64_encoded_t;
typedef char b64_decoded_t;
typedef size_t b64_required_storage_size_t;
typedef short b64_encoding_padding_t;

b64_encoding_padding_t get_encoding_offset(size_t input_len);

b64_encoded_t* encode_base_64(char *input);
b64_decoded_t* decode_base64(char *input);

#endif