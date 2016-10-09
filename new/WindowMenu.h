#ifndef WINDOWMENU_H
#define WINDOWMENU_H
#include <iostream>
#include <ncurses.h>

class WindowMenu {

 public:
  WindowMenu(int height, int width);
  ~WindowMenu();
  void displayWindowMenu();
  int getUserMenuChoice();

 private:
  WINDOW *menuWindow;
  int userMenuChoice, keyIn;
  char menuOptions[4][9] = {"Open","Save","Save As","Exit"}; //9 because our longest string is 9 chars long
  char item[9]; //will be used for temp storage of menuOptions
}; //WindowMenu

#endif
