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
#define pyes cout << "Yes" << endl;
#define pno cout << "No" << endl;
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

/*
Catch : To form a Chain, we will need ->
1. 2 vertices with black degree as 1
2. No vertice with black degree as >=3
3. Exception case : Only 1 Node is colored black -> Chain is formed! -> (cnt[0] + cnt[1] + cnt[2] + cnt[3] == 1)
Black Degree refers to No. of Black Childs!

cnt vector will store black degree!
ins(x) : White(col = 0) to Black(col = 1)
rem : Black to White
upd(x,v) : Update Degree of a Node x to v
*/

vector<set<ll>> black;
vector<ll> par,deg,color;
vector<ll> cnt;  // 0,1,2,>=3

void dfs(ll i,ll p){
    par[i] = p;
    for(auto x:adj[i]){
        if(x != p){
            dfs(x,i);
        }
    }
}

void upd(ll x,ll v){
    if(deg[x] <= 2){
        cnt[deg[x]]--;
    }else{
        cnt[3]--;
    }

    deg[x] = v;

    if(deg[x] <= 2){
        cnt[deg[x]]++;
    }else{
        cnt[3]++;
    }
}

void ins(ll x){
    ll p = par[x];
    color[x] = 1;

    deg[x] = 0;
    cnt[0]++;

    if(color[p]){
        upd(p,deg[p]+1);
        if(black[p].size() <= 1){
            upd(x,deg[x]+1);
        }else if(black[p].size() == 2){
            // No use as adding child will cost deg[p] >= 3
            // So we reduce the contribution of par in all its child
            for(auto childs:black[p]){
                upd(childs,deg[childs]-1);
            }
        }
    }

    black[p].insert(x);
    if(black[x].size() <= 2){
        for(auto it:black[x]){
            upd(it,deg[it]+1);
        }
    }
    upd(x,deg[x]+black[x].size());
}

void rem(ll x){
    ll p = par[x];
    color[x] = 0;

    if(deg[x] >= 3){
        cnt[3]--;
    }else{
        cnt[deg[x]]--;
    }

    deg[x] = 0; // Will find by all of its child again!
    black[p].erase(x);

    if(color[p]){
        upd(p,deg[p]-1);
        if(black[p].size() == 2){ // Par will start contributing now
            for(auto childs:black[p]){
                upd(childs,deg[childs]+1);
            }
        }
    }   

    if(black[x].size() <= 2){
        for(auto childs:black[x]){
            upd(childs,deg[childs]-1);
        }
    }
}

void solve(){
    ll n,q;cin>>n>>q;
    black = vector<set<ll>>(n+1);
    par.assign(n+1,0);deg.assign(n+1,0);color.assign(n+1,0);cnt.assign(4,0);
    vector<ll> v(n+1,0);
    forj(n+1){
        adj[j].clear();
        if(j){
            cin>>v[j];
        }
    }

    forj(n-1){
        ll u,v;cin>>u>>v;
        adj[u].push_back(v);adj[v].push_back(u);
    }

    dfs(1,0);

    forj(n+1){
        if(j){
            if(v[j]){
                ins(j);
            }
        }
    }

    while(q--){
        ll x;cin>>x;
        if(color[x]){
            rem(x);
        }else{
            ins(x);
        }

        if(((cnt[3]+cnt[0] == 0) and cnt[1] == 2) || (cnt[0] + cnt[1] + cnt[2] + cnt[3] == 1)){
            pyes;
        }else{
            pno;
        }
    }
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