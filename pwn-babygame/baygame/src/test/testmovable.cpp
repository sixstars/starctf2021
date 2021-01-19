#include <iostream>
#include "../cpp/Movable.h"

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;

int main(){
    PRT("1)test movable:");
    Position p;
    Movable m(p);
    m.move(Direction::RIGHT);
    m.move(Direction::DOWN);
    Position tar(1,1);
    ASSERT(m.getPosition(),tar);

    PRT("2)test player:");
    Player player(p);
    player.move(Direction::RIGHT);
    player.move(Direction::DOWN);
    ASSERT(player.getPosition(),tar);
    vector<Direction::Direction> rec = player.getRecord();
    PRT("Print record:");
    for(Direction::Direction dir:rec){
        switch (dir)
        {
        case Direction::UP:
            cout<<"UP"<<endl;
            break;
        case Direction::DOWN:
            cout<<"DOWN"<<endl;
            break;
        case Direction::LEFT:
            cout<<"LEFT"<<endl;
            break;
        case Direction::RIGHT:
            cout<<"RIGHT"<<endl;
            break;
        default:
            break;
        }
    }

    PRT("3)test box:");
    Box box(p);
    box.moveToTile(TileType::FLOOR);
    ASSERT(box.getOnTarget(),false);
    box.moveToTile(TileType::TARGET);
    ASSERT(box.getOnTarget(),true);

    return 0;
}
