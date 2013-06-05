#include <iostream>
#include <set>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
double var(vector<int> &V) {
  vector<int> VI2;
  VI2.clear();
  for (int i = 0 ; i < V.size(); i++) {
     VI2.push_back(V[i]*V[i]);
//     cout << V[i]<<",";
  }
//  cout << endl;
  double x1 = accumulate(V.begin(),V.end(),(double) 0.0)/V.size();
  double x2 = accumulate(VI2.begin(),VI2.end(),0);
  return x2/V.size() - x1*x1;
  
}
double average(vector<int> &V) {
  return accumulate(V.begin(),V.end(),0)*1.0/V.size();
}
int main()
{
     cout << "gameid,var_degree,avr_degree"<<endl;
   for (int gameid = 1; gameid<=100; gameid++) {  
     int n,m,k;
     cin >> n >>k >> m;
     set<int> s[100];
     for (int i = 0 ; i < n ; i++) s[i].clear();
   //  for (int i = 0 ; i < n;
     for (int i = 0 ; i<m; i++)  {
       int a,b;
       cin >> a >> b;
     //  cout << a << b<< endl;
       s[a].insert(b);
       s[b].insert(a);
     }
     vector<int> VI; VI.clear();
     for (int i = 0 ; i < n; i++)
       VI.push_back(s[i].size());
     cout <<gameid<<","<< var(VI)<<","<<average(VI) << endl;
   }
}
