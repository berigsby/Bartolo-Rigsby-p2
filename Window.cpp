#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Window.h"
#include <string>
#include <ncurses.h>

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

  const int padWidth = width-6;
  const int padHeight = getPadHeight(windowContent,padWidth);
  bool continuePad = true;
  int keyIn;
  int rows = 0;
  WINDOW *contentPad = newpad(padHeight,padWidth);
 
  keypad(contentPad, TRUE);
  waddstr(contentPad,windowContent.c_str());
  //prefresh(contentPad,0,0,4,4,padHeight,padWidth); 

  while(continuePad){

    prefresh(contentPad,rows,0,4,4,4+height,4+width); 
    keyIn = wgetch(contentPad); //record user key press

    switch(keyIn) 
      { 
      case KEY_UP: 
	{ 
	  if (rows <= 0){
	    continue;
	  } //if
	  rows--; 
	  break; 
	} //case
      case KEY_DOWN: 
	{ 
	  if (rows+height+1 >= padHeight){
	    continue;
	  } //if
	  rows++; 
	  break; 
	} //case 
      case KEY_F(1):
	{
	  continuePad = false;
	  break;
	} //case
      } //switch
    wrefresh(fileWindow);
  } //while
} //updatewindow

 //updateWindow

/* fuction determines the total
 * number of lines in a text
 * file
 */
int Window::getPadHeight(string content, int padWidth){

  int w = 0;
  int totalPadLines = 1; //for any half lines at the end of the file
  
  for(int i = 0;i<content.length();i++){
    if(++w >= padWidth){
      w = 0;
      ++totalPadLines;
    } //if
    if(content[i] == '\n'){ //in case of new line arguments
      w = 0;
      ++totalPadLines; 
    } //if
  } //for
    
  return totalPadLines;
} //getPadHeigt
