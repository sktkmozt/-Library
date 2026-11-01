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

bool comp(const pll &a,const pll &b){//RP^1としてsortする(下向きに分枝が入ってる)<
    ll A=0;//左側ですか？
    if((a.fi==0&&a.se<0)||(a.fi<0)){
        A=1;
    }
    ll B=0;
    if((b.fi==0&&b.se<0)||(b.fi<0)){
        B=1;
    }
    if(A!=B){
        return A<B;
    }
    return (__int128_t)a.se*b.fi<(__int128_t)b.se*a.fi;
}

bool rev_comp(const pll &a,const pll &b){
    return comp(b,a);
}

bool same(const pll &a,const pll &b){//RP^1としてsortする(下向きに分枝が入ってる)
    ll A=0;//左側ですか？
    if((a.fi==0&&a.se<0)||(a.fi<0)){
        A=1;
    }
    ll B=0;
    if((b.fi==0&&b.se<0)||(b.fi<0)){
        B=1;
    }
    if(A!=B){
        return 0;
    }
    return (__int128_t)a.se*b.fi==(__int128_t)b.se*a.fi;
}

void _solve(){
    priority_queue<pll,vector<pll>,decltype(&rev_comp)> pq(rev_comp);
    cin>>N;
    vepll a(N);
    rep(i,0,N){
        cin>>x>>y;
        a[i]={x,y};
        pq.push({x-1,y});
    }
    ll cnt=0;
    pll pos={1,-1000000008};
    while(!pq.empty()){
        pll now=pq.top();
        pq.pop();
        now.fi+=1;
        now.se--;
        if(comp(pos,now)||same(pos,now)){
            pos={now.fi-1,now.se+1};
            cnt++;
        }
    }
    cout<<cnt<<"\n";
}


int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);


    ll _;
    
    bool multitest=0;

    if(multitest)cin>>_;
    else _=1;
    rep(__,0,_){
        _solve();
    }
}