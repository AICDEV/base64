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

void b64_decode(char *t);
void b64_encode(char *t, char *r);

static const char b64_table[65] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'};


void b64_decode(char *t)
{   
    int c = 2;
    for (int i = 0; i < strlen(t);)
    {
        int blocks = 0x0;
        blocks |= (t[i] == 61) ? 0 : (t[i] >= 48 && t[i] <= 57) ? ((t[i] % 64) + 4) :  (t[i] > 90) ? ((t[i] % 64) - 7) : ((t[i] % 64) - 1);
        i++;

        blocks <<= 6;
        blocks |=  (t[i] == 61) ? 0 : (t[i] >= 48 && t[i] <= 57) ? ((t[i] % 64) + 4) :  (t[i] > 90) ? ((t[i] % 64) - 7) : ((t[i] % 64) - 1);
        i++;

        blocks <<= 6;
        blocks |=  (t[i] == 61) ? 0 : (t[i] >= 48 && t[i] <= 57) ? ((t[i] % 64) + 4) :  (t[i] > 90) ? ((t[i] % 64) - 7) : ((t[i] % 64) - 1);
        i++;

        blocks <<= 6;
        blocks |=  (t[i] == 61) ? 0 : (t[i] >= 48 && t[i] <= 57) ? ((t[i] % 64) + 4) :  (t[i] > 90) ? ((t[i] % 64) - 7) : ((t[i] % 64) - 1);
        i++;

        while(c >= 0) {
            if((blocks >> (c * 8) & 0xFF) > 0) {
                printf("%c", blocks >> (c * 8) & 0xFF);
            }
            c--;
        }

        c = 2;
    }
}


void b64_encode(char *t, char *r)
{

    int l = strlen(t);
    int base = 0;
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
                strncat(r, &b64_table[blocks >> (a * 6) & 0x3F], 1);
                a--;
            }

            while (offset > 0)
            {
                strcat(r, "=");
                offset--;
            }
        }

        else
        {
            int c = 3;
            while (c >= 0)
            {
                strncat(r, &b64_table[blocks >> (c * 6) & 0x3F], 1);
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
        char *r = malloc(4 * ((strlen(input) + 2) / 3));

        b64_encode(input, r);
        printf("%s \n", r);

        return EXIT_SUCCESS;
    }

    if (argc == 3)
    {
        if (!strcmp(argv[1], "-d"))
        {
            char *input = argv[2];
            b64_decode(input);
            printf("\n");
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
