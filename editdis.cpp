/***********************************************************************************
        CS307(P)- 
         Amit Kumar    (B13107)
         Vinod Kumar   (B13141)
         Paawan Mukker (B13218)

	Implementing Edit distance for finding the similarity between two documents.

       EDIT DISTANCE-
        Given two strings str1 and str2 and below operations that can performed on str1. 
        Find minimum number of edits (operations) required to convert ‘str1′ into ‘str2′.
        All of the below operations are of equal cost.

        Insert  (Add a new character in one string)
        Replace (Replace a character in one string with another string)
        Remove  (Remove a character from string)
        
        The above algorithm is implemented using dynamic programming paradigm with time
        complexity of O(n^2) and space complexity of O(n^2) as well.

	In this trivial Edit distance algorithm is modified.

	Treating the document in P paragraphs each of size 'N' and then applying 
	Edit Distance between every two paragraphs of the two submissions.
	This ensures to catch the plagariasm even if the relative ordering of two
	paragraphs are changed in the two submissions to trick/by-pass plagarism
	checker.

	A final score is generated as the sum of scores by application of edit
	-distance paragraph wise.
 
*************************************************************************************/	  

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<algorithm>
#include<limits.h>
#include "parser.h"
using namespace std;
char a[2005],b[2005];
int dp[2005][2005];

int N=500;


int  min(int a,int b)  // Function returning the minimum of two numbers a and b.
{
  if(a>b)
    return b;
  else 
    return a;
}

int fix(int i,int j)  // function to check equality of characters
{
  if(a[i-1]==b[j-1])
    return 0;
  else 
    return 1;
}

void editdistance(char a[],char b[],int dp[][2005],int len,int len1) //Edit-distance algorithm
                                                                     //Parameters a,b for comparison and dp[][] table for memoization
                                                                     // len is length of a and len1 length of string b
{
  int i,j;
  for(i=0;i<=len;i++)
    {
      for(j=0;j<=len1;j++)                                           //For every character in a traverse every character in b
	{
	  if(i==0)
	    {dp[i][j]=j;}					     //If one of the string is empty then edits required is 
	                                                             //equal to length of substring of other
	  else if(j==0)
	    {dp[i][j]=i;}
	  else
	    {                                                        //Take minimum of operations of Insert/Replace/Remove
	      long long int p=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+(fix(i,j)));
	      dp[i][j]=p;
	    }
	}
      
    }
}

int main(int argc,char * argv[])            //argv[1] consists of filename of first file
                                            //and argv[2] filename of file2
{
  char ch,f1[]="tmp1.txt",f2[]="tmp2.txt";
  int t,i,j;
  fstream ifile,ofile;
  int total_edit=0;
  int l1=parse(argv[1],f1);                //parse function opens file parses document 
                                           //and stores the parsed string in file with second 
                                           //argument to parse function and returns length of parsed string
  int l2=parse(argv[2],f2);
  if(l1<l2)                                //Comparing lengths of parsed outputs and stores the smaller length in f1(tmp1.txt)
    {
      strcpy(f1,"tmp1.txt");
      strcpy(f2,"tmp2.txt");
    }
  else                                     //Comparing lengths of parsed outputs and stores the smaller length in f1(tmp1.txt)
    {
      strcpy(f2,"tmp1.txt");
      strcpy(f1,"tmp2.txt");
    }
  ifile.open(f1,ios::in);
  while(ifile>>ch)
    {
      i=0;
      while(ifile>>ch && i<N)
	{
	  a[i++]=ch;
	}
      a[i]='\0';                    //Breaking first file in paragraph of 'N' words
      ofile.open(f2,ios::in);
      int minimum=INT_MAX;		
      while(ofile)
	{
	  j=0;
	  while(ofile>>ch && j<N)
	    {
	      b[j++]=ch;            //Breaking second file in paragraph of 'N' words
	    }
	  b[j]='\0';
	  int len=strlen(a);
	  int len1=strlen(b);		
	  editdistance(a,b,dp,len,len1);  //Applying Edit Distance on these bisected paragraphs

	  minimum=min(minimum,dp[len][len1]); //Store minimum edit distance score (Maximum similarity) of all scores 
	}
      ofile.close();
      //  printf("Minimum  %d\n",minimum);
      total_edit+=minimum;                    //Add all minimum scores to compute total score.
    }
  cout<<"Total Edits required = "<<total_edit<<"\n";
  return 0;
}
