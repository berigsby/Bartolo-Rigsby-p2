#include <iostream>
#include <iomanip>
#include "Window.h"
#include "WindowMenu.h"
#include "fileHandler.h"
#include <ncurses.h>
#include <string.h>
#include <cstdlib>

using namespace std;

int main(){

  char instructions[] = "F1: Menu";
  char title[] = "CSCI 1730 Editor!";
  string openFileContent, fileName;
  int col, height, width, startInput, userMenuChoice;
  bool continueLoop = true;

  initscr();
  col = getmaxx(stdscr);
  mvprintw(0,2,"%s",instructions); //keep visible at top left corner
  mvprintw(0,(col-strlen(title))/2,"%s",title);
  refresh();
  
  getmaxyx(stdscr, height, width); 
  
  Window w(height, width); //initialize and display empty editor border
  WindowMenu wm(height, width);
  fileHandler fh(height, width);

  keypad(stdscr,TRUE); //will need this for user input by keys
 
  while(continueLoop){  //loop until EXIT is selected
    
    startInput = getch(); //store user key press in startInput
  
    if(startInput == KEY_F(1)){
      wm.displayWindowMenu();
      userMenuChoice = wm.getUserMenuChoice();

      switch(userMenuChoice){
      case 0: //Open
	openFileContent = fh.openFile();
	mvprintw(height-1,2,"%s",(fh.getFileName()).c_str()); //show open file name in bottom left corner
	refresh();
	w.updateWindow(openFileContent);
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
	continueLoop = false; //break out of the loop and terminate program
	break;
      } //switch
    } //if
    else{
      //to implement: if user begins editing
    } //else
  } //while

  endwin(); //end program
} //main

