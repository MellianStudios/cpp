#ifndef PROJECT_CORE_PLAYER_H
#define PROJECT_CORE_PLAYER_H

#include "iostream"

using std::string;

class Player
{
private:
    int account;
    string name;
public:
    Player(int account, string name);

    string getName()
    { return name; }
};


#endif //PROJECT_CORE_PLAYER_H
