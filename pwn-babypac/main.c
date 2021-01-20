// clang -s -I/usr/aarch64-linux-gnu/include --target=aarch64-linux-gnu -march=armv8.3a -mbranch-protection=pac-ret -z now -o chall main.c 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

struct block
{
    size_t num;
    size_t locked;
};

struct w
{
    char name[0x20];
    struct block pool[5];
} W;

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void menu()
{
    puts("");
    puts("=== BabyPAC ===");
    puts("1. add");
    puts("2. lock");
    puts("3. show");
    puts("4. auth");
    puts("5. exit");
    printf(">> ");
}

uint64_t read_num()
{
    char buf[0x20];

    fgets(buf, 0x20, stdin);
    return atoi(buf);
}

size_t encrypt_func(size_t x)
{
    x ^= x << 7;
    x ^= x >> 11;
    x ^= x << 31;
    x ^= x >> 13;

    return x;
}

void add()
{
    size_t i;
    size_t x = 0;

    for (i = 0; i < 5 && W.pool[i].num != 0; i++)
        ;
    if (i == 5)
        return;

    printf("identity: ");
    x = read_num();

    W.pool[i].num = x;
    W.pool[i].locked = 0;
}

void lock()
{
    int idx;
    printf("idx: ");
    idx = read_num();

    if (idx >= 5)
        return;

    if (W.pool[idx].num != 0 && W.pool[idx].locked == 0)
    {
        size_t x = W.pool[idx].num;
        __asm__ __volatile__("pacia %0, sp"
                             : "=r"(x)
                             : "0"(x));
        x = encrypt_func(x);

        W.pool[idx].num = x;
        W.pool[idx].locked = 1;
    }
}

void win()
{
    char buf[0x20];
    read(0, buf, 0x100);
}

void show()
{
    printf("name: %s\n", W.name);
    for (int i = 0; i < 5; i++)
    {
        if (W.pool[i].num == 0)
            continue;
        if (W.pool[i].locked == 1)
        {
            printf("%d: **censored**\n", i);
        }
        else
        {
            printf("%d: %ld\n", i, W.pool[i].num);
        }
    }
}

void auth()
{
    int idx;
    printf("idx: ");
    idx = read_num();

    if (idx >= 5)
        return;

    if (W.pool[idx].num != 0 && W.pool[idx].locked == 1)
    {
        size_t tmp = 1145141919810;
        __asm__ __volatile__("pacia %0, sp"
                             : "=r"(tmp)
                             : "0"(tmp));

        if (W.pool[idx].num == encrypt_func(tmp))
        {
            win();
        }
    }
}

void title()
{
    puts("");
    puts(" #   #    ####    #####  ######");
    puts("  # #    #    #     #    #");
    puts("### ###  #          #    #####");
    puts("  # #    #          #    #");
    puts(" #   #   #    #     #    #");
    puts("          ####      #    #");
    puts("");
}

void babypac()
{
    int choice;

    title();

    printf("input your name: ");
    read(0, W.name, 0x20);

    while (1)
    {
        menu();
        choice = read_num();
        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            lock();
            break;
        case 3:
            show();
            break;
        case 4:
            auth();
            break;
        case 5:
            puts("Goodbye~");
            exit(0);
        default:
            continue;
        }
    }
}

int main()
{
    init();
    babypac();

    return 0;
}
