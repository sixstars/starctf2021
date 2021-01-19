#ifndef SESSION_H
#define SESSION_H

#include "map.h"

namespace RULE{
    /* check win or not */
    bool isWin(const Map& m);

    /* check next move is valid */
    bool isRightMove(const Map& m, Direction::Direction dir);
}

class Session{
    const int level;
    int step;
    bool isFinish;
    Map map;
    std::string mapBuffer;
    char* information;
    
public:
    Session(int width,int height,int l,const std::string& s);
    char* message;
    ~Session();

    void move(Direction::Direction dir);

    const Map& getMap() const;

    void finish();

    bool isFinished() const;

    /* back feature */
    void backToPreviousPlace();

    /* restart game */
    void restart();

    int getLevel() const;
};

#endif //SESSION_H
