#include "Bot.h"
class Tank4 : public Bot //ЛОВИМ СЕГМЕНТЕЙШН
{
//   стреляет пулями с автоприцелом
    public:
    Bullet bull[3];
    stack <pair<int, int>> steck2[3];
    int timer_for_bull=20, timer=5;
    
    Tank4(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window);
    
    pair<int, int> print_vystrel(Bullet &bull, vector < vector <char> > &pole);
    
    bool find_direction_for_bull(vector < vector <char> > &pole, int x, int y, stack <pair<int, int>> &steck2, int i);
    
    pair<int, int> preparation_for_bullet(int player_x, int player_y, vector < vector <char> > &pole);
    pair<int, int> NextStep(vector < vector <char> > &pole, int player_x, int player_y);
};