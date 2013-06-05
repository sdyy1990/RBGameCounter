#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <numeric>
using namespace std;
int map_n;
int graph[32][32];
void readgraph(int gameid) {
   ifstream fin ("graph.txt");
   string s;
   for (int i = 1; i<gameid; i++) getline(fin,s);
   getline(fin,s);
//   cout << s << endl;
   stringstream ss;
   ss << s;
   int k,m,a,b;
   memset(graph,0,sizeof(graph));
   ss >> map_n>> k >> m;
        while(m--){
            ss >> a >> b;
            graph[a][b]=graph[b][a]=1;
        }
}
int lch[1024];
int brother[1024];
int father[1024];
int data[1024];
int data_enable[1024];
int degree[1024];
int treesize = 0;
string s;
char * readbuf;
void cleantree(){
   readbuf = const_cast<char *> (s.c_str());
   while (*readbuf !=';') readbuf++;
   readbuf++;
}
#define MOVE_UNDO 1
#define MOVE_D 0
int get_move_style(int &who, int &thereismore) {
   char c1; int x1;
//   printf("%s\n",readbuf);
   sscanf(readbuf,"%c,%d",&c1,&who);
   while (*readbuf !=';') readbuf ++; readbuf++;
   if (*readbuf =='\0') thereismore = 0; else thereismore = 1;
   if (c1 =='U') return MOVE_UNDO; else return MOVE_D;
}
//MP2 mapcnt;
int main(int argc, char * argv[])
{
//   printf("argc = %d\n",argc);
     printf("usage of modecounter:\n");
     printf("-----------graph.txt must exist\n");
   int gameid;
      vector<int> VQ;
   map<int,int> mapCNT;
   vector<int> backtracklength[101];
   while (cin >> s) {
      if (s[0]!='C') continue;
      char *p = const_cast<char *> (s.c_str());
      int mgameid;
      char s1[100];
      sscanf(p,"C%[^,]",s1);
      sscanf(s1,"%d",&mgameid);
      if (gameid>0)  if (mgameid != gameid) continue;
      readgraph(mgameid);
      //cout << s << endl;
      cleantree();
      memset(degree,0,sizeof(degree));
      for (int i = 0 ; i < map_n; i++)
         for (int j = 0 ; j < map_n; j++)
            if (graph[i][j]) degree[i]++;
      int who, thereismore=1;
      int lastaction = 0;
      vector<int> V1(degree,degree+map_n);
      stack<vector<int> > SVI; SVI.push(V1);
      int nowlength = 0 ;
      while (thereismore) {
         int action = get_move_style(who,thereismore);
         if (action == MOVE_UNDO) SVI.pop(); else {
            vector<int> newV ( SVI.top());
            newV[who] = 0;
            for (int i = 0 ; i < map_n; i++)
              if (newV[i]>0 && graph[who][i]) newV[i] --;
	    SVI.push(newV);
         }
         int graphsize = V1.size()-count(SVI.top().begin(),SVI.top().end(),0);
         if (action == MOVE_UNDO && lastaction != MOVE_UNDO)  {
           VQ.push_back(graphsize);
           mapCNT[graphsize]++;
           nowlength = 0;
         }
         if (action == MOVE_UNDO) nowlength ++;
         if (action!= MOVE_UNDO && lastaction == MOVE_UNDO) {
           backtracklength[mgameid].push_back(nowlength);
         }
         
          lastaction = action;
      //   printf("%d %d --> graphsize= %d\n",action,who,graphsize);
      }
   //   printf("\n");
   }
   cout <<" average graph size at the first backtrack of a list of backtrack= ";
   cout << accumulate(VQ.begin(),VQ.end(),0)*1.0/VQ.size()<<endl;
   cout <<"with distribtion" << endl;
   for (map<int,int>::iterator iM  = mapCNT.begin(); iM!=mapCNT.end(); iM++) 
     cout << iM->first<<"->:"<<iM->second<<endl;
   cout <<"average consequtive backtrack list length ";
   int x = 0 , y = 0 ;
   for (int i = 1; i<=100; i++) {
       x += accumulate(backtracklength[i].begin(),backtracklength[i].end(),0);
       y += backtracklength[i].size();
   }
   cout << x*1.0/y<<endl;
   cout <<"by gameid is "<<endl;
   for (int i = 1; i<=100; i++) 
     cout << accumulate(backtracklength[i].begin(),backtracklength[i].end(),0)*1.0/backtracklength[i].size() << endl;
}
