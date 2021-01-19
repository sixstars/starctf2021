#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "chacha20.h"

int main(int argc, char *argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    char buf[0x100];

    strcpy(buf, argv[1]);
    size_t len = strlen(buf);

    struct chacha20_context ctx;
    chacha20_init_context(&ctx, "tzgkwukglbslrmfjsrwimtwyyrkejqzo", "oaeqjfhclrqk", 128);
    chacha20_xor(&ctx, buf, len);
    write(1, buf, len);
}
