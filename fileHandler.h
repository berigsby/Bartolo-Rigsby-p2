#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <locale>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

class fileHandler {

 public:
  fileHandler(int theHeight, int theWidth);
  ~fileHandler();
  void saveFile();
  void saveAsFile();
  string openFile();
  void displayErrorWindow(string theErrorMessage);
  bool file_exists(const string& name);
  string getFileName();
  bool hasOpenedFile();

 private:
  WINDOW *fileWindow;
  char fileName[50];
  ifstream openedFile;
  int height;
  int width;
  bool openSuccess = false;
}; //fileHandler

#endif
