#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define bl __int128_t
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define vem vector<mint>
#define vvem vector<vector<mint>>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define vvepll vector<vepll>
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

ll N,K,M,L,R,T,Q,H,W,i,j,k,l;
ll x,y,z;
string S,SS;
vel mod={998244353,1000000007,1000000009,1000000021,1000000033};//(1<<61)-1も素数
ll p=998244353;
// p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(all(a,0,a.size()));
    a.erase(unique(all(a,0,a.size())),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(all(a,0,a.size()),A.at(i))-a.begin();
    swap(A,a);
*/

struct mint{
    ll num;
    static ll P;
    mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=P;
            x=P-x;
        }
        x%=P;
        num=x;
    }
    static void set_mod(ll PP) {
        P=PP;
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
        rep(i,0,60){
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
    friend ostream& operator<<(ostream& os, const mint& m) {
        os << m.num;
        return os;
    }
    friend istream& operator>>(istream& is, mint& m) {
        ll x;
        is>>x;
        m=mint(x);
        return is;
    }
};
ll mint::P=p;

struct CB{
    vem n,r;
    CB(ll N){//N以下のものをmod INFで返す
        n.assign(N+1,1);
        r.assign(N+1,1);
        rep(i,2,N+1){
            n.at(i)=n.at(i-1)*mint(i);
        }
        r.back()=n.back().inv();
        rrep(i,N,0) r.at(i)=r.at(i)*(mint)(i+1);
    }
    mint comb(ll N,ll R){//NCR
        if(N<R) return 0;
        return n.at(N)*r.at(R)*r.at(N-R);
    }
    mint P(ll N,ll R){//NPR
        return n.at(N)*r.at(N-R);
    }
};

int main(){
}

/*
g++ a.cpp -std=c++20
*/