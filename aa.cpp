#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;
int main()
{
   string s;
   map<string,int> ID;
   set<int>  QQ[1000];
   int totcount = 0;
   while (cin >> s) {
     char *p = const_cast<char *> (s.c_str());
     char s1[100];
     char s2[100];
     char s3[100];
     sscanf(p,"C%[^,],%[^,],%[^,]",s1,s2,s3);
     string name(s3);
     int gameid;
     sscanf(s1,"%d",&gameid);
     cout << gameid << " " << name<< endl;
     if (ID.find(name) !=ID.end())
       QQ[ID[name]].insert(gameid);
     else 
       QQ[ID[name]=totcount++].insert(gameid);
   }
   for (map<string,int>::iterator iS = ID.begin(); iS!=ID.end(); iS++) {
     cout << iS-> first <<"\t,";
     bool ib [ 1000];
     int cnt = 0;
     for (int i = 1; i<=100; i++) {
       if (QQ[iS->second].find(i)!=QQ[iS->second].end()){
         cout <<"A"; cnt++;
         }
       else cout <<".";
       
     }
      cout << ","<<cnt<< endl;
   }
   return 0;
}
