#ifndef MAP_H
#define MAP_H
#include "Moveable.h"
#include "Tile.h"
#include <string>
#include <map>

class Map{
    const int width,height;
    Player player;
    std::vector<Box> boxs;
    std::map<Position,Tile> tileMap;
    /* a tile to stand for tile that not exist */
    Tile OUT_SIDE_TILE;

    Tile& getTile(const Position& p);
    void moveBox(Tile& situ, Direction::Direction dir);
public:
    Map(int w, int h);

    ~Map();

    int getWidth() const;

    int getHeight() const;

    void initMap(std::string str);

    State::State getStateOf(const Position& pos) const;

    std::string to_string() const;

    void move(Direction::Direction dir);

    const std::vector<Box>& getBoxs() const;

    const Position& getPlayerPosition() const;

    void back();
};


#endif //MAP_H
