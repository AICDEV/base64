#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./lib/b64.h"


void usage() {
    printf("encode: './b4 <value>'\n");
    printf("decode: './b4 -d <value>'\n");
}

int main(int argc, char *argv[]) {

    if (argc == 2) {
        
        char *input = argv[1];
        b64_encoded_t *b_out = encode_base_64(input);

        printf("%s\n", b_out);
        free(b_out);
       
    } else if (argc == 3) {
     
        char *input = argv[2];
        b64_decoded_t *b_out = decode_base64(input);
        
        printf("%s\n", b_out);
        free(b_out);
    } else {
        usage();
        return EXIT_FAILURE;
    }
}