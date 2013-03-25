#include <iostream>
#include <string>
#include <set>
using namespace std;
int main()
{
   set<string> E;
   string S;
   while (cin >> S)
     E.insert(S);
   for(set<string>::iterator iS = E.begin(); iS!=E.end(); iS++)
     cout << *iS << endl;
   return 0;
}
