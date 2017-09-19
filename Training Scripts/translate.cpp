#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	fstream train_in, new_train_in;

	train_in.open(argv[1]);
	new_train_in.open(argv[2]);

	vector<int> grids;
	vector<int> temp;

	int mem_num;

	while(train_in >> mem_num)
		grids.push_back(mem_num);

	int lines = grids.size()/16;

	int count = 0;
	for(unsigned int i = 0; i < grids.size()/16; i++)
	{	
		for(unsigned int j = 0; j < 16; j++)
		{
			if(grids[count] == 111)
				new_train_in << "0 ";
			if(grids[count] == 119)
				new_train_in << "2 ";
			if(grids[count] == 127)
				new_train_in << "4 ";
			if(grids[count] == 135)
				new_train_in << "8 ";
			if(grids[count] == 143)
				new_train_in << "16 ";
			if(grids[count] == 151)
				new_train_in << "32 ";
			if(grids[count] == 159)
				new_train_in << "64 ";
			if(grids[count] == 167)
				new_train_in << "128 ";
			if(grids[count] == 175)
				new_train_in << "256 ";
			if(grids[count] == 183)
				new_train_in << "512 ";
			if(grids[count] == 191)
				new_train_in << "1024 ";
			if(grids[count] == 200)
				new_train_in << "2048 ";
			count++;
		}
		new_train_in << "\n";
	}

	train_in.close();
	new_train_in.close();

}