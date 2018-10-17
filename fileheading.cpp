#include<iostream>
#include<fstream>
#include<map>
#include<string.h>
#include<string>
#include<math.h>
#include<stdio.h>
#include<unistd.h>
#define piby2 1.5708
using namespace std;
int main(int argc,char * argv[])
{
 fstream wfile1;
 char str[50]; 
 getcwd(str, sizeof(str));
 char stud1[50],stud2[50],path1[50];
 strcat(str,"//logstatus");
 chdir(str); 
 strcpy(stud1,argv[1]);
 strcat(stud1,"_logfile.txt");
  wfile1.open(stud1,ios::out);
 wfile1<<"File1"<<"\t\t"<<"File2"<<"\t\t"<<"W1"<<"\t"<<"W2"<<"\t"<<"Sim_score\t\t"<<"Edit_score\t"<<"LCS_score\t\t"<<"Wt_Score"<<"\n";  
 return 0;
}
