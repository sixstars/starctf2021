#ifndef MOVABLE_H
#define MOVABLE_H
#include "Position.h"
#include "Enums.h"
#include <iostream>
#include <vector>

class Moveable{
    Position pos;
public:
    Moveable(const Position& position):pos(position){
        /* default constructor */
    }

    virtual void move(Direction::Direction dir){
        pos += DIRS[dir];
    }

    const Position& getPosition() const{
        return pos;
    }

    void setPosition(const Position& p){
        pos = p;
    }

    void back(Direction::Direction dir){
        dir = reverse(dir);
        move(dir);
    }

    static inline Direction::Direction reverse(Direction::Direction dir){
        switch (dir)
        {
            case Direction::UP:
                return Direction::DOWN;
            case Direction::DOWN:
                return Direction::UP;
            case Direction::LEFT:
                return Direction::RIGHT;
            case Direction::RIGHT:
                return Direction::LEFT;
    
            default:
                return Direction::SITU;
        }
    }
};

class Player:public Moveable{
    std::vector<Direction::Direction> record;
    std::vector<bool> pushFlag;
public:
    Player():Moveable(Position::of(0,0)){
        /* default constructor */
    }

    Player(const Position& position):Moveable(position){
        /* default constructor */
    }

    void move(Direction::Direction dir, bool pushOrNot){
        /* record move direction */
        record.push_back(dir);
        pushFlag.push_back(pushOrNot);
        /* call move method of parent */
        Moveable::move(dir);
    }

    Direction::Direction getPreviousDirection(){
        int size = record.size();
        if(size == 0){
            return Direction::SITU;
        }
        Direction::Direction dir = record[size-1];
        record.pop_back();
        return dir;
    }

    bool getPreviousPushFlag(){
        int size = pushFlag.size();
        if(size == 0){
            return false;
        }
        bool flag = pushFlag[size-1];
        pushFlag.pop_back();
        return flag;
    }

    void clear(){
        /* use to restart */
        record.clear();
        pushFlag.clear();
    }
};

class Box:public Moveable{
    bool onTarget;
public:
    Box(const Position& position):Moveable(position),onTarget(false){
        /* default constructor */
    }

    void moveToTile(TileType::TileType type){
        /* change ontarget state */
        onTarget = (type == TileType::TARGET);
    }

    bool getOnTarget() const{
        return onTarget;
    }

};

#endif //MOVABLE_H
