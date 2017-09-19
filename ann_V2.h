#ifndef ANN_V2_H
#define ANN_V2_H
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <math.h>
#include <sstream>
#include <string>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::string;
using std::stringstream;
using std::map;
using std::stod;
using std::setprecision;
using std::fixed;
using std::showpoint;
class ANN
{
  public:
    //ANN();
    ~ANN();
    void import(char*);
    void import_structure(char*,char*);
    void train(char*,char*,char*,char*); 
    void in_Encoding(char*);
    double a_Converter(long double);
    void assign_OutDelta(char*,int);
    void assign_InnerDelta();
    void update_Weights(double);
    void print();
    int classify(vector<int> Frame,vector<bool>);
    int Euclidean_distance(int,vector<bool>);
  private:
    struct Nodes
    {
      vector<long double>weights;
      //vector<Nodes*> to_nodes;
      map<Nodes*,long double> to_nodes;
      map<Nodes*,long double> from_nodes;
      double a_value;
      long double in;
      double delta;
    };
    vector<vector<double> > encoding_table;
    vector< vector<Nodes*> >  Neural_net;
    double precision = 0;
    int num_lines = 0;
};
#endif
