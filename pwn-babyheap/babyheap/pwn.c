/*
 * pwn.c
 * Copyright (C) 2020 saltedfish <17302010022@fudan.edu.cn>
 * 
 * Distributed under terms of the MIT license.
 */

/*
 * gcc -fPIE -pie -o pwn ./pwn.c
 *
 */ 
# include <stdio.h>


void* pools[0xf];
int sizes[0xf];
void * name = 0;
void add(){
    puts("input index");
    int idx = readInt();
    if (idx < 0 || idx > 0xf){
        puts("bye!");
        exit(0);
    }
    puts("input size");
    int size = readInt();
    if (size < 0x10 || size > 0x60){
        puts("bye!");
        exit(0);
    }
    pools[idx] = malloc(size);
    sizes[idx] = size;
}
int readInt(){
    char temp[0x10];
    memset(&temp, 0, 0x10);
    read(0, &temp, 0xf);
    return atoi(&temp);
}
void delete(){
    puts("input index");
    int idx = readInt();
    if (idx < 0 || idx > 0xf || !pools[idx]){
        puts("bye!");
        exit(0);
    }
    free(pools[idx]);
}

void edit(){
    puts("input index");
    int idx = readInt();
    if (idx < 0 || idx > 0xf || !pools[idx]){
        puts("bye!");
        exit(0);
    }
    puts("input content");
    read(0, pools[idx] + 8, sizes[idx] - 8);
}

void show(){
    puts("input index");
    int idx = readInt();
    if (idx < 0 || idx > 0xf || !pools[idx]){
        puts("bye!");
        exit(0);
    }
    puts(pools[idx]);
}
void leaveYouName(){
    if (name != 0)
        return;
    name = malloc(0x400);
    puts("your name:");
    read(0, name, 0x100);
}
void showYourName(){
    puts(name);
}
void menu(){
    puts("1. add");
    puts("2. delete");
    puts("3. edit");
    puts("4. show");
    puts("5. leaveYourName");
    puts("6. showYourName");
    puts(">> ");
}


void inittial(){
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    alarm(0xff);
}
int main(){
    inittial();
    puts("welcome");
    while (1){
        menu();
        int choice = readInt();
        switch (choice){
            case 1:add();break;
            case 2:delete();break;
            case 3:edit();break;
            case 4:show();break;
            case 5:leaveYouName();break;
            case 6:showYourName();break;       
            default:exit(0);
        }
    }
}
