#include "../cpp/MapRepository.h"
#include "iostream"

#define PRT(A) std::cout<<(A)<<std::endl
#define ASSERT(A,B) if((A)==(B)) cout<<"Success"<<endl; else cout<<"Failed"<<endl

using namespace std;

int main(){
    using namespace MapRepository;
    PRT("1)test 1.map");
    MapBuffer buf = getMap(MAP1);
    PRT(buf.to_string());

    PRT("2)test mymap.map");
    MapBuffer mymap = getMap(MYMAP);
    PRT(mymap.to_string());
    return 0;
}
