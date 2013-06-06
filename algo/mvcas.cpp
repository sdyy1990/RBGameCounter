#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

#include "subgraph.cpp"
int map_n;
int map_ans;
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
   map_ans = k;
}
string getmodestringA(int todel,int mask) {
//   int todel = data[lch[root]];
   int isAdj[32];   int isAdjAdj[32];
   memset(isAdj,0,sizeof(isAdj)); 
   memset(isAdjAdj,0,sizeof(isAdjAdj));
   for (int i = 0,im = 1 ; i < map_n; i++,im<<=1) 
     if (graph[todel][i] && ((im & mask)==0)) isAdj[i] = 1; 
//   cout << endl;
   SubGraph * sg = new SubGraph(0);
   for (int i = 0 , im = 1; i< map_n; i++, im<<=1)      if (isAdj[i])
       for (int j = 0 , jm=1; j<map_n; j++, jm<<=1)
         if (i!=j && j!=todel && graph[i][j] && ((jm&mask)==0))  
            sg->insertEdge(i,j);
     
   
   for (int i = 0 , im = 1; i< map_n; i++, im<<=1)      if (isAdj[i])
       for (int j = 0 , jm=1; j<map_n; j++, jm<<=1) if (isAdj[j])
         if (i!=j && graph[i][j]) {
            sg->insertEdge(i,j);            sg->insertEdge(j,i);
         }
   string s = sg->degree_string_A();

   return s;
   

}
typedef void pfunc(int [], int &,int); //put result into [], length == n
//calc 
int path[32];
int degree[32];
int totcnt=0;
void original_order_func(int result[],int &n,int mask) {
  n = 0 ;
  for (int i = 0,im = 1 ;  i < map_n; i++,im<<=1)
     if ((mask & im) ) 
        result[n++] = i;
}
void degree_order_func(int result[],int &n, int mask) {
   original_order_func(result,n,mask);
   for (int i = 0; i < n ; i++)
     for (int j = i+1 ; j < n ; j++)
        if (degree[result[i]]<degree[result[j]]) {
           int t = result[i]; result[i] = result[j]; result[j] = t;
        }
}
void random_order_func(int result[],int &n,int mask) {
   original_order_func(result,n,mask);
   random_shuffle(result,&result[n]);
}

string tostring(vector<int> VI) {
  stringstream ss;
  for(int i = 0 ; i < VI.size(); i++) ss << VI[i]<<".";
//  for (int i = 0 ; i < VI.size(); i++) cout << VI[i] <<",";
  string s; ss >> s;   return s;
}
map<string,int> mapcnt2;
#define MODE_MINUM_THRESH 800
void loadmode() {
   mapcnt2.clear();
   while (1) {
     string s;
     getline(cin,s);
     if (s.size()==0) break;
     stringstream ss; ss << s;
     int a,b;
     ss>>a >>s >>b;
     mapcnt2[s]+=b;
//     if (iM->second > MODE_MINUM_THRESH) cerr << s <<"--"<< b << endl;
   }
   for(map<string,int>::iterator iM = mapcnt2.begin(); iM!=mapcnt2.end(); iM++)
     if (iM->second>MODE_MINUM_THRESH) cerr << iM->first<<"-->"<<iM->second<<endl;
        else iM->second = 0;
}
int get_modecount(int todel,int mask) {
     vector<int> VI; VI.clear();
     for (int i = 0 , im = 1; i< map_n; i++, im<<=1) 
       if (graph[todel][i] && ((im & mask)))
         VI.push_back(degree[i]);
     sort(VI.begin(),VI.end());
     string s = tostring(VI);
//     cout << s <<"||->"<<mapcnt2[s]<<endl;
     int res=  mapcnt2[s];
     if (res>0) return res; return 1000+degree[todel];
 
}
map<string,int> expandmodesmap;
void loadexpandedmode() {
    expandmodesmap.clear();
    while (1) {
      string s;
      getline(cin,s);
      if (s.size() ==0) break;
      stringstream ss; ss << s;
      int i;  ss>> s >> i; if (s[s.size()-1] !='.') s.push_back('.');
//      cout << s << endl;
      expandmodesmap[s] = i;
    }
}
void expanded_mode_func(int result[], int &n, int mask) {
   original_order_func(result,n,mask);
   int cnt[32];
   for (int i = 0 ; i < n ; i++) {
      string s = getmodestringA(result[i],mask);
//      cout << result[i] <<"::"<< s << expandmodesmap[s] << endl;

//      cnt[result[i]] = expandmodesmap[getmodestringA(result[i],mask)];
   }
   for (int i = 0; i < n ; i++)
     for (int j = i+1 ; j < n ; j++)
        if (cnt[result[i]]<cnt[result[j]]) {
           int t = result[i]; result[i] = result[j]; result[j] = t;
        }

}
void mode_order_func(int result[],int &n,int mask) {
   original_order_func(result,n,mask);
 //  if (n>=5) {
 //     degree_order_func(result,n,mask);
 //     return;
 //  }
   int cnt[32]; //memcpy(tmp,result,sizeof(tmp));
   for (int i = 0 ; i < n ; i++)
      cnt[result[i]] = get_modecount(result[i],mask);
    
   for (int i = 0; i < n ; i++)
     for (int j = i+1 ; j < n ; j++)
        if (cnt[result[i]]<cnt[result[j]]) {
           int t = result[i]; result[i] = result[j]; result[j] = t;
        }
 //  for (int i = 0 ; i<n; i++) {
 //    printf("%d:%d %d\t",result[i],cnt[result[i]],degree[result[i]]);
 //  }
 //  printf("\n");
}
bool dfs(int mask, int left, pfunc P,int depth );
map<int,int> visitedmaskwithminiumD;
#define MAXX 10000000
bool needprejudge = false;
int prejudgesize;

int main(int argc, char * argv[])
{
   if (argc <= 2) {
     printf("usage : mvcas gameid algorithm prejudgesize\n, gameid in 1..100, \n algorithm: \tO for order_id\n");
     printf("\tD for degree-decrease\n\tM for modecount\n\tR for random\t");
     
     return 0;
   }
   int gameid;
   sscanf(argv[1],"%d",&gameid);
//   printf("%d gameid",gameid);
   readgraph(gameid);
   memset(degree,0,sizeof(degree));
   visitedmaskwithminiumD.clear();
   if (argc>=4) {needprejudge = true;  sscanf(argv[3],"%d",&prejudgesize); }
   for (int i = 0 ; i < map_n ; i++) 
      for (int j = 0 ; j < map_n ; j++) 
         if (graph[i][j]) degree[i]++;
   if (argv[2][0] =='O')
      dfs((1<<map_n)-1,map_ans,original_order_func,0);
   else if (argv[2][0] =='D')
      dfs((1<<map_n)-1,map_ans,degree_order_func,0);
   else if (argv[2][0] =='M') {
      loadmode();
      dfs((1<<map_n)-1,map_ans,mode_order_func,0);
   }
   else if (argv[2][0] =='m') {
      loadexpandedmode(); //return 0;
      dfs((1<<map_n)-1,map_ans,expanded_mode_func,0);
   }
   else if (argv[2][0] =='R')
      dfs((1<<map_n)-1,map_ans,random_order_func,0);
   
  
    
   if (totcnt>MAXX) printf("tot backtrack count > %d\n",MAXX); 
   else printf("gid=,%d, btcnt=,%d, method=,%s,prejudgesize=,%d\n",gameid,totcnt,argv[2],prejudgesize);
}
int bitcount(unsigned int x) {
   int count=0 ;
   while (x){
         count++ ;
         x &= (x - 1) ;
   }
      return count ;
}
bool prejudge(int mask,int left) {
   for (int i = 0 ; i < mask; i++) if ((i & mask) == i)
     if (bitcount(i)==left) {
        bool succ = true;
        for (int xi = 0, xm = 1; xi<map_n && succ; xi++,xm<<=1) if (xm & mask) 
           for (int yi = 0, ym = 1; yi<map_n && succ; yi++,ym<<=1) if (ym & mask)
              if (graph[xi][yi] && ((xm & i) ==0) &&((ym&i)==0)) succ=false;
        if (succ) return true;
     }
  return false;
}
#define PREJUDGE_SIZE 5
bool dfs(int mask, int left, pfunc P, int depth){
//   for (int i = 0 ; i < depth; i++) cerr << path[i]<<"\t"; cerr << endl;
   if (mask ==0 ) {
   //   for (int i = 0 ; i < depth; i++) printf("%d\t",path[i]); printf("\n");
      if (mask==0) return true;
   }
   if (needprejudge) if (bitcount(mask)<=prejudgesize) {
      if (!prejudge(mask,left)) { //printf("!!");
           totcnt++; return false;
      }
//      return true;
   }
   visitedmaskwithminiumD[mask] = depth;
   if (totcnt > MAXX|| left ==0) { totcnt++;  return false;} 
//   if (left ==0) return false;
   int buf[32]; int n_buf;
   memset(buf,0,sizeof(buf));
   P(buf,n_buf,mask);
   for (int i = 0 ; i < n_buf; i++) {
      int todel;
      todel=path[depth]=buf[i];
      int backdegree= degree[todel]; degree[todel] = 0;
      for (int j = 0 , jm=1; j<map_n; j++, jm<<=1)
        if ((jm & mask) && graph[todel][j]) degree[j]--;
      int newmask = 0 ;
      for (int j = 0 , jm=1; j<map_n; j++, jm<<=1)
        if (degree[j]) newmask += jm;
      bool flag = (visitedmaskwithminiumD.count(newmask) ==0);
      if (!flag) flag = (depth+1<visitedmaskwithminiumD[newmask]);
      if (flag)//  {
         if (dfs(newmask,left-1,P,depth+1)) return true;
      
      degree[todel] = backdegree;
      for (int j = 0 , jm=1; j<map_n; j++, jm<<=1)
        if ((jm & mask) && graph[todel][j]) degree[j]++;
   }
         totcnt++;
   return false;
}
