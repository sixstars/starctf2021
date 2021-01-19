#include <iostream>
#include "../cpp/Session.h"

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;

int main(){

    string str2 = 
        "11111111"
        "12222221"
        "12223221"
        "15222221"
        "12222421"
        "12223221"
        "12222421"
        "11111111";

    Session ses(8,8,1,str2);

    PRT("test session");
    PRT("loop test?");
    string input;
    cin>>input;
    char buffer[100];
    bool finish = false;
    if(input == "y"){
        PRT(ses.getMap().to_string());
        Direction::Direction dir;
        while (!finish && cin.getline(buffer,100))
        {
            char ch = buffer[0];
            switch (ch)
            {
            case 'w':
                dir = Direction::UP;
                ses.move(dir);
                break;
            case 's':
                dir = Direction::DOWN;
                ses.move(dir);
                break;
            case 'a':
                dir = Direction::LEFT;
                ses.move(dir);
                break;
            case 'd':
                dir = Direction::RIGHT;
                ses.move(dir);
                break;
            case 'q':
                finish = true;
                break;
            default:
                PRT("wrong input!");
                break;
            }

            PRT(ses.getMap().to_string());
        }
    }
    PRT("test finish");
}
