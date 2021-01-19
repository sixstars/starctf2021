#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
void encrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i < 16; i++) {                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void hexdump(unsigned char* buf, size_t size) {
    int i,j;
    for (i = 0; i < size; i += 16)
    {
        printf("%08x:", i);
        for (j = i;j < size && j < i + 16;j++)
        {
            printf(" %02x", buf[j]);
        }
        printf("  ");
        for (j = i;j < size && j < i + 16;j++)
        {
            if (buf[j] >= 0x20 && buf[j] < 0x7f) {
                printf("%c", buf[j]);
            } else {
                printf(".");
            }
        }
        puts("");
    }
}
uint32_t k[4] = {325623995, 420138526, 903390039, 650062945};
int main(int argc, char *argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    char buf[0x100];
    strcpy(buf, argv[1]);
    size_t len = strlen(buf);
    if (strlen(buf) & 7) return 1;
    for (int i = 0; i < len/8; ++i) {
        encrypt(buf+i*8, k);
    }
    write(1, buf, len);
}
