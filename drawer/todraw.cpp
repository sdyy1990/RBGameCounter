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
/*
\begin{tikzpicture}[scale=1.8, auto,swap]
    % First we draw the vertices
    \foreach \pos/\name in {{(0,2)/a}, {(2,1)/b}, {(4,1)/c},
                            {(0,0)/d}, {(3,0)/e}, {(2,-1)/f}, {(4,-1)/g}}
        \node[vertex] (\name) at \pos {$\name$};
    % Connect vertices with edges and draw weights
    \foreach \source/ \dest /\weight in {b/a/7, c/b/8,d/a/5,d/b/9,
                                         e/b/7, e/c/5,e/d/15,
                                         f/d/6,f/e/8,
                                         g/e/9,g/f/11}
        \path[edge] (\source) -- (\dest);
    % Start animating the vertex and edge selection.

\end{tikzpicture}

*/
int main(int argc, char * argv[])
{
  printf("usage: drawer [graphid]\n") ;
  printf("graph.txt must exist\n");
  printf("std for (x,y) locations\n");
  int gameid;
  sscanf(argv[1],"%d",&gameid);
  readgraph(gameid);
  int x[32],y[32];
  for (int i = 0 ; i < map_n; i++)  {
    printf("x y for %d:\n",i);
    scanf("%d %d", &x[i],&y[i]);
 }

  FILE * fout =   fopen("out.txt","w");
  fprintf(fout,"\\tikzstyle{vertex}=[circle,fill=black!25,minimum size=20pt,inner sep=0pt] \n\\tikzstyle{edge} = [draw,thick,-]\n\n");

  fprintf(fout,"\\begin{tikzpicture}[scale=1.8, auto,swap]\n");
  fprintf(fout,"    %% First we draw the vertices");

  fprintf(fout,"    \\foreach \\pos/\\name in {\n");
  for (int i = 0 ; i < map_n; i++) {
    fprintf(fout,"{(%d,%d)/v%d}",x[i],y[i],i);
    if (i!=map_n-1) fprintf(fout,",");
    if (i%5 ==0) fprintf(fout,"\n");
    }
  fprintf(fout,"}\n");
  fprintf(fout,"       \\node[vertex] (\\name) at \\pos {$\\name$}; \n   %% Connect vertices with edges\n");
  fprintf(fout,"\\foreach \\source/ \\dest in \n");
  int  t = 0;
  for (int i = 0 ; i < map_n; i++)
    for (int j = i+1; j< map_n; j++) if (graph[i][j]){
       if (t) fprintf(fout,","); else fprintf(fout,"{");
       fprintf(fout,"v%d/v%d",i,j);
       if ((++t % 5) == 0 ) fprintf(fout,"\n");
    }
  fprintf(fout,"}\n        \\path[edge] (\\source) -- (\\dest); \n");
  fprintf(fout,"\\end{tikzpicture}\n");
  fclose(fout);
  return 0;
}
