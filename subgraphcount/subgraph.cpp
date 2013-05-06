#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int map_n;
int graph[32][32];
map<int,string> graphlines;
void readgraph(int gameid) {
   stringstream ss;
   if (graphlines.find(gameid)!=graphlines.end()) {
       ss << graphlines[gameid];
   } else {
   ifstream fin ("graph.txt");
   string s;
   for (int i = 1; i<gameid; i++) getline(fin,s);
   getline(fin,s);
   ss << s;
   }
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
int  dfs(int ,int ,int,int);
typedef pair<int,int> P2;
typedef map<P2,int> MP2;
MP2 mapcnt;
int idcnts[200];
int subgraphid;
int main(int argc, char * argv[])
{
//   printf("argc = %d\n",argc);
   memset(idcnts,0,sizeof(idcnts));
   int totcount = 0;
   while (cin >> s) {
      if (s[0]!='C') continue;
      char *p = const_cast<char *> (s.c_str());
      int mgameid;
      char s1[100];
      sscanf(p,"C%[^,]",s1);
      sscanf(s1,"%d",&mgameid);
      readgraph(mgameid);
      subgraphid = 0;
      idcnts[mgameid]++;
      //cout << s << endl;
      cleantree();
      int root = 0;
      father[root] = -1;
      int thereismore = 1;
      while (thereismore) thereismore =insert(root);
      while (father[root] !=-1) root = father[root];
      memset(degree,0,sizeof(degree));
      for (int i = 0 ; i < map_n; i++)
         for (int j = 0 ; j < map_n; j++)
            if (graph[i][j]) degree[i]++;
      dfs(root,0,0,mgameid);
   }
}
class SubGraph {
public:
  int n,e,mgameid;
  map<int,int> subid;
  set< pair<int,int> > SPI;
  SubGraph(int mgid) {
     n = 0;
     e = 0;
     this->mgameid = mgid;
     subid.clear(); SPI.clear();
     subgraphid++;
  }
  int getsubid(int x) {
//     cout << "GSid" << x << endl;
     if (subid.find(x)!=subid.end()) return subid[x];
     subid[x] = ++n;
     return subid[x];
  }
  void insertEdge(int x, int y) {
     int mx = this->getsubid(x);
     int my = this->getsubid(y);
     if (mx < my) SPI.insert(make_pair(mx,my));
           else   SPI.insert(make_pair(my,mx));
  }
  void tofile() {
     char filename[100];
     sprintf(filename,"%d.%d.%d.sg\0",mgameid,idcnts[mgameid],subgraphid);
     if (SPI.empty()) return ;
     FILE *file = fopen(filename,"w");
     int kk;
     fprintf(file,"%d %d\n",n,kk = (int) (SPI.size()));
     for (int i = 1; i<=kk; i++) fprintf(file,"%d\n",i);
     for (set<pair<int,int> > ::iterator iSPI = SPI.begin(); iSPI!=SPI.end(); iSPI++)
       fprintf(file,"%d %d\n",(iSPI->first),(iSPI->second));
     fclose(file);
  }  
 
};
int dfs(int root,int mask,int mode,int mgid) {
   if (lch[root]<0) return 0;
   int todel = data[lch[root]];
   //COUNT_situation
   int isAdj[32];
   int isAdjAdj[32];
   memset(isAdj,0,sizeof(isAdj)); 
   memset(isAdjAdj,0,sizeof(isAdjAdj));
   //cout <<"todel is "<<todel<< endl;
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) isAdj[i] = 1;
   SubGraph * sg = new SubGraph(mgid);
   for (int i = 0 , im = 1; i< map_n; i++, im<<=1) 
     if (isAdj[i])
       for (int j = 0 , jm=1; j<map_n; j++, jm<<=1)
         if (i!=j && j!=todel && graph[i][j] && ((jm&mask)==0))
            sg->insertEdge(i,j);
   stringstream ss; ss <<"todelis"<<todel; string filename; ss>>filename;
   sg->tofile();
   delete sg;
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) degree[i] --;

   dfs(lch[root], mask | (1<<todel), mode,mgid);
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1)
     if (graph[todel][i] && ((im & mask)==0)) degree[i] ++;

}
