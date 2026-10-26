#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define bl __int128_t
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
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
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
// LLONG_MAX

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

//[x^M]1/(1-x)^N=comb(N-1+M,M)

struct mint{
    ll num;
    static ll P;
    static void set_mod(ll MOD){
        P=MOD;
    }
    mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=P;
            x=P-x;
        }
        x%=P;
        num=x;
    }
    mint operator+(const mint &other)const{
        return mint(num+other.num);
    }
    mint operator-(const mint &other)const{
        return mint(num-other.num);
    }
    mint operator*(const mint &other)const{
        return mint(num*other.num);
    }
    mint &operator+=(const mint &other){
        num+=other.num;
        if(num>=P) num-=P;
        return *this;
    }
    mint &operator-=(const mint &other){
        num-=other.num;
        if(num<0) num+=P;
        return *this;
    }
    mint &operator*=(const mint &other){
        num=(num*other.num)%P;
        return *this;
    }
    mint beki(const ll &x)const{
        mint res=1;
        mint now=num;
        rep(i,0,60){
            if(x&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    mint inv()const{
        mint res=1;
        mint now=num;
        rep(i,0,30){
            if((P-2)&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    mint operator/(const mint &other)const{
        return *this*other.inv();
    }
    mint &operator/=(const mint &other){
        num=(num*other.inv())%P;
        return *this;
    }
    operator ll()const{
        return (ll)(num);
    }
    friend ostream& operator<<(ostream& os, const mint& m){
        os << m.num;
        return os;
    }
    friend istream& operator>>(istream& is,mint& m){
        ll x;
        is>>x;
        m=mint(x);
        return is;
    }
};
ll mint::P=998244353;

template<typename T,typename F>
T POW(T id,T a,ll K,F op){
    T res=id;
    while(K){
        if(1&K){
            res=op(res,a);
        }
        a=op(a,a);
        K/=2;
    }
    return res;
}

void _solve(){
    cin>>K>>M;
    mint::set_mod(M*10007);
    mint ans=(mint)0;
    rep(i,0,K){
        cin>>x>>y;
        vvem A={{(mint)10,(mint)1},{(mint)0,(mint)1}};
        vvem id={{(mint)1,(mint)0},{(mint)0,(mint)1}};
        auto mul=[&](vvem a,vvem b){
            vvem res={{(mint)0,(mint)0},{(mint)0,(mint)0}};
            rep(j,0,2){
                rep(k,0,2){
                    rep(l,0,2){
                        res[j][l]+=a[j][k]*b[k][l];
                    }
                }
            }
            return res;
        };
        ans=ans*POW((mint)1,(mint)10,y,std::multiplies<mint>())+(mint)(x)*POW(id,A,y,mul)[0][1];
    }
    cout<<ans.num/M<<"\n";
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