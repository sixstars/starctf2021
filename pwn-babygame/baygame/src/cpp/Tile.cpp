#include "Tile.h"
#include <iostream>

Tile::Tile(TileType::TileType t/* = FLOOR */):type(t),flag(TileFlag::NONE){
    // std::cout<<"call Tile(TileType t)"<<std::endl;
}

Tile::Tile(const Tile& tile):pos(tile.pos),type(tile.type),flag(tile.flag){
    // std::cout<<"call Tile(const Tile& t)"<<std::endl;
}

Tile::~Tile(){
    /* destructor */
}

void Tile::setPosition(int x, int y){
    pos.setX(x);
    pos.setY(y);
}

void Tile::setFlag(TileFlag::TileFlag f){
    flag = f;
}

TileType::TileType Tile::getType() const{
    return type;
}

State::State Tile::getState() const{
    /* if flag is NONE, just the type */
    if(flag == TileFlag::NONE){
        switch (type)
        {
        case TileType::WALL:
            return State::WALL;
        case TileType::FLOOR:
            return State::FLOOR;
        case TileType::TARGET:
            return State::TARGET;
        case TileType::FLOOR_OUT_SIDE:
            return State::FLOOR_OUT_SIDE;
        default:
            return State::FLOOR;
        }
    }
    /* if flag is BOX, may BOX or BOX_ON_TARGET */
    else if(flag == TileFlag::BOX){
        if(type == TileType::TARGET){
            return State::BOX_ON_TARGET;
        }
        else{
            return State::BOX;
        }
    }
    /* if flag is PLAYER, PLAYER first */
    else if(flag == TileFlag::PLAYER){
        return State::PLAYER;
    }
    /* default FLOOR */
    return State::FLOOR;
}

const Position& Tile::getPosition() const{
    return pos;
}

Tile& Tile::operator=(const Tile& t){
    type = t.type;
    flag = t.flag;
    pos = t.pos;
    // std::cout<<"call operator="<<std::endl;
}
