# base64
Simple base64 encod and decode in C. Coded and tested on my ubuntu linux machine with following version:
 - gcc version 11.2.0 (Ubuntu 11.2.0-7ubuntu2)
 - ubuntu 21.10 (Impish Indri)

## Compile
```bash
 gcc b64.c -o b64 -Wall -O3 
```

## Encode
```bash
 ./b64 "base64 is sometimes weird to implement but it makes fun"
 YmFzZTY0IGlzIHNvbWV0aW1lcyB3ZWlyZCB0byBpbXBsZW1lbnQgYnV0IGl0IG1ha2VzIGZ1bg== 
```

## Decode
```bash
./b64 -d YmFzZTY0IGlzIHNvbWV0aW1lcyB3ZWlyZCB0byBpbXBsZW1lbnQgYnV0IGl0IG1ha2VzIGZ1bg==
base64 is sometimes weird to implement but it makes fun
```
