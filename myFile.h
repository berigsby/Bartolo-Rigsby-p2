
#ifndef MYFILE
#define MYFILE

#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <fcntl.h>

using namespace std;
typedef unsigned int uint;

class myFile{
  
  bool hasFilePath;
  char * wholeFile;
  uint numDown;
  uint numRight;
  uint totalDown;
  bool justSaved;
  char * filePath;
 public:
  uint wholeFileLength;
  uint numGreatestDown;

  /**
   * Contructor. Creates an object with no path
   */
  myFile();

  /**
   * Contructor. Creates an object and sets its path
   *
   * @param filePathIn the path of the file to open
   */
  myFile(string filePathIn);

  /**
   * Deconstructor. Deletes dynamically allocate values
   */
  ~myFile();

  /**
   * Used to reset the file to a different file. Will
   * reset initialize all values and delete old things
   *
   * @param filePathIn the file path of the new file to open
   */
  void deMyFile(string filePathIn);

  /**
   * Used to get the part of the file that needs to be printed
   * to the screen
   *
   * @return string the part of the file to be printed
   */
  string getViewFile();

  /**
   * Used internally to set the file path and update the file 
   * via the filePathIn
   *
   * @param filePathIn the name of the file to set
   * @return bool false if the file already has a path
   */
  bool setFileAndPath(string filePathIn);

  /**
   * Used to insert a chatacter at the current location in the file
   * Also handles if a '\b' is entered.
   *
   * @param character the character to be added
   */
  void insertChar(char character);

  /**
   * Returns the file path of this file
   *
   * @return pointer to a char of the file path
   */
  char * getFilePath();

  /**
   * Returns a string of the currect views line numbers
   *
   * @return string of the current views line numbers
   */
  string getLineNums();

  /**
   * Returns the file contents of this file
   *
   * @return pointer to a char of the file contents
   */
  char * getWholeFile();

  /**
   * Increments the number of times down is pressed. 
   * Wont go past the file length
   */
  void incDown();

  /**
   * Decrements the number of times down is pressed, usually
   * because up is pressed. Wont go less than 0
   */
  void decDown();


  /**
   * Sets the number of downs that have been pressed
   *
   * @param down the number of downs to set
   */
  void setDown(int down);

  /**
   * Gets the number of downs that has been pressed
   *
   * @return uint the number of downs pressed
   */
  uint getDown();
  
  /**
   * Increments the number of rights that have been clicked
   */
  void incRight();

  /**
   * Decrements the number of rights that have been clicked, usally
   * because left has been clicked.
   */
  void decRight();

  /**
   * Sets the number of Rights that has been clicked
   *
   * @param right the number of rights to set
   */
  void setRight(int right);

  /**
   * Gets the number of Rights that have been clicked
   *
   * @return uint the numebr of rights clicked
   */
  uint getRight();
 
  /**
   * Saves the file content of this file to name
   *
   * @param name the name of the file to save as
   */
  void saveAs(string name);

  /**
   * Saves the file content to itself
   */
  void saveAs();

  /**
   * checks to see if changes have been made since last save
   */
  bool isSaved();
};//myFile

#endif
