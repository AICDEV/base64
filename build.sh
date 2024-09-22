#!/usr/bin/bash
gcc base.c ./lib/b64.c -Wno-initializer-overrides -Wall -O3 -std=c99 -o base