#include <iostream>
#include "../cpp/Map.h"

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;

int main(){
    PRT("1)test initialize");
    Map m1(3,3);
    string str = "111121111";
    m1.initMap(str);
    PRT(m1.to_string());

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

    PRT("2)test move");
    PRT("loop test?");
    string input;
    cin>>input;
    char buffer[100];
    bool finish = false;
    if(input == "y"){
        PRT(m2.to_string());
        while (!finish && cin.getline(buffer,100))
        {
            char ch = buffer[0];
            switch (ch)
            {
            case 'w':
                m2.move(Direction::UP);
                break;
            case 's':
                m2.move(Direction::DOWN);
                break;
            case 'a':
                m2.move(Direction::LEFT);
                break;
            case 'd':
                m2.move(Direction::RIGHT);
                break;
            case 'q':
                finish = true;
                break;
            default:
                PRT("wrong input!");
                break;
            }

            PRT(m2.to_string());
        }
    }
    PRT("test finish");
}
