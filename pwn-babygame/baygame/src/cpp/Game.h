#ifndef GAME_H
#define GAME_H

#include "Session.h"
#include "MapRepository.h"
#include "Viewer.h"
#include <ctime>
#include <vector>
class Game{
    std::vector<Session> sessions;
    clock_t begin,end;
    double duration;
    /* level between {1,2,3,4,5,6,7,8,9}, start from 1 */
    int curLevel;
    /* max level */
    const int MAX_LEVEL;
    /* flag of finishing the session */
    bool isFinish;
    /* flag of quit the game */
    bool isQuit;
    Session *curSession;
    
    char * message ;
    void handleCmd(char ch);

    void handleStartCmd(char ch);

    void initSession();

    void startSession();

    void endSession();
public:
    
    Game(int level = 0);

    static std::vector<std::string> myName;
    ~Game();

    void start();

    bool isFinished() const;

    double getDuration() const;
};

#endif //GAME_H
