#include <iostream>
#include <string>
// #include <conio.h>
#include <cstdlib>

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;


/* 
 * \033[s 保存光标位置
 * \033[u 恢复光标位置
 * \033[?25l 隐藏光标
 * \033[?25h 显示光标
 * \033[?1049h 保存屏幕
 * \033[?1049l 恢复屏幕
 * \033[H 清除屏幕，
 * \033[2J 光标移到左上角
 */

void init(){
    PRT("\033[s");
    PRT("\033[?1049h");
    PRT("\033[H");
    PRT("\033[?25l");
    PRT("\033[2J");
}

void recover(){
    PRT("\033[H");
    PRT("\033[?1049l");
    PRT("\033[u");
}

int main(){
    init();
    int count = 0;
    char ch = 'p';
    system("stty -echo");
    while(ch != 'q'){
        cin >> ch;
        PRT(ch);
    }
    system("stty echo");
    recover();
    return 0;
}
