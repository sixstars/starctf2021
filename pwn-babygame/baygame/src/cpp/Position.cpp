#include "Position.h"
Position::Position():x(0),y(0){}

Position::Position(int i,int j):x(i),y(j){}

Position::Position(const Position& pos){
    x = pos.x;
    y = pos.y;
}

Position::~Position(){
    /* destructor */
}

Position& Position::operator=(const Position& pos){
    x = pos.x;
    y = pos.y;
    return *this;
}

Position& Position::operator+=(const Position& pos){
    x += pos.x;
    y += pos.y;
    return *this;
}

bool Position::operator==(const Position& pos) const{
    return (x == pos.x)&&(y == pos.y);
}

bool Position::operator<(const Position& pos) const{
    /* compare x first */
    if(x < pos.x){
        return true;
    }
    /* then compare y */
    else if(x == pos.x){
        if(y < pos.y){
            return true;
        }
    }
    return false;
}

int Position::getX() const{
    return x;
}

int Position::getY() const{
    return y;
}

void Position::setX(int xx){
    x = xx;
}

void Position::setY(int yy){
    y = yy;
}

const Position Position::of(int x,int y){
    return Position(x,y);
}

Position DIRS[] = {
    Position(0,-1),
    Position(0,1),
    Position(-1,0),
    Position(1,0),
    Position(0,0)
};

const Position OUT_OF_RANGE = Position(-1,-1);
