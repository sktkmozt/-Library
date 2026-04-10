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
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
// #define mint Mint<998244353>
//#define mint Mint<1000000007>
//#define mint Mint<676767677>
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

void _solve(){
    ll P;
    cin>>N>>K>>P;
    if(N==1){
        cout<<"1\n";
        return ;
    }
    mint::set_mod(P);

    vvem dp(N,vem(K+1));//depthがi以下がj個残ってる
    vvem ndp(N,vem(K+1));//depthがiの自分の子供以外がすべて決まってる
    vem r(K+1);
    rep(i,1,K+1)r[i]=(mint)1/(mint)i;
    rep(i,0,K+1)dp[1][i]=1;//最初に0に割り振る数
    vem POW(N+1);
    POW[0]=1;
    rep(i,0,N)POW[i+1]=POW[i]*(mint)2;
    rep(j,0,K+1){
        mint now=1;
        mint pow=POW[N-1]-(mint)1;
        rep(k,0,j+1){//右に割く数
            if(k*2<j){
                //2^(N-1)をkこに振り分ける
                //comb(pow+k-1,k-1)
                ndp[1][j-k]+=dp[1][j]*now*(mint)2;
            }else{
                break;
            }
            now*=(pow+(mint)k)*r[k+1];
        }
    }
    rep(i,2,N){
        rep(j,0,K+1){
            rep(k,0,j+1){
                dp[i][j-k]+=ndp[i-1][j];
            }
        }
        rep(j,0,K+1){
            mint now=1;
            mint pow=POW[N-i]-(mint)1;
            rep(k,0,j+1){
                if(2*k<j){
                    ndp[i][j-k]+=dp[i][j]*now*(mint)2;
                }else{
                    break;
                }
                now*=(pow+(mint)k)*r[k+1];
            }
        }
    }
    mint ans=0;
    rep(i,0,K+1){
        ans+=ndp.back()[i];
    }
    cout<<ans<<"\n";
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
