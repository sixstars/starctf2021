#include "Viewer.h"
#include "Enums.h"
#include <iostream>
#include <cstdlib>

#define PRT(A) std::cout<<(A)<<std::endl;

static const int BLOCK_WIDTH = 1;
static const int BLOCK_HEIGHT = 1;

static inline bool isDirection(char ch){
    return (ch == 'w')||(ch == 's')||(ch == 'a')||(ch == 'd');
}

static inline bool isBuildInCmd(char ch){
    return (ch == 'h')||(ch == 'b')||(ch == 'q')||(ch == 'r');
}

static inline bool isAcceptInput(char ch){
    return isDirection(ch)||isBuildInCmd(ch);
}

static inline bool isNumber(char ch){
    return (ch >= '0')&&(ch <= '9');
}

static inline const std::string& getLog(){
    static std::string log = ""\
    "           _         _                 \n"\
    " ___  ___ | | _____ | |__   __ _ _ __  \n"\
    "/ __|/ _ \\| |/ / _ \\| '_ \\ / _` | '_ \\ \n"\
    "\\__ \\ (_) |   < (_) | |_) | (_| | | | |\n"\
    "|___/\\___/|_|\\_\\___/|_.__/ \\__,_|_| |_|\n";
    return log;
}

/* 
 * \033[s 保存光标位置
 * \033[u 恢复光标位置
 * \033[?25l 隐藏光标
 * \033[?25h 显示光标
 * \033[?1049h 保存屏幕
 * \033[?1049l 恢复屏幕
 * \033[H 清除屏幕，
 * \033[2J 光标移到左上角
 */

static inline void hide(){
    PRT("\033[s");
    PRT("\033[?1049h");
    PRT("\033[H");
    PRT("\033[?25l");
    PRT("\033[2J");
    system("stty -echo");
}

static inline void recover(){
    system("stty echo");
    PRT("\033[H");
    PRT("\033[?1049l");
    PRT("\033[u");
}

static inline void clearScreen(){
    PRT("\033[H");
    PRT("\033[2J");
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
    std::string input;
    while (!accept)
    {
        PRT("Please input an level from 1-9:");
        getline(cin,input);
        if(input.size() == 1){
            ret = input.at(0);
        }
        else{
            accept = false;
            PRT("Wrong input, type 'h' for help");
            continue;
        }
        accept = isNumber(ret);
        if(!accept){
            PRT("Wrong input, type 'h' for help");
        }
    }
    return ret;
}

void Viewer::displayMap(const Map& map,int level){
    using namespace std;
    clearScreen();
    int w = map.getWidth();
    int h = map.getHeight();
    string showString;
    // "+---------------+\n"
    // "|    level 5    |\n"
    // "+---------------+\n"
    string levelStr = "+---------------+\n|    level " + to_string(level);
    levelStr += "    |\n+---------------+\n";
    PRT(levelStr);
    // PRT("Map:");
    /* convert state to symbols */
    for(int i = 0; i < h*BLOCK_HEIGHT; i++){
        for(int j = 0; j < w*BLOCK_WIDTH; j++){
            Position p(j/BLOCK_WIDTH,i/BLOCK_HEIGHT);
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
    hide();
}

void Viewer::finish(){
    recover();
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
        "    7)r: restart the session\n"\
        "    8)b: move back\n";
    PRT(s);
}
