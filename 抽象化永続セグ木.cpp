#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define bl __int128_t
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

struct Combine {
    inline ll operator()(ll a,ll b){
        return a+b;
    }
};

template<typename T, typename Combine>
struct perseg{
    struct Node{
        T val;
        int l,r;
        Node(T x):val(x),l(0),r(0){};
    };
    int N;
    Combine combine;
    T id;
    vector<Node> node;
    int sz=0;
    int new_Node(T v){
        Node res(v);
        node.emplace_back(res);
        return sz++;
    }

    perseg(int n,Combine com,T ident):combine(com),id(ident){
        N=1;
        while(N<n)N<<=1;
        node.reserve(1000000);
        new_Node(id);
    }

    int build(const vector<T> &a,int nowl,int nowr){
        int now=new_Node(id);
        if(nowl+1==nowr){
            node[now].val=nowl>=a.size()?id:a[nowl];
            return now;
        }
        int mid=(nowl+nowr)/2;
        node[now].l=build(a,nowl,mid);
        node[now].r=build(a,mid,nowr);
        node[now].val=combine(node[node[now].l].val,node[node[now].r].val);
        return now;
    }

    perseg(const vector<T>& a,Combine com,T ident,ll &initial_node):combine(com),id(ident){
        int n=a.size();
        N=1;
        while(N<n)N<<=1;
        node.reserve(max(1000000,2*N)); 
        new_Node(id);
        initial_node=build(a,0,N);
    }

    inline int _chan(int pre_now,int i,T x,int nowl,int nowr){//書き換えたいversionのnodeのindexをpre_nowを書くとそのバージョンのi番目をxに変える
        int now=new_Node(id);
        node[now]=node[pre_now];
        if(nowl+1==nowr){
            node[now].val=x;
            return now;
        }
        int mid=(nowl+nowr)/2;
        if(i<mid){
            node[now].l=_chan(node[now].l,i,x,nowl,mid);
        }else{
            node[now].r=_chan(node[now].r,i,x,mid,nowr);
        }
        node[now].val=combine(node[node[now].l].val,node[node[now].r].val);
        return now;
    }

    int chan(int pre_now,int i,T x){
        return _chan(pre_now,i,x,0,N);
    }

    inline T _Ique(int now,int l,int r,int nowl,int nowr){//verがnowのセグ木での[a,b)のcombine
        if(nowr<=l||r<=nowl)return id;
        if(l<=nowl&&nowr<=r){
            return node[now].val;
        }
        int mid=(nowl+nowr)/2;
        return combine(_Ique(node[now].l,l,r,nowl,mid),_Ique(node[now].r,l,r,mid,nowr));
    }

    T Ique(int now,int l,int r) {
        return _Ique(now,l,r,0,N);
    }

    template<typename F>
    int _lower(int now,int nowl,int nowr,int l,F check){
        if(nowr<=l||!check(node[now].val)){
            return N;
        }
        if(nowl+1==nowr)return nowl;
        int mid=(nowl+nowr)/2;
        int res=_lower(node[now].l,nowl,mid,l,check);
        if(res==N){
            res=_lower(node[now].r,mid,nowr,l,check);
        }
        return res;
    }

    template<typename F>
    int lower(int now,int l,F check){
        return _lower(now,0,N,l,check);
    }

    template<typename F>
    int _upper(int now,int nowl,int nowr,int r,F check){
        if(r<=nowl||!check(node[now].val)){
            return -1;
        }
        if(nowl+1==nowr)return nowl;
        int mid=(nowl+nowr)/2;
        int res=_upper(node[now].r,mid,nowr,r,check);
        if(res==-1){
            res=_upper(node[now].l,nowl,mid,r,check);
        }
        return res;
    }

    template<typename F>
    int upper(int now,int r,F check){
        return _upper(now,0,N,r,check);
    }
};

void _solve(){
    cin>>N>>M>>Q;
    perseg<ll,Combine> st(M,Combine(),0);
    vel root(N,0);
    rep(q,0,Q){
        cin>>x;
        if(x==1){
            cin>>x>>y;
            x--;
            y--;
            root[x]=root[y];
        }else if(x==2){
            cin>>x>>y>>z;
            x--;
            y--;
            root[x]=st.chan(root[x],y,z);
        }else{
            cin>>x>>l>>r;
            x--;
            l--;
            cout<<st.Ique(root[x],l,r)<<"\n";
        }
    }
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