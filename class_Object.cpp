#include "class_Object.h"

Object::Object(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, RenderWindow &window1) : storona(storona1), heals(heals1), count_shots(count_shots1), armor(armor1), alive(alive1) 
{
    window=&window1;
    texture_bullet.loadFromFile("images/6.jpg", IntRect(0, 0, 20, 20));
    sprite_bullet.setTexture(texture_bullet);
    sprite_bullet.setScale(0.5f, 0.5f);
}

bool Object::proverka(int x, int y, vector < vector <char> > &pole)
{ 
    if(x>3 && x<width && y>3 && y<length && pole[x][y]!='*' && pole[x][y]!='+' && pole[x][y]!='#') return true;
    else return false;
}

void Object::del_tank(int x, int y, vector < vector <char> > &pole)
{
    if(x>3 && x<width-2 && y>3 && y<length-2)
    {
        pole[x][y]=pole[x-1][y]=pole[x+1][y]=' ';
        pole[x][y-1]=pole[x-1][y-1]=pole[x+1][y-1]=' ';
        pole[x][y+1]=pole[x-1][y+1]=pole[x+1][y+1]=' ';
    }
}

bool Object::print_tank(int x, int y, direction storona, vector < vector <char> > &pole, char symbol)
{
    if(x>3 && x<width-2 && y>3 && y<length-2) 
    {
    Transform transform;
    if(storona==1) //прямо
    {
        if(!(proverka(x-1, y, pole) && proverka(x-1, y-1, pole) && proverka(x-1, y+1, pole))) return false;
        pole[x][y]=pole[x-1][y]=pole[x+1][y]=symbol;
        pole[x][y-1]=pole[x][y+1]=symbol;
        pole[x+1][y-1]=pole[x+1][y+1]=symbol;    

        (sprite).setPosition(y*coef, x*coef); 
        (*window).draw(sprite);
    }
    else if(storona==2) //vpravo
    {
        if(!(proverka(x, y+1, pole) && proverka(x-1, y+1, pole) && proverka(x+1, y+1, pole))) return false;
        pole[x][y]=pole[x-1][y]=pole[x+1][y]=symbol;
        pole[x][y-1]=pole[x-1][y-1]=pole[x+1][y-1]=symbol;
        pole[x][y+1]=symbol;

        (sprite).setPosition(y*coef, x*coef-30);     
        transform.rotate(90.f,  { y*coef/1.f, x*coef/1.f }); 
        (*window).draw(sprite, transform);
    }
    else if(storona==3) //vlevo
    {
        if(!(proverka(x, y-1, pole) && proverka(x-1, y-1, pole) && proverka(x+1, y-1, pole))) return false;
        pole[x][y]=pole[x-1][y]=pole[x+1][y]=symbol;
        pole[x][y+1]=pole[x-1][y+1]=pole[x+1][y+1]=symbol;
        pole[x][y-1]=symbol;

        (sprite).setPosition(y*coef-30, x*coef);     
        transform.rotate(-90.f, { y*coef/1.f, x*coef/1.f }); 
        (*window).draw(sprite, transform);
    }
    else //v zad nazad
    {
        if(!(proverka(x+1, y, pole) && proverka(x+1, y+1, pole) && proverka(x+1, y-1, pole))) return false;
        pole[x][y]=pole[x-1][y]=pole[x+1][y]=symbol;
        pole[x][y-1]=pole[x][y+1]=symbol;
        pole[x-1][y-1]=pole[x-1][y+1]=symbol;

        (sprite).setPosition(y*coef-30, x*coef-25);
        transform.rotate(180.f, { y*coef/1.f, x*coef/1.f }); 
        (*window).draw(sprite, transform);
        
    }
    return true; 
    }
    else return false;
}
