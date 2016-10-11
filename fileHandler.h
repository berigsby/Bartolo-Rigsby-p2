#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <locale>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

class fileHandler {

 public:
  
  /**
   * inializes the fileHandeler
   *
   * @param theHight the number of Lines in ncurses
   * @param theWidth the number of Rows in ncurses
   */
  fileHandler(int theHeight, int theWidth);
  
  /**
   * Saves the stuffToSave to the current filePath
   *
   * @param stuffToSave a pointer to a char of the contents to save
   * @param stuffToSaveLength an uint of the length of stuffToSave
   */
  void saveAsFile(char * stuffToSave, unsigned int stuffToSaveLength);
  /**
   * this function opens a new window asking user for file name
   * and attempts to open file. Can also be passed a file to open
   *
   * @param input a string of a file to try and open. pass "" if none
   */
  void openFile(string input);

  /**
   * Function displayes the passed error message in a new window
   *
   * @param theErrorMessage a string of error to show
   */
  void displayErrorWindow(string theErrorMessage);

  /**
   * checks to see if the file exists. Returns true if it does
   *
   * @param name the string of the file to check
   * @return bool true if file exists
   */
  bool file_exists(const string& name);

  /**
   * Returns the name of the file that is opened
   *
   * @return string of the file name
   */
  string getFileName();

  /**
   * Returns true if file is currently open
   *
   * @return bool true if file is currently open
   */
  bool hasOpenedFile();

  /**
   * Opens an new window and asks the user if they want
   * to save before performing the next action
   *
   * @return bool true if they do want to save
   */
  bool wouldYouLikeToSave();

  /**
   * Opens a new window and asks the user if they wany 
   * to overwrite the file that already exists
   */
  bool overWrite();

 private:
  WINDOW *fileWindow;
  char fileName[100];
  ifstream openedFile;
  int height;
  int width;
  bool openSuccess = false;
}; //fileHandler

#endif
