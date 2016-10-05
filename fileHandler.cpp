#include <ncurses.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <locale>
#include <sys/stat.h>
#include <unistd.h>
#include "fileHandler.h"
#include <cerrno>

using namespace std;

fileHandler::fileHandler(int theHeight, int theWidth){
  
  height = theHeight;
  width = theWidth;
  fileWindow = newwin(8, 30, (height-10)/2, (width-25)/2); //create a new window in center of screen

} //fileHandler

fileHandler::~fileHandler(){

} //fileHandler deconstructor

void fileHandler::saveFile(){
  /*TO IMPLEMENT
   * store content in pad to array
   * and in turn read that conrent
   * from array and store to opened
   * file
   */
} //saveFile

void fileHandler::saveAsFile(){ //UNFINISHED ********************

  const string saveAsInst = "Enter the file name you wish to save as: ";
  bool saveAsSuccess = false;
  WINDOW *content;
  
  box(fileWindow,0,0); //add border around outer window only
  wrefresh(fileWindow);

  while(!(saveAsSuccess)){ //while no file is successfully saved

    content = derwin(fileWindow, 5, 24, 2, 2); //create a sub window inside main window
    waddstr(content, saveAsInst.c_str()); //add instructions to inner window

    curs_set(1); //show cursor
    wmove(content,3,5); //move cursor below prompt
    echo(); //show typed input
    keypad(content,TRUE); //enable keyboard input to inner window
       
    touchwin(fileWindow); //throw away all optimization information
    wrefresh(content);
	
    wgetstr(content,fileName); //store input in fileName
    saveAsSuccess = true;

    //NOTE TO SELF: change openedFile to the file we are applying SaveAs to ****************
    //in order to be able to update the file again using just Save

  } //while
  
  werase(content);
  werase(fileWindow);
  
  wrefresh(content);
  wrefresh(fileWindow);

  delwin(content);
  delwin(fileWindow);

} //saveAsFile

/* function opens new window asking
 * user for file name and attempts
 * to open file and return its 
 * contents back to it caller
 */
string fileHandler::openFile(){
 
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

    wgetstr(content,fileName); //store input in fileName

    if(file_exists(fileName)){

      openedFile.open(fileName); //if file eixsts attempt to open it
	
	if(openedFile.is_open()){
	  openSuccess = true;
	  while(!openedFile.eof()){
	    openedFile>>fileItem; //store current string in fileItem
	    fileContent += (fileItem+" "); //merge all strings read from file
	  } //while

	} //if
	else{
	  fileName[0] = '\0';
	  werase(content); //erase inner window
	  wrefresh(content);
	  displayErrorWindow("Error opening file");
	} //else
      } //if file_exists
    else{
      fileName[0] = '\0';
      werase(content); //erase inner window
      wrefresh(content);
      displayErrorWindow("File does not exist");
      } //else
    
  } //while

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
  
  while(!(keyIn == 10)){ //while not equal to ENTER
    keyIn = wgetch(errorContent);
  } //while

  werase(errorContent);
  wrefresh(errorContent);
  delwin(errorContent);
  return; //return on ENTER

} //displayErrorWindow

/* function checks to see if file
 * exists. returns true if file
 * exists
 */
bool fileHandler::file_exists(const string& name) {
  
  ifstream f(name.c_str());
  return f.good();
}

/* function returns the name
 * of the file that is opened
 */
string fileHandler::getFileName(){
  
  return fileName;
} //getFileName

/* function returns true if
 * a file is currently open
 * and false otherwise
 */
bool fileHandler::hasOpenedFile(){
  
  return openSuccess;
} //hasOpenedFile
