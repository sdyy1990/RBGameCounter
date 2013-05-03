#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
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
   treesize = 1;
   memset(lch,sizeof(lch),0xFF);
   memset(brother,sizeof(brother),0xFF);
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
int insert(int &root) {
   int who,thereismore;
   int move_style = get_move_style(who,thereismore);
   if (move_style == MOVE_UNDO) {
      data_enable[root] = -1;
      root = father[root];
      return thereismore;
   }
      int prlch = lch[root];
      lch[root] = treesize++;
      father[lch[root]]= root;
      brother[lch[root]] = prlch;
      root = lch[root];
      data[root] = who;
      data_enable[root] = 1;
      lch[root] = -1;
      return thereismore;
   

}
int  dfs(int ,int ,int);
void doSubGraphDegreeCount(int);
typedef pair<int,int> P2;
typedef map<P2,int> MP2;
MP2 mapcnt;
int main(int argc, char * argv[])
{
//   printf("argc = %d\n",argc);
   if (argc == 1) {
     printf("usage of modecounter:\n");
     printf("-----------graph.txt must exist\n");
     printf("modecounter [gameid] : count modes of gameid, gameid<0: gameid for all, input : stdin,\n\n");
     printf("modecounter [gameid] C: count sub-graph-degree-modes of gameid \n"); 
     printf("output format: Ggameid, mode ,count \n");
     return 0;
   }
   int gameid;
   sscanf(argv[1],"%d",&gameid);
   //printf("%d",gameid);
   if (argc == 3) {
      doSubGraphDegreeCount(gameid); return 0;
   }
   mapcnt.clear();
   int totcount = 0;
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
      int root = 0;
      int thereismore = 1;
      while (thereismore) thereismore =insert(root);
      while (father[root] !=0) root = father[root];
      memset(degree,0,sizeof(degree));
      for (int i = 0 ; i < map_n; i++)
         for (int j = 0 ; j < map_n; j++)
            if (graph[i][j]) degree[i]++;
      dfs(root,0,0);
   }
   int ans[32][32];
   memset(ans,0,sizeof(ans));
      for (MP2::iterator iMP = mapcnt.begin(); iMP!=mapcnt.end(); iMP++) {
           ans[(iMP->first).first][(iMP->first).second] = iMP->second;
      }
   for (int i = 1; i<=20; i++) {
      for (int j = 1; j<=20; j++)
         printf("%6d,",ans[i][j]);
      printf("\n");
   }
}
map<string,int> mapcnt2;
void doSubGraphDegreeCount(int gameid) {
    mapcnt2.clear();
    while (cin >> s) { if (s[0]!='C') continue;
       int mgameid; char s1[100]; char *p = const_cast<char *> (s.c_str()); 
       sscanf(p,"C%[^,]",s1); sscanf(s1,"%d",&mgameid); 
       if (mgameid!=gameid) continue;
       readgraph(mgameid);
  //     cout << s<< endl;
       cleantree(); int root = 0, thereismore = 1;
       while (thereismore) thereismore = insert(root);
       while (father[root]!=0) root = father[root];
      // for (int i = 0 ; i < treesize; i++) 
       //  printf("%3d %3d %3d %3d\n", father[i], lch[i],brother[i],data[i]);
       memset(degree,0,sizeof(degree));
       for (int i = 0 ; i < map_n; i++)
          for (int j = 0 ; j < map_n; j++)
             if (graph[i][j]) degree[i]++;
       dfs(root,0,1);
    }
    for (map<string,int>::iterator iM = mapcnt2.begin(); iM!=mapcnt2.end(); iM++)
      printf("%03d\t%s\t\t%d\n",gameid,iM->first.c_str(),iM->second);
}
string tostring(vector<int> VI) {
  stringstream ss;
  for(int i = 0 ; i < VI.size(); i++) ss << VI[i]<<".";
//  for (int i = 0 ; i < VI.size(); i++) cout << VI[i] <<",";
  string s; ss >> s;   return s;
}
int dfs(int root,int mask,int mode) {
   if (lch[root]<0) return 0;
   int todel = data[lch[root]];
   //COUNT_situation
   if (mode == 0) {
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) {
        P2 p = make_pair(degree[i],degree[todel]);
        mapcnt[p]++;
     }
   }
   if (mode == 1) {
     vector<int> VI; VI.clear();
     for (int i = 0 , im = 1; i< map_n; i++, im<<=1) 
       if (graph[todel][i] && ((im & mask) ==0))
         VI.push_back(degree[i]);
     sort(VI.begin(),VI.end());
//     cout << tostring(VI)<< endl;
     mapcnt2[tostring(VI)]++;
   }

   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) degree[i] --;

   dfs(lch[root], mask | (1<<todel), mode);
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) degree[i] ++;

}
