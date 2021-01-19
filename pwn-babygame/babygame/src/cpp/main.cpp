#include "Game.h"
#include "Viewer.h"
#include <iostream>
#include <unistd.h>
void initial(){
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    alarm(0xff);
}
using namespace std;
int begin(){
    Game game;
    /* exception may occur */
    try{
        game.start();
    }catch(std::string e){
        std::cout<<e<<std::endl;
    }
}

int main(){
    bool flag = true;
    while (flag){
        begin();

        cout << "restart?" << endl;
        char order;
        order = Viewer::getInput();
        if (order!= 'y'){
                flag = false;
        }
    }
}
