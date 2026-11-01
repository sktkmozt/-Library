#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned ll
#define ld long double
#define bl __int128_t
#define fi first
#define se second
#define vel vector<ll>
#define vvel vector<vel>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define vvepll vector<vepll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
#define pmm pair<mint,mint>
#define cleout(i) cout<<fixed<<setprecision(i)
template<class T>using PQ=priority_queue<T,vector<T>,greater<T>>;
//               上  右 下 左
vector<int> di={-1, 0, 1, 0};
vector<int> dj={ 0, 1, 0,-1};

vector<int> dx={ 0, 1, 0,-1};
vector<int> dy={ 1, 0,-1, 0};


vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll inf=1000000000000000000;//1e18
// LLONG_MAX

mt19937_64 rng((ull)chrono::steady_clock::now().time_since_epoch().count());

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
        ll pos=x;
        mint res=1;
        mint now=num;
        while(pos){
            if(pos&1){
                res*=now;
            }
            now*=now;
            pos/=2;
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
//ll mint::P=1000000007;

vvem dp(1.1e6,vem(11));

/**
 * @brief 線形篩（素数・最小素因数・メビウス関数の列挙）
 * @details O(N)の計算量で[1,N)の範囲の素数、最小素因数、メビウス関数を同時に計算する。
 *          実行後、グローバル変数の primes に素数リストが、minprime に最小素因数が格納される。
 * @param N 探索する範囲の上限（N未満の値を計算する）
 * @return vel 各インデックスにおけるメビウス関数の値を格納した配列
 */
vel primes;
vel minprime;
vel make_mobius(ll N){
    minprime.assign(N,N);
    vel mobius(N,0);
    mobius[1]=1;
    rep(i,2,N){
        if(minprime[i]>i){
            minprime[i]=i;
            primes.push_back(i);
            mobius[i]=-1;
        }
        for(ll p:primes){
            if(p*i>=N)break;
            minprime[p*i]=p;
            if(minprime[i]==p){//i=p*xとなってる
                mobius[p*i]=0;
                break;
            }else mobius[p*i]=-mobius[i];
        }
    }
    return mobius;
}

/**
 * @brief 商列挙
 * @details N/x の値が等しくなる区間 [l, r) とその商 val の組を列挙する
 * @param N 対象の整数
 * @return vector<pair<pair<long long, long long>, long long>> {{l, r}, val}
 */
vector<pair<pll,ll>> div_enumerate(ll N){
    vector<pair<pll,ll>> res;
    for(ll l=1;l<=N;){
        ll val=N/l;
        res.push_back({{l,N/val+1},val});
        l=res.back().fi.se;
    }
    return res;
}

void _solve(){
    ll N,M,K;
    cin>>N>>M>>K;
    mint ans=0;
    auto get=[&](ll l,ll r){
        if(l>M)l=min(l,M);
        if(r>M)r=min(r,M);
        return dp[r][K]-dp[l][K];
    };
    for(auto [lr,x]:div_enumerate(M)){
        mint pow=x;
        ans+=get(lr.fi-1,lr.se-1)*pow.beki(N);
    }
    cout<<ans<<"\n";
}


int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);


    ll N=dp.size();
    ll K=dp[0].size();
    vel mobius=make_mobius(N);
    vem pow(K,1);
    rep(now,1,N){
        ll i=1;
        rep(j,1,K)pow[j]=pow[j-1]*(mint)now;
        while(now*i<N){
            if(mobius[i]==0){
                //
            }else{
                rep(j,1,K){
                    if(mobius[i]==1)dp[now*i][j]+=pow[j];
                    else dp[now*i][j]-=pow[j];
                }
            }
            i++;
        }
    }
    rep(i,1,N){
        rep(j,1,K){
            dp[i][j]=dp[i-1][j]+dp[i][j];
        }
    }
    
    ll _;
    bool multitest=1;
    if(multitest)cin>>_;
    else _=1;
    rep(__,0,_){
        _solve();
    }
}