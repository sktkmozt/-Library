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
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
//               上  右 下 左
vector<int> dx={ -1, 0, 1, 0 };
vector<int> dy={ 0, 1, 0, -1 };

vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll N, K, M, L, R, T, Q, H, W, i, j, l;
ll x, y, z;
unsigned long long q;
string S;
long double k;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};
ll inf=998244353;
// inf=1e9+7;
// LLONG_MAX

/*座圧
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
*/

/*
g++ a.cpp -std=c++20
*/

struct mint{
    ll num;
    mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=inf;
            x=inf-x;
        }
        x%=inf;
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
        if(num>=inf) num-=inf;
        return *this;
    }
    mint &operator-=(const mint &other){
        num-=other.num;
        if(num<0) num+=inf;
        return *this;
    }
    mint &operator*=(const mint &other){
        num=(num*other.num)%inf;
        return *this;
    }
    mint beki(const mint &x)const{
        mint res=1;
        mint now=num;
        rep(i,0,60){
            if(x.num&(1ll<<i)){
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
            if((inf-2)&(1ll<<i)){
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
        num=(num*other.num)%inf;
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



int main(){
    cin>>N;
    vector<mint> a(N-1);
    mint ans=0;
    rep(i,0,N-1){
        cin>>x;
        a.at(i)=mint(x);
    }
    vector<mint> dp(N-1,0);
    vector<mint> sum(N,0);
    sum.at(0)=1;
    sum.at(1)=-1;
    rep(i,0,N-1){
        mint p=a.at(i)+mint(1);
        p=mint(1)/p;
        mint iv=(mint(1)-p).inv();
        mint plus=p*iv*dp.at(i);
        if(i+1<N-1)dp.at(i+1)+=plus;
        if(i+a.at(i)+1<N-1)dp.at(i+a.at(i)+1)-=plus;
        ans+=(max(0ll,i+a.at(i)+1-N+1)*plus);
        plus=sum.at(i)*p*iv;
        if(i+1<N-1)sum.at(i+1)+=plus;
        if(i+a.at(i)+1<N-1) sum.at(i+a.at(i)+1)+=inf-plus;
        plus=p*sum.at(i)*iv*iv;
        if(i+1<N-1)dp.at(i+1)+=plus;
        if(i+a.at(i)+1<N-1)dp.at(i+a.at(i)+1)-=plus;
        ans+=(max(0ll,i+a.at(i)+1-N+1)*plus);
        if(i+1<N-1){
            dp.at(i+1)+=dp.at(i);
            sum.at(i+1)+=sum.at(i);
        }
    }
    cout<<ans;
}
