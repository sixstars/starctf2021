#include "Session.h"
#include <iostream>

static inline bool isWrongPlace(State::State s){
    return (s == State::FLOOR_OUT_SIDE)||(s == State::WALL);
}

static inline bool isBox(State::State s){
    return (s == State::BOX)||(s == State::BOX_ON_TARGET);
}

static inline bool isFloor(State::State s){
    return (s == State::FLOOR)||(s == State::TARGET);
}

/**********   Rule Part  *************/

bool RULE::isWin(const Map& m){
    const std::vector<Box> boxs = m.getBoxs();
    std::vector<Box>::const_iterator iter;
    for(iter = boxs.cbegin();iter != boxs.cend(); iter++){
        if(!iter->getOnTarget()){
            return false;
        }
    }
}

bool RULE::isRightMove(const Map& m, Direction::Direction dir){
    Position shadow = m.getPlayerPosition();
    shadow += DIRS[dir];
    State::State state = m.getStateOf(shadow);
    if(isFloor(state)){
        return true;
    }
    else if(isWrongPlace(state)){
        return false;
    }
    else if(isBox(state)){
        shadow += DIRS[dir];
        state = m.getStateOf(shadow);
        if(isWrongPlace(state)||isBox(state)){
            return false;
        }
        else if(isFloor(state)){
            return true;
        }
    }
    return false;
}

/**********   Rule Part  *************/

/**********   Session Part  *************/

Session::Session(int width,int height,int l,const std::string& s):map(width,height),level(l){
    step = 0;
    isFinish = false;
    map.initMap(s);
    mapBuffer = s;
    information = new char[0x50];
 
}

Session::~Session(){
    step = 0;
    delete information;
}

void Session::move(Direction::Direction dir){
    /* check is right move */
    bool flag = RULE::isRightMove(map,dir);
    if(!flag||isFinish){
        return;
    }
    /* move in the map */
    map.move(dir);
    step++;

    /* check is winning now */
    flag = RULE::isWin(map);
    if(flag){
        finish();
    }
}

const Map& Session::getMap() const{
    return map;
}

void Session::finish(){
    /* session finish */
    isFinish = true;
}

bool Session::isFinished() const{
    return isFinish;
}

void Session::backToPreviousPlace(){
    map.back();
}

void Session::restart(){
    /* just init map again */
    map.initMap(mapBuffer);
}

int Session::getLevel() const{
    return level;
}

/**********   Session Part  *************/
