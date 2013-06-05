#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
const int maxn = 21;
long long dp[1<<maxn][maxn];//
int mp[maxn][maxn];
long long CountCircle(string s, long long & pp){
    int n,m,a,b,i,j,k;
    stringstream ss;
    ss << s;
    ss >> n >> k >> m;
    pp = 1;
    for (int i = 2; i<=n; i++) pp *= i;
//    while(scanf("%d%d",&n,&m)!=EOF){
//        memset(mp,0,sizeof(mp));
        while(m--){
            ss >> a >> b;
            a--;b--;
            mp[a][b]=mp[b][a]=1;
        }
        for(i=0;i<(1<<n);i++) for(j=0;j<n;j++) dp[i][j]=0;
        for(i=0;i<n;i++)  dp[1<<i][i]=1;
        long long ans=0;
        for(i=0;i<(1<<n);i++){
            for(j=0;j<n;j++){
                if(!dp[i][j])  continue;
                bool flag=0;
                for(k=0;k<n;k++){
                    if((1<<k)&i){
                        if(!flag&&mp[j][k]&&i!=((1<<j)+(1<<k))){//如果是起始点，且和结束点相连，且点集中至少有三个点，则构成了环
                            ans+=dp[i][j];
                        }
                        flag=1;
                    }
                    else if(flag && mp[j][k])
                     dp[i^(1<<k)][k]+=dp[i][j];
                }
            }
        }
    return ans;
}
int main() {
   string s;
   int i = 0 ; long long powerby; long long calc;
   cout <<"gameid,circlecount,n!,log(CC/n!)"<<endl;
   while (getline(cin,s)) { 
      if (s.length()<=0) break;
      cout << ++i <<","<<(calc = CountCircle(s,powerby));
      cout <<","<<powerby<<","<<log(calc)-log(powerby)<< endl;
   }
}
