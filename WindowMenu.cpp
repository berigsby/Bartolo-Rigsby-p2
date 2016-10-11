#include <iostream>
#include <iomanip>
#include "WindowMenu.h"
#include <string>

using namespace std;

WindowMenu::WindowMenu(int height, int width){

  menuWindow = newwin(6, 12, (height-10)/2, (width-25)/2); //create a new window in center of screen

} //WindowMenu

void WindowMenu::displayWindowMenu(){

  box(menuWindow,0,0);
  int j = 0;
  userMenuChoice = 0;

  for(int i = 0;i<4;i++) {
    if(i == 0){ 
      wattron(menuWindow,A_STANDOUT); //highlight first element
    } //if
    else{
      wattroff(menuWindow,A_STANDOUT ); //turn off highlight once passed 1st element
    } //else
    sprintf(item,"%-9s",menuOptions[i]); //temp store in item followed by 9 space post indent
    mvwprintw(menuWindow,i+1,2,"%s",item); //print to window with border space i+1,2 what is in item
  } //for
      
  wrefresh(menuWindow); // update the terminal screen
      
  keypad(menuWindow,TRUE); //enable keyboard input for the window
  curs_set(0); //hide the cursor from window
  noecho(); //disable all echoes

  while((keyIn = wgetch(menuWindow)) != 10){ //while input is not ENTER         
    sprintf(item,"%-9s",menuOptions[j]);
    mvwprintw(menuWindow,j+1,2,"%s",item); //location where to print menu option
    
    switch(keyIn) {
    case KEY_UP:
      j--;
      j = (j<0) ? 3 : j; //if highlight is top option go to bottom element
      break;
    case KEY_DOWN:
      j++;
      j = (j>3) ? 0 : j; //if highlight is bottom option go to top
      break;
    } //case
    
    wattron(menuWindow, A_STANDOUT); //highlight turned on for next print
             
    sprintf(item,"%-9s",menuOptions[j]);
    userMenuChoice = j; //storing which option the user chooses
    mvwprintw(menuWindow,j+1,2,"%s",item); //print new highlighted option
    wattroff(menuWindow,A_STANDOUT); //turn highlight off and wait for next key in
  } //while
  
  werase(menuWindow); //get rid of menu window after ENTER
  wrefresh(menuWindow);

} //displayWindowMenu

int WindowMenu::getUserMenuChoice(){

  return userMenuChoice; 
 
} //getUserChoice
