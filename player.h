#pragma once
#include "class_Object.h"

#if defined(_WIN32) || defined(_WIN64) 
    #include <windows.h>
    #define msleep(msec) Sleep(msec)
#else
    #include <unistd.h>
    #define msleep(msec) usleep(msec*10)
#endif



class Player : public Object
{
    public:
    Bullet bull[5] = {0, 0, Up, true};
    bool buttons1[4]; //1-Up, 2-R, 3-L, 4-D, 5-Space
    
    Player(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window);
    pair<int, int> print_vystrel(Bullet &bull, vector < vector <char> > &pole);
    pair<int, int> NextStep(vector < vector <char> > &pole, int player_x, int player_y);
};

