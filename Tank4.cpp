#include "Tank4.h"

Tank4::Tank4(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, vector < vector <char> > &pole, RenderWindow &window) : Bot(storona1, heals1, count_shots1, armor1, alive1, window)
{
    while(1)
    {
        
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
    print_tank(current_x, current_y, Up, pole, '+');
    for(int i=0; i<count_shots; i++) bull[i] = {0, 0, Up, true, timer_for_bull};
    //texture.loadFromFile("5.jpg");
    texture.loadFromFile("images/5.jpg", IntRect(2, 0, 30, 45));
    sprite.setTexture(texture);
    sprite.setScale(1.0f, 0.8f);
}

pair<int, int> Tank4::print_vystrel(Bullet &bull, vector < vector <char> > &pole)
{      
    bull.time_of_live--;
    if(pole[bull.x][bull.y]=='+' || pole[bull.x][bull.y]=='*') { int x=bull.x; bull.x=0; return {x, bull.y}; }  
    if(pole[bull.x][bull.y]!='#') 
    {
        pole[bull.x][bull.y]='.'; 
        Transform transform;
        if(bull.storona==1)  { (sprite_bullet).setPosition(bull.y*coef+10, bull.x*coef); (*window).draw(sprite_bullet); }
        if(bull.storona==2)  { (sprite_bullet).setPosition(bull.y*coef+10, bull.x*coef-30); transform.rotate(90.f,  { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); }
        if(bull.storona==3)  { (sprite_bullet).setPosition(bull.y*coef-20, bull.x*coef);    transform.rotate(-90.f, { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); }
        if(bull.storona==4)  { (sprite_bullet).setPosition(bull.y*coef-25, bull.x*coef-25); transform.rotate(180.f, { bull.y*coef/1.f, bull.x*coef/1.f }); (*window).draw(sprite_bullet, transform); }
    }
    else { bull.x=0; }
    return {0, 0};
}

bool Tank4::find_direction_for_bull(vector < vector <char> > &pole, int x, int y, stack <pair<int, int>> &steck2, int i)
{
  x_end=x;
  y_end=y;
  if(x==0 && y==0)
  {
    while(1) //выбор рандомной координаты
    {
        x=width-10;
        y=length-10;
        x_end = rand() % x + 6;
        y_end = rand() % y + 6;
        bool t=true;
        if(x_end>3 && x_end<width && y_end>3 && y_end<length) 
        {
            for(int i=x_end-2; i<=x_end+2; i++) for(int j=y_end-2; j<=y_end+2; j++) if(pole[i][j]=='#') t=false;
            if(t==true) break;
        }
    }
  }
  
  pair<int, int> kletka;
  queue <pair<int, int>> plan;
  bool visited[107][203];
  int path[107][203];
  for(int i=0; i<width; i++)
  {
      for(int j=0; j<length; j++)
      {
          visited[i][j] = false;  
          path[i][j] = -1;
      }
  }
  path[x_end][y_end] = 1;
  int x1, y1;
  if(bull[i].first)
  {
      x1=current_x, y1=current_y;
      if(storona==1) x1-=2;
      if(storona==2) y1+=2;
      if(storona==3) y1-=2;
      if(storona==4) x1+=2;
  }
  else
  {
      x1=bull[i].x;
      y1=bull[i].y;
  }
  
  plan.push({x1, y1});
  
  while(!plan.empty())
  {
    kletka=plan.front();
    plan.pop();
    int x = kletka.first;
    int y = kletka.second;
    find_path(x, y, pole, visited, path, plan, true);
  }
  if(!visited[x_end][y_end]) return false;
  else 
  {
    int x = x_end;
    int y = y_end;
    int count=0;
    while (path[x][y] != 2 && count<length*width) 
    { // восстановление пути
        if ((x-1) >= 0 && (x-1) < width && (path[x-1][y] == path[x][y] - 1))  { x = x-1; steck2.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/} else
        if ((x+1) >= 0 && (x+1) < width && (path[x+1][y] == path[x][y] - 1))  { x = x+1; steck2.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/} else
        if ((y-1) >= 0 && (y-1) < length && (path[x][y-1] == path[x][y] - 1)) { y = y-1; steck2.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/} else
        if ((y+1) >= 0 && (y+1) < length && (path[x][y+1] == path[x][y] - 1)) { y = y+1; steck2.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/}
        count++;
    }
    if(path[x][y]!=2) return false;
    return true;
  }
}

pair<int, int> Tank4::preparation_for_bullet(int player_x, int player_y, vector < vector <char> > &pole) // Use of uninitialised value + pole
{
    pair<int, int> kletka={0, 0}, kletka2={0, 0};
    for(int i=0; i<count_shots; i++) 
    {
        if( bull[i].x!=0) 
        {
            if(bull[i].first!=true) pole[bull[i].x][bull[i].y]=' ';
            if((bull[i].time_of_live) < 0)                                                                  // если время жизни пули вышло то пуля умерает
            {
                while(!steck2[i].empty()) steck2[i].pop();                                                  // очищаем стек
                bull[i] = {0, 0, Up, true, timer_for_bull};                                                 // обнуляем пулю
            }
            else                                                                                            // если пуля жива
            {
                if(steck2[i].empty())                                                                       // если стек пустой
                { 
                    if(abs(player_x-bull[i].x)>3 || abs(player_y-bull[i].y)>3)                              // если бот далеко от игрока
                    {
                        if(find_direction_for_bull(pole, player_x, player_y, steck2[i], i))                 // находим путь до игрока
                        {
                            kletka = steck2[i].top();                                                       // берем 1 пару из стека пути
                            bull[i] = {kletka.first, kletka.second, bull[i].storona, true, timer_for_bull}; // заполняем данные пули
                        }
                        else while(!steck2[i].empty()) steck2[i].pop();                                     // если не нашли путь, очищаем стек
                    }
                    else { bull[i] = {0, 0, Up, true, timer_for_bull}; return {player_x, player_y}; }                                     // если стек пустой и бот близко
                }
                else                                                                                        // если стек не пустой
                {  
                    steck2[i].pop();                                                                        // удаляем пару из стека 

                    if(steck2[i].empty()) 
                    {
                        if((abs(player_x-bull[i].x)>3 || abs(player_y-bull[i].y)>3))
                        {
                            if(find_direction_for_bull(pole, player_x, player_y, steck2[i], i)) 
                            {
                                kletka = steck2[i].top();
                                bull[i] = {kletka.first, kletka.second, storona, true, timer_for_bull};
                            }
                            else while(!steck2[i].empty()) steck2[i].pop();
                        }
                        else { bull[i] = {0, 0, Up, true, timer_for_bull}; return {player_x, player_y}; }
                    }
                    else
                    {
                        kletka = steck2[i].top();
                        steck2[i].pop();                                                                    // удаляем пару из стека и смотрим как поворачивается пуля

                        if(bull[i].x==kletka.first   && bull[i].y-2==kletka.second) bull[i].storona=Left;
                        if(bull[i].x==kletka.first   && bull[i].y+2==kletka.second) bull[i].storona=Right;
                        if(bull[i].x-2==kletka.first && bull[i].y==kletka.second)   bull[i].storona=Up;
                        if(bull[i].x+2==kletka.first && bull[i].y==kletka.second)   bull[i].storona=Down;

                        int x=kletka.first, y=kletka.second;
                        bull[i] = {x, y, bull[i].storona, false, bull[i].time_of_live};
                        kletka2 = print_vystrel(bull[i], pole); 
                        if(bull[i].x==0) {while(!steck2[i].empty()) steck2[i].pop();}
                        if(kletka2.first!=0 && kletka2.second!=0) return kletka2;
                    }
                }
            }
        }   
    }
    return kletka2;
}

pair<int, int> Tank4::NextStep(vector < vector <char> > &pole, int player_x, int player_y) //неправильно освобождаем какой-то стек
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
                    if(abs(player_x-current_x)>4 || abs(player_y-current_y)>4) { while(!find_direction(pole, kletka.first, kletka.second)) {while(steck.empty()) steck.pop();}; }
                }
            }

            if(!steck.empty()) kletka = steck.top(); else return {0, 0};
            steck.pop();
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
            
            //..............СОЗДАЕМ МАРШРУТ ДЛЯ 1 ПУЛИ.............
            if(see_player && timer>=10) for (int i=0; i<count_shots; i++) if(bull[i].x==0) //timer
            {
                timer=0;
                if(abs(player_x-current_x)>4 || abs(player_y-current_y)>4) {
                    if(find_direction_for_bull(pole, player_x, player_y, steck2[i], i)) 
                    {
                        kletka = steck2[i].top();
                        bull[i] = {kletka.first, kletka.second, storona, true, timer_for_bull};
                        break;
                    }
                    else while(!steck2[i].empty()) steck2[i].pop();
                }
                else return {player_x, player_y};
            }
            timer++;
            
            //............ПУЛИ ПЕРЕДВИГАЮТСЯ НА 1 ПОЗИЦИЮ..........
            kletka2=preparation_for_bullet(player_x, player_y, pole);
        
            //napms(1000/(30+10*level));
            //napms(1000/10);
            //msleep(100);
            return kletka2;
        }
        else 
        {
            kletka={0, 0};
            kletka=preparation_for_bullet(player_x, player_y, pole);
            see_player=false;
            if(!find_direction(pole, 0, 0)) while(!steck.empty()) steck.pop();
            return kletka;
        }
    }
    else
    {
        kletka={0, 0};
        while(!steck.empty()) steck.pop();
        kletka=preparation_for_bullet(player_x, player_y, pole);
        for(int i=0; i<count_shots; i++) while(!steck2[i].empty()) steck2[i].pop();
        //napms(1000/(30+10*level));
        //msleep(100);
        return kletka;
    }
    return {0, 0};
}
