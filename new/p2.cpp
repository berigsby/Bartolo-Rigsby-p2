#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <fcntl.h>
#include "myFile.h"
#include <iostream>

using namespace std;
/*
bool toListen(myFile file){
  int ch;
  ch = getch();
  //while((ch = getch()) != KEY_F(1)){
    switch(ch){
	case KEY_UP:
	  file.decDown();
	  break;
	case KEY_DOWN:
	  file.incDown();
	  break;
        case KEY_LEFT:
	  file.decRight();
	  break;
        case KEY_RIGHT:
	  file.incRight();
	  break;
        case KEY_F(1):
	  break;
        default:
	  file.insertChar((char)ch);
	  return true;
	  break;
    }//switch
    return false;
    //}//while
}//listen

int mainWindow(myFile file){
  clear();
  WINDOW * boarderWindow;
  WINDOW * contentWindow;
  boarderWindow = newwin(LINES-2,COLS-2,2,2);
  contentWindow = newwin(LINES-8,COLS-8,4,4);
  box(boarderWindow,0,0);
  wrefresh(boarderWindow);
  waddstr(contentWindow,(file.getViewFile()).c_str());
  wrefresh(contentWindow);
  wmove(contentWindow, 0, file.getRight());
  wrefresh(contentWindow);
  return wgetch(contentWindow);
}//mainWindow
*/
int main(){
  myFile file = myFile("p2.cpp");

  initscr();
  cbreak();
  keypad(stdscr, TRUE);

  WINDOW * boarderWindow;
  WINDOW * contentWindow;
  boarderWindow = newwin(LINES-2,COLS-2,2,2);
  contentWindow = newwin(LINES-4,COLS-4,3,3);
  noecho();

  while(true){

    wclear(contentWindow);
    box(boarderWindow,0,0);
    wrefresh(boarderWindow);
    wprintw(contentWindow,(file.getViewFile()).c_str());
    wrefresh(contentWindow);
    wmove(contentWindow, 0, file.getRight());
    wrefresh(contentWindow);

    int ch = getch();

    switch(ch){
    case KEY_UP:
      file.decDown();
      break;
    case KEY_DOWN:
      file.incDown();
      break;
    case KEY_LEFT:
      file.decRight();
      break;
    case KEY_RIGHT:
      file.incRight();
      break;
    case KEY_F(1):
      return 0;
      break;
    default:
      file.insertChar((char)ch);
      break;
    }//switch
  }//while
  endwin();
  return 0;
}//main
