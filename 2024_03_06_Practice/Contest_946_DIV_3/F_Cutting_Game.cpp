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
Store the indices to find which will first conquer the point (p,q)
*/
void solve(){
    ll a,b,n,m;cin>>a>>b>>n>>m;

    vector<pair<ll,ll>> v;
    forj(n){
        ll x,y;cin>>x>>y;
        v.push_back({x,y});
    }

    vector<ll> d,u,l,r; // To use for Binary searching the values which will be removed & at what Index
    map<ll,ll> md,mu,ml,mr;  // To store Indices
    ll idx = 0,totd = 0,totu = 0,totl = 0,totr = 0;
    while(m--){
        char ch;cin>>ch;
        ll x;cin>>x;
        if(ch == 'R'){
            totr += x;
            r.push_back(totr);
            mr[totr] = idx;
        }else if(ch == 'L'){
            totl += x;
            l.push_back(totl);
            ml[totl] = idx;
        }else if(ch == 'U'){
            totu += x;
            u.push_back(totu);
            mu[totu] = idx;
        }else{
            totd += x;
            d.push_back(totd);
            md[totd] = idx;
        }
        ++idx;
    }
    
    ll alice = 0,bob = 0;
    for(auto it:v){
        ll up = it.first,left = it.second,down = a+1-up,right = b+1-left;
        ll left_chances = 1e6, right_chances = 1e6, up_chances = 1e6, down_chances = 1e6; // Chances required to remove from all directions
        auto idx = lower_bound(all(u),up)-u.begin();
        if(idx != u.size()){
            up_chances = mu[u[idx]];
        }

        idx = lower_bound(all(d),down)-d.begin();
        if(idx != d.size()){
            down_chances = md[d[idx]];
        }

        idx = lower_bound(all(l),left)-l.begin();
        if(idx != l.size()){
            left_chances = ml[l[idx]];
        }

        idx = lower_bound(all(r),right)-r.begin();
        if(idx != r.size()){
            right_chances = mr[r[idx]];
        }

        ll mn_chances = min({up_chances,down_chances,left_chances,right_chances});
        if(mn_chances == 1e6){continue;}
        if(mn_chances == up_chances){
            if(up_chances & 1){
                ++bob;
            }else{
                ++alice;
            }
        }else if(mn_chances == down_chances){
            if(down_chances & 1){
                ++bob;
            }else{
                ++alice;
            }
        }else if(mn_chances == left_chances){
            if(left_chances & 1){
                ++bob;
            }else{
                ++alice;
            }
        }else{
            if(right_chances & 1){
                ++bob;
            }else{
                ++alice;
            }
        }
    }
    cout<<alice<<" "<<bob<<endl;
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