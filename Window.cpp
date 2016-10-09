#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Window.h"
#include <string>
//#include <ncurses.h>
//#include <cstdlib>
#include <ncurses.h>
//#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <fcntl.h>
#include "myFile.h"
#include <iostream>

using namespace std;

Window::Window(int theHeight, int theWidth){

  height = theHeight-2;
  width = theWidth-2;

  fileWindow = newwin((height),(width),1,1);
  box(fileWindow,0,0);
  wrefresh(fileWindow);

} //Window

Window::~Window(){

} //Window deconstructor

void Window::updateWindow(string windowContent){

  myFile file = myFile(windowContent);

  //initscr();
  //cbreak();
  //keypad(stdscr, TRUE);

  //WINDOW * boarderWindow;
  WINDOW * contentWindow;
  //boarderWindow = newwin(LINES-2,COLS-2,1,1);
  contentWindow = newwin(LINES-4,COLS-4,2,2);
  noecho();
  //box(boarderWindow,0,0);
  //wrefresh(boarderWindow);
  while(true){

    //wclear(contentWindow);
    //box(boarderWindow,0,0);
    //wrefresh(boarderWindow);
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
      delwin(contentWindow);
      return;
      break;
    default:
      file.insertChar((char)ch);
      break;
    }//switch
    wclear(contentWindow);
  }//while  
  delwin(contentWindow);
  /*
  const int padWidth = width-6;
  const int padHeight = getPadHeight(windowContent,padWidth);
  const int startY = 4;
  const int startX = 4;
  bool continuePad = true;
  int keyIn;
  int rows = 0;
  WINDOW *contentPad = newpad(padHeight,padWidth);
 
  keypad(contentPad, TRUE);
  waddstr(contentPad,windowContent.c_str());

  while(continuePad){ //handles scrolling

    prefresh(contentPad,rows,0,startY,startX,height-4,startX+width); //update pad content
    keyIn = wgetch(contentPad); //record user key press

    switch(keyIn) 
      { 
      case KEY_UP: 
	{ 
	  if (rows <= 0) continue;
	  rows--;
	  break;
	} //case
      case KEY_DOWN: 
	{ 
	  if(rows+height+1 >= padHeight) continue;
	  rows++;
	  break;
	} //case 
      case KEY_F(1): //only temporary. maybe? ****************
	{
	  continuePad = false;
	  break;
	} //case
      } //switch
    wrefresh(fileWindow);
  } //while

*/
} //updatewindow

/* fuction determines the total
 * number of lines in a text
 * file
 *
int Window::getPadHeight(string content, int padWidth){

  int w = 0;
  int totalPadLines = 1; //for any half lines at the end of the file
  
  for(int i = 0;i<content.length();i++){
    if(++w >= padWidth){ //if total length is greater than the pad's width
      w = 0; //start counting for a new line
      totalPadLines+=2; //add a line (adds 1 to pad height)
    } //if
    
    if(content[i] == '\n'){ //in case of new line arguments
      w = 0; //start new line
      totalPadLines++; //add a line
    } //if
  } //for
    
  return totalPadLines;
} //getPadHeigt
*/
