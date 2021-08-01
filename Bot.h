#pragma once
#include "class_Object.h"
#include <stack>
#include <queue>

class Bot : public Object
{
public:
    Bot(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, RenderWindow &window);
protected:

    bool prov(int x, int y, vector < vector <char> > &pole, bool prov_bull);
    void find_path(int row, int col, vector < vector <char> > &pole, bool ( &visited )[107][203], int ( &path )[107][203], queue<pair<int, int>>& plan, bool path_bull);
    bool find_direction(vector < vector <char> > &pole, int x, int y);
    pair<int, int> Oblast_vidimosti(vector < vector <char> > &pole, int bot_x, int bot_y, int player_x, int player_y);
    virtual pair<int, int> print_vystrel(Bullet &bull, vector < vector <char> > &pole) = 0;
    virtual pair<int, int> NextStep(vector < vector <char> > &pole, int player_x, int player_y) = 0;

    int x_end=0, y_end=0;
    bool see_player=false, no_barrier=true;
    stack <pair<int, int>> steck;
    
};