#include "grid.h"

Grid::Grid(){
  vector<string> row;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0 ; j < 4; j++)
      row.push_back("0");
    Game_map.push_back(row);
    row.clear();
  }
  score = 0;
  print();
}
void Grid::update_map(vector<string> new_frame) {
  int row;
  int column;
  for(int i = 0 ; i < new_frame.size(); i += 2)
  {  
    transform(new_frame[i],row,column);
    Game_map[row][column] = memToNum(new_frame[i+1]);
  }
  print();
} 
void Grid::transform(string num,int& row, int& column)
{
  if(num =="1")
  {
    row = 0;
    column = 0;
  }
  if(num == "2")
  {
    row = 0;
    column = 1;
  }
  if(num == "3")
  {
    row = 0; 
    column = 2;
  }
  if(num == "4")
  {
    row = 0; 
    column = 3;
  }
  if(num == "5")
  {
    row = 1;
    column = 0;
  }
  if(num == "6")
  {
    row = 1;
    column = 1;
  }
  if(num == "7")
  {
    row = 1;
    column = 2;
  }
  if(num == "8")
  {
    row = 1;
    column = 3;
  }
  if(num == "9")
  {
    row = 2;
    column = 0;
  }
  if(num == "10")
  {
    row = 2;
    column = 1;
  }
  if(num == "11")
  {
    row = 2;
    column = 2;
  }
  if(num == "12")
  {
    row = 2;
    column = 3;
  }
  if(num == "13")
  {
    row = 3;
    column = 0;
  }
  if(num == "14")
  {
    row = 3;
    column = 1;
  }
  if(num == "15")
  {
    row = 3;
    column = 2;
  }
  if(num == "16")
  {
    row = 3;
    column = 3;
  }
}
void Grid::getGrid(vector<int>& Frame)
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      Frame.push_back(stoi(Game_map[i][j]));
    }
  }
}
void Grid::possible(vector<bool>& moves)
{
  bool vertical = false;
  bool horizontal= false;
  bool left = false;
  bool right = false;
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(Game_map[i][j] == Game_map[i+1][j] || Game_map[i+1][j] == "0")
        vertical = true;
      if(Game_map[i][j] == Game_map[i][j+1] || Game_map[i][j+1] == "0")
        horizontal = true;
      if(i ==2)
      {
        if(Game_map[i+1][j] == Game_map[i+1][j+1])
          horizontal = true;
      }
    }
  }
  moves.push_back(horizontal);
  moves.push_back(vertical);
}
void Grid::check_score(vector<bool>& possible)
{
  bool horizontal = false;
  bool vertical = false;
  int num;
  int same;
  //if(horizontal == "up" || command == "down")
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      { 
        vector<int> column;
        int cur_num = stoi(Game_map[i][j]);
        column.push_back(cur_num);
        for(int x = 1; x < 4; x++)
        {
          column.push_back(stoi(Game_map[x][j]));
          if(column[x] ==0)
            vertical = true;
        }
        if(column[0] == column[1] && column[0] != 0)
        {
          same++;
          num = column[0];
        }
        else if(column[0] != column[1] && column[1] == 0 && column[0] == column[2])
        {
          same++;
          num = column[0];
        }
        else if(column[0] != column[1] && column[1] ==0 && column[2] ==0 && column[0] == column[3])
        {
          same++;
          num = column[0];
        }
        else if(column[1] == column[2] && column[1] != 0)
        {
          same++;
          num = column[1];
        }
        else if(column[1] != column[2] && column[2] == 0 && column [1] == column[3])
        {
          same++;
          num = column[1];
        }
        else if(column[2] == column[3] && column[2] != 0)
        {
          same++;
          num = column[2];
        }
        if(same ==1 && num != 0)
          vertical = true;
        /*if(same == 2 && num != 0)
          score += num*4;
        */
        same = 0;
      }
    }   
  }
  //if(command == "left" || command == "right")
  {
    {
      for(int j = 0; j < 4; j++)
      {
        vector<int> row;
        int cur_num = stoi(Game_map[j][0]);
        row.push_back(cur_num);
        for(int x = 1; x < 4; x++)
        {
          row.push_back(stoi(Game_map[j][x]));
          if(row[x] == 0)
            horizontal = true;
        }
        if(row[0] == row[1] && row[0] != 0)
        {
          same++;
          num = row[0];
        }
        else if(row[0] != row[1] && row[1] == 0 && row[0] == row[2])
        {
          same++;
          num = row[0];
        }
        else if(row[0] != row[1] && row[1] == 0 && row[2] == 0 && row[0] == row[4])
        {
          same++;
          num = row[0];
        }
        else if(row[1] == row[2] && row[1] != 0)
        {
          same++;
          num = row[1];
        }
        else if(row[1] != row[2] && row[2] == 0 && row[1] == row[3])
        {
          same++;
          num = row[1];
        }
        else if(row[2] == row[3] && row[1] != 0)
        {
          same++;
          num = row[2];
        }
        if(same ==1 && num != 0)
          horizontal = true;
      same = 0;
      }
    }
  }
  possible.push_back(vertical);
  possible.push_back(horizontal);
}
void Grid::print()
{
  int iter = 0;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
      cout << Game_map[i][j] << " ";
    cout << endl;
  }
  cout << "score: " << score << endl;
  cout << "--------" << endl;
}
string Grid::memToNum(string mem_num)
{
  if(mem_num == "111")
    return "0";
  if(mem_num == "119")
    return "2";
  if(mem_num == "127")
    return "4";
  if(mem_num == "135")
    return "8";
  if(mem_num == "143")
    return "16";
  if(mem_num == "151")
    return "32";
  if(mem_num == "159")
    return "64";
  if(mem_num == "167")
    return "128";
  if(mem_num == "175")
    return "256";
  if(mem_num == "183")
    return "512";
  if(mem_num == "191")
    return "1024";
  if(mem_num == "200")
    return "2048";
  return "not number";
}
/*int main()
{
  Grid* game = new Grid();
  game->print();
  delete game;
  return 0;
}*/


