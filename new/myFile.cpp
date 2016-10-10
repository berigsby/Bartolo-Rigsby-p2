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
}//myFile

myFile::myFile(string filePathIn){
  setDown(0);
  setRight(0);
  totalDown = 0;
  wholeFileLength = 0;
  hasFilePath = false;
  setFileAndPath(filePathIn);
}//myFile

bool myFile::setFileAndPath(string filePathIn){
  if(!checkPath(filePathIn)){
    return false;
  }//if
  hasFilePath = true;

  filePath = new char[filePathIn.length()-1];
  for(uint adj = 0; adj < filePathIn.length(); ++adj){
    *(filePath+adj) = filePathIn[adj];
  }//for

  fstream in(filePath);
  stringstream buffer;
  buffer << in.rdbuf();
  string test = buffer.str();

  wholeFile = new char[test.length()];
  wholeFileLength = test.length();
  for(uint adj = 0; adj < test.length()-1; ++adj){
    *(wholeFile+adj) = test[adj];
    if(test[adj] == '\n')
      totalDown++;
  }//for
  wholeFile[wholeFileLength-1] = '\0';
  numGreatestDown = LINES-4;
  return true;
}//setFilePath

bool myFile::checkPath(string filePathIn){
  return true;
}//checkPath

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
  setFileAndPath(filePathIn);
}//deMyFile

string myFile::getViewFile(){
  if(getDown() <= 0)
    setDown(0);

  if(getDown() >= totalDown){
    setDown(totalDown);
  }//if

  int numLines = LINES - 5;

  if (getDown() > numGreatestDown){
    numGreatestDown = getDown();
  } else if (getDown() < (numGreatestDown - numLines)){
    numGreatestDown = getDown() + numLines;
  }//else

  string wholeString(wholeFile);
  string returnString = wholeString;
  string testingString = wholeString;
  for(uint x = 0; x < (numGreatestDown - numLines); x ++){
    returnString = returnString.substr(returnString.find_first_of('\n')+ 1);
  }//for

  for(uint x = 0; x < getDown(); x ++){
    testingString = testingString.substr(testingString.find_first_of('\n')+ 1);
  }//for  
  if((testingString.find_first_of('\n')) <= getRight()){
    setRight(testingString.find_first_of('\n'));
  }
  if((testingString.find_first_of('\n')) == string::npos){
    if(testingString.length() <= getRight())
      setRight(testingString.length());
  }//else
  return returnString;
}//getViewFile

void myFile::insertChar(char character){
  uint offset = 0;
  int lastbackn = 0;
  if(getDown() <= 0)
    setDown(0);
  string wholeString(wholeFile);
  string returnString = wholeString;
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

  if(character == '\b'){
    if(offset == 0)
      return;
    wholeFileLength--;
    for (uint x = offset; x < wholeFileLength; x++){
      wholeFile[x-1] = wholeFile[x];
    }//for
    wholeFile[wholeFileLength-1] = '\0';
    if(getRight() == 0){
      totalDown--;
      decDown();
      setRight(lastbackn);
    }else{
      decRight();
    }//else
  }else if(false){
    for (uint x = offset; x < wholeString.length(); x++){
      wholeFile[x] = wholeFile[x+1];
    }//for
    wholeFile[wholeString.length()-1] = '\0';
    //decRight();
  }else {
    wholeFileLength ++;
    char * newWholeFile = new char[wholeFileLength];
    //char newWholeFile[wholeFileLength];
    for(uint adj = 0; adj < offset; ++adj){
      newWholeFile[adj] = wholeFile[adj];
    }//for 
    newWholeFile[offset] = character;
    for(uint adj = offset+1; adj < wholeFileLength-1; ++adj){
      newWholeFile[adj] = wholeFile[adj-1];
    }//for 
    newWholeFile[wholeFileLength-1] = '\0';
    delete[] wholeFile;
    //wholeFile = new char[wholeFileLength];
    wholeFile = newWholeFile;
    //delete[] newWholeFile;
    if(character =='\n'){
      incDown();
      setRight(0);
      totalDown++;
    } else{
      incRight();
    }//else
  }//else
}//insertChar

void myFile::incDown(){
  numDown++;
}//incDown

void myFile::decDown(){
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
