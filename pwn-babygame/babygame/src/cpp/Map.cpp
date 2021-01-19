#include "Map.h"
#include <iostream>

static TileType::TileType stateToType(State::State s);
static TileFlag::TileFlag stateToFlag(State::State s);
static void printState(State::State s);
static Box& getBox(const Position& p, std::vector<Box>& boxs);

Map::Map(int w, int h)
    :width(w),height(h),player(Position::of(-100,-100))
    ,OUT_SIDE_TILE(TileType::FLOOR_OUT_SIDE){
    /* tiles is a map */
}

Map::~Map(){
    /* clear all vector */
    boxs.clear();
    tileMap.clear();
}

int Map::getWidth() const{
    return width;
}

int Map::getHeight() const{
    return height;
}

void Map::initMap(std::string str){
    char ch;
    State::State state;
    boxs.clear();
    player.clear();

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            /* coordinate (x,y)  */
            Position pos(j,i);
            Box box(pos);
            ch = str.at(i * width + j);
            /* read character as state */
            state = (State::State)(ch - '0');
            Tile tile(stateToType(state));
            /* handle special tile which owns player grid or box grid */
            switch (state)
            {
            case State::PLAYER:
                player.setPosition(pos);
                tile.setFlag(TileFlag::PLAYER);
                break;
            case State::BOX:
            case State::BOX_ON_TARGET:
                boxs.push_back(box);
                tile.setFlag(TileFlag::BOX);
                /* code */
                break;
            default:
                break;
            }
            /* initialize tiles map */
            tile.setPosition(j,i);
            tileMap[pos] = tile;
        }
    }
}

State::State Map::getStateOf(const Position& pos) const{
    std::map<Position,Tile>::const_iterator iter;
    /* find position in map */
    iter = tileMap.find(pos);
    /* if not found */
    if(iter == tileMap.end()){
        return State::FLOOR_OUT_SIDE;
    }
    else {
        return iter->second.getState();
    }
}

std::string Map::to_string() const{
    std::string ret;
    std::map<Position,Tile>::const_iterator iter;
    // std::cout<<tileMap.size()<<std::endl;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            /* coordinate (x,y)  */
            Position pos(j,i);
            /* find position in map */
            iter = tileMap.find(pos);
            int state = iter->second.getState();
            ret += std::to_string(state);
        }
        ret.append("\n");
    }
    return ret;
}

void Map::move(Direction::Direction dir){
    /* make sure dir is a right direction
     * if not then error occur
     * we will check that in rule part */

    Position shadow = player.getPosition();
    /* shadow move to check the position */
    shadow += DIRS[dir];
    Tile& situ = getTile(player.getPosition());
    Tile& tile = getTile(shadow);
    switch (tile.getState())
    {
    case State::FLOOR:
    case State::TARGET:
        situ.setFlag(TileFlag::NONE);
        tile.setFlag(TileFlag::PLAYER);
        player.move(dir,false);
        break;
    case State::FLOOR_OUT_SIDE:
    case State::WALL:
        /* move into wrong place */
        break;
    case State::BOX:
    case State::BOX_ON_TARGET:
        moveBox(tile,dir);
        player.move(dir,true);
        situ.setFlag(TileFlag::NONE);
        tile.setFlag(TileFlag::PLAYER);
        break;
    
    default:
        break;
    }
}

void Map::back(){
    /* back to previous position */
    /* get previous direction */
    Direction::Direction dir = player.getPreviousDirection();
    bool flag = player.getPreviousPushFlag();
    /* shadow to try previous position */
    Position shadow = player.getPosition();

    /* set current player position */
    Tile& trial = getTile(player.getPosition());
    trial.setFlag(TileFlag::NONE);
    player.back(dir);

    /* set new player position */
    Tile& trial1 = getTile(player.getPosition());
    trial1.setFlag(TileFlag::PLAYER);

    /* check whether need pull box? */
    shadow += DIRS[dir];
    Tile& trial2 = getTile(shadow);
    State::State s = trial2.getState();
    if(flag && (s == State::BOX || s == State::BOX_ON_TARGET)){
        /* process of pull box */
        Box& b = getBox(shadow,boxs);
        trial2.setFlag(TileFlag::NONE);
        b.back(dir);
        Tile& trial3 = getTile(b.getPosition());
        trial3.setFlag(TileFlag::BOX);
        b.moveToTile(trial3.getType());
    }
}

const std::vector<Box>& Map::getBoxs() const{
    return boxs;
}

Tile& Map::getTile(const Position& p){
    std::map<Position,Tile>::iterator iter;
    /* find position in map */
    iter = tileMap.find(p);
    /* if not found */
    if(iter == tileMap.end()){
        return OUT_SIDE_TILE;
    }
    else {
        return iter->second;
    }
}

void Map::moveBox(Tile& situ, Direction::Direction dir){
    Position shadow = situ.getPosition();
    shadow += DIRS[dir];
    Tile& next = getTile(shadow);
    /* check whether next position can place */
    switch (next.getState())
    {
    case State::FLOOR_OUT_SIDE:
    case State::WALL:
    case State::BOX:
    case State::BOX_ON_TARGET:
        return;
    default:
        break;
    }
    /* process of move box */
    Box& b = getBox(situ.getPosition(),boxs);
    b.move(dir);
    b.moveToTile(next.getType());
    situ.setFlag(TileFlag::NONE);
    next.setFlag(TileFlag::BOX);
}

const Position& Map::getPlayerPosition() const{
    return player.getPosition();
}

static Box& getBox(const Position& p, std::vector<Box>& boxs){
    /* make sure the position must have a box or an error will occur */
    std::vector<Box>::iterator iter;
    for(iter = boxs.begin();iter != boxs.end(); iter++){
        if(iter->getPosition() == p){
            return *iter;
        }
    }
    /* if not found, throw a error */
    std::string e("Box not found");
    throw e;
}

static TileType::TileType stateToType(State::State s){
    switch (s)
    {
    case State::FLOOR:
        return TileType::FLOOR;
    case State::FLOOR_OUT_SIDE:
        return TileType::FLOOR_OUT_SIDE;
    case State::WALL:
        return TileType::WALL;
    case State::BOX:
        return TileType::FLOOR;
    case State::TARGET:
        return TileType::TARGET;
    case State::PLAYER:
        return TileType::FLOOR;
    case State::BOX_ON_TARGET:
        return TileType::TARGET;
    
    default:
        return TileType::FLOOR;
    }
}

static TileFlag::TileFlag stateToFlag(State::State s){
    switch (s)
    {
    case State::FLOOR:
        return TileFlag::NONE;
    case State::FLOOR_OUT_SIDE:
        return TileFlag::NONE;
    case State::WALL:
        return TileFlag::NONE;
    case State::BOX:
        return TileFlag::BOX;
    case State::TARGET:
        return TileFlag::NONE;
    case State::PLAYER:
        return TileFlag::PLAYER;
    case State::BOX_ON_TARGET:
        return TileFlag::BOX;
    
    default:
        return TileFlag::NONE;
    }
}

static void printState(State::State s){
    switch (s)
    {
    case State::FLOOR:
        std::cout<<"FLOOR"<<std::endl;
        break;
    case State::FLOOR_OUT_SIDE:
        std::cout<<"FLOOR_OUT_SIDE"<<std::endl;
        break;
    case State::WALL:
        std::cout<<"WALL"<<std::endl;
        break;
    case State::BOX:
        std::cout<<"BOX"<<std::endl;
        break;
    case State::TARGET:
        std::cout<<"TARGET"<<std::endl;
        break;
    case State::PLAYER:
        std::cout<<"PLAYER"<<std::endl;
        break;
    case State::BOX_ON_TARGET:
        std::cout<<"BOX_ON_TARGET"<<std::endl;
        break;
    
    default:
        std::cout<<"default"<<std::endl;
        break;
    }
}
