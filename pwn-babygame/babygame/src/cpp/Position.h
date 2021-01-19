#ifndef POSITION_H
#define POSITION_H

class Position{
    int x,y;
public:
    Position();

    Position(int,int);

    Position(const Position&);

    ~Position();

    Position& operator=(const Position&);

    Position& operator+=(const Position&);

    bool operator==(const Position&) const;

    bool operator<(const Position&) const;

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    static const Position of(int x,int y);
};

/*
 * map:
 *     (0,0)   (1,0)
 *      +------+
 *      |      |
 *      |      |
 *      +------+
 *     (0,1)   (1,1)
 * 
 */

/* UP,DOWN,LEFT,RIGHT,SITU */
extern Position DIRS[];

/* Wrong flag */
extern const Position OUT_OF_RANGE;

#endif//POSITION_H
