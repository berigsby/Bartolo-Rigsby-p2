#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <ncurses.h>
#include <string>
#include <iomanip>

using namespace std;

class Window {

 public:
  Window(int theHeight, int theWidth);
  ~Window();
  const int getHeight();
  const int getWidth();
  void updateWindow(string windowContent);
  int getPadHeight(string content, int padWidth);

 private:
  int height;
  int width;
  WINDOW *fileWindow;

}; //Window

#endif
