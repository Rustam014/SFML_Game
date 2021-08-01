#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;



enum direction {Up=1, Right=2, Left=3, Down=4, UUR=5, UUL=6, DDR=7, DDL=8, URR=9, DRR=10, ULL=11, DLL=12, NON=13};
static int level=1, length=203, width=107, coef=9;

struct Bullet
{
    int x, y;
    direction storona;
    bool first;
    int time_of_live;
};

class Object
{
public:
    direction storona;
    int current_x, current_y, heals, count_shots , armor;
    bool alive;
    sf::RenderWindow* window;
    sf::Texture texture, texture_bullet;
    sf::Sprite sprite, sprite_bullet;

    Object() {};
    Object(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, sf::RenderWindow &window1);// : storona(storona1), heals(heals1), count_shots(count_shots1), armor(armor1), alive(alive1);

    bool proverka(int x, int y, vector < vector <char> > &pole);

    void del_tank(int x, int y, vector < vector <char> > &pole);

    bool print_tank(int x, int y, direction storona, vector < vector <char> > &pole, char symbol);

    virtual pair<int, int> print_vystrel(Bullet &bull, vector < vector <char> > &pole) = 0;
    virtual pair<int, int> NextStep(vector < vector <char> > &pole, int player_x, int player_y) = 0;

};