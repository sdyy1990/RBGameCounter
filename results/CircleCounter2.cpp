#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <cstdio>
using namespace std;
const int maxn = 21;
long long dp[1<<maxn][maxn];//
int mp[maxn][maxn];
template<typename T> double var(vector<T> V) {
  vector<T> VI2;
  VI2.clear();
  for (int i = 0 ; i < V.size(); i++) {
     VI2.push_back(V[i]*V[i]);
  }
  double x1 = accumulate(V.begin(),V.end(),(double) 0.0)/V.size();
  double x2 = accumulate(VI2.begin(),VI2.end(),0);
  return x2/V.size() - x1*x1;
}
int getbitcount(int i) {
   int ans = 0;
   while (i) {
     i -= (i & (-i)); ans ++;
   }
   return ans;
}
void CountCircle(string s, long long & pp, vector<long long> &retans,int &nnn,long long &rans,long long &lmdcnt){
    int n,m,a,b,i,j,k;
    stringstream ss;
    ss << s;
    ss >> n >> k >> m;
    retans.resize(n);
    nnn = n;
    pp = 1;
    for (int i = 2; i<=n; i++) pp *= i;
//    while(scanf("%d%d",&n,&m)!=EOF){
        for (int i = 0 ; i < n ; i++) for(int j = 0 ; j < n ; j ++) mp[i][j] = 0;
        while(m--){
            ss >> a >> b;
//            a--;b--;
            mp[a][b]=mp[b][a]=1;
        }
        for(i=0;i<(1<<n);i++) for(j=0;j<n;j++) dp[i][j]=0;
        for(i=0;i<n;i++)  dp[1<<i][i]=1;
        long long ans=0;
        for(i=0;i<(1<<n);i++){
            int ccnti = getbitcount(i);
            for(j=0;j<n;j++){
                if(!dp[i][j])  continue;
                bool flag=0;
                for(k=0;k<n;k++){
                    if((1<<k)&i){
                        if(!flag&&mp[j][k]&&i!=((1<<j)+(1<<k))){//如果是起始点，且和结束点相连，且点集中至少有三个点，则构成了环
                            retans[ccnti]+=dp[i][j];
                        }
                        flag=1;
                    }
                    else if(flag && mp[j][k])
                     dp[i^(1<<k)][k]+=dp[i][j];
                }
            }
        }
    rans = 0;
    for (vector<long long>::iterator iR = retans.begin(); iR!=retans.end(); iR++)
      rans += *iR;
    lmdcnt = 0;
    for (int i = 0 ; i < n ; i++)
       for (int j = 0 ; j < n ; j++) if (i!=j && mp[i][j]==1)
          for (int k = 0 ; k < n ; k ++) if (i!=k && j!=k)
             if (mp[j][k]==1 && (mp[k][i] ==0)) lmdcnt++;
//   cout << rans << endl;
   // return rans; 
}
double logVar(vector<double> cntV) {
   vector<double> CC;
   for (int i = 0 ; i < cntV.size(); i++)
      if (cntV[i]>1e-20) CC.push_back(log(cntV[i]));
   return var(CC);
}
int main() {
   string s;
   int i = 0 ; long long powerby; long long calc,lamdacount;
   vector<long long> cntV;
   cntV.resize(1000);
   cout <<"gameid,circlecount,lamdacount/cn3,n,log(CC/n!),averagelen,logVar,3len/3!,4len/4!,..."<<endl;
   while (getline(cin,s)) { 
      int nnn;
      if (s.length()<=0) break;
      
      CountCircle(s,powerby,cntV,nnn,calc,lamdacount);
      printf("%d,%lld,%.3lf,%d,%.5lf",++i,calc,lamdacount*1.0,nnn,log(calc)-log(powerby));
//      cout << ++i <<","<<calc;
  //    cout <<","<<nnn<<","<<log(calc)-log(powerby);
      long long pp = 2;
      vector<double> ppCntV;
      double totlen = 0.0;
      for (int i = 3; pp<powerby; i++) {
              pp*=i;
	      ppCntV.push_back(cntV[i]*1.0/ pp);
              totlen += i*1.0*cntV[i];
             
      }
      
      cout << ","<<totlen/calc ;
      cout <<","<< logVar(ppCntV) ;
      for (int i = 0 ; i < ppCntV.size(); i++) cout << ","<<ppCntV[i] ;
    
     cout << endl;
   }
}
