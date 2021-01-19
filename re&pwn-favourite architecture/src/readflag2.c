#include <stdio.h>
#include <stdlib.h>
char buf[1024] = {};
int main(int argc, char *argv[])
{
    FILE *fp = fopen("/flag2", "r");
    if (!fp) {
        perror("fopen");
        exit(-1);
    }
    fgets(buf, 1024, fp);
    printf("%s", buf);
    return 0;
}
