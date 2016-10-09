#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <fcntl.h>
#include "myFile.h"
#include <iostream>
#include "WindowMenu.h"
#include "fileHandler.h"

using namespace std;

bool menu1(myFile & file){
  WindowMenu wm(LINES,COLS);
  wm.displayWindowMenu();
  int userMenuChoice = wm.getUserMenuChoice();
  fileHandler fh(LINES,COLS);

  switch(userMenuChoice){
      case 0: //Open
	fh.openFile();
	mvprintw(LINES-1,2,"%s",(fh.getFileName()).c_str()); //show open file name in bottom left corner
	refresh();
	file.~myFile();
	file = myFile(fh.getFileName());
	//file.setFileAndPath(fh.getFileName());
	break;
      case 1: //Save
	if(fh.hasOpenedFile()){ //true if a file was previously opened
	  fh.saveFile();
	}else{
	  fh.saveAsFile(); //automatically call Save As if no file was opened
	} //else
	break;
      case 2: //Save As
	fh.saveAsFile();
	break;
      case 3: //Exit
	return true; //break out of the loop and terminate program
	break;
      } //switch


  return false;
}//menu

void cycle(string input){
  //WindowMenu wm(LINES,COLS);
  myFile file = myFile("myFile.cpp");

  initscr();
  cbreak();
  keypad(stdscr, TRUE);

  //WINDOW * boarderWindow;
  //boarderWindow = newwin(LINES-2,COLS-2,2,2);
  //box(boarderWindow,0,0);
  //wrefresh(boarderWindow);  
  
  WINDOW * boarderWindow;
  WINDOW * contentWindow;
  boarderWindow = newwin(LINES-2,COLS-2,2,2);
  contentWindow = newwin(LINES-4,COLS-4,3,3);
  noecho();

  //wm.displayWindowMenu();
  //int stuff = wm.getUserMenuChoice();

  bool breakout = false;
  while(!breakout){

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
      breakout = ::menu1(file);
      break;
    default:
      file.insertChar((char)ch);
      break;
    }//switch
  }//while
  //delwin(contentWindow);

  endwin();
}//cycle

int main(){
   string file = "";
  ::cycle(file);
  
  return 0;
}//main
