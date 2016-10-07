
#include <fstream>
#include <sstream>
#include <cstring>
#include "myFile.h"

using namespace std;
typedef unsigned int uint;

myFile::myFile(){
  setDown(0);
  setRight(0);
  hasFilePath = false;
}//myFile

myFile::myFile(string filePathIn){
  setDown(0);
  setRight(0);
  hasFilePath = false;
  setFileAndPath(filePathIn);
}//myFile

bool myFile::setFileAndPath(string filePathIn){
  if(!checkPath(filePathIn)){
    return false;
  }//if
  hasFilePath = true;

  filePath = new char[filePathIn.length()];
  for(uint adj = 0; adj < filePathIn.length(); ++adj){
    *(filePath+adj) = filePathIn[adj];
  }//for

  fstream in(filePath);
  stringstream buffer;
  buffer << in.rdbuf();
  string test = buffer.str();

  wholeFile = new char[test.length()];
  for(uint adj = 0; adj < test.length(); ++adj){
    *(wholeFile+adj) = test[adj];
  }//for
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
}//destructor

string myFile::getViewFile(){
  if(getDown() <= 0)
    setDown(0);
  string wholeString(wholeFile);
  string returnString = wholeString;
  for(uint x = 0; x < getDown(); x ++){
    returnString = returnString.substr(returnString.find_first_of('\n')+ 1);
    
  }//for
  if((returnString.find_first_of('\n')) <= getRight()){
    setRight(returnString.find_first_of('\n'));
  }//if
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
    //setRight(0);
  } else{
    offset += getRight();
  }//else

  if(character == '\b'){
    if(offset == 0)
      return;
    for (uint x = offset; x < wholeString.length(); x++){
      wholeFile[x-1] = wholeFile[x];
    }//for
    wholeFile[wholeString.length()-1] = '\0';
    if(getRight() == 0){
      decDown();
      setRight(lastbackn);
    }else{
      decRight();
    }//else
  }else if(character == 127){
    for (uint x = offset; x < wholeString.length(); x++){
      wholeFile[x] = wholeFile[x+1];
    }//for
    wholeFile[wholeString.length()-1] = '\0';
    //decRight();
  }else {
    char * newWholeFile = new char[wholeString.length()+1];
    for(uint adj = 0; adj < offset; ++adj){
      newWholeFile[adj] = wholeFile[adj];
    }//for 
    newWholeFile[offset] = character;
    for(uint adj = offset+1; adj < wholeString.length()+1; ++adj){
      newWholeFile[adj] = wholeFile[adj-1];
    }//for 
    delete[] wholeFile;
    wholeFile = new char[wholeString.length()+1];
    wholeFile = newWholeFile;
    if(character =='\n'){
      incDown();
      setRight(0);
    } else{
      incRight();
    }//else
    //delete[] newWholeFile;
    //(wholeFile+offset) = (wholeFile+offset+1);
    //wholeFile[offset] = character;
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
