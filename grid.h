#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <fstream>
#include "ann_V2.h"
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
class Grid
{
  public:
    Grid();
    void update_map(vector<string>);
    void print();
    void check_score(vector<bool>&); 
    void transform(string,int&,int&); 
    void getGrid(vector<int>&);
    void possible(vector<bool>&);
    string memToNum(string);
  private:
    vector<vector<string> >Game_map;
    int score;
};
#endif
