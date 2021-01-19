#ifndef ENUMS_H
#define ENUMS_H

namespace State{
    enum State{
        FLOOR_OUT_SIDE=0,
        WALL=1,
        FLOOR=2,
        BOX=3,
        TARGET=4,
        PLAYER=5,
        BOX_ON_TARGET=6
    };
}

namespace TileType{
    enum TileType{
        WALL,FLOOR,TARGET,FLOOR_OUT_SIDE
    };
}

namespace TileFlag{
    enum TileFlag{
        NONE,PLAYER,BOX
    };
}

namespace Direction{
    enum Direction{
        UP=0,DOWN=1,LEFT=2,RIGHT=3,SITU=4
    };
}

#endif//ENUMS_H
