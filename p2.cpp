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

  //display menu choices
  WindowMenu wm(LINES,COLS);
  wm.displayWindowMenu();

  int userMenuChoice = wm.getUserMenuChoice();

  string fn;

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
  noecho();
  switch(userMenuChoice){
      case 0: //Open

	//check if file was saved or not
	fh.openFile("");
	if(!file.isSaved()){
	  if(fh.wouldYouLikeToSave()){
	    file.saveAs();
	  }//if
	}//if

	clear();
	mvprintw(LINES-1,2,"%s",(fh.getFileName()).c_str()); //show open file name in bottom left corner
	mvprintw(0,2,"%s",instructions); //keep visible at top left corner
	mvprintw(0,(COLS-strlen(title))/2,"%s",title);//display title in top middle
	refresh();
	noecho();

	file.deMyFile(fh.getFileName());

	break;
      case 1: //Save
	file.saveAs();
	noecho();
	break;
      case 2: //Save As
	fh.saveAsFile(file.getWholeFile(),file.wholeFileLength);
	file.deMyFile(fh.getFileName());
	noecho();
	break;
      case 3: //Exit
	//check if file is saved or not
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
  bool firstfirst = true;//used if input was specified

  initscr();
  cbreak();
  keypad(stdscr, TRUE);

  WINDOW * boarderWindow;//the box around outside
  WINDOW * contentWindow;//the working area
  WINDOW * numPadWindow;//the numbers of left
  boarderWindow = newwin(LINES-2,COLS-2,1,1);
  contentWindow = newwin(LINES-4,COLS-8,2,6);
  numPadWindow = newwin(LINES-4,4,2,2);
  noecho();

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
  mvprintw(0,2,"%s",instructions); //keep visible at top left corner
  mvprintw(0,(COLS-strlen(title))/2,"%s",title);//show title in top middle
  mvprintw(LINES-1,2,"%s",input.c_str()); //show open file name in bottom left corner
  refresh();

  box(boarderWindow,0,0);
  wrefresh(boarderWindow);
  noecho();

  fileHandler fh(LINES,COLS);

  //if input was specified, check that it is a file, then open it
  if(input != ""){
    firstfirst = false;
    fh.openFile(input);
    file.deMyFile(fh.getFileName());
  }//if

  bool breakout = false; //used to see if F1 exit is selected
  bool first = true;//if this is the first iteration, select UP so that all is displayed
  while(!breakout){
    curs_set(1);//display cursor

    //clear old contents
    wclear(contentWindow);
    wclear(numPadWindow);

    //dispaly box
    box(boarderWindow,0,0);
    wrefresh(boarderWindow);

    //dispaly contents of file
    wprintw(contentWindow,(file.getViewFile()).c_str());
    wrefresh(contentWindow);

    //display number pad on left
    wprintw(numPadWindow, (file.getLineNums()).c_str());
    wrefresh(numPadWindow);

    //find cursor position
    int vertm = (file.getDown() - (file.numGreatestDown - LINES+5));

    //ser cursor position
    wmove(contentWindow, vertm, file.getRight());
    wrefresh(contentWindow);
    noecho();

    int ch;
    //check to see if this is the first time of file was specified
    //if no file specified, open menu by default
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
      //none of the others, insert the char of the button clicked
      file.insertChar((char)ch);
      break;
    }//switch
  }//while

  endwin();
}//cycle

int main(int argc, char * argv[]){
   string file = "";
   //check to see if any files were input
   if(argc == 2){
     string file2(argv[1]);
     ::cycle(file2);
   }else{
     ::cycle(file);
   }//else
   return 0;
}//main
