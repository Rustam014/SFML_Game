#include <cmath>
#include <iostream>
#include <memory>
//#include "class_Object.h"
#include "player.h"
#include "Tank2.h"
#include "Tank3.h"
#include "Tank4.h"



int cout_pixel_x=0, cout_pixel_y=0;

void print_blok(int x, int y, vector < vector <char> > &pole)
{
  if(x>3 && x<width && y>3 && y<length) for(int i=x-2; i<=x+3; i++) for(int j=y-2; j<=y+3; j++) pole[i][j]=' ';
}

void print_map( vector < vector <char> > &pole )
{
    //for(int i=2; i<width; i++) for(int j=2; j<length; j++) pole[i][j]='#';
    //for(int i=4; i<width-2; i++) for(int j=4; j<length-2; j++) pole[i][j]=' ';
    srand ( time(NULL) );
    for(int i=2; i<width; i++) for(int j=2; j<length; j++) pole[i][j]='#';
    //ScreenOutput(pole);
    int dx=0, dy=0, x, y, count=0;
    x = 6;
    y = 6;
    print_blok(x, y, pole);
    
    while(count<500000)
    {
        int t = rand() % 2;
        int t1 = rand() % 2;
        if(t==1) dx = (rand() % 2) * 12;
        else dy = (rand() % 2) * 12;

        if(t1==1) dx *= (-1);
        else dy *= (-1);
        x+=dx;
        y+=dy;
        if( x<width-1 && x>3 && y<length-1 && y>3)
        {
            if(pole[x][y]=='#')
            {
                print_blok(x, y, pole);
                print_blok(x-dx/2, y-dy/2, pole);
            }
        }
        else { x=6; y=6; }
        count++;
        dx=dy=0;
    }
}

void game_over(bool t, RenderWindow &window)
{
    Texture texture;
    texture.loadFromFile("images/end_of_game.jpg");
    window.clear(Color::Black);
    Sprite sprite(texture);
    
    if(t) sprite.setTextureRect(IntRect(0, 350, 500, 100));   //you won
    else sprite.setTextureRect(IntRect(0, 0, 400, 200));
    sprite.setPosition(cout_pixel_x/2-250, cout_pixel_y/2-50);


    window.draw(sprite);
    window.display();
    msleep(100000);
    //window.clear(Color::Black);
}

bool StartMenu(int s, RenderWindow &window) 
{
	Texture texture, texture_tank;
    texture.loadFromFile("images/game_menu2.jpg");
    texture_tank.loadFromFile("images/4.jpg");
    Sprite sprite1(texture, IntRect(0, 0, 400, 300));   //start level exit
    Sprite sprite2(texture, IntRect(20, 330, 50, 80)); //1
    Sprite sprite3(texture, IntRect(90, 330, 50, 80)); //2
    Sprite sprite4(texture, IntRect(160, 330, 50, 80)); //3
    Sprite sprite_tank(texture_tank, IntRect(2, 0, 30, 45)); //tank
    sprite_tank.rotate(90);
    sprite_tank.setPosition(0, 20);
    sprite1.setPosition(cout_pixel_x/2-200, cout_pixel_y/2);
    sprite2.setPosition(cout_pixel_x/2+190, cout_pixel_y/2+110);
    sprite3.setPosition(cout_pixel_x/2+190, cout_pixel_y/2+110);
    sprite4.setPosition(cout_pixel_x/2+190, cout_pixel_y/2+110);
    sprite_tank.setPosition(cout_pixel_x/2-220, cout_pixel_y/2+10);
    sprite_tank.setScale(1.5f, 1.5f);
    bool t=true;
    Event event;
    while (t)
    {
        while (window.pollEvent(event))
        {
            if((event).type == Event::Closed) t=false;
        }
        window.clear(Color::Black);
        if(t==false) break;
        if ((event).type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up) && (s>1) ) s--;
        else if ((event).type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down) && (s<3)) s++;
	    else if ((event).type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right)) { if(level<3) level++; }
	    else if ((event).type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Left))  { if(level>1) level--; }
	    else if ((event).key.code == sf::Keyboard::Enter) 
        {  
            if(s==1) { t=true;  break; }
            if(s==3) { t=false; break; }
        }

		window.draw(sprite1);
		if(level==1) window.draw(sprite2); 
		if(level==2) window.draw(sprite3); 
		if(level==3) window.draw(sprite4); 
        if(s==1) sprite_tank.setPosition(cout_pixel_x/2-220, cout_pixel_y/2+10);
        if(s==2) sprite_tank.setPosition(cout_pixel_x/2-220, cout_pixel_y/2+130);
        if(s==3) sprite_tank.setPosition(cout_pixel_x/2-220, cout_pixel_y/2+240);
        window.draw(sprite_tank);
		//window.draw(sprite5);
        window.display();
        msleep(10000);
    }
    //window.clear();
    return t;
}

void func(vector < vector <char> > &pole, RenderWindow &window)
{
    Texture texture;
    texture.loadFromFile("images/pics3.jpg");
    Sprite sprite(texture, IntRect(0, 0, coef, coef));
    for(int x=0; x<width; x++)
    {
        for(int y=0; y<length; y++)
        {
            if(pole[x][y]=='#')
            {
                sprite.setPosition(y*coef+10, x*coef+10);
                window.draw(sprite);
            }
        }
    }
    
}

int main()
{
    int count_tanks=3, count_dead=0;                                //x, y - координаты игрока. storona - куда повернут игрок. count_dead - сколько убил ботов
    bool igra=true;                                                 //пока идет игра
    pair<int, int> kletka={0, 0}, kletka2={0, 0};
    RenderWindow window(VideoMode(203*coef, 107*coef), "SFML Works!");

    Vector2u size = window.getSize();
    cout_pixel_x = size.x; //1848
    cout_pixel_y = size.y; //1016

    while (window.isOpen())
    { 
        window.clear(Color::Black);
        if(!StartMenu(1, window))
        {
            window.clear(Color::Black);
            window.close();
            window.clear();
            return 0;
        }
        window.clear(Color::Black);
        vector < vector <char> > pole(width+1, vector <char> (length+1) ); 
        vector <shared_ptr<Object>> objects;
        print_map(pole);
        Player p(Up, 100, 5, 20, true, pole, window);
        

        shared_ptr<Object> t2 = make_shared<Tank2>(Up, 100, 5, 20, true, pole, window);
        shared_ptr<Object> t3 = make_shared<Tank3>(Up, 100, 15, 20, true, pole, window);
        shared_ptr<Object> t4 = make_shared<Tank4>(Up, 100, 3, 20, true, pole, window);
        objects.push_back(t2);
        objects.push_back(t3);
        objects.push_back(t4);
        if(level==2) 
        {
            count_tanks=4;
            shared_ptr<Object> t5 = make_shared<Tank2>(Up, 100, 5, 20, true, pole, window);
            objects.push_back(t5);
        }
        if(level==3) 
        {
            count_tanks=5;
            shared_ptr<Object> t6 = make_shared<Tank2>(Up, 100, 5, 20, true, pole, window);
            objects.push_back(t6);
            shared_ptr<Object> t7 = make_shared<Tank3>(Up, 100, 15, 20, true, pole, window);
            objects.push_back(t7);
        }

        while(igra)
        {
            window.clear(Color::Black);
            
            kletka2=p.NextStep(pole, p.current_x, p.current_y);
            if(kletka2.first==-1 && kletka2.second==-1) { igra=false; window.close(); break;}
            func(pole, window);
            for (auto it = objects.begin(); it != objects.end(); it++)
		    {

                if(abs((*it)->current_x - kletka2.first)<2 && abs((*it)->current_y - kletka2.second)<2) { (*it)->alive=false; (*it)->del_tank((*it)->current_x, (*it)->current_y, pole); count_dead++;}
                kletka=(*it)->NextStep(pole, p.current_x, p.current_y);
                if(abs(p.current_x - kletka.first)<2 && abs(p.current_y - kletka.second)<2 ) { igra=false; msleep(100000); break; }
                if(count_dead==count_tanks) igra=false;
		    }
            window.display();
        }
        game_over(count_dead==count_tanks, window);
        for (auto it = objects.begin(); it != objects.end(); it++)
		{
            (*it)->alive=false;
            (*it)->NextStep(pole, 0, 0);
        }
        count_dead=0;
        count_tanks=3;
        level=1;
        objects.clear();
        pole.clear();
        igra=true;
    }
    
    return 0;
}
