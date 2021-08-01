#include "Tank2.h"

Tank2::Tank2(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window) : Bot(storona1, heals1, count_shots1, armor1, alive1, window)
{
    //storona=storona1;
    while(1)
    {
        //srand( time(NULL) );
        int x=width-10, y=length-10;
        current_x = rand() % x + 6;
        current_y = rand() % y + 6;
        bool t=true;
        for(int i=current_x-2; i<=current_x+2; i++) for(int j=current_y-2; j<=current_y+2; j++) if(pole[i][j]=='#') t=false;
        if(t==true) break;
    }
    x_end=current_x;
    y_end=current_y;
    storona=Up;
    //print_tank(current_x, current_y, Up, pole, '+');
    for(int i=0; i<(2+level); i++) bull[i].x=0;
    texture.loadFromFile("images/3.jpg", IntRect(2, 0, 30, 45));
    sprite.setTexture(texture);
    sprite.setScale(1.0f, 0.8f);
}

pair<int, int> Tank2::print_vystrel(Bullet &bull, vector < vector <char> > &pole)
{      
    Transform transform;
    if(bull.first!=true) pole[bull.x][bull.y]=' ';
    if(bull.storona==1) { bull.x-=2; if(bull.first!=false) bull.x--; bull.first=false; if(pole[bull.x+1][bull.y]=='+' || pole[bull.x+1][bull.y]=='*') {int x=bull.x; bull.x=0; return {x+1, bull.y};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x+1][bull.y]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef+10, bull.x*coef); (*window).draw(sprite_bullet); } else bull.x=0;  }
    if(bull.storona==2) { bull.y+=2; if(bull.first!=false) bull.y++; bull.first=false; if(pole[bull.x][bull.y-1]=='+' || pole[bull.x][bull.y-1]=='*') {int x=bull.x; bull.x=0; return {x, bull.y-1};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x][bull.y-1]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef+10, bull.x*coef-30); transform.rotate(90.f,  { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); }   else bull.x=0;  }
    if(bull.storona==3) { bull.y-=2; if(bull.first!=false) bull.y--; bull.first=false; if(pole[bull.x][bull.y+1]=='+' || pole[bull.x][bull.y+1]=='*') {int x=bull.x; bull.x=0; return {x, bull.y+1};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x][bull.y+1]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef-20, bull.x*coef);    transform.rotate(-90.f, { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); }   else bull.x=0;  }
    if(bull.storona==4) { bull.x+=2; if(bull.first!=false) bull.x++; bull.first=false; if(pole[bull.x-1][bull.y]=='+' || pole[bull.x-1][bull.y]=='*') {int x=bull.x; bull.x=0; return {x-1, bull.y};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x-1][bull.y]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef-25, bull.x*coef-25); transform.rotate(180.f, { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); }   else bull.x=0;  }
    return {0, 0};
}

pair<int, int> Tank2::NextStep(vector < vector <char> > &pole, int player_x, int player_y) //програ зацикливается при столкновении двух танков
    {
        pair<int, int> kletka={0, 0}, kletka2={0, 0};
        if(alive==true) {
            if(!steck.empty())
            {
                if(see_player!=true) 
                {
                    kletka = Oblast_vidimosti(pole, current_x, current_y, player_x, player_y);
                    if(see_player) //есди бот видит игрока, изменить направление движения в его сторону
                    {
                        while(!steck.empty()) steck.pop();
                        if(abs(player_x-current_x)>4 || abs(player_y-current_y)>4) while(!find_direction(pole, kletka.first, kletka.second)) {}; 
                    }
                }
                if(see_player) for (int i=0; i<(2+level); i++) if(bull[i].x==0) {bull[i] = {current_x, current_y, storona, true}; break;}
                for(int i=0; i<(2+level); i++) 
                {
                    if( bull[i].x!=0) 
                    {
                        kletka2 = print_vystrel(bull[i], pole); 
                        if(kletka2.first!=0 && kletka2.second!=0) break;
                    }   
                }  
                if(!steck.empty()) kletka = steck.top(); else return {0, 0};
                //del_tank(current_x, current_y, pole);
                if(!steck.empty()) steck.pop();
                int x = kletka.first, y = kletka.second;

                
                if(current_x==x && current_y==y+1) storona=Left;
                if(current_x==x && current_y==y-1) storona=Right;
                if(current_x==x+1 && current_y==y) storona=Up;
                if(current_x==x-1 && current_y==y) storona=Down;
                del_tank(current_x, current_y, pole);
                no_barrier = print_tank(x, y, storona, pole, '+');
                if(no_barrier)
                {
                    current_x=x;
                    current_y=y;
                }
                else
                {
                    print_tank(current_x, current_y, storona, pole, '+');
                    while(!steck.empty()) steck.pop();
                    no_barrier=true;
                }

                //napms(1000/(30+10*level));
                return kletka2;
            }
            else 
            {
                
                kletka={0, 0};
                for(int i=0; i<(2+level); i++) 
                {
                    if( bull[i].x!=0) 
                    {
                        kletka = print_vystrel(bull[i], pole); 
                        if(kletka2.first!=0 && kletka2.second!=0) break;
                    }   
                } 
                
                see_player=false;
                if(!find_direction(pole, 0, 0)) while(!steck.empty()) steck.pop();
                
                return kletka;
            }
        }
        else
        {
            while(!steck.empty()) steck.pop();
            for(int i=0; i<(2+level); i++) 
            {
                if(bull[i].x!=0) kletka = print_vystrel(bull[i], pole); 
                if(kletka2.first!=0 && kletka2.second!=0) return kletka;    
            }
           // napms(1000/(30+10*level));
        }
        return {0, 0};
    }
