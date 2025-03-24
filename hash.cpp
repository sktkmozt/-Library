#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define all(a,i,j) a.begin()+i,a.begin()+j
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
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

ll N, K, M, L, R, Q, H, W, i, j, k, l;
ll x, y, z;
string S,T;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};//(1<<61)-1も素数
ll p=998244353;
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
// LLONG_MAX

/*座圧
    vel A=a;
    sort(all(a,0,a.size()));
    a.erase(unique(all(a,0,a.size())),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(all(a,0,a.size()),A.at(i))-a.begin();
    swap(A,a);
*/

struct mint{
    ll num;
    mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=p;
            x=p-x;
        }
        x%=p;
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
        if(num>=p) num-=p;
        return *this;
    }
    mint &operator-=(const mint &other){
        num-=other.num;
        if(num<0) num+=p;
        return *this;
    }
    mint &operator*=(const mint &other){
        num=(num*other.num)%p;
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
            if((p-2)&(1ll<<i)){
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
        num=(num*other.inv())%p;
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
    cin>>N>>S;
    vector<pair<mint,mint>> a(S.size(),{1,1});
    rep(i,1,S.size()){
        a.at(i).fi=a.at(i-1).fi*base;
        a.at(i).se=a.at(i-1).se/base;
    }
    seg hash(a,S);
    if(hash.hash(0,N)==hash.rhash(N,2*N)){
        cout<<S.substr(0,N)<<endl;
        cout<<N;
        return 0;
    }
    rrep(i,N,0){
        mint l=hash.hash(0,i)+a.at(i).fi*hash.hash(i+N,2*N);
        mint r=hash.rhash(i,i+N);
        if(l==r){
            T=S.substr(i,N);
            reverse(T.begin(),T.end());
            cout<<T<<endl;
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<-1;
}
/*
g++ a.cpp -std=c++20
*/