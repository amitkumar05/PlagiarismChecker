/***********************************************************************************
        CS307(P)- 
         Amit Kumar    (B13107)
         Vinod Kumar   (B13141)
         Paawan Mukker (B13218)

	Parses the input file(Argument1) to remove all character except the alpha
	numeric and stores the result in a file with filename given as argument-2
	The parser function returns length of parsed string. 

*************************************************************************************/	  

#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int parse(char a[],char b[])
{
  ifstream f;
  f.open(a);                           //open first file
  if ( f.fail() )
  {
    cout << "Error: Cannot open file"; //Error - File cannot be opened
    exit(0);
  }
  char ch;
  ofstream of;
  of.open(b);                          //Open the file where output has to be stored
  int no_of_char=0;
  while(f) 
    {
      f >> ch;                         //Take input from first file as a charachter
      if(isalnum(ch))   
      {
       of << ch;                       //If character is alphanumeric then put it in the 
				       //output file and increase count of char by 1
       no_of_char++;
      }                                //else do nothing with that character and read next
    }                                    
  return no_of_char;
}

#endif
