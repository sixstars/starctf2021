#include "../cpp/Tile.h"
#include "iostream"

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;

int main(){
    Tile tile(TileType::FLOOR);
    tile.setFlag(TileFlag::BOX);
    ASSERT(tile.getState(),State::BOX);
    tile.setFlag(TileFlag::PLAYER);
    ASSERT(tile.getState(),State::PLAYER);
    tile.setFlag(TileFlag::NONE);
    ASSERT(tile.getState(),State::FLOOR);
    Tile t(TileType::TARGET);
    t.setFlag(TileFlag::NONE);
    ASSERT(t.getState(),State::TARGET);
    t.setFlag(TileFlag::BOX);
    ASSERT(t.getState(),State::BOX_ON_TARGET);
    return 0;
}
