#include "Bot.h"

Bot::Bot(direction storona1, int heals1, int count_shots1, int armor1, bool alive1, RenderWindow &window) : Object(storona1, heals1, count_shots1, armor1, alive1, window) {;}

bool Bot::prov(int x, int y, vector < vector <char> > &pole, bool prov_bull)
{
    bool t=true;   // if(x>3 && x<width && y>3 && y<length)
    if(!prov_bull) {for(int i=x-1; i<=x+1; i++) for(int j=y-1; j<=y+1; j++) if(x>3 && x<width && y>3 && y<length && pole[i][j]!=' ' && pole[i][j]!='+' && pole[i][j]!='*' && pole[i][j]!='.') t=false;}
    else {for(int i=x-1; i<=x+1; i++) for(int j=y-1; j<=y+1; j++) if(x>3 && x<width && y>3 && y<length && pole[i][j]!=' ' && pole[i][j]!='*' && pole[i][j]!='.') t=false;}
    return t;
}

void Bot::find_path(int row, int col, vector < vector <char> > &pole, bool ( &visited )[107][203], int ( &path )[107][203], queue<pair<int, int>>& plan, bool path_bull)
{
    if(!path_bull) {
        if(!visited[row][col])
        {
            // проверяем не вышли ли мы за границы лабиринта, есть ли клетка в массиве посещенных и можно ли через нее пройти
            if ((row+1) < width && (row+1) >= 3 && !visited[row+1][col] && (pole[row+1][col] == ' ' || pole[row+1][col] == '+' || pole[row+1][col] == '*' || pole[row+1][col] == '.') && prov(row+1, col, pole, path_bull))
            {
                path[row+1][col] = path[row][col] + 1;
                plan.push({row+1, col});
            }
            if((row-1) < width && (row-1) >= 3 && !visited[row-1][col] && (pole[row-1][col] == ' ' || pole[row-1][col] == '+' || pole[row-1][col] == '*' || pole[row-1][col] == '.') && prov(row-1, col, pole, path_bull))
            {
                path[row-1][col] = path[row][col] + 1;
                plan.push({row-1, col});
            }
            if((col + 1) < length && (col + 1) >= 3 && !visited[row][col+1] && (pole[row][col+1] == ' ' || pole[row][col+1] == '+' || pole[row][col+1] == '*' || pole[row][col+1] == '.') && prov(row, col+1, pole, path_bull))
            {
                path[row][col+1] = path[row][col] + 1;
                plan.push({row, col+1});
            }
            if((col - 1) < length && (col - 1) >= 3 && !visited[row][col-1] && (pole[row][col-1] == ' ' || pole[row][col-1] == '+' || pole[row][col-1] == '*' || pole[row][col-1] == '.') && prov(row, col-1, pole, path_bull))
            {
                path[row][col-1] = path[row][col] + 1;
                plan.push({row, col-1});
            }
            visited[row][col] = true; 
        }
    }
    else
    {
        if(!visited[row][col])
        {
            // проверяем не вышли ли мы за границы лабиринта, есть ли клетка в массиве посещенных и можно ли через нее пройти
            if ((row+1) < width && (row+1) >= 3 && !visited[row+1][col] && (pole[row+1][col] == ' ' || pole[row+1][col] == '*' || pole[row+1][col] == '.') && prov(row+1, col, pole, path_bull))
            {
                path[row+1][col] = path[row][col] + 1;
                plan.push({row+1, col});
            }
            if((row-1) < width && (row-1) >= 3 && !visited[row-1][col] && (pole[row-1][col] == ' ' || pole[row-1][col] == '*' || pole[row-1][col] == '.') && prov(row-1, col, pole, path_bull))
            {
                path[row-1][col] = path[row][col] + 1;
                plan.push({row-1, col});
            }
            if((col + 1) < length && (col + 1) >= 3 && !visited[row][col+1] && (pole[row][col+1] == ' ' || pole[row][col+1] == '*' || pole[row][col+1] == '.') && prov(row, col+1, pole, path_bull))
            {
                path[row][col+1] = path[row][col] + 1;
                plan.push({row, col+1});
            }
            if((col - 1) < length && (col - 1) >= 3 && !visited[row][col-1] && (pole[row][col-1] == ' ' || pole[row][col-1] == '*' || pole[row][col-1] == '.') && prov(row, col-1, pole, path_bull))
            {
                path[row][col-1] = path[row][col] + 1;
                plan.push({row, col-1});
            }
            visited[row][col] = true; 
        }
    }
}

bool Bot::find_direction(vector < vector <char> > &pole, int x, int y)
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
  plan.push({current_x, current_y});
  
  while(!plan.empty())
  {
    kletka=plan.front();
    plan.pop();
    int x = kletka.first;
    int y = kletka.second;
    
    find_path(x, y, pole, visited, path, plan, false);
    
  }
  
  if(!visited[x_end][y_end]) return false;
  else 
  {
    int x = x_end;
    int y = y_end;
    int count=0;
    while (path[x][y] != 2 && count<length*width) 
    { // восстановление пути
        if ((x-1) >= 0 && (x-1) < width && (path[x-1][y] == path[x][y] - 1))  { x = x-1; steck.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/} else
        if ((x+1) >= 0 && (x+1) < width && (path[x+1][y] == path[x][y] - 1))  { x = x+1; steck.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/} else
        if ((y-1) >= 0 && (y-1) < length && (path[x][y-1] == path[x][y] - 1)) { y = y-1; steck.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/} else
        if ((y+1) >= 0 && (y+1) < length && (path[x][y+1] == path[x][y] - 1)) { y = y+1; steck.push({x, y}); /*if(current_x!=x_start || current_y!=y_start) pole[x][y]='.';*/}
        count++;
    }
    if(path[x][y]!=2) return false;
    return true;
  }
}

pair<int, int> Bot::Oblast_vidimosti(vector < vector <char> > &pole, int bot_x, int bot_y, int player_x, int player_y)
{
    //создаем 4 линии - квадрат вокруг бота, кадая из этих 4 линий движется в одном из 4 направлений N количество раз (зависит от уровня)
    //координаты: bot_x-2; bot_y-2            bot_x-2; bot_y+2
    //            bot_x+2; bot_y-2            bot_x+2; bot_y+2
    for(int i=-1; i<2; i=i+2)//ошибка т.к. учли только хороший вариант
    { 
        int x1=bot_x-2, x2=bot_x+2, y1=bot_y-2, y2=bot_y+2;
        if(pole[x1][y1]=='#') {x1++; x2++;}     if(pole[x1][y1]=='#') {x1++; x2++;}     if(pole[x2][y1]=='#') {x1--; x2--;}     if(pole[x2][y1]=='#') {x1--; x2--;}
        if(pole[x1][y2]=='#') {x1++; x2++;}     if(pole[x1][y2]=='#') {x1++; x2++;}     if(pole[x2][y2]=='#') {x1--; x2--;}     if(pole[x2][y2]=='#') {x1--; x2--;}
        while(y2>2 && y2<length && pole[x1][y2]!='#') y2+=i;
        storona=Right;
        if(i<0) {y1=y2; y2=bot_y-2; storona=Left;}
        if(player_x>=x1 && player_x<=x2 && player_y>=y1 && player_y<=y2) { see_player=true; return { player_x, player_y}; }
    }
    for(int i=-1; i<2; i=i+2)
    {
        int x1=bot_x-2, x2=bot_x+2, y1=bot_y-2, y2=bot_y+2;
        if(pole[x1][y1]=='#') {y1++; y2++;}     if(pole[x1][y1]=='#') {y1++; y2++;}     if(pole[x1][y2]=='#') {y1--; y2--;}     if(pole[x1][y2]=='#') {y1--; y2--;}
        if(pole[x2][y1]=='#') {y1++; y2++;}     if(pole[x2][y1]=='#') {y1++; y2++;}     if(pole[x2][y2]=='#') {y1--; y2--;}     if(pole[x2][y2]=='#') {y1--; y2--;}
        while(x2>2 && x2<width && pole[x2][y1]!='#') x2+=i;
        storona=Down;
        if(i<0) {x1=x2; x2=bot_x-2; storona=Up;}
        if(player_x>=x1 && player_x<=x2 && player_y>=y1 && player_y<=y2) { see_player=true; return { player_x, player_y}; }
    }
    see_player=false;
    return {0, 0};
}