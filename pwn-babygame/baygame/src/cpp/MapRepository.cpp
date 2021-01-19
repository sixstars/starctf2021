#include "MapRepository.h"
#include <fstream>
#include <iostream>

/**********   FileUtil part   ***********/
static inline bool isNumber(char ch){
    return (ch <= '9' && ch >= '0');
}

// void FileUtil::readFile(std::string path, int& w, int& h, std::string& buffer){
//     /* open input stream */
//     std::ifstream in(path);
//     if(!in.is_open()){
//         std::cout<<path<<std::endl;
//         std::string e("file open failed");
//         throw e;
//     }

//     /* init return value */
//     w = 0;
//     h = 0;
//     buffer = "";

//     /* buffer argument */
//     const int SIZE = 100;
//     char buff[SIZE];
//     std::string buf;

//     /* get width and height value */
//     in.getline(buff,SIZE);
//     buf= buff;
//     int idx = 0, size = buf.size();
//     for(;idx < size; idx++){
//         char ch = buf.at(idx);
//         if(!isNumber(ch)){
//             break;
//         }
//         w *= 10;
//         w += (ch - '0');
//     }
//     /* jump blank */
//     idx++;
//     for(;idx < size; idx++){
//         char ch = buf.at(idx);
//         if(!isNumber(ch)){
//             break;
//         }
//         h *= 10;
//         h += (ch - '0');
//     }

//     /* read map content */
//     for(int i = 0; i < h; i++){
//         in.getline(buff,SIZE);
//         std::string temp(buff);
//         buffer += temp.substr(0,w);
//     }

//     /* close input stream */
//     in.close();
// }


/**********   FileUtil part   ***********/

/**********   MapRepository part   ***********/
MapRepository::MapBuffer::MapBuffer(int wid, int hei, const std::string& b):w(wid),h(hei),buf(b){
    /* default constructor */
}

MapRepository::MapBuffer::MapBuffer(const MapBuffer& mb){
    w = mb.w;
    h = mb.h;
    buf = mb.buf;
}

MapRepository::MapBuffer& MapRepository::MapBuffer::operator=(const MapBuffer& mb){
    w = mb.w;
    h = mb.h;
    buf = mb.buf;
}

int MapRepository::MapBuffer::getWidth() const{
    return w;
}

int MapRepository::MapBuffer::getHeight() const{
    return h;
}

const std::string& MapRepository::MapBuffer::getBuffer() const{
    return buf;
}

const std::string MapRepository::MapBuffer::to_string() const{
    std::string buffer;
    buffer += "(" + std::to_string(w) + "," + std::to_string(h) + ")\n" + buf;
    return buffer;
}

const MapRepository::MapBuffer MapRepository::getMap(MapRepository::MAP_ID id){
    int w,h;
    std::string buffer;
    switch (id){
        case MAP1:
                w = 8;
                h = 8;
                buffer = maps[id];
        break;
        case MAP2:
                w = 6;
                h = 8;
                buffer = maps[id];
        break;
        default:
                w = 8;
                h = 8;
                buffer = maps[0];
    }
    
    return MapBuffer(w,h,buffer);
}


/**********   MapRepository part   ***********/
