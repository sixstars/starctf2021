#ifndef VIEWER_H
#define VIEWER_H
#include <string>
#include "map.h"

namespace Viewer{

    // static const std::string SYMBOLS[] = {
    //     " ","\033[1;32mW\033[0m"," ","\033[1;33mB\033[0m","\033[1;35mT\033[0m","\033[1;34mP\033[0m","\033[1;31mR\033[0m"
    // };

    // static const std::string SYMBOLS[] = {
    //     " ","W"," ","B","T","P","R"
    // };

    static const std::string SYMBOLS[] = {
        " ","█"," ","□","○","♀","●"
    };

    char getInput();

    char getLevel();

    void displayMap(const Map& m,int level);

    void display(const std::string& s);

    void win();

    void help();

    void init();

    void finish();
}

#endif //VIEWER_H
