/**************************************************************************************
        CS307(P)- 
         Amit Kumar    (B13107)
         Vinod Kumar   (B13141)
         Paawan Mukker (B13218)

	Implementing Document distance for finding the similarity between two document
	
	Document similarities are measured based on the content overlap between documents.
        There exist a vast number of complex algorithms to solve this problem. One of such
        algorithms is a cosine similarity - a vector based similarity measure. The cosine
        distance of two documents is defined by the angle between their feature vectors 
        which are, in our case, word frequency vectors.The word frequency distribution of
        a document is a mapping from words to their frequency count.

	Treating the document as a N  dimentional vector and finding distance
	measure between two submissions.

        The input is not parsed since we need vector in form of words and not character

****************************************************************************************/	  

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<math.h>
#define piby2 1.5708
using namespace std;
int main(int argc,char * argv[])
{
  fstream ifile,ofile;
  
  ifile.open(argv[1],ios::in);          //  opening the file 
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
     // cout<<s<<"\n";
  }

 //reading file 2
  while(ofile>>s)
  {
    m[s]=0;
     m2[s]++;
     cnt2++;
     //   cout<<s<<"\n";
  }

  double dot=0,mod1=0,mod2=0,costheta=0;
  
 // Calculating disatance between two documents using dot product as distance measure 

  map<string,int> :: iterator it;
  for(it=m.begin();it!=m.end();it++)
   {
     
     //      cout<<it->first<<"   "<<m1[it->first]<<"   "<<m2[it->first]<<"\n";
     double a,b;
     a=m1[it->first];
     b=m2[it->first];
     dot+=a*b;
     mod1+=(a*a);
     mod2+=(b*b);
     // cout<<dot<<"\n";
   }
 
  costheta=dot/(sqrt(mod1)*sqrt(mod2));
  // cout<<costheta<<"  "<<mod1<<"  "<<mod2<<"\n";
  // cout<<"Similarity score is = "<<"  "<<acos(costheta)<<"  "<<1-acos(costheta)/piby2<<"\n";
  //cout<<"Similarity score is = "<<1-acos(costheta)/piby2<<"\n";
  cout << "words in doc 1 : " << cnt1 << "  Words in doc2 : " << cnt2 << "\n";
  cout << "Distance between docs is :" << acos(costheta)/piby2<< "\n";

  return 0;
}
