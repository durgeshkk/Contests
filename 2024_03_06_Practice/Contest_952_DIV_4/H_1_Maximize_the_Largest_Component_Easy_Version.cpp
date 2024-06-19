/*
Once in a LifeTime,
Will never let you Down!!
*/
#include <bits/stdc++.h>
#include<iomanip>
#include <deque>
#include <bitset>
#include <cstdint>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ll long long int
#define all(a) a.begin(),a.end()
#define enter(a) for(ll i=0;i<a.size();i++) cin>>a[i];
#define forj(n) for (ll j = 0; j < n; j++)
#define show(a) for(auto e: a) cout<<e<<" "; cout<<endl;
#define pyes cout << "YES" << endl;
#define pno cout << "NO" << endl;
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
ll ceil_div(ll a, ll b) {return a % b == 0 ? a / b : a / b + 1;}
bool revsort(ll a, ll b) {return a > b;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0)n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
*/

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


vector<ll> adj[100004];

void tree(){
    ll n;
    cin>>n;

    ll u,v;
    cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

//  "A" : 65, "a" : 97  (-> |) (<- &(~))
// YE DIL MAANGE MORE!!

ll n,m;
bool isSafe(ll i,ll j){
    if(i<0 || j<0 || i>=n || j>=m){return 0;}
    return 1;
}

vector<vector<ll>> vis,dp;
vector<vector<char>> v;
vector<pair<ll,ll>> mover = {{1,0},{-1,0},{0,1},{0,-1}};
map<ll,ll> mp;

void bfs(ll i,ll j, ll cntr){

    queue<pair<ll,ll>> q;
    q.push({i,j});
    vis[i][j] = 1;

    while(!q.empty()){
        ll sz = q.size();
        while(sz--){
            auto p = q.front();q.pop();
            ll i = p.first,j=p.second;
            vis[i][j] = 1;
            dp[i][j] = cntr;
            mp[cntr]++;

            for(auto it:mover){
                ll x = i+it.first,y = j+it.second;
                if(isSafe(x,y) and !vis[x][y] and (v[x][y] == '#')){
                    vis[x][y] = 1;
                    q.push({x,y});
                }
            }
        }
    }
}

void solve(){
    cin>>n>>m;
    
    v.clear();vis.clear();dp.clear();mp.clear();

    v.assign(n, vector<char>(m,'0'));
    vis.assign(n, vector<ll>(m,0));
    dp.assign(n, vector<ll>(m,0));
    for(ll i = 0;i<n;++i){
        forj(m){
            cin>>v[i][j];
        }
    }


    ll cntr = 1;
    for(ll i = 0;i<n;++i){
        forj(m){
            if(!vis[i][j] and v[i][j] == '#'){
                bfs(i,j,cntr);
                ++cntr;
            }
        }
    }

    ll ans = 0;
    for(ll i = 0;i<n;++i){
        ll sa = m;
        set<ll> s;
        // For this row check how many connections we can create in (i-1) and (i+1)
        forj(m){
            if(v[i][j] == '#'){--sa;}
            if(dp[i][j]){
                if(s.find(dp[i][j]) != s.end()){
                }else{
                    s.insert(dp[i][j]);
                    sa += mp[dp[i][j]];
                }
            }
        }

        if(i > 0){
            forj(m){
                if(dp[i-1][j]){
                    if(s.find(dp[i-1][j]) != s.end()){
                    }else{
                        s.insert(dp[i-1][j]);
                        sa += mp[dp[i-1][j]];
                    }
                }
            }
        }

        if(i+1 < n){
            forj(m){
                if(dp[i+1][j]){
                    if(s.find(dp[i+1][j]) != s.end()){
                    }else{
                        s.insert(dp[i+1][j]);
                        sa += mp[dp[i+1][j]];
                    }
                }
            }
        }

        ans = max(ans,sa);
    }

    forj(m){
        ll sa = n;
        set<ll> s;
        // For this row check how many connections we can create in (i-1) and (i+1)
        for(ll i = 0;i<n;++i){
            if(v[i][j] == '#'){--sa;}
            if(dp[i][j]){
                if(s.find(dp[i][j]) != s.end()){
                }else{
                    s.insert(dp[i][j]);
                    sa += mp[dp[i][j]];
                }
            }
        }

        if(j > 0){
            for(ll i = 0;i<n;++i){
                if(dp[i][j-1]){
                    if(s.find(dp[i][j-1]) != s.end()){
                    }else{
                        s.insert(dp[i][j-1]);
                        sa += mp[dp[i][j-1]];
                    }
                }
            }
        }

        if(j+1 < m){
            for(ll i = 0;i<n;++i){
                if(dp[i][j+1]){
                    if(s.find(dp[i][j+1]) != s.end()){
                    }else{
                        s.insert(dp[i][j+1]);
                        sa += mp[dp[i][j+1]];
                    }
                }
            }
        }

        ans = max(ans,sa);
    }
    cout<<ans<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //setprecision(20);// also use precision with ans now
    // use setprecision before ans
    //precomputefact();
    //createsieve();
    //bfs();//call in solve()
    //dfs(1,0);//call in solve()
    
    ll t=1;
    cin >> t;
    ll i = 1;
    while (t--)
    {
        solve();
        ++i;
    }
    //solve();
    return 0;
}