#ifndef MAPREPOSITORY_H
#define MAPREPOSITORY_H
#include <string>

namespace FileUtil{
    void readFile(std::string path, int& w, int& h, std::string& buffer);
}

namespace MapRepository{

    /* file name of map */
    static const std::string MAP_PATH[] = {
        "1.map",
        "2.map",
        "3.map",
        "4.map",
        "5.map",
        "6.map",
        "7.map",
        "8.map",
        "9.map",
        "mymap.map"
    };

    /* relation between bin and maps directory */
    static const std::string MAP_DIR = "../maps/";

    /* index of MAP_PATH */
    enum MAP_ID{
        MAP1 = 0,
        MAP2 = 1,
        MAP3 = 2,
        MAP4 = 3,
        MAP5 = 4,
        MAP6 = 5,
        MAP7 = 6,
        MAP8 = 7,
        MAP9 = 8,
        MYMAP = 9
    };

    static const std::string maps[] = {
        "0001110000014100111131001423511111132341001211110014100000111000",
        "011110112210153210113211112321143221144941111111"
    };
   
    /* inner class used to store map information */
    class MapBuffer{
        int w,h;
        std::string buf;
    public:
        MapBuffer(int wid, int hei, const std::string& b);

        MapBuffer(const MapBuffer& mb);

        MapBuffer& operator=(const MapBuffer& mb);
        
        int getWidth() const;

        int getHeight() const;

        const std::string to_string() const;

        const std::string& getBuffer() const;
    };

    const MapBuffer getMap(MAP_ID id);
};

#endif //MAPREPOSITORY_H
