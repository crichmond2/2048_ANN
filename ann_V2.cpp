#include "ann_V2.h"

/**
  *\brief prints out the weights for the first node in the input layer
  */
void ANN::print()
{
  for(auto it = Neural_net[0][0]->to_nodes.begin(); it!=Neural_net[0][0]->to_nodes.end(); it++)
  {
    cout << showpoint << fixed << setprecision(12) << it->second << " ";
  }
  cout << endl;
}
/**
  *\brief Destructor for each node in the Neural Network
  */
ANN::~ANN()
{
  for(unsigned int i = 0; i < Neural_net.size(); i++)
  {
    for(unsigned int j = 0; j < Neural_net[i].size(); j++)
    {
      delete Neural_net[i][j];
    }
  }
}
/**
  * /param in_structure: file name for Neural Net structure
  *        in_weights: file name for Neuron weights 
  * /brief imports the Neural Net
  *  We first create the nodes necessary for each layer
  *  then reads in the weights and assigns them to the map for each node
  *  each weight for the nodes to a node and from a node
  */
void ANN::import_structure(char* in_structure,char* in_weights)
{
  ifstream ins;
  ifstream inw;
  ins.open(in_structure);
  inw.open(in_weights);
  int num_nodes;
  vector<double> weights;
  while(ins >> num_nodes)
  {
    vector<Nodes*> n_layer;
    for(int i = 0; i < num_nodes; i++)
    {
      Nodes* node = new Nodes;
      n_layer.push_back(node);
    }
    Neural_net.push_back(n_layer);
  }
  double weight;
  while(inw >> weight)
    weights.push_back(weight);
  int num = 0;
  int Num = 0;
  for(unsigned int i = 0; i < Neural_net.size(); i++)
  {
    for(unsigned int j = 0; j < Neural_net[i].size(); j++)
    {
      if(i+1 == Neural_net.size())
        Neural_net[i][j]->to_nodes[nullptr] = 0.01;
      for(unsigned int x = 0; x < Neural_net[i+1].size(); x++)
      {
        if(i+1 == Neural_net.size())
        {
          Neural_net[i][j]->to_nodes[nullptr] = 0.01;
          break;
        }
        if(x==0&&i!=0)
          Neural_net[i][j]->to_nodes[nullptr] = 0.01;
        if(i < Neural_net.size()-1)
        {
          Neural_net[i][j]->to_nodes[Neural_net[i+1][x]] = weights[num];
          Neural_net[i][j]->weights.push_back(weights[num]);
          num++;
        }
      }
      if(i > 0)
      {
        for(unsigned int a = 0; a < Neural_net[i-1].size(); a++)
        {
          Neural_net[i][j]->from_nodes[Neural_net[i-1][a]] = Neural_net[i-1][a]->weights[j];
          Num++;
        }
      }
    }
  }
  ins.close();
  inw.close();
}
/**
  * \brief Trains the weights from node to node 
  * \param in_train: File name for the training data sets
  *        out_train: File name for the training output for each data set
  *        alpha: the alpha used to update weights
  *        iterations: The number of iterations for training the Neural Network
  */
void ANN::train(char* in_train,char* out_train,char* alpha,char* iterations)
{
  ifstream inf;
  ifstream of;
  int number = atoi(iterations);
  double Alpha = atof(alpha);
  inf.open(in_train);
  of.open(out_train);
  string line;
  while(getline(inf,line))
  {
    num_lines++;
  } 
  for(int iter = 0; iter < number; iter++)
  {
    //cout << iter << endl;
    inf.clear();
    inf.seekg(0,std::ios::beg);
    of.clear();
    of.seekg(0,std::ios::beg);
    for(int p = 0 ; p < num_lines; p++)
    {
      vector<double> init_a;
      double inV;
      for(unsigned int i = 0; i < Neural_net[0].size(); i++)
      {
        inf >> inV;
        Neural_net[0][i]->a_value = inV;
      }
      int train_output;
      of >> train_output;
      for(unsigned int i = 1; i < Neural_net.size(); i ++)
      {
        for(unsigned int j = 0; j < Neural_net[i].size(); j++)
        {
          long double temp_in = 0;
          int x = 0;
          for(auto it = Neural_net[i][j]->from_nodes.begin(); it != Neural_net[i][j]->from_nodes.end(); it++)
          {
            Nodes* cur_node = it->first;
            if(x == 0)
            {
              auto iter = Neural_net[i][j]->to_nodes.find(nullptr);
              temp_in += 1*iter->second;
              x++;
            }
              temp_in += cur_node->a_value * it->second;
          }
          Neural_net[i][j]->in = temp_in;
          Neural_net[i][j]->a_value = a_Converter(Neural_net[i][j]->in); 
        }
      }
      //step 4 Error checking
      assign_OutDelta(out_train,train_output);
      //step 5 Delta for other nodes
      assign_InnerDelta();
      //step 7 Update Weights
      update_Weights(Alpha);    
    }
  }
}
/**
  *\brief Classifies the testing data set using Euclidean Distance
  *\param test_in: Name of file with testing data sets
  *       test_out: Name of file with the expected ouput for the testing data sets
  */
int ANN::classify(vector<int> Frame,vector<bool> possible)
{
  
  //ifstream infile;
  ifstream ofile;
  //infile.open(test_in);
  ofile.open("2048_TrainingDataOutput.txt");
  double in_value;
  string line;
  int num_lines = 1;
  int p = 0;
  //while(getline(infile,line))
   // num_lines++;
  //infile.clear();
  //infile.seekg(0,std::ios::beg);
  for(p = 0; p < 1; p++) //Needs the size of the input file AKA FIGURE IT OUT
  {
    for(unsigned int x = 0; x < Neural_net[0].size(); x++)
    {
      //infile >> in_value;
      Neural_net[0][x]->a_value = Frame[x];
    }
    int result = 3;
    //ofile >> result;
    //ofile >> result;
    for(unsigned int i = 1; i < Neural_net.size(); i++)
    {
      for(unsigned int j = 0; j < Neural_net[i].size(); j++)
      {
        long double temp_in = 0;
        for(auto it = Neural_net[i][j]->from_nodes.begin(); it != Neural_net[i][j]->from_nodes.end();it++)
        {
          Nodes* cur_node = it->first;
          if(cur_node == Neural_net[i][j]->from_nodes.begin()->first)
          {
            auto iter = Neural_net[i][j]->to_nodes.find(nullptr);
            temp_in += 1*iter->second;
          }
          temp_in += cur_node->a_value * it->second;
        }
        Neural_net[i][j]->in = temp_in;  
        Neural_net[i][j]->a_value = a_Converter(Neural_net[i][j]->in);
      }
    }

    int classification = Euclidean_distance(result,possible);
    if(classification == result)
      precision++;
    cout << classification << endl;
    return classification;
  }
  cout << precision/num_lines << endl;
}
/**
  *brief Calculates the Euclidean Distance for the given test query
  * First it calculates the Euclidean distance for all numbers in the encoding
  * sequence and then classifies the query to the closest value
  */
int ANN::Euclidean_distance(int result,vector<bool> possible)
{
  //ifstream of;
  //of.open(test_out);
  //int result;
  //of >> result;
  vector<double> Encoded_values;
  double summation = 0;
  bool horizontal;
  bool vertical;
  horizontal = possible[0];
  vertical = possible[1];
  for(unsigned int x = 0; x < encoding_table.size(); x++)
  {
    summation = 0; 
    for(unsigned int i = 0; i < encoding_table[x].size(); i++)
      summation += pow(encoding_table[x][i] - Neural_net[Neural_net.size()-1][i]->a_value,2);
    summation = sqrt(summation);
    Encoded_values.push_back(summation);
  }
  int classification = 0;
  double check = 100;
  if(vertical == 1 && horizontal == 1)
  {
    for(unsigned int i = 0; i < Encoded_values.size(); i++)
    {
      if(Encoded_values[i] < check )
      {
        classification = i;
        check = Encoded_values[i];
      }
    }
  }
  if(vertical == 1 && horizontal == 0)
    for(int i = 0; i < 2; i++)
    {
      classification = i;
      check = Encoded_values[i];
    }
  if(vertical == 0 && horizontal ==1)
    for(int i = 2; i < 4; i++)
    {
      classification = i;
      check = Encoded_values[i];
    }
  return classification; 
}
/**
  *\brief Converts the given value into its a value for the node
  * Uses the equation 1/1+e^-x to calculate
  *\param in_value : Value given to the converter function
  */
double ANN::a_Converter(long double in_value)
{
  in_value *= -1;
  double result = 1/(1+exp(in_value));
  return result;
}
/**
  *\brief Assigns all of the delta values for the output layer
  *\param out_train: the name of the ouput file for the training data
  */
void ANN::assign_OutDelta(char* out_train,int result)
{
  ifstream inf;
  inf.open(out_train);
  for(unsigned int i = 0; i < Neural_net[Neural_net.size()-1].size(); i++)
  {
    Nodes* cur_node = Neural_net[Neural_net.size()-1][i];
    double error = cur_node->a_value*(1-cur_node->a_value)*(encoding_table[result][i] - cur_node->a_value);
    Neural_net[Neural_net.size()-1][i]->delta = error;
  }
}
/**
  *\brief Assigns the delta values for all of the hidden layers
  */
void ANN::assign_InnerDelta()
{
  for(int i = Neural_net.size()-2; i >= 0; i--)
  {
    for(unsigned int j = 0; j < Neural_net[i].size(); j++)
    {
      Nodes* cur_node = Neural_net[i][j];
      double error;
      double summation = 0;
      for(auto it = cur_node->to_nodes.begin(); it != cur_node->to_nodes.end(); it++)
      {
        if(it->first == nullptr)
        {
          continue;
        }
        summation += it->first->delta * it->second;
        //contin:;
      }
      error = cur_node->a_value * (1-cur_node->a_value) * summation;
      cur_node->delta = error;
    }
  }
}
/**
  *\brief Updates the weights for all nodes in the Neural Network
  *       First we get the nodes and weights for the nodes coming from the 
  *       one we're looking at. Then assigns the updated weights for the current
  *       nodes from_nodes list and also the previous nodes to_nodes list
  *\param alpha: The small alpha value to alter the given weights value
  */
void ANN::update_Weights(double alpha)
{
  for(unsigned int i = 1; i < Neural_net.size(); i++)//i < Neural)net.size()-1
  {
    for(unsigned int j = 0; j < Neural_net[i].size(); j++)
    {
      Nodes* cur_node = Neural_net[i][j];
      for(auto it = cur_node->from_nodes.begin(); it != cur_node->from_nodes.end(); it++)
      {
        if(it->first == cur_node->from_nodes.begin()->first)
        {
          auto iter = cur_node->to_nodes.find(nullptr);
          iter->second = iter->second + alpha*1*cur_node->delta;
        }
        it->second = it->second + alpha*it->first->a_value*cur_node->delta;
        it->first->to_nodes[cur_node] = it->second;
      }
    }
  }
}
/**
  *\brief Reads in the encoding table and assigns the value into a 2D vector
  *\param enc_file : The name of the file that the encoding table is in
  */
void ANN::in_Encoding(char* enc_file)
{
  ifstream inf;
  inf.open(enc_file);
  string number;
  string indv_out;
  while(getline(inf,number))
  {
    stringstream ss(number);
    vector<double> out;
    while(getline(ss,indv_out,' '))
     out.push_back(stod(indv_out));
    encoding_table.push_back(out);
  }
  inf.close();
}   
