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
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
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

/*座圧
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
*/

/*
g++ a.cpp -std=c++17
*/

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

mint base=114514;

using P = pair<mint, mint>;

struct seg{
    int N;
    vector<P> node;
    vector<P> A;

    seg(const vector<P> &a,string &S) {
        int sz=a.size();
        int m=1;
        while(m<sz)m*=2;
        N=m;
        A.assign(sz,{mint(0),mint(0)});
        A=a;
        node.assign(2*m,{mint(0),mint(0)});
        for(int i=0;i<sz;i++){
            node[i+m]=a[i];
            node[i+m].fi*=(mint)(S.at(i)-'A'+1);
            node[i+m].se*=(mint)(S.at(i)-'A'+1);
        }
        for(int i=m-1;i>=1;i--){
            node[i]={node[2*i].first+node[2*i+1].first,node[2*i].second+node[2*i+1].second};
        }
    }
    void chan(int i,const char &c) {
        i+=N;
        node[i].fi=A.at(i-N).fi*(mint)(c-'A'+1);
        node[i].se=A.at(i-N).se*(mint)(c-'A'+1);
        for(i/=2;i>=1;i/=2) {
            node[i]={node[2*i].first+node[2*i+1].first,node[2*i].second+node[2*i+1].second};
        }
    }
    P Ique(int l, int r) {
        P resLeft={mint(0),mint(0)},resRight={mint(0),mint(0)};
        l+=N;r+=N;
        while(l<r){
            if(l&1){
                resLeft.first+=node[l].first;
                resLeft.second+=node[l].second;
                l++;
            }
            if(r&1){
                r--;
                resRight.first+=node[r].first;
                resRight.second+=node[r].second;
            }
            l/=2;r/=2;
        }
        return {resLeft.first+resRight.first,resLeft.second+resRight.second};
    }
    mint hash(int l, int r) {
        mint rev=A.at(l).se;
        mint resLeft=mint(0),resRight=mint(0);
        l+=N;r+=N;
        while(l<r){
            if(l&1){
                resLeft+=node[l].first;
                l++;
            }
            if(r&1){
                r--;
                resRight+=node[r].first;
            }
            l/=2;r/=2;
        }
        return (resLeft+resRight)*rev;
    }
    mint rhash(int l, int r) {
        mint rev=A.at(r-1).fi;
        mint resLeft=mint(0),resRight=mint(0);
        l+=N;r+=N;
        while(l<r){
            if(l&1){
                resLeft+=node[l].se;
                l++;
            }
            if(r&1){
                r--;
                resRight+=node[r].se;
            }
            l/=2;r/=2;
        }
        return (resLeft+resRight)*rev;
    }
};

int main(){
    cin>>N>>Q>>S;
    vel ans;
    vector<pair<mint,mint>> a(S.size(),{1,1});
    rep(i,1,S.size()){
        a.at(i).fi=a.at(i-1).fi*base;
        a.at(i).se=a.at(i-1).se/base;
    }
    seg hash(a,S);
    rep(q,0,Q){
        cin>>x;
        if(x==1){
            char c;
            cin>>x>>c;
            x--;
            hash.chan(x,c);
        }else{
            cin>>x>>y;
            x--;
            ans.push_back(hash.hash(x,y)==hash.rhash(x,y));
        }
    }
    rep(i,0,ans.size()) cout<<(ans.at(i)==1?"Yes":"No")<<endl;
}
/*
g++ a.cpp -std=c++20
*/