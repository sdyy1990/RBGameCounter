#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int main(){
   string s; int k = 0 ;
   while (1) {
     getline(cin,s);
     if (s.size()<10) break;
     char *p = const_cast <char *> (s.c_str());
     int a,b; char c; int d;
     char s1[100],s2[100],s3[100],s4[100];
     char s5[100],s6[100],s7[100],s8[100],s9[100];
     //printf("%s\n",p);
     sscanf(p,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",s1,s2,s3,s4,s5,s6,s7,s8,s9);
//     cout << a <<" "<< b << c <<" "<<d  << endl;
     printf("%s,",s4);
     if ((++k)%12 ==0) printf("\n");
//     printf("%s.%s.%s.%s\n",s5,s6,s7,s8);
    
   }
}
