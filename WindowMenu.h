#ifndef WINDOWMENU_H
#define WINDOWMENU_H
#include <iostream>
#include <ncurses.h>

class WindowMenu {

 public:

  /**
   * Constructor of the WindowMenu
   *
   * @param height the height of ncurses
   * @param width the width of ncurses
   */
  WindowMenu(int height, int width);

  /**
   * Displays the Window choice menu for when F1 is clicked
   */
  void displayWindowMenu();

  /**
   * Gets the user choic
   *
   * @return int 0 for open, 1 for save, 2 for saveAs, 3 for exit
   */
  int getUserMenuChoice();

 private:
  WINDOW *menuWindow;
  int userMenuChoice, keyIn;
  char menuOptions[4][9] = {"Open","Save","Save As","Exit"}; //9 because our longest string is 9 chars long
  char item[9]; //will be used for temp storage of menuOptions
}; //WindowMenu

#endif
