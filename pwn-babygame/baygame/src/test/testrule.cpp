#include <iostream>
#include "../cpp/Session.h"

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;

int main(){

    Map m2(8,8);
    string str2 = 
        "11111111"
        "12222221"
        "12223221"
        "15222221"
        "12222421"
        "12223221"
        "12222421"
        "11111111";
    m2.initMap(str2);
    PRT(m2.to_string());

    PRT("test rule");
    PRT("loop test?");
    string input;
    cin>>input;
    char buffer[100];
    bool finish = false;
    if(input == "y"){
        PRT(m2.to_string());
        Direction::Direction dir;
        while (!finish && cin.getline(buffer,100))
        {
            char ch = buffer[0];
            bool isRightMove = false;
            switch (ch)
            {
            case 'w':
                dir = Direction::UP;
                isRightMove = RULE::isRightMove(m2,dir);
                break;
            case 's':
                dir = Direction::DOWN;
                isRightMove = RULE::isRightMove(m2,dir);
                break;
            case 'a':
                dir = Direction::LEFT;
                isRightMove = RULE::isRightMove(m2,dir);
                break;
            case 'd':
                dir = Direction::RIGHT;
                isRightMove = RULE::isRightMove(m2,dir);
                break;
            case 'q':
                finish = true;
                break;
            default:
                PRT("wrong input!");
                break;
            }
            if(isRightMove){
                m2.move(dir);
            }

            PRT(m2.to_string());
        }
    }
    PRT("test finish");
}
