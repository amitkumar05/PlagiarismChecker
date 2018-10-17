/*********************************************************************************** 
        CS307(P)- 
         Amit Kumar    (B13107)
         Vinod Kumar   (B13141)
         Paawan Mukker (B13218)

	Implementing Edit distance for finding the similarity between two documents.

       LONGEST COMMON SUB-SEQUENCE
        The longest common subsequence (LCS) problem is the problem of finding the 
        longest subsequence common to two sequences. Subsequences are not required to
        occupy consecutive positions within the original sequences.

        The above algorithm is implemented using dynamic programming paradigm with time
        complexity of O(n^2) and space complexity of O(n^2) as well.

	In this trivial LCS algorithm is modified.

	Treating the document in P paragraphs each of size 'N' and then applying 
	LCS between every two paragraphs of the two submissions.
	This ensures to catch the plagariasm even if the relative ordering of two
	paragraphs are changed in the two submissions to trick/by-pass plagarism
	checker.

	A final score is generated as the sum of scores by application of LCS paragraph wise.
 
*************************************************************************************/	  

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "parser.h"
#include<algorithm>
#include<limits.h>
using namespace std;
int N=500;
char a[2005],b[2005];
int dp[2005][2005];

int max(int x,int y) // Function returning the maximum of two numbers a and b.
{
  if(x>y)
    return x;
  else 
    return y;
}

void lcs(char a[],char b[],int dp[][2005],int len,int len1)  //Longest common subsequence
                                                                     //Parameters a,b for comparison and dp[][] table for memoization
                                                                     // len is length of a and len1 length of string b
{
  int i,j;
  for(i=0;i<=len;i++)
    {
      for(j=0;j<=len1;j++)                                           //For every character in a traverse every character in b
	{
	  if(i==0 || j==0)                                           //If one of the string is empty length of LCS is 0
	    dp[i][j]=0;
	  else if(a[i-1]==b[j-1])                                    //If characters are same then length of LCS is simply one 
	                                                             //more than Length of LCS of these characters removed
	    dp[i][j]=dp[i-1][j-1]+1;
	  else
	    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);                     //Otherwise the length of LCS is max of LCS of i-1,j or i,j-1
	}
    }
}

int main(int argc,char * argv[])            //argv[1] consists of filename of first file
                                            //and argv[2] filename of file2
{
  char ch,f1[]="tmp1.txt",f2[]="tmp2.txt";
  int t,i,j;
  fstream ifile,ofile;
  int total_lcs=0;
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
	a[i]='\0';                          //Breaking first file in paragraph of 'N' words
	ofile.open(f2,ios::in);
	int maximum=INT_MIN;		
	while(ofile)
	  {
	    j=0;
	    while(ofile>>ch && j<N)
	      {
		b[j++]=ch;                  //Breaking second file in paragraph of 'N' words
	      }
	    b[j]='\0';
	    int len=strlen(a);
	    int len1=strlen(b);
  	    lcs(a,b,dp,len,len1);           //Applying LCS on these bisected paragraphs

	    maximum=max(maximum,dp[len][len1]);//Store maximum length of LCS among the two paragraphs
	                                       //(Maximum similarity) of all scores 
	  }
	ofile.close();                        //Close open files
      printf("Maximum  %d\n",maximum);
      total_lcs+=maximum;                    //Add all maximum scores to compute total score.
    }
  cout<<"Longest common subsequence  = "<<total_lcs<<"\n";
  return 0;
}
