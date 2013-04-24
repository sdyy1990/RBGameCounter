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
   string name;
   stringstream sid; sid << gameid; sid>>name;  name = name +".csv";
   ofstream fout; 
   fout.open(name.c_str());
   for (int i = 0 ; i < map_n; i++) {
     for (int j = 0 ; j < map_n ; j++)
        fout << graph[i][j]<<",";
     fout << endl;
   }
   fout.close();
}
int main(){
   for (int i = 1; i<= 100; i++)
     readgraph(i);
}
