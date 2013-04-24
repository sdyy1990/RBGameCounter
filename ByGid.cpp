#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
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

int median(vector<int> VInew) {
   sort(VInew.begin(),VInew.end());
   return VInew[VInew.size()/2];
}
int min(vector<int> VInew) {
   int ii = VInew[0];
   for (int i = 0 ; i < VInew.size(); i++)
     if (ii > VInew[i]) ii = VInew[i];
   return ii;
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
   cout <<"Gameid,totSubmit,tot_U,avr_U,ans,U/ans,median_U,min_U"<<endl;
   for (map<int , vector<string> >::iterator iMID = MAPID.begin(); iMID!=MAPID.end(); iMID++) {
     gamelist = &( iMID->second) ;
     int tot = 0 , cnt = 0 ;
     int DCNT;
     vector<int> VIL;
     for (vector<string>::iterator iG = gamelist-> begin(); iG!=gamelist->end(); iG++) {
        tot ++;
        int U; int D;
        DCNT= getCount(*iG,U,D);
        VIL.push_back(U);
     //   cout << U <<" " << D;
        cnt += U;
     }
     cout << iMID->first<<","<<tot<<","<<cnt<<","<<cnt*1.0/tot<<","<<DCNT<<","
           <<cnt*1.0/(tot*DCNT)<<","<<median(VIL)<<","<<min(VIL)<<endl;
   }
   return 0;
}
