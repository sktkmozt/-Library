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

struct Combine {
    inline mint operator()(mint a,mint b){
        return a+b;
    }
};

template<typename T, typename Combine>
struct seg{
    int N;
    Combine combine;
    T id;
    vector<T> node;
    int sz;

    seg(vector<T> &a,Combine com,T ident){
        sz=a.size();
        combine=com;
        id=ident;
        ll m=1;
        while(m<sz) m*=2;
        node.resize(2*m,id);
        rep(i,0,sz){
            node[i+m]=a[i];
        }
        rrep(i,m,1){
            node[i]=combine(node[2*i],node[2*i+1]);
        }
        N=m;
    }
    inline void chan(int i,T x){//i番目をxに変える
        i+=N;
        node[i]*=x;
        while(i>0){
            i/=2;
            node[i]=combine(node[2*i],node[2*i+1]);
        }
    }
    inline T  Ique(int l,int r){//[a,b)のmin
        T resl=id,resr=id;
        l+=N;
        r+=N;
        while(l<r){
            if(l&1){//左のほうの右側なので
                resl=combine(resl,node[l]);
                l++;
            }
            if(r&1){//半開区間なのでrが右だといい
                r--;
                resr=combine(node[r],resr);
            }
            l/=2;
            r/=2;
        }
        return combine(resl,resr);
    }

    inline int upper(T x){
        int now=1;
        T res=id;
        if(node[now]<=x){
            return sz;
        }
        while(now<N){
            if(combine(res,node[2*now])<=x){
                res=combine(res,node[2*now]);
                now*=2;
                now++;
            }else{
                now*=2;
            }
        }
        return now-N;
    }
};

int main(){
    cin>>N>>S;
    char c='a'-1;
    vem a(2*N,1);
    mint now=base;
    rep(i,1,2*N){
        a.at(i)=a.at(i-1)*base;
    }
    ///セグ木初期化パート
    mint id=0;
    seg<mint,Combine> hash(a,Combine(),id);
    seg<mint,Combine> rhash(a,Combine(),id);
    seg<mint,Combine> res(a,Combine(),id);
    rep(i,0,2*N){
        x=S.at(i)-'a';
        x++;
        res.chan(i,x);
    }
    rep(i,0,N){
        x=S.at(i)-'a';
        x++;
        hash.chan(i,x);
        rhash.chan(N-1-i,x);
    }
    if(res.Ique(0ll,2*N)==hash.Ique(0ll,N)+a.at(N)*rhash.Ique(0ll,N)){
        rep(j,0,N) cout<<S.at(j);
        cout<<endl<<N;
        return 0;
    }
    mint plus=0;
    rrep(i,N,0){//i文字目をi+N文字目にする
        mint x=S.at(i)-'a';
        x+=1;
        mint div=1;
        rhash.chan(N-1-i,div/x);
        x=S.at(i+N)-'a';
        x+=1;
        rhash.chan(N-1-i,x);
        plus+=a.at(i)*a.at(N)*(mint)x;
        if(res.Ique(0ll,2*N)==hash.Ique(0ll,i)+plus+a.at(i)*rhash.Ique(0ll,N)){
            rep(j,0,i)cout<<S.at(j);
            rep(j,i+N,2*N) cout<<S.at(j);
            cout<<endl;
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
}
/*
g++ a.cpp -std=c++20
*/