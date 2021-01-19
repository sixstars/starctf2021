#include "Viewer.h"
#include "Enums.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#define PRT(A) std::cout<<(A)<<std::endl;

static inline bool isDirection(char ch){
    return (ch == 'w')||(ch == 's')||(ch == 'a')||(ch == 'd');
}

static inline bool isBuildInCmd(char ch){
    return (ch == 'h')||(ch == 'b')||(ch == 'q')||(ch == 'r')||(ch == 'l') || (ch == 'm') || (ch =='y') || (ch == 'n' || (ch == 'k'));
}

static inline bool isNumber(char ch){
    return (ch >= '1')&&(ch <= '9');
}

static inline bool isAcceptInput(char ch){
    return isDirection(ch)||isBuildInCmd(ch)||isNumber(ch);
}

char Viewer::getInput(){
    using namespace std;
    char ret;
    bool accept = false;
    std::string input;
    while (!accept)
    {
        PRT("Please input an order:");
        getline(cin,input);
        if(input.size() == 1){
            ret = input.at(0);
        }
        else{
            accept = false;
            PRT("Wrong input, type 'h' for help");
            continue;
        }
        accept = isAcceptInput(ret);
        if(!accept){
            PRT("Wrong input, type 'h' for help");
        }
    }
    return ret;
}

char Viewer::getLevel(){
    using namespace std;
    char ret;
    bool accept = false;
    string input;
    while (!accept)
    {
        PRT("Please input an level from 1-9:");
        getline(cin, input);
        if(input.length() == 1){
            ret = input[0];
        }
        else{
            accept = false;
            PRT("Wrong input, type 'h' for help");
            continue;
        }
        accept = isAcceptInput(ret);
        if(!accept){
            PRT("Wrong input, type 'h' for help");
        }
    }
    return ret;
}

void Viewer::displayMap(const Map& map,int level){
    using namespace std;
    int w = map.getWidth();
    int h = map.getHeight();
    string showString;
    PRT("Map:");
    /* convert state to symbols */
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            Position p(j,i);
            showString += SYMBOLS[map.getStateOf(p)];
        }
        showString += '\n';
    }
    PRT(showString);
}

void  Viewer::display(const std::string& s){
    PRT(s);
}

void Viewer::win(){
    PRT("Congratulation!!!");
}

void Viewer::init(){

}

void Viewer::finish(){
    
}

void Viewer::help(){
    static std::string s;
    s = "     Sokoban    \n"\
        "How to Play:\n    Push all boxs into target place\n"\
        "Map:\n"\
        "    1)"+SYMBOLS[State::WALL]+":wall\n"\
        "    2)"+SYMBOLS[State::TARGET]+":Target\n"\
        "    3)"+SYMBOLS[State::BOX]+":Box\n"\
        "    4)"+SYMBOLS[State::PLAYER]+":Player\n"\
        "    5)"+SYMBOLS[State::BOX_ON_TARGET]+":Box on target\n"\
        "Command:\n"\
        "    1)h: show this message\n"\
        "    2)q: quit the game\n"\
        "    3)w: move up\n"\
        "    4)s: move down\n"\
        "    5)a: move left\n"\
        "    6)d: move right\n"\
        "    7)b: move back\n"\
        "    8)m: leave message\n"\
        "    k)n: show name\n"\
        "    10)l: show message\n";
    PRT(s);
}
