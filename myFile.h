
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
  uint totalDown;
  // uint wholeFileLength;
  bool justSaved;
  char * filePath;
 public:
  uint wholeFileLength;
  uint numGreatestDown;

  myFile();
  myFile(string filePathIn);
  ~myFile();

  void deMyFile(string filePathIn);
  bool checkPath(string filePathIn);

  string getViewFile();
  bool setFileAndPath(string filePathIn);
  void insertChar(char character);
  char * getFilePath();
  string getLineNums();
  char * getWholeFile();

  void incDown();
  void decDown();
  void setDown(int down);
  uint getDown();
  
  void incRight();
  void decRight();
  void setRight(int right);
  uint getRight();
 
  void saveAs(string name);
  void saveAs();
  bool isSaved();
};//myFile

#endif
