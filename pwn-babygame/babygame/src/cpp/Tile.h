#ifndef TILE_H
#define TILE_H
#include "Enums.h"
#include "Position.h"

class Tile{
    Position pos;
    /* static tile type */
    TileType::TileType type;
    /* dynamic tile flag */
    TileFlag::TileFlag flag;
public:
    Tile(TileType::TileType t = TileType::FLOOR);

    Tile(const Tile& tile);

    ~Tile();

    void setPosition(int x, int y);

    void setFlag(TileFlag::TileFlag f);

    State::State getState() const;

    TileType::TileType getType() const;

    const Position& getPosition() const;

    Tile& operator=(const Tile& t);
};

/*
 * explain about type and flag
 * 
 * 1. the map based on tile type
 * tile type cannot change after set
 * 
 *  WWWW
 *  W  W
 *  W  W
 *  WWWW
 * 
 * 2. then put flag on tile
 * flag can change when move
 *  NNNN
 *  NPNN
 *  NNBN
 *  NNNN
 * 
 * 3. merge type and flag, get state map
 *  WWWW
 *  WP W
 *  W BW
 *  WWWW
 * 
 *  */

#endif //TILE_H
