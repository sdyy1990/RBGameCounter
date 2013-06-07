#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int graph[32][32];
int putedge(int n,float p) {
  srand(time(0));
  int ans  = 0 ;
  for (int i = 0 ; i < n ; i++)
     for (int j =i+1 ; j < n ; j ++)
        ans += (graph[i][j] = graph[j][i] = ((rand() % 32767) < (p*32768)));
  return ans;
}
int count(int i ) {
   int ans = 0 ;
   while (i) {
      if (i & 1) ans ++;
      i >>= 1;
   }
   return ans;
}
int isvc(int mask,int n) {
  for (int i = 0 ; i < n ; i ++)
    for (int j = i +1; j< n ; j++) 
      if (graph[i][j])
        if (( ((1<<i)+(1<<j)) & mask) ==0) return 0;
  return 1;
}
int getmvc(int n) {
  int min = n;
  for (int i = 0 ; i < (1<<n); i++)
    if (isvc(i,n) && count(i) < min)
      min = count(i);
  return min;
}
int main( int argc, char * argv[])
{
   int n; float p;
   if (argc<3) printf("parameter n p\n");
   sscanf(argv[1],"%d",&n);
   sscanf(argv[2],"%f",&p);
//   printf("%d %.2f",n,p);
   int e = putedge(n,p);
   printf("%d %d %d",n,getmvc(n),e);
   for (int i = 0 ; i < n ; i++)
     for (int j = i+1; j<n; j++) if (graph[i][j]) 
        printf(" %d %d",i,j);
   printf("\n");
   return 0;
}
