//#include "class_Object.h"
#include "Bot.h"
class Tank2 : public Bot
{

public:
Bullet bull[5] = {0, 0, Up, true};

Tank2(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window);

pair<int, int> print_vystrel(Bullet &bull, vector < vector <char> > &pole);

pair<int, int> NextStep(vector < vector <char> > &pole, int player_x, int player_y); 

};