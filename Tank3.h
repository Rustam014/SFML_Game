#include "Bot.h"

class Tank3 : public Bot
{

public:
Bullet bull[15] = {0, 0, Up, true};
int time1=5;
Tank3(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window);

pair<int, int> print_vystrel(Bullet &bull, vector < vector <char> > &pole);

pair<int, int> NextStep(vector < vector <char> > &pole, int player_x, int player_y);

};