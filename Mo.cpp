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
#define pmm pair<mint,mint>
#define vepmm vector<pmm>
#define mint Mint<998244353>
//#define mint Mint<1000000007>
#define cleout(i) cout<<fixed<<setprecision(i)
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
//ll inf=1000000000000000000;//1e18
ll inf=(1ll<<61);
// inf=1e9+7;
//ll inf=LLONG_MAX;

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

//[x^M]1/(1-x)^N=comb(N-1+M,M)

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

void add(vector<pair<ll,mint>> &SQ,vel &cnt,vel &a,ll now,ll QQ){
    cnt[a[now]]++;
    ll id=a[now]/QQ;
    SQ[id].se*=(mint)cnt[a[now]];
    SQ[id].fi++;
}

void remove(vem &r,vector<pair<ll,mint>> &SQ,vel &cnt,vel &a,ll now,ll QQ){
    ll id=a[now]/QQ;
    SQ[id].se*=r[cnt[a[now]]];
    SQ[id].fi--;
    cnt[a[now]]--;
}

CB cb(3e5);

pair<ll,mint> f(vector<pair<ll,mint>> &SQ,vel &cnt,ll X,ll QQ){
    ll id=X/QQ;
    pair<ll,mint> res={0,1};
    rep(i,0,id){
        res.fi+=SQ[i].fi;
        res.se*=SQ[i].se;
    }
    rep(i,id*QQ,X){
        res.se*=cb.n[cnt[i]];
        res.fi+=cnt[i];
    }
    return res;
}

void _solve(){
    cin>>N>>Q;
    vel a(N);
    rep(i,0,N)cin>>a[i];
    rep(i,0,N)a[i]--;
    vepll q(Q);
    vel X(Q);
    rep(i,0,Q){
        cin>>q[i].fi>>q[i].se>>X[i];
        q[i].fi--;
        X[i]--;
    }
    vel id(Q);
    rep(i,0,Q)id[i]=i;
    ll B=max(1ll,(ll)(N/sqrt(Q)));
    sort(id.begin(),id.end(),[&](int x,int y){
        int bx=q[x].fi/B;
        int by=q[y].fi/B;
        if(bx!=by)return bx<by;
        if(bx%2)return q[x].se>q[y].se;
        return q[x].se<q[y].se;
    });
    vem res(Q);
    vel cnt(N,0);
    pair<ll,mint> ID={0,1};
    ll QQ=sqrt(N);
    vector<pair<ll,mint>> SQ(N/QQ+1,ID);
    vem rev(N+1,1);
    rep(i,1,N+1)rev[i]=i;
    rep(i,1,N+1)rev[i]=rev[i].inv();
    ll l=0;
    ll r=0;
    for(auto i:id){
        while(l>q[i].fi)add(SQ,cnt,a,--l,QQ);
        while(r<q[i].se)add(SQ,cnt,a,r++,QQ);
        while(l<q[i].fi)remove(rev,SQ,cnt,a,l++,QQ);
        while(r>q[i].se)remove(rev,SQ,cnt,a,--r,QQ);


        pair<ll,mint> get=f(SQ,cnt,X[i],QQ);
        res[i]=cb.n[get.fi]/get.se;
    }
    rep(i,0,Q)cout<<res[i]<<"\n";
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
