#include <stdio.h>
#include <stdlib.h>
#include "chacha20.h"
#include "flag1.h"
#include "flag2.h"

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

void die(const char *s) {
    perror(s);
    exit(1);
}

uint32_t k[4] = {325623995, 420138526, 903390039, 650062945};

int main(int argc, char *argv[])
{
    char input[0x100];
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    printf("Input the flag: ");
    gets(input); // vul

    if (strlen(input) != flag1_enc_len + flag2_enc_len)
        goto fail;

    char *second_part = strdup(input+flag1_enc_len);

    struct chacha20_context ctx;
    chacha20_init_context(&ctx, "tzgkwukglbslrmfjsrwimtwyyrkejqzo", "oaeqjfhclrqk", 128);
    chacha20_xor(&ctx, input, flag1_enc_len);

    if (!memcmp(input, flag1_enc, flag1_enc_len)) {
        size_t len = strlen(second_part);
        for (int i = 0; i < len/8; ++i) {
            encrypt(second_part+i*8, k);
            if (memcmp(second_part+i*8, flag2_enc+i*8, 8)) {
                goto fail;
            }
        }
        puts("You are right :D");
        return 0;
    }
fail:
    puts("You are wrong ._.");
    return 1;
}
