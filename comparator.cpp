/*

	Implementing Document distance for finding the similarity between two document

	Treating the document as a N  dimentional vector and finding distance
	measure between two submissions

*/	  

#include<iostream>
#include<fstream>
#include<map>
#include<string.h>
#include<string>
#include<math.h>
#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include "parser.h"
#define piby2 1.5708
using namespace std;

////////////////////// edit dis
char a[2005],b[2005];
int dp[2005][2005];

int N=200;

int  min(int a,int b)
{
  if(a>b)
    return b;
  else 
    return a;
}

///////////////////  lcs


int max(int x,int y)
{
  if(x>y)
    return x;
  else 
    return y;
}

void lcs(char a[],char b[],int dp[][2005],int len,int len1)
{
  int i,j;
  for(i=0;i<=len;i++)
    {
      for(j=0;j<=len1;j++)
	{
	  if(i==0 || j==0)
	    dp[i][j]=0;
	  else if(a[i-1]==b[j-1])
	    dp[i][j]=dp[i-1][j-1]+1;
	  else
	    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
	}
    }
}



//////////////////


// function to check equality of characters

int fix(int i,int j)
{
  if(a[i-1]==b[j-1])
    return 0;
  else 
    return 1;
}

void editdistance(char a[],char b[],int dp[][2005],int len,int len1)
{
  int i,j;
  for(i=0;i<=len;i++)
    {
      for(j=0;j<=len1;j++)
	{
	  if(i==0)
	    {dp[i][j]=j;}						
	  else if(j==0)
	    {dp[i][j]=i;}
	  else
	    {
	      long long int p=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+(fix(i,j)));
	      dp[i][j]=p;
	    }
	}
      
    }
}
//////////////////////


int main(int argc,char * argv[])
{
 
 char str[50]; 
 getcwd(str, sizeof(str));
 strcat(str,"//samples");
 chdir(str); 


 fstream ifile,ofile;
  
 //  opening the file
 ifile.open(argv[1],ios::in);
  ofile.open(argv[2],ios::in);
  string s;
  int cnt1=0,cnt2=0;
  map <string,int> m,m1,m2;
 
 //reading file 1
 while(ifile>>s)
  {
    m[s]=0;
     m1[s]++;
     cnt1++;
  }

 //reading file 2
  while(ofile>>s)
  {
    m[s]=0;
     m2[s]++;
     cnt2++;
  }

  double dot=0,mod1=0,mod2=0,costheta=0;
  
 // Calculating disatance between two documents using dot product as distance measure 

  map<string,int> :: iterator it;
  for(it=m.begin();it!=m.end();it++)
   {
     
     double a,b;
     a=m1[it->first];
     b=m2[it->first];
     dot+=a*b;
     mod1+=(a*a);
     mod2+=(b*b);
   }
  if(mod1==0 || mod2 ==0)
	costheta=0;
  else
  costheta=dot/(sqrt(mod1)*sqrt(mod2));
 // cout<<costheta<<"\n";
 float sim_score;
 if(costheta>=0.9999)
	sim_score=1;
 else
      sim_score=1 - acos(costheta)/piby2;
 float edit_score,lcs_score,weight_score;
  // cout<<costheta<<"  "<<mod1<<"  "<<mod2<<"\n";
  // cout<<"Similarity score is = "<<"  "<<acos(costheta)<<"  "<<1-acos(costheta)/piby2<<"\n";
  //cout<<"Similarity score is = "<<1-acos(costheta)/piby2<<"\n";
//  cout << "words in doc 1 : " << cnt1 << "  Words in doc2 : " << cnt2 << "\n";
//  cout << "Distance between docs is :" << 1 - acos(costheta)/piby2<< "\n";
 ifile.close();ofile.close();   


/////////////////////////edit dis



char ch,f1[]="tmp1.txt",f2[]="tmp2.txt";
  int t,i,j;
  float total_edit=0;
  int l1=parse(argv[1],f1);
  int l2=parse(argv[2],f2);
 
if(l1<l2)
    {
      strcpy(f1,"tmp1.txt");
      strcpy(f2,"tmp2.txt");
    }
  else 
    {
      strcpy(f2,"tmp1.txt");
      strcpy(f1,"tmp2.txt");
    }
  ifile.open(f1,ios::in);

  while(ifile>>ch)
    {
      // Breaking both files in paragraphs of 500 words and then  applying Edit Distance on the files
      i=0;
     while(ifile>>ch && i<N)
	{
	  a[i++]=ch;
	}
	a[i]='\0';
	ofile.open(f2,ios::in);
	int minimum=INT_MAX;		
	while(ofile)
	  {
	    j=0;
	    while(ofile>>ch && j<N)
	      {
		b[j++]=ch;
	      }
	    b[j]='\0';
	    int len=strlen(a);
	    int len1=strlen(b);		
	    editdistance(a,b,dp,len,len1);
	    minimum=min(minimum,dp[len][len1]);
	  }
      ofile.close();
   //     printf("Minimum  %d\n",minimum);
      total_edit+=minimum;
    }
 edit_score=total_edit;
 edit_score=1-(edit_score/(2*max(min(l1,l2),N)));
 ifile.close();
 ofile.close();
//////////////////////////////


////////////////////////////lcs


   strcpy(f1,"tmp1.txt");
  strcpy(f2,"tmp2.txt");
  //int t,i,j;
  //fstream ifile,ofile;
  int total_lcs=0;
   l1=parse(argv[1],f1);
   l2=parse(argv[2],f2);
  if(l1<l2)
    {
      strcpy(f1,"tmp1.txt");
      strcpy(f2,"tmp2.txt");
    }
  else 
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
	a[i]='\0';
	ofile.open(f2,ios::in);
	int maximum=INT_MIN;		
	while(ofile)
	  {
	    j=0;
	    while(ofile>>ch && j<N)
	      {
		b[j++]=ch;
	      }
	    b[j]='\0';
	    int len=strlen(a);
	    int len1=strlen(b);
  	    lcs(a,b,dp,len,len1);
	    maximum=max(maximum,dp[len][len1]);
	  }
      ofile.close();
   //   printf("Maximum  %d\n",maximum);
      total_lcs+=maximum;
    }
//  cout<<"Longest common subsequence  = "<<total_lcs<<"\n";
  lcs_score=total_lcs;
  if(min(l1,l2) == 0)
	lcs_score = 0;
  else
 lcs_score=lcs_score/min(l1,l2);
// cout<<" Lcs score = "<<lcs_score<<"\n";
 

/////////////////////////////


 fstream wfile1,wfile2;
  
 //  opening the file 
 chdir("..");
 //char str[50]; 
 getcwd(str, sizeof(str));
 char stud1[50],stud2[50],path1[50];
 strcat(str,"//logstatus");
 //strcpy(path2,"\\home");
// cout<<str<<"\n";
 chdir(str); 
//cout<<str<<"\n";
 

 strcpy(stud1,argv[1]);
 strcpy(stud2,argv[2]);
 strcat(stud1,"_logfile.txt");
 strcat(stud2,"_logfile.txt");

 //strcat(path1,stud1);
 //strcat(path2,stud2);
 
 
  wfile1.open(stud1,ios::out|ios::app);
  wfile2.open(stud2,ios::out|ios::app);

 weight_score=(sim_score+edit_score+lcs_score)/3;
 wfile1<<argv[1]<<"\t"<<argv[2]<<"\t"<<cnt1<<"\t"<<cnt2<<"\t"<<sim_score<<"\t\t"<<edit_score<<"\t\t"<<lcs_score<<"\t\t"<<weight_score<<"\n";  
  wfile2<<argv[2]<<"\t"<<argv[1]<<"\t"<<cnt2<<"\t"<<cnt1<<"\t"<<sim_score<<"\t\t"<<edit_score<<"\t\t"<<lcs_score<<"\t\t"<<weight_score<<"\n"; 
 //wfile.fclose();
//   wfile1<<sim_score<<"\n";
 return 0;
}
