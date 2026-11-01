#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<ll>
#define vvel vector<vector<ll>>
#define vvvel vector<vvel>
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
//#define mint Mint<1000000007>
#define cleout(i) cout<<fixed<<setprecision(i)
#define ppcnt __builtin_popcount
template<class T>using PQ=priority_queue<T,vector<T>,greater<T>>;
//               上  右 下 左
vector<int> dx={ -1, 0, 1, 0 };
vector<int> dy={ 0, 1, 0, -1 };


vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll N, K, M, L, R, T, Q, H, W, i, j, l, r;
ll x, y, z;
unsigned long long q;
string S;
long double k;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};
ll p=998244353;
//ll p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
//ll inf=LLONG_MAX;

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

//[x^M]1/(1-x)^N=comb(N-1+M,M)

ll floor_sum(ll n,ll m,ll a,ll b){
    ll ans=0;
    if(a<0){
        ll a2=a%m;
        if(a2<0)a2+=m;
        ans-=n*(n-1)/2*((a2-a)/m);
        a=a2;
    }
    if(b<0){
        ll b2=b%m;
        if(b2<0)b2+=m;
        ans-=n*((b2-b)/m);
        b=b2;
    }
    while(1){
        if(a>=m){
            ans+=n*(n-1)/2*(a/m);
            a%=m;
        }
        if(b>=m){
            ans+=n*(b/m);
            b%=m;
        }
        ll y=a*n+b;
        if(y<m) break;
        n=y/m;
        b=y%m;
        swap(a,m);
    }
    return ans;
}



void _solve(){
    ll A,B;
    cin>>N>>M>>A>>B;
    cout<<floor_sum(N,M,A-1,B+M-1)-floor_sum(N,M,A,B)<<"\n";
}


int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);


    ll _;
    
    bool multitest=1;

    if(multitest)cin>>_;
    else _=1;
    rep(__,0,_){
        _solve();
    }
}