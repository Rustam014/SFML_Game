#include "player.h"


Player::Player(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window) : Object(storona1, heals1, count_shots1, armor1, alive1, window)
{
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
    //print_tank(current_x, current_y, storona, pole, '*');
    texture.loadFromFile("images/7.jpg", IntRect(2, 0, 30, 45));
    sprite.setTexture(texture);
    sprite.setScale(1.0f, 0.8f);
    
    buttons1[0]=false;
    buttons1[1]=false;
    buttons1[2]=false;
    buttons1[3]=false;
}


pair<int, int> Player::print_vystrel(Bullet &bull, vector < vector <char> > &pole)
{      
    Transform transform;
    if(bull.first!=true) pole[bull.x][bull.y]=' ';
    if(bull.storona==1) { bull.x-=2; if(bull.first!=false) bull.x--; bull.first=false; if(bull.x>3 && bull.x<width-2 && bull.y>3 && bull.y<length-2) if(pole[bull.x+1][bull.y]=='+' || pole[bull.x+1][bull.y]=='*') {int x=bull.x; bull.x=0; return {x+1, bull.y};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x+1][bull.y]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef+10, bull.x*coef); (*window).draw(sprite_bullet); } else bull.x=0;  }
    if(bull.storona==2) { bull.y+=2; if(bull.first!=false) bull.y++; bull.first=false; if(bull.x>3 && bull.x<width-2 && bull.y>3 && bull.y<length-2) if(pole[bull.x][bull.y-1]=='+' || pole[bull.x][bull.y-1]=='*') {int x=bull.x; bull.x=0; return {x, bull.y-1};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x][bull.y-1]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef+10, bull.x*coef-30); transform.rotate(90.f,  { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); } else bull.x=0;  }
    if(bull.storona==3) { bull.y-=2; if(bull.first!=false) bull.y--; bull.first=false; if(bull.x>3 && bull.x<width-2 && bull.y>3 && bull.y<length-2) if(pole[bull.x][bull.y+1]=='+' || pole[bull.x][bull.y+1]=='*') {int x=bull.x; bull.x=0; return {x, bull.y+1};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x][bull.y+1]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef-20, bull.x*coef);    transform.rotate(-90.f, { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); } else bull.x=0;  }
    if(bull.storona==4) { bull.x+=2; if(bull.first!=false) bull.x++; bull.first=false; if(bull.x>3 && bull.x<width-2 && bull.y>3 && bull.y<length-2) if(pole[bull.x-1][bull.y]=='+' || pole[bull.x-1][bull.y]=='*') {int x=bull.x; bull.x=0; return {x-1, bull.y};}  if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  if(!(pole[bull.x][bull.y]=='#' || pole[bull.x-1][bull.y]=='#')) { pole[bull.x][bull.y]='.'; (sprite_bullet).setPosition(bull.y*coef-25, bull.x*coef-25); transform.rotate(180.f, { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); } else bull.x=0;  }

    return {0, 0};
}


pair<int, int> Player::NextStep(vector < vector <char> > &pole, int player_x, int player_y) 
{
    Event event;
    while ((*window).pollEvent(event))
    {
        if ((event).type == Event::Closed || ((event).type == sf::Event::KeyPressed && (event).key.code == sf::Keyboard::Escape)) { return {-1, -1}; }
    }
    Transform transform;
    pair<int, int> kletka={0, 0};
	//if ( (event).type == Event::Closed) (*window).close();
    if((event).type == Event::KeyReleased) {
        if((event).key.code==Keyboard::W) buttons1[0]=false;
        if((event).key.code==Keyboard::D) buttons1[1]=false;
        if((event).key.code==Keyboard::A) buttons1[2]=false;
        if((event).key.code==Keyboard::S) buttons1[3]=false;
    } 
    else if((event).type == Event::TextEntered) {
        if((event).text.unicode==119) buttons1[0]=true; 
        if((event).text.unicode==100) buttons1[1]=true; 
        if((event).text.unicode==97)  buttons1[2]=true; 
        if((event).text.unicode==115) buttons1[3]=true;
    } 
    

    bool t=true, p=true;
    if(buttons1[0])  { t=false;  (*window).clear(Color::Black); del_tank(current_x, current_y, pole); current_x--; storona=Up;    if(!(print_tank(current_x, current_y, Up, pole, '*')))    { current_x++; print_tank(current_x, current_y, Up, pole, '*');    } } 
    if(buttons1[1])  { t=false;  (*window).clear(Color::Black); del_tank(current_x, current_y, pole); current_y++; storona=Right; if(!(print_tank(current_x, current_y, Right, pole, '*'))) { current_y--; print_tank(current_x, current_y, Right, pole, '*'); } }
    if(buttons1[2])  { t=false;  (*window).clear(Color::Black); del_tank(current_x, current_y, pole); current_y--; storona=Left;  if(!(print_tank(current_x, current_y, Left, pole, '*')))  { current_y++; print_tank(current_x, current_y, Left, pole, '*');  } } 
    if(buttons1[3])  { t=false;  (*window).clear(Color::Black); del_tank(current_x, current_y, pole); current_x++; storona=Down;  if(!(print_tank(current_x, current_y, Down, pole, '*')))  { current_x--; print_tank(current_x, current_y, Down, pole, '*');  } } 
    if(t)
    {
        if(storona==Right) { transform.rotate(90.f,  { current_y*coef/1.f, current_x*coef/1.f });  (sprite).setPosition(current_y*coef, current_x*coef-30); (*window).draw(sprite, transform);   } else
        if(storona==Left)  { transform.rotate(-90.f, { current_y*coef/1.f, current_x*coef/1.f });  (sprite).setPosition(current_y*coef-30, current_x*coef); (*window).draw(sprite, transform);   } else
        if(storona==Down)  { transform.rotate(180.f, { current_y*coef/1.f, current_x*coef/1.f });  (sprite).setPosition(current_y*coef-30, current_x*coef-25); (*window).draw(sprite, transform);   }
        else { (sprite).setPosition(current_y*coef, current_x*coef); (*window).draw(sprite); }
    }

    if ((event).type == sf::Event::TextEntered && Keyboard::isKeyPressed(Keyboard::Space) ) 
    { 
        for (int i=0; i<5; i++) if(bull[i].x==0) {bull[i] = {current_x, current_y, storona, true}; break;} 
    } 
    
    for(int i=0; i<5; i++) 
    {
        if(bull[i].x!=0) 
        {
            kletka=print_vystrel(bull[i], pole);
            if(kletka.first!=0 && kletka.second!=0) break;
        }
    }
    msleep(5000);
    return kletka;


}
