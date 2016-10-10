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

bool menu1(myFile & file, fileHandler & fh){
  WindowMenu wm(LINES,COLS);
  wm.displayWindowMenu();
  int userMenuChoice = wm.getUserMenuChoice();
  
  //fileHandler fh(LINES,COLS);
  string fn;

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
  noecho();//
  switch(userMenuChoice){
      case 0: //Open

	fh.openFile("");
	if(!file.isSaved()){
	  if(fh.wouldYouLikeToSave()){
	    file.saveAs();
	  }//if
	}//if
	clear();
	mvprintw(LINES-1,2,"%s",(fh.getFileName()).c_str()); //show open file name in bottom left corner
	mvprintw(0,2,"%s",instructions); //keep visible at top left corner
	mvprintw(0,(COLS-strlen(title))/2,"%s",title);
	refresh();
	noecho();
	//if(!file.isSaved()){
	//  if(fh.wouldYouLikeToSave()){
	//    file.saveAs();
	//  }//if
	//}//if
	file.deMyFile(fh.getFileName());
	//w.updateWindow(fh.getFileName());
	break;
      case 1: //Save
	file.saveAs();
	noecho();
	break;
      case 2: //Save As
	//file.saveAs(fh.saveAsFile());
	fh.saveAsFile(file.getWholeFile(),file.wholeFileLength);
	noecho();
	break;
      case 3: //Exit
	if(!file.isSaved()){
	  if(fh.wouldYouLikeToSave()){
	    file.saveAs();
	  }//if
	}//if
	return true; //break out of the loop and terminate program
	break;
      } //switch
  return false;
}//menu

void cycle(string input){
  myFile file;
  //fileHandler fh(LINES,COLS);
  bool firstfirst = true;
  //if(input != ""){
  //  firstfirst = false;
  //  fh.openFile(input);
  //  file.deMyFile(input);
  //}//if
  //myFile file;// = myFile("myFile.cpp");
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  WINDOW * boarderWindow;
  WINDOW * contentWindow;
  WINDOW * numPadWindow;
  boarderWindow = newwin(LINES-2,COLS-2,1,1);
  contentWindow = newwin(LINES-4,COLS-8,2,6);
  numPadWindow = newwin(LINES-4,4,2,2);
  noecho();

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
  mvprintw(0,2,"%s",instructions); //keep visible at top left corner
  mvprintw(0,(COLS-strlen(title))/2,"%s",title);
  mvprintw(LINES-1,2,"%s",input.c_str()); //show open file name in bottom left corner
  refresh();

  box(boarderWindow,0,0);
  wrefresh(boarderWindow);
  noecho();//
  fileHandler fh(LINES,COLS);
  if(input != ""){
    firstfirst = false;
    fh.openFile(input);
    file.deMyFile(fh.getFileName());
  }//if

  bool breakout = false;
  bool first = true;
  while(!breakout){
    curs_set(1);
    wclear(contentWindow);
    wclear(numPadWindow);
    box(boarderWindow,0,0);
    wrefresh(boarderWindow);
    wprintw(contentWindow,(file.getViewFile()).c_str());
    wrefresh(contentWindow);
    wprintw(numPadWindow, (file.getLineNums()).c_str());
    wrefresh(numPadWindow);
    int vertm = (file.getDown() - (file.numGreatestDown - LINES+5));

    wmove(contentWindow, vertm, file.getRight());
    wrefresh(contentWindow);
    noecho();//

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
      breakout = ::menu1(file,fh);
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
