#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <numeric>
using namespace std;
int getCount(string &game,int &U,int &D) {
   bool has = false; U = D = 0;
   for (int i = 0 ; i < game.size(); i++) {
       if (game[i] == ';') has = true;
       if (has &&  game[i] =='U') U ++;
       if (has &&  game[i] =='D') D ++;
   }
   return D-U;
}
int check(vector<int> &VI) {
   int avr = accumulate(VI.begin(),VI.end(),0) / VI.size();
   for (int i = 0 ; i < VI.size(); i++)
     if (VI[i] > avr * 20) VI[i] = avr;
//   return 0;
}
int func(int i) {
  cout << i <<",";
}
int print(vector<int> &VI) {
   for_each(VI.begin(),VI.end(),func);
   cout << endl;
}
int getUsedTime(string &game) {
   vector<int> VI;
   char *p = const_cast<char *> (game.c_str());
//  printf("%s\n",p);
//   cout  << endl;
   while (*p!=';') p++;
   p++;
   char c1; int x1,x2; int time = 0, ptime = 0;
   while ( sscanf(p,"%c,%d,%d",&c1,&x1,&x2) > 0) {
//     cout << c1 <<x1 <<","<<x2<<endl;
     //printf("%s\n",p);
     while (*p!=';') p++; p++;
     if (c1 == 'D') time = x2; else time = x1;
     VI.push_back(time-ptime);
     ptime = time;
   }
  // if (check(VI)) {
//      cout << game << endl;
 //     print(VI);
//   }
   check(VI);
   return accumulate(VI.begin(),VI.end(),0);
}
int main()
{
   string s;
//   map<string,vector<string> > MAPNAME;
   map<int,   vector<string> > MAPID;
   int totcount = 0;
   while (cin >> s) {
     if (s[0]!='C') continue;
     char *p = const_cast<char *> (s.c_str());
     char s1[100];
     char s2[100];
     char s3[100];
     sscanf(p,"C%[^,],%[^,],%[^,]",s1,s2,s3);
     string name(s3);
     int gameid;
     sscanf(s1,"%d",&gameid);
     MAPID[gameid].push_back(s);
//     MAPNAME[name].push_back(s);
   }
   vector<string> * gamelist;
   cout <<"Gameid,totSubmit,avr_T" << endl;
   for (map<int , vector<string> >::iterator iMID = MAPID.begin(); iMID!=MAPID.end(); iMID++) {
     gamelist = &( iMID->second) ;
     int tot = 0 , cnt = 0 ;
     int DCNT;
     for (vector<string>::iterator iG = gamelist-> begin(); iG!=gamelist->end(); iG++) {
        tot ++;
        int U; int D;
        cnt+= getUsedTime(*iG);
     //   cout << U <<" " << D;
     //   cnt += U;
     }
     cout << iMID->first<<","<<tot<<","<<cnt*1.0/tot<<endl;
   }
   return 0;
}
