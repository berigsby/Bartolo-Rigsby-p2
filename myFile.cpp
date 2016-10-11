#include <fstream>
#include <sstream>
#include <cstring>
#include "myFile.h"
#include <ncurses.h>

using namespace std;
typedef unsigned int uint;

myFile::myFile(){
  setDown(0);
  setRight(0);
  totalDown = 0;
  wholeFileLength = 0;
  hasFilePath = false;
  justSaved = true;
}//myFile

myFile::myFile(string filePathIn){
  setDown(0);
  setRight(0);
  totalDown = 0;
  wholeFileLength = 0;
  hasFilePath = false;
  justSaved = true;
  setFileAndPath(filePathIn);
}//myFile

bool myFile::setFileAndPath(string filePathIn){

  //if it has a filePath, it wont change it
  if(hasFilePath){
    return false;
  }//if
  hasFilePath = true;

  //sets the filePath from the filePathIn
  filePath = new char[filePathIn.length()-1];
  for(uint adj = 0; adj < filePathIn.length(); ++adj){
    *(filePath+adj) = filePathIn[adj];
  }//for

  //gets the content of the filePath and puts
  //it into a tmp string. Derived from cplusplus.com/
  //forum/beginner/78150
  fstream in(filePath);
  stringstream buffer;
  buffer << in.rdbuf();
  string test = buffer.str();

  //takes the string stored in the test value and puts
  // it into the wholeFile variable
  wholeFile = new char[test.length()];
  wholeFileLength = test.length();
  for(uint adj = 0; adj < test.length()-1; ++adj){
    *(wholeFile+adj) = test[adj];
    if(test[adj] == '\n')
      totalDown++;
  }//for
  
  //adds a end of file marker at the end of the char array
  wholeFile[wholeFileLength-1] = '\0';

  //resets the number of greatest downs to the window size
  numGreatestDown = LINES-4;
  return true;
}//setFilePath

myFile::~myFile(){
  if(hasFilePath){
    delete[] filePath;
    delete[] wholeFile;
  }//if
  totalDown = 0;
  setDown(0);
  setRight(0);
  wholeFileLength = 0;
  hasFilePath = false;  
}//destructor

void myFile::deMyFile(string filePathIn){
  if(hasFilePath){
    delete[] filePath;
    delete[] wholeFile;
  }//if
  totalDown = 0;
  setDown(0);
  setRight(0);
  wholeFileLength = 0;
  hasFilePath = false;
  justSaved = true;
  setFileAndPath(filePathIn);
}//deMyFile

string myFile::getViewFile(){

  //if no filePath, return an empty string
  if(!hasFilePath)
    return "";

  //check getDown is in bounds
  if(getDown() <= 0)
    setDown(0);
  if(getDown() >= totalDown){
    setDown(totalDown);
  }//if

  //used to find where the file begins being printed
  int numLines = LINES - 5;
  if (getDown() > numGreatestDown){
    numGreatestDown = getDown();
  } else if (getDown() < (numGreatestDown - numLines)){
    numGreatestDown = getDown() + numLines;
  }//else

  string wholeString(wholeFile);
  string returnString = wholeString;
  string testingString = wholeString;//used to check certain cases

  //sets the retrun string 
  for(uint x = 0; x < (numGreatestDown - numLines); x ++){
    returnString = returnString.substr(returnString.find_first_of('\n')+ 1);
  }//for

  //sets the testing string
  for(uint x = 0; x < getDown(); x ++){
    testingString = testingString.substr(testingString.find_first_of('\n')+ 1);
  }//for  

  //checks the getRight bounds in certain cases
  if((testingString.find_first_of('\n')) <= getRight()){
    setRight(testingString.find_first_of('\n'));
  }
  if((testingString.find_first_of('\n')) == string::npos){
    if(testingString.length() <= getRight())
      setRight(testingString.length());
  }//else

  return returnString;
}//getViewFile

string myFile::getLineNums(){
  //stores the numbers to be printed as pads as
  //essentially a vertical line
  string nums = "";
  if(!hasFilePath)
    return nums;
  int numLines = LINES - 5;
  int startLines = numGreatestDown - numLines;
  if(startLines < 1)
    startLines = 1;
  for(uint x = startLines; x <= numGreatestDown+1; x++){
    nums += std::to_string(x);
    nums += '\n';
  }//for
  return nums;
}//getLineNums

void myFile::insertChar(char character){
  justSaved = false;//if something is being changed, then it needs to be saved now
  uint offset = 0;
  int lastbackn = 0;
  
  //checks bounds of getDown
  if(getDown() <= 0)
    setDown(0);

  string wholeString(wholeFile);
  string returnString = wholeString;

  //finds the location of the cursor, used to increment offset
  for(uint x = 0; x < getDown(); x ++){
    offset += returnString.find_first_of('\n')+1;
    lastbackn = returnString.find_first_of('\n');
    returnString = returnString.substr(returnString.find_first_of('\n')+ 1);     
  }//for
  if((returnString.find_first_of('\n')) <= getRight()){
    offset += returnString.find_first_of('\n');
  } else{
    offset += getRight();
  }//else

  //if character ==\b, then it was backspace
  if(character == '\b'){
    if(offset == 0)
      return;
    wholeFileLength--;
    
    //transfers all items one back from where the where after the offser
    for (uint x = offset; x < wholeFileLength; x++){
      wholeFile[x-1] = wholeFile[x];
    }//for
    wholeFile[wholeFileLength-1] = '\0';

    //checks where getRIght and get Down need to be set to
    if(getRight() == 0){
      totalDown--;
      decDown();
      setRight(lastbackn);
    }else{
      decRight();
    }//else
  }else {
    //dont add content if string is going to overflow
    if(returnString.find_first_of('\n') >= (uint)COLS-9){
      if(returnString.length() < (uint)COLS-9){
	//donothing
      }//if
      else{
	if(character != '\n')
	  return;
      }//else
    }//if

    //all other cases, insert a char
    wholeFileLength ++;
    char * newWholeFile = new char[wholeFileLength];

    //sets all values before offset as same
    for(uint adj = 0; adj < offset; ++adj){
      newWholeFile[adj] = wholeFile[adj];
    }//for 

    //inserts new characer
    newWholeFile[offset] = character;

    //increments all values after offset and sets them
    for(uint adj = offset+1; adj < wholeFileLength-1; ++adj){
      newWholeFile[adj] = wholeFile[adj-1];
    }//for 

    //adds end file character at end of char array
    newWholeFile[wholeFileLength-1] = '\0';

    //delete old file content
    delete[] wholeFile;

    //stroe new content
    wholeFile = newWholeFile;

    //sets new location of cursor
    if(character =='\n'){
      incDown();
      setRight(0);
      totalDown++;
    } else{
      incRight();
    }//else
  }//else
}//insertChar

char * myFile::getWholeFile(){
  return wholeFile;
}//getWholeFile

char * myFile::getFilePath(){
  return filePath;
}//getFilePath

void myFile::incDown(){
  numDown++;
}//incDown

void myFile::decDown(){
  //cant be less than zero
  if(getDown() == 0)
    return;
  numDown--;
}//decDown

void myFile::setDown(int down){
  numDown = down;
}//setDown

uint myFile::getDown(){
  return numDown;
}//getDown

void myFile::incRight(){
  numRight++;
}//incRight

void myFile::decRight(){
  //cant be less than zero
  if(getRight() == 0)			
    return;
  numRight--;
}//decRight

void myFile::setRight(int right){
  numRight = right;
}//setRight

uint myFile::getRight(){
  return numRight;
}//getRight

void myFile::saveAs(string name){
  //derived from cplusplus.com/forum/beginner/36080
  justSaved = true;
  string input(wholeFile);
  std::ofstream out(name);
  out << input;
  out.close();
}//SaveAs

void myFile::saveAs(){
  //derived from cplusplus.com/forum/beginner/36080
  justSaved = true;
  string input(wholeFile);
  //std::cin >> input;
  std::ofstream out(filePath);
  out << input;
  out.close();
}//SaveAs

bool myFile::isSaved(){
  return justSaved;
}//isSave
