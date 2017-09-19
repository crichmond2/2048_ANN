#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ofstream file, file2;//, file3;
  int count = 0;
  //file3.open("ygrids.txt");
  while(1)
  {
    char c;
    cin >> c;
    if(c == 'w')
    {
      file.open("commands.txt");
      file << 0;
      file.close();
      file2.open("check.txt");
      file2 << count;
      file2.close();
      count++;
      //file3 << 0 << endl;
    }
    if(c == 'a')
    {
      file.open("commands.txt");
      file << 2;
      file.close();
      file2.open("check.txt");
      file2 << count;
      file2.close();
      count++;
      //file3 << 2 << endl;
    }
    if(c == 's')
    {
      file.open("commands.txt");
      file << 1;
      file.close();
      file2.open("check.txt");
      file2 << count;
      file2.close();
      count++;
      //file3 << 1 << endl;
    }
    if(c == 'd')
    {
      file.open("commands.txt");
      file << 3;
      file.close();
      file2.open("check.txt");
      file2 << count;
      file2.close();
      count++;
      //file3 << 3 << endl;
    }
    if(c == 'x')
    {
      return 0;
    }
  }
}