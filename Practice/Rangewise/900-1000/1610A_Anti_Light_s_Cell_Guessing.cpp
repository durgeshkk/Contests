#include<bits/stdc++.h>
#include <deque>
#define ll long long int
using namespace std;
 
void solve()
{
    ll n,m;
    cin>>n>>m;

    if(n==1 && m==1){
        cout<<0<<endl;
        return;
    }

    if(n==1 || m==1){
        cout<<1<<endl;
        return;
    }
    
    cout<<2<<endl;
    return;
}
 
int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   ll t;
   cin >> t;
   while (t--)
   {
       solve();
   }
   return 0;
}