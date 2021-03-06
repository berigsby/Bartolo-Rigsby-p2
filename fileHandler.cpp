#include <ncurses.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <locale>
#include <sys/stat.h>
#include <unistd.h>
#include "fileHandler.h"
#include <cerrno>
#include <string>
#include <fcntl.h>

using namespace std;

fileHandler::fileHandler(int theHeight, int theWidth){
  
  height = theHeight;
  width = theWidth;
  fileWindow = newwin(8, 30, (height-10)/2, (width-25)/2); //create a new window in center of screen

} //fileHandler
 
void fileHandler::saveAsFile(char * stuffToSave, uint stuffToSaveLength){
  
  string saveAsInst = "Enter the file name you wish to save as: ";
  bool saveAsSuccess = false;
  char saveFileName[50];
  fstream f;
  int fd; //file descriptor
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
	
    wgetstr(content,saveFileName); //store input in saveFileName
    
    werase(content); //erase inner window
    wrefresh(content);

    
    if(file_exists(saveFileName)){
      if(overWrite()){
	fd = open(saveFileName, O_TRUNC); //opens file and erases its content
	close(fd);
	open(saveFileName,O_RDWR);
	if (fd < 0) {
	  close(fd);
	  werase(content); //erase inner window
	  wrefresh(content);
	  displayErrorWindow("Error opening file or no permission to write");
	} //if open fails
	else{ //if opens succeeds
	  write(fd, stuffToSave, stuffToSaveLength); //write to specified saveAs file
	  //strcpy(fileName, saveFileName); //store new open file as the saveAs file name
	  saveAsSuccess = true; //to break out of SaveAs window loop
	} //else
      } //if
    } //if file exists
    else{ 
      fd = open(saveFileName, O_RDWR | O_CREAT,0777); //create new file thats is readable and writable
      if (fd < 0) {
	close(fd);
	werase(content); //erase inner window
	wrefresh(content);
	displayErrorWindow("Error opening file or no permission to write");
      } //if open fails
      else{ //if opens succeeds
	write(fd, stuffToSave, stuffToSaveLength); //write to specified saveAs file
	strcpy(fileName, saveFileName); //store new open file as the saveAs file name
	saveAsSuccess = true; //to break out of SaveAs window loop
      } //else
    } //else if file does not exist
  } //while
  
  werase(content); //get rid of saveAs prompt
  werase(fileWindow);
  
  wrefresh(content);
  wrefresh(fileWindow);

  delwin(content);

} //saveAsFile

void fileHandler::openFile(string input){
 
  const string openInst = "Enter the file name you wish to open: ";
  string fileItem;
  string fileContent;
  WINDOW *content;
  //  char * cfilePath[100];
  
  box(fileWindow,0,0); //add border around outer window only
  wrefresh(fileWindow);
  openSuccess = false;
  while(!(openSuccess)){ //while no file is successfully opened

    content = derwin(fileWindow, 5, 24, 2, 2); //create a sub window inside main window
    waddstr(content, openInst.c_str()); //add instructions to inner window
    
    curs_set(1); //show cursor
    wmove(content,3,5); //move cursor below prompt
    echo(); //show typed input
    keypad(content,TRUE); //enable keyboard input to inner window
  
    touchwin(fileWindow); //throw away all optimization information
    wrefresh(content);

    if(input != ""){
      for(uint x = 0; x < 99; x++){
    fileName[x] = input[x];
    }//for
    input = "";
    }else{
      wgetstr(content,fileName); //store input in fileName
    }//else

    if(file_exists(fileName)){

      openedFile.open(fileName); //if file eixsts attempt to open it
	
	if(openedFile.is_open()){
	  openSuccess = true;
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

  string rs = "";
  for(unsigned int x = 0; x <= strlen(fileName); ++x){
    rs += fileName[x];
  }//for
  
  return; //return name of opened file

} //openFile

bool fileHandler::overWrite(){
  
   WINDOW *overWriteContent;
   string overWriteMessage = "File already exists. Overwrite? y/n \n  ";
   char userAnswer[10]; //where the y or n will be stored
   string answer;

   overWriteContent = derwin(fileWindow, 2, 25, 2,1); //create a sub window

   curs_set(1); //show cursor
   echo();
   keypad(overWriteContent,TRUE); //enable keyboard input to inner window

   while(!(answer == "y" || answer == "n")){
     wclear(overWriteContent);
     mvwaddstr(overWriteContent,0,0,overWriteMessage.c_str());
     wmove(overWriteContent, 5,6);
     wgetstr(overWriteContent,userAnswer);
     answer = userAnswer;
   } //while

   werase(overWriteContent);
   wrefresh(overWriteContent);
   delwin(overWriteContent);

   return (answer == "y"); //returns true or false
} //overWrite

bool fileHandler::wouldYouLikeToSave(){
  
   WINDOW *overWriteContent;
   string overWriteMessage = "Would you like to save\nthis file first? y/n \n  ";
   char userAnswer[10]; //where the y or n will be stored
   string answer;

   box(fileWindow,0,0); //add border around outer window only
   wrefresh(fileWindow);

   overWriteContent = derwin(fileWindow, 2, 25, 2,1); //create a sub window

   curs_set(1); //show cursor
   echo();
   keypad(overWriteContent,TRUE); //enable keyboard input to inner window

   while(!(answer == "y" || answer == "n")){
     wclear(overWriteContent);
     mvwaddstr(overWriteContent,0,0,overWriteMessage.c_str());
     wmove(overWriteContent, 5,6);
     wgetstr(overWriteContent,userAnswer);
     answer = userAnswer;
   } //while

   werase(overWriteContent);
   wrefresh(overWriteContent);
   delwin(overWriteContent);

   return (answer == "y"); //returns true or false
}//wouldYouLikeToSave

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

bool fileHandler::file_exists(const string& name) {
  
  ifstream f(name.c_str());
  return f.good();
}

string fileHandler::getFileName(){
  string rs = "";
  for(int x =0; x < 100; x++){
    if(fileName[x] == '\n' || fileName[x] == ' '){
      break;
    }else{
      rs += fileName[x];
    }//else
  }//for
  return rs;
} //getFileName

bool fileHandler::hasOpenedFile(){
  
  return openSuccess;
} //hasOpenedFile
