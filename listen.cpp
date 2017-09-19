#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "grid.h"
//#include "ann_files/ann_V2.h"
using std::cout;
using std::ifstream;
using std::string;
using std::endl;
using std::vector;
using std::ofstream;
using std::cin;
int main(int argc, char* argv[])
{
  ofstream out;
  //out.close();
	ANN ann;
  ann.import_structure(argv[1],argv[2]);
  ann.in_Encoding(argv[4]);
  ann.train(argv[3],argv[5],argv[6],argv[7]);
  Grid* gameGrid = new Grid();
  vector<string> last_one;
	bool the_same = false;
  vector<int> Frame;
  vector<int> direc;
  vector<bool> possible;
  int iter = 0;
  int prev_choice = 100;
  int choice;
  int same_frame_iter = 0;
  while(true)
  {
    choice = NULL;
    Frame.clear();
    possible.clear();
    out.open("commands.txt");
	  the_same = false;
	  vector<string> sequence;
	  const char* filename = "Changes.txt";
	  ifstream inf;
	  string lines;
	  int num_lines;
    string answer;
    inf.open(filename);
    while(iter == 0 && inf >> lines)
      sequence.push_back(lines);
    if(iter ==0)
      gameGrid->update_map(sequence);
    inf.clear();
    inf.seekg(0,std::ios::beg);
    sequence.clear();
    gameGrid->getGrid(Frame);
    gameGrid->possible(possible);
    //gameGrid->possible(possible);
    choice = ann.classify(Frame,possible);
    if(choice == prev_choice && Frame == direc)
    {
      same_frame_iter++;
      if(choice == 0 && same_frame_iter == 3)
        choice = 1;
      else if(choice == 1 && same_frame_iter == 3)
        choice = 0;
      else if(choice == 2 && same_frame_iter == 3)
        choice = 3;
      else if(choice == 3 && same_frame_iter == 3)
        choice = 2;
      if(same_frame_iter == 10)
        same_frame_iter = 0;
    }
    prev_choice = choice;
    direc = Frame;
    cout << "choose direction" << endl;
    //cin >> answer;
    //gameGrid->check_score(answer);
    if(choice == 0)
      out << "up";
    if(choice == 1)
      out << "down";
    if(choice == 2)
      out << "left";
    if(choice == 3)
      out << "right";
	  out.close();
    bool loop = true;
    if(last_one.size() == 0)
      last_one = sequence;
	  sequence.clear();
    std::chrono::milliseconds dura(250);
	  std::this_thread::sleep_for(dura);
	  while(inf>> lines)
    {
		  num_lines++;
		  sequence.push_back(lines);
	  }
    if(sequence != last_one)
    {
      //cout << "not equal" << endl;
      loop = false;
    }
    inf.clear();
	  inf.seekg(0,std::ios::beg);
    gameGrid->update_map(sequence);
    last_one = sequence;
    //cout << "broke out of loop" << endl;
    inf.clear();
    inf.seekg(9,std::ios::beg);
    iter++;
  }
  delete gameGrid;
  return 0;
}

