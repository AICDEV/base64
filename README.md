# base64
Small and simple base64 library programmed in C.

## Compile
To compile the library, simply run the script 'build.sh'. Or directly in your bash:
```bash
gcc base.c ./lib/b64.c -Wall -O3 -s -std=c99 -o base
```

## Encodind with compiled bin
```bash
./base "base64 implementation makes fun"
YmFzZTY0IGltcGxlbWVudGF0aW9uIG1ha2VzIGZ1bg==
```

## Decoding with compiled bin
```bash
./base -d YmFzZTY0IGltcGxlbWVudGF0aW9uIG1ha2VzIGZ1bg==
base64 implementation makes fun
```

## Usage in your C program
If you only want to use the library, you can find a complete example in the base.c file.
```c
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
```

## Testing
The test is written in python. Simple run the following commands for testing:
```bash
#decoding test
python3 decoding_test.py

#encoding test
python3 encoding_test.py
```