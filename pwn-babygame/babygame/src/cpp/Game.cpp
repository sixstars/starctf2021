#include "Game.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#define PRT(A) std::cout<<(A)<<std::endl
using namespace std;

vector<string> Game::myName;

static inline Direction::Direction inputToDirection(char ch){
    switch (ch)
    {
    case 'w':
        return Direction::UP;
    case 's':
        return Direction::DOWN;
    case 'a':
        return Direction::LEFT;
    case 'd':
        return Direction::RIGHT;
    default:
        return Direction::SITU;
    }
}

static inline bool isDirection(char ch){
    return (ch == 'w')||(ch == 's')||(ch == 'a')||(ch == 'd');
}

static inline bool isBuildInCmd(char ch){
    return (ch == 'l')||(ch == 'h')||(ch == 'b')||(ch == 'q')||(ch == 'r') || (ch == 'm');
}

static inline bool isNumber(char ch){
    return (ch >= '1')&&(ch <= '9');
}

Game::Game(int level/* = 0 */):curLevel(level),isFinish(false),MAX_LEVEL(9),isQuit(false){
    message = new char[0x500];
    /* constructor */
    // PRT("call constructor");
    // message = new char[0x500];
}


Game::~Game(){

    cout << "leave your name?" <<endl;
    char order = Viewer::getInput();
    if (order == 'y' ){
        cout << "your name:" <<endl;
        string temp;
        getline(cin, temp);
        myName.push_back(temp);
    }
    sessions.clear();
    delete message;
    /* destructor */
}

void Game::start(){
    // PRT("call start");
    Viewer::init();
    isFinish = true;
    curLevel =  -1;
    while(!isQuit){
        // Viewer::display("Level "+std::to_string(curLevel));
        /* get input level */
        while(!((curLevel != -1)||isQuit)){
            char ch = Viewer::getLevel();
            handleStartCmd(ch);
        }
        if(isQuit){
            break;
        }
        /* session part */
        initSession();
        startSession();
        endSession();
    }
    // Viewer::display("total time:"+std::to_string(duration)+" seconds");
    Viewer::finish();
}

void Game::initSession(){
    // PRT("call init session");
    using namespace MapRepository;
    MAP_ID id = MAP_ID(curLevel);
    MapBuffer buffer = getMap(id);
    // PRT("get map buffer over");
    curSession = new Session(buffer.getWidth(),buffer.getHeight(),curLevel,buffer.getBuffer());
    isFinish = false;
}

void Game::startSession(){
    // PRT("call start session");
    begin = std::clock();
    Viewer::displayMap(curSession->getMap(),curSession->getLevel());
    while (!curSession->isFinished())
    {
        char input = Viewer::getInput();
        if(isDirection(input)){
            Direction::Direction dir = inputToDirection(input);
            curSession->move(dir);
            Viewer::displayMap(curSession->getMap(),curSession->getLevel());
        }
        else{
            handleCmd(input);
        }
    }

    /* normal finish(not choose level or quit) */
    if(!isFinish){
        Viewer::win();
        curLevel = -1;
    }

    end = std::clock();
    /* compute total time(seconds) */
    duration += (double)(end - begin)/CLOCKS_PER_SEC;
}

void Game::endSession(){    
    sessions.push_back(*curSession);
    // curSession = nullptr;
    /* finish flag */
    isFinish = true;
}

bool Game::isFinished() const{
    return isFinish;
}

double Game::getDuration() const{
    return duration;
}

void Game::handleCmd(char ch){
    if(isNumber(ch)){
        curLevel = ch - '0' - 1;
        curSession->finish();
        isFinish = true;
        return;
    }
    switch(ch){
        case 'h':
            Viewer::help();
            break;
        case 'q':
            isQuit = true;
            isFinish = true;
            curSession->finish();
            break;
        case 'm':
            cout << "message:" <<endl;
            read(0, message, 0x10);
            break;
        case 'b':
            curSession->backToPreviousPlace();
            Viewer::displayMap(curSession->getMap(),curSession->getLevel());
            break;
        default:
            Viewer::display("Wrong input, type 'h' for help");
            break;
    }
}

void Game::handleStartCmd(char ch){
    if(isNumber(ch)){
        curLevel = ch - '0' - 1;
        isFinish = true;
    }
    else if(ch == 'q'){
        isQuit = true;
        isFinish = true;
    }
    else if(ch == 'h'){
        Viewer::help();
    }else if(ch == 'l'){
            printf("message:%s\n",this->message);
    }
    else{
        Viewer::display("Wrong input, try again");
    }
}
