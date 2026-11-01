#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
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
// LLONG_MAX

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

template<ll P>
struct Mint{
    ll num;
    static constexpr ll MOD=P;
    Mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=P;
            x=P-x;
        }
        x%=P;
        num=x;
    }
    Mint operator+(const Mint &other)const{
        return Mint(num+other.num);
    }
    Mint operator-(const Mint &other)const{
        return Mint(num-other.num);
    }
    Mint operator*(const Mint &other)const{
        return Mint(num*other.num);
    }
    Mint &operator+=(const Mint &other){
        num+=other.num;
        if(num>=P) num-=P;
        return *this;
    }
    Mint &operator-=(const Mint &other){
        num-=other.num;
        if(num<0) num+=P;
        return *this;
    }
    Mint &operator*=(const Mint &other){
        num=(num*other.num)%P;
        return *this;
    }
    Mint beki(const ll &x)const{
        Mint res=1;
        Mint now=num;
        rep(i,0,60){
            if(x&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    Mint inv()const{
        Mint res=1;
        Mint now=num;
        rep(i,0,30){
            if((P-2)&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    Mint operator/(const Mint &other)const{
        return *this*other.inv();
    }
    Mint &operator/=(const Mint &other){
        num=(num*other.inv())%P;
        return *this;
    }
    operator ll()const{
        return (ll)(num);
    }
    friend ostream& operator<<(ostream& os, const Mint& m) {
        os << m.num;
        return os;
    }
    friend istream& operator>>(istream& is, Mint& m) {
        ll x;
        is>>x;
        m=Mint(x);
        return is;
    }
};

struct CB{
    vem n,r;
    CB(ll N){//N以下のものをmod INFで返す
        n.assign(N+1,1);
        r.assign(N+1,1);
        rep(i,2,N+1){
            n.at(i)=n.at(i-1)*mint(i);
        }
        r.back()=n.back().inv();
        rrep(i,N,0) r.at(i)=r.at(i+1)*(mint)(i+1);
    }
    mint comb(ll N,ll R){//NCR
        if(N<R) return 0;
        return n.at(N)*r.at(R)*r.at(N-R);
    }
    mint P(ll N,ll R){//NPR
        return n.at(N)*r.at(N-R);
    }
};

CB cb(200030);

void dfs(vepll &G,vepll &lr,ll now){
    lr[now]={now,now};
    if(G[now].fi!=-1){
        dfs(G,lr,G[now].fi);
        lr[now].fi=lr[G[now].fi].fi;
    }
    if(G[now].se!=-1){
        dfs(G,lr,G[now].se);
        lr[now].se=lr[G[now].se].se;
    }
    return ;
}

void solve(vepll &G,vepll &lr,ll now,vem &dp){
    pll LR=lr[now];
    mint ret=1;
    if(G[now].fi!=-1){
        solve(G,lr,G[now].fi,dp);
        ret*=dp[G[now].fi];
    }
    if(G[now].se!=-1){
        solve(G,lr,G[now].se,dp);
        ret*=dp[G[now].se];
    }
    ll l=now-lr[now].fi;
    ll r=lr[now].se-now;
    if(LR.fi!=0&&LR.se+1!=G.size()){//両側でok
        dp[now]=ret*(cb.comb(l+r+1,r)+cb.comb(l+r+1,l)-cb.comb(l+r,l));
    }else if(LR.se+1!=G.size()){//右側だけ
        dp[now]=ret*cb.comb(l+r+1,r+1);
    }else if(LR.fi!=0){//左側だけ
        dp[now]=ret*cb.comb(l+r+1,l+1);
    }else{
        dp[now]=ret*cb.comb(l+r,l);
    }
}

ll make_cartesiantree(vepll &G,vel &p){//maxの時
    stack<ll> st;
    G.assign(p.size(),{-1,-1});
    rep(i,0,p.size()){
        ll last=-1;
        while(!st.empty()&&p[st.top()]<p[i]){//
            last=st.top();
            st.pop();
        }
        if(last!=-1)G[i].fi=last;
        if(!st.empty()){
            G[st.top()].se=i;
        }
        st.push(i);
    }
    ll m=0;
    rep(i,0,p.size()){
        if(p[i]>p[m])m=i;//
    }
    return m;
}

void _solve(){
    cin>>N;
    vel p(N);
    rep(i,0,N)cin>>p[i];
    vepll G;
    ll m=make_cartesiantree(G,p);
    vepll lr(N);
    dfs(G,lr,m);
    vem dp(N);
    solve(G,lr,m,dp);
    cout<<dp[m]<<"\n";
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
//https://atcoder.jp/contests/arc212/submissions/73848445