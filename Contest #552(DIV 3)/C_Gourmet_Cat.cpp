//CELEBRATING SEMIANNIVERSARY OF DADDY_DYNAMO!!
#include<bits/stdc++.h>
#include<iomanip>
#include <deque>
#include <bitset>
#include <cstdint>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ll long long int
#define enter(a) for(ll i=0;i<a.size();i++) cin>>a[i];
#define show(a) for(ll e: a) cout<<e<<" "; cout<<endl;
using namespace std;
ll mod = (ll)(1e9+7);
 
/*
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 10; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return mod_add(arr[0], 0, b);} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0)n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
*/
 
ll LCM(ll a,ll b){
   ll ans = (a*b)/__gcd(a,b);
   return ans;
}
 
bool isPrime(int n){
   if (n <= 1)
       return false;
   for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
    return true;
}
 
bool isPalindrome(string str)
{
    int low = 0;
    int high = str.length() - 1;

    while (low < high)
    {
        // if a mismatch happens
        if (str[low] != str[high]) {
            return false;
        }

        low++;
        high--;
    }

    return true;
}
// Fxn call(for ((b/a)%mod)) :
// ll c = (b*power(a,mod-2(prime num in power of a),mod))%mod;
// Also for formula like nCr..
ll power(ll base,ll n,ll mod){
   ll ans = 1;
   while( n!= 0){
      if(n%2){
          n-=1;
          ans = (ans*base)%mod;
      }
      else{
          n /= 2;
          base = (base*base)%mod;
      }
   }
   return ans;
}
 
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
 
ll sieve[1000005];
void createsieve(){
    ll ntlen = 1000000;
    sieve[0] = 0;
    sieve[1] = 0;
    for(ll i = 2;i<=ntlen;++i){
        sieve[i] = 1;
    }
 
    for(ll i = 2;i*i<=ntlen;++i){
 
        // Set all multiples to 0
        if(sieve[i] == 1){
 
            for(ll j = i*i;j<=ntlen;j+=i){
                 sieve[j] = 0;
            }
        }
    }
}
 
 
ll fact[100005];
ll powfact[100005];
void precomputefact(){
    fact[0] = 1;
    ll ans = 1;
    for(ll i = 1;i<=100005;++i){
         ans = (ans*i)%mod;
         fact[i] = ans;
         powfact[i] = power(fact[i],mod-2,mod);
    }
}
 
ll nCr(ll n,ll r){
     ll at = powfact[r];
     ll at2 = powfact[n-r];
     return ((fact[n]*((at*at2)%mod))%mod);
}
 
vector<ll> adj[100004];
 
void bfs(){
    queue<pair<ll,ll>> q;
    q.push({1,0});
 
    while(!q.empty()){
        auto it = q.front();
        q.pop();
 
        ll node = it.first;
        ll par = it.second;
 
        cout<<node<<" ";
 
        for(auto it:adj[node]){
            if(it != par){
                q.push({it,node});
            }
        }
    }
}
 
ll height;
ll subtree[100005];
ll lev[100005];
ll parent[200005];
 
void dfs(ll node, ll par, ll level=1){

    cout<<node<<" ";
    lev[node] = level;
    height = max(height,level);
 
    ll sm = 0;
 
    parent[node] = par;
    for(auto it:adj[node]){
        if(it != par){
            dfs(it,node,level+1);
            sm += subtree[it];
        }
    }
    subtree[node] = 1+sm;
}
 
void tree(){
    ll n;
    cin>>n;

    ll u,v;
    cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 
void solve()
{
 
    ll a,b,c;
    cin>>a>>b>>c;

    ll x = a/3, y = b/2,z = c/2; 

    ll min_days = min(x,min(y,z));
    a -= (min_days*3);
    b -= (min_days*2);
    c -= (min_days*2);
    // cout<<min_days<<endl;

    ll ans = min_days*7; 
    /*   
    if(a == 0 and b == 0 and c == 0){
    }else if(a == 0 and b == 0){
        ++ans;
    }else if(c == 0 and b == 0){
        if(a >= 2){
            ans += 2;
        }else{
            ++ans;
        }
    }else if(a == 0 and c == 0){
        ++ans;
    }else if(a == 0){
        if(b >= 1 and c >= 1){
            ans+=2;
        }else{
            ++ans;
        }
    }else if(b == 0){
        if(c >= 2 and a >= 1){
            ans += 3;
        }else if(a >= 2){
            ans += 2;
        }else if(c >= 1 and a >= 1){
            ans += 2;
        }else{
            ++ans;
        }
    }else if(c == 0){
        if(b >= 2 and a >= 2){
            ans += 4;
        }else if(a >= 2 and b >= 1){
            ans += 3;
        }else if(a >= 1 and b >= 1){
            ans += 2;
        }else{
            ++ans;
        }
    }else{

    }*/

    map<pair<ll,pair<ll,ll>>,ll> mp;
    mp[{0,{0,0}}] = 0;
    mp[{0,{0,1}}] = 1;
    mp[{0,{1,0}}] = 1;
    mp[{1,{0,0}}] = 1;
    mp[{1,{0,1}}] = 2;
    mp[{1,{1,0}}] = 2;
    mp[{1,{1,1}}] = 3;

    mp[{2,{0,0}}] = 2;
    mp[{2,{0,1}}] = 2;
    mp[{2,{1,0}}] = 3;
    mp[{2,{1,1}}] = 4;
    mp[{2,{1,2}}] = 4;
    mp[{2,{2,1}}] = 5;
    mp[{2,{2,2}}] = 6;
    mp[{2,{0,2}}] = 3;
    mp[{2,{2,0}}] = 4;
    
    mp[{0,{2,0}}] = 1;
    mp[{1,{2,1}}] = 3;
    mp[{1,{2,0}}] = 2;
    mp[{0,{2,1}}] = 2;
    mp[{1,{2,2}}] = 5;
    mp[{0,{2,2}}] = 2;

    mp[{0,{0,2}}] = 1;
    mp[{1,{1,2}}] = 4;
    mp[{1,{0,2}}] = 3;
    mp[{0,{1,2}}] = 2;

    mp[{3,{0,0}}] = 2;
    mp[{3,{0,1}}] = 2;
    mp[{3,{1,0}}] = 3;
    mp[{3,{1,1}}] = 5;

    mp[{3,{0,2}}] = 3;
    mp[{3,{2,0}}] = 4;
    mp[{3,{1,2}}] = 6;
    mp[{3,{2,1}}] = 6;
    mp[{3,{2,2}}] = 7;

    if(a >= 3){
        a = 3;
    }
    
    if(b >= 2){
        b = 2;
    }

    if(c >= 2){
        c = 2;
    }
    
    ans += mp[{a,{b,c}}];
    cout<<ans<<endl;
    return;
}
 
int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   //setprecision(20);// also use precision with ans now
   //precomputefact();
   //createsieve();
   //bfs();//call in solve()
   //dfs(1,0);//call in solve()
 
   ll t=1;
//    cin >> t;
   ll i = 1;
   while (t--)
   {
       solve();
       ++i;
   }
   //solve();
   return 0;
}