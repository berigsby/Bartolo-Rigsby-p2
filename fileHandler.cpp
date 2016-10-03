#include <ncurses.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <locale>
#include <sys/stat.h>
#include <unistd.h>
#include "fileHandler.h"

using namespace std;

fileHandler::fileHandler(int theHeight, int theWidth){
  
  height = theHeight;
  width = theWidth;
  fileWindow = newwin(8, 30, (height-10)/2, (width-25)/2); //create a new window in center of screen

} //fileHandler

fileHandler::~fileHandler(){

} //fileHandler deconstructor

void fileHandler::saveFile(string saveFile){

} //saveFile

void fileHandler::saveAsFile(string saveAsFile){
  
  string saveAsInst = "Enter the file name you wish to save as: ";

} //saveAsFile

/* function opens new window asking
 * user for file name and attempts
 * to open file and return its 
 * contents back to it caller
 */
string fileHandler::openFile(){
  
  bool openSuccess = false;
  const string openInst = "Enter the file name you wish to open: ";
  string fileItem;
  string fileContent;
  WINDOW *content;
  
  box(fileWindow,0,0); //add border around outer window only
  wrefresh(fileWindow);

  while(!(openSuccess)){ //while no file is successfully opened

    content = derwin(fileWindow, 5, 24, 2, 2); //create a sub window inside main window
    waddstr(content, openInst.c_str()); //add instructions to inner window
    
    curs_set(1); //show cursor
    wmove(content,3,5); //move cursor below prompt
    echo(); //show typed input
    keypad(content,TRUE); //enable keyboard input to inner window
  
    touchwin(fileWindow); //throw away all optimization information
    wrefresh(content);

    wgetstr(content,fileName); //store input in openedFile

    if(file_exists(fileName)){

	openedFile.open(fileName);
	
	if(openedFile.is_open()){
	  openSuccess = true;
	  while(!openedFile.eof()){
	    openedFile>>fileItem; //store current string in fileItem
	    fileContent += (fileItem+" ");
	  } //while

	} //if
	else{
	  werase(content); //erase inner window
	  wrefresh(content);
	  displayErrorWindow("Error opening file");
	} //else
      } //if file_exists
    else{
      werase(content); //erase inner window
      wrefresh(content);
      displayErrorWindow("File does not exist");
      } //else
    
  } //while

  openedFile.close();
  werase(fileWindow); //erase outer window
  werase(content); //erase inner window
  wrefresh(fileWindow);
  wrefresh(content);
  delwin(fileWindow); //delete outer window
  delwin(content); //delete inner window
  
  return fileContent; //return content of opened file

} //openFile

/* function displays the passed error
 * message in a new window
 */
void fileHandler::displayErrorWindow(string theErrorMessage){
  
  string errorMessage = theErrorMessage+" Press <ENTER> to go back";
  WINDOW *errorContent;
  int keyIn; //where the ENTER will be stored
 
  errorContent = derwin(fileWindow, 2, 25, 3,2); //create a sub window

  curs_set(1); //show cursor
  wmove(errorContent,3,5); //move cursor below prompt
  noecho();
  keypad(errorContent,TRUE); //enable keyboard input to inner window
  
  waddstr(errorContent, errorMessage.c_str());
  
  keyIn = wgetch(errorContent);
  
  while(!(keyIn == 10)){ //while not equal to ENTER
    //loop until ENTER is pressed
  } //while

  werase(errorContent);
  wrefresh(errorContent);
  delwin(errorContent);
  return; //return on ENTER

} //displayErrorWindow

/* function check to see if file
 * exists. returns true if file
 * exists
 */
bool fileHandler::file_exists(const string& name) {
  
  ifstream f(name.c_str());
  return f.good();
}

string fileHandler::getFileName(){
  
  return fileName;
} //getFileName


