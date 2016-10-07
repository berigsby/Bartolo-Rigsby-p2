
#ifndef MYFILE
#define MYFILE

#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <fcntl.h>

using namespace std;
typedef unsigned int uint;

class myFile{
  bool hasFilePath;
  char * wholeFile;
  uint numDown;
  uint numRight;
  char * filePath;
 public:
  myFile();
  myFile(string filePathIn);
  ~myFile();

  bool checkPath(string filePathIn);

  string getViewFile();
  bool setFileAndPath(string filePathIn);
  void insertChar(char character);

  void incDown();
  void decDown();
  void setDown(int down);
  uint getDown();
  
  void incRight();
  void decRight();
  void setRight(int right);
  uint getRight();
  
};//myFile

#endif
