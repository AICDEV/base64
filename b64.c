/**
 * @file b64.c
 * @author aicdev
 * @date 2022-02-08
 * Simple base64 implementation
 * ./b64 <some_input> to encode
 * ./b64 -d <some_input> to decode
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void b64_decode(char *t, char *r, size_t l);
void b64_encode(char *t, char *r, size_t l);

static const char b64_table[65] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'};


void b64_decode(char *t, char *r, size_t l)
{   
    int c = 2;
    int index = 0;
    for(int i = 0; i < l; i += 4)
    {
        unsigned int blocks = 0x0;
        blocks |= (t[i] == 61) ? 0 : (t[i] >= 48 && t[i] <= 57) ? ((t[i] % 64) + 4) :  (t[i] > 90) ? ((t[i] % 64) - 7) : ((t[i] % 64) - 1);


        blocks <<= 6;
        blocks |=  (t[i + 1] == 61) ? 0 : (t[i + 1] >= 48 && t[i + 1] <= 57) ? ((t[i + 1] % 64) + 4) :  (t[i + 1] > 90) ? ((t[i + 1] % 64) - 7) : ((t[i + 1] % 64) - 1);


        blocks <<= 6;
        blocks |=  (t[i + 2] == 61) ? 0 : (t[i + 2] >= 48 && t[i + 2] <= 57) ? ((t[i + 2] % 64) + 4) :  (t[i + 2] > 90) ? ((t[i + 2] % 64) - 7) : ((t[i + 2] % 64) - 1);


        blocks <<= 6;
        blocks |=  (t[i + 3] == 61) ? 0 : (t[i + 3] >= 48 && t[i + 3] <= 57) ? ((t[i + 3] % 64) + 4) :  (t[i + 3] > 90) ? ((t[i + 3] % 64) - 7) : ((t[i + 3] % 64) - 1);


        while(c >= 0) {
            if((blocks >> (c * 8) & 0xFF) > 0) {
                r[index] = blocks >> (c * 8) & 0xFF;
            }
            index++;
            c--;
        }

        c = 2;
    }

      r[index] = 0x0;
}


void b64_encode(char *t, char *r,  size_t l)
{
    int base = 0;
    int index = 0;
    short offset = 3 - (l % 3);

    for (int i = 0; i < l; i += 3)
    {
        unsigned int blocks = 0x0;
        blocks |= t[i];
        blocks <<= 8;
        blocks |= t[i + 1];
        blocks <<= 8;
        blocks |= t[i + 2];

        if (i + 3 > l)
        {
            int a = 3;
            base = offset;
            while (a >= base)
            {
                r[index] =  b64_table[blocks >> (a * 6) & 0x3F];
                index++;
                a--;
            }

            while (offset > 0)
            {
                r[index] =  0x3D;
                index++;
                offset--;
            }

             r[index] = 0x0;
        }

        else
        {
            int c = 3;
            while (c >= 0)
            {
                r[index] =  b64_table[blocks >> (c * 6) & 0x3F];
                index++;
                c--;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        char *input = argv[1];
        size_t l = strlen(input);
        size_t al = (4 * (l / 3) + 1);

        char r[al];
        memset(r, 0, al);

        b64_encode(input, r, l);
        fwrite(r, al, 1, stdout);
        printf("\n");

        return EXIT_SUCCESS;
    }

    if (argc == 3)
    {
        if (!strcmp(argv[1], "-d"))
        {
            char *input = argv[2];
            size_t l = strlen(input);
            size_t al = (3 * (l / 4) + 1);

            char r[al];
            memset(r, 0, al);
            
            b64_decode(input, r, l);
            fwrite(r, al, 1, stdout);
            printf("\n");
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
