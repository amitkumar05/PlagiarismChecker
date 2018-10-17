/*
		Code to generate final_log file after checking plagarised document having similarity score more than threshold
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

#define piby2 1.5708

#define threshold 0.70

using namespace std;

int main(int argc,char * argv[])
{
 fstream wfile1,rfile;
 char str[50]; 
 getcwd(str, sizeof(str));
 char stud1[50],stud2[50],path1[50];
 strcat(str,"//logstatus");
 chdir(str); 
 strcpy(stud1,argv[1]);
 //strcat(stud1,"_logfile.txt");
 strcpy(stud2,"final_logfile.txt");
 
 char name1[50],name2[50],mname1[50],mname2[50];
 float l1,l2,dd,ed,lcs,wt,ml1,ml2,mdd,med,mlcs,mwt;
 float max=0;
rfile.open(stud1,ios::in);
rfile>>name1>>name2>>name1>>name2>>name1>>name2>>name1>>name2;
//cout<<name2<<"\n";
 while(rfile)
 {
//cout<<"hi\n";

	rfile>>name1>>name2>>l1>>l2>>dd>>ed>>lcs>>wt;
        //cout<<name1<<"\t"<<name2<<"\n";
        if(wt>max)
	{
		strcpy(mname1,name1);
		strcpy(mname2,name2);
		ml1=l1;
		ml2=l2;
		mdd=dd;
		med=ed;
		mlcs=lcs;
		mwt=wt;
		max=wt;
	}
 }
  char result[50];
  if(mwt>threshold)
	strcpy(result,"Plagarised");
  else
	strcpy(result,"Not Plagarised");

  wfile1.open(stud2,ios::out|ios::app);
  wfile1<<mname1<<"\t\t"<<mname2<<"\t\t"<<ml1<<"\t"<<ml2<<"\t"<<mwt<<"\t\t"<<result<<"\n";

return 0;
}

