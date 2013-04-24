#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
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
int  dfs(int ,int );
typedef pair<int,int> P2;
typedef map<P2,int> MP2;
MP2 mapcnt;
int main(int argc, char * argv[])
{
   int gameid;
   sscanf(argv[1],"%d",&gameid);
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
//      printf("root is %d\n",root);
      /*for (int i = 0 ; i < treesize; i++) {
         printf("%d:%14d%17d%4d%4d%4d\n",i,lch[i],brother[i],data[i],data_enable[i],father[i]);
      }
*/
      memset(degree,0,sizeof(degree));
      for (int i = 0 ; i < map_n; i++)
         for (int j = 0 ; j < map_n; j++)
            if (graph[i][j]) degree[i]++;
      dfs(root,0);
   }
   int ans[32][32];
   memset(ans,0,sizeof(ans));
      for (MP2::iterator iMP = mapcnt.begin(); iMP!=mapcnt.end(); iMP++) {
//         cout << (iMP->first).first<<"\t"<<(iMP->first).second<<"\t"<<iMP->second << endl;
           ans[(iMP->first).first][(iMP->first).second] = iMP->second;
      }
   for (int i = 1; i<=20; i++) {
      for (int j = 1; j<=20; j++)
         printf("%6d,",ans[i][j]);
      printf("\n");
   }
}

int dfs(int root,int mask) {
   if (lch[root]<0) return 0;
   int todel = data[lch[root]];
   //COUNT_situation
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) {
        P2 p = make_pair(degree[i],degree[todel]);
        mapcnt[p]++;
     }


   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) degree[i] --;

   dfs(lch[root], mask | (1<<todel));
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) degree[i] ++;

}
