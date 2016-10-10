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
  string fn;

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
 
  switch(userMenuChoice){
      case 0: //Open

	fh.openFile();
	clear();
	mvprintw(LINES-1,2,"%s",(fh.getFileName()).c_str()); //show open file name in bottom left corner
	mvprintw(0,2,"%s",instructions); //keep visible at top left corner
	mvprintw(0,(COLS-strlen(title))/2,"%s",title);
	refresh();
	noecho();
	file.deMyFile(fh.getFileName());
	//w.updateWindow(fh.getFileName());
	break;
      case 1: //Save
	file.saveAs();
	break;
      case 2: //Save As
	file.saveAs(fh.saveAsFile());
	break;
      case 3: //Exit
	return true; //break out of the loop and terminate program
	break;
      } //switch


  return false;
}//menu

void cycle(string input){
  myFile file;
  bool firstfirst = true;
  if(input != ""){
    firstfirst = false;
    file = myFile(input);
  }//if
  //myFile file;// = myFile("myFile.cpp");

  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  WINDOW * boarderWindow;
  WINDOW * contentWindow;
  boarderWindow = newwin(LINES-2,COLS-2,1,1);
  contentWindow = newwin(LINES-4,COLS-4,2,2);
  noecho();

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
  mvprintw(0,2,"%s",instructions); //keep visible at top left corner
  mvprintw(0,(COLS-strlen(title))/2,"%s",title);
  refresh();


  bool breakout = false;
  bool first = true;
  while(!breakout){
    curs_set(1);
    wclear(contentWindow);
    box(boarderWindow,0,0);
    wrefresh(boarderWindow);
    wprintw(contentWindow,(file.getViewFile()).c_str());
    wrefresh(contentWindow);
    int vertm = (file.getDown() - (file.numGreatestDown - LINES+5));

    wmove(contentWindow, vertm, file.getRight());
    wrefresh(contentWindow);

    int ch;
    if(firstfirst){
      ch = KEY_F(1);
      firstfirst = false;
    }else if(first){
      ch = KEY_UP;
      first = false;
    }else {
      ch = getch();
    }
   
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

  endwin();
}//cycle

int main(int argc, char * argv[]){
   string file = "";
   if(argc == 2){
     string file2(argv[1]);
     ::cycle(file2);
   }else{
     ::cycle(file);
   }//else
   return 0;
}//main
