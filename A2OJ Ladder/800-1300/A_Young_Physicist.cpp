#include<bits/stdc++.h>
#include <deque>
#define ll long long int
using namespace std;
 
void solve()
{
 
    ll n;
    cin>>n;

    vector<ll> v;
    ll x=0,y=0,z=0;

    for(ll i=0;i<3*n;i++){
       ll ele;
       cin>>ele;
       v.push_back(ele);

       if(i%3 == 0){
           x += v[i];
       }
       else if(i%3 == 1){
           y += v[i];
       }
       else{
           z += v[i];
       }
    }

    if(x == 0 && y==0 && z == 0){
        cout<<"YES\n";
    }
    else{
        cout<<"NO\n";
    }

    return;
}
 
int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
//    ll t;
//    cin >> t;
//    while (t--)
//    {
       solve();
//    }
   return 0;
}