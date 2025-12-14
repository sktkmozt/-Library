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
    bool c=1;
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

struct combineT {
    // combineT:nodeをcombineする
    inline mint operator()(mint l,mint r, pll rng) const {return (l+r); }
};

struct op {
    // op:nodeにlazyを作用させる
    inline mint operator()(mint node,mint lazy, pll rng) const {
        if(!lazy.c)return 0;
        return lazy*(mint)(rng.se-rng.fi);
    }
};

struct combineE {
    // combineE:lazyをcombineする
    inline mint operator()(mint New,mint Old, pll rng) const {
        return New;
    }
};

template<typename T, typename E, typename F, typename G, typename H>
struct lsg {
    int N;
    F combineT;
    H combineE;
    G op;
    T idT; // 単位元（区間合成用）
    E idE; // 単位元（lazy用）
    
    vector<T> node;
    vector<E> lazy;
    vector<pll> range;  // 各ノードが担当する区間 [first, second)
    
    // コンストラクタ
    lsg(const vector<T> &a,F combineT,H combineE,G op,T idT,E idE)
        : combineT(combineT),op(op),combineE(combineE),idT(idT),idE(idE)
    {
        int sz=a.size();
        N=1;
        while(N<=sz)N*=2;
        node.assign(2*N-1,idT);
        lazy.assign(2*N-1,idE);
        range.assign(2*N-1,{0,N});
        
        rep(i,0,sz){
            node[i+N-1]=a[i];
        }
        rrep(i,N-2,0){
            node[i]=combineT(node[2*i+1],node[2*i+2],range[2*i+1]);
        }
        for (int i=0;i<N-1;i++) {
            pll r=range[i];
            int mid=(r.first+r.second)/2;
            range[2*i+1]={r.first,mid};
            range[2*i+2]={mid,r.second};
        }
    }
    
    inline void val(int idx) {
        if (lazy[idx]!=idE){
            if (idx<N-1) {
                lazy[2*idx+1]=combineE(lazy[idx],lazy[2*idx+1],range[2*idx+1]);
                lazy[2*idx+2]=combineE(lazy[idx],lazy[2*idx+2],range[2*idx+2]);
            }
            node[idx]=op(node[idx],lazy[idx],range[idx]);
            lazy[idx]=idE;
        }
    }
    
    inline void Ichan(int l,int r,E x,int idx,int L,int R) {
        val(idx);
        if (R<=l||r<=L)return;
        if (l<=L&&R<=r) {
            lazy[idx]=combineE(x,lazy[idx],{L,R});
            val(idx);
        } else {
            int mid=(L+R)/2;
            Ichan(l,r,x,2*idx+1,L,mid);
            Ichan(l,r,x,2*idx+2,mid,R);
            node[idx]=combineT(node[2*idx+1],node[2*idx+2],range[2*idx+1]);
        }
    }
    inline void Ichan(int l,int r,E x){
        Ichan(l,r,x,0,0,N);
    }
    
    inline T Ique(int l,int r,int idx,int L,int R){
        val(idx);
        if (R<=l||r<=L)return idT;
        if (l<=L&&R<=r)return node[idx];
        int mid=(L+R)/2;
        T leftVal=Ique(l,r,2*idx+1,L,mid);
        T rightVal=Ique(l,r,2*idx+2,mid,R);
        return combineT(leftVal,rightVal,range[2*idx+1]);
    }

    inline T Ique(int l, int r) {
        return Ique(l, r, 0, 0, N);
    }
};

int main(){
    cin>>N>>M;
    vem a(N);
    rep(i,0,N)cin>>a.at(i);
    mint idT=0;
    mint idE=0;
    idE.c=false;
    lsg<mint,mint, combineT, op, combineE> st(a, combineT(),combineE(),op(),idT,idE);
    rep(i,0,M){
        cin>>l>>r;
        mint res=st.Ique(l-1,r);
        //cout<<res/(mint)(r-l+1)<<endl;
        st.Ichan(l-1,r,res/(mint)(r-l+1));
    }
    rep(i,0,N){
        cout<<st.Ique(i,i+1)<<" ";
    }
}