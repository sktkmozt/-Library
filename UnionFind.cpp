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
#define bl __int128_t
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

struct Merge{//a->b
    inline void operator()(vepll &a,vepll &b){
        if(a.size()>b.size()){
            for(pll x:b)a.push_back(x);
            swap(a,b);
        }else{
            for(pll x:a)b.push_back(x);
        }
        return ;
    }
};

template<typename T,typename Merge>
struct UF{
    vel par;
    vvel siz;
    vector<T> val;
    int grp_size;
    Merge merge;
    UF(int N,T id){
        par.assign(N,0);
        siz.assign(N,{});
        val.assign(N,id);
        grp_size=N;
        rep(i,0,N){
            siz[i].push_back(i);
            par[i]=i;
        }
    }
    int root(int x){
        if(par[x]==x)return x;
        par[x]=root(par[x]);
        return par[x];
    }
    void unite(int y,int x){
        int rx=root(x);
        int ry=root(y);
        if(rx==ry) return ;
        grp_size--;
        if(siz[rx].size()>siz[ry].size()){
            for(auto v:siz[ry]){
                siz[rx].push_back(v);
            }
        }else{
            for(auto v:siz[rx]){
                siz[ry].push_back(v);
            }
            swap(siz[rx],siz[ry]);
        }
        siz[ry].clear();
        par[ry]=par[rx];
        merge(val[ry],val[rx]);
    }
    void add(int i,T x){
        merge(x,val[root(i)]);
    }
    T get(ll x){
        return val[root(x)];
    }
    int size(int x){
        return siz[root(x)].size();
    }
    const vel& grp(int x){
        return siz[root(x)];
    }
    bool same(int x,int y){
        return root(x)==root(y);
    }
};

void _solve(){
    ll N,M;
    cin>>N>>M;
    UF<vepll,Merge> tree(N,{});
    rep(i,0,M){
        ll x,y;
        cin>>x>>y;
        x--;
        y--;
        if(tree.same(x,y)){
            tree.add(x,{{i,y}});
        }else{
            tree.unite(x,y);
        }
    }
    priority_queue<pll> pq;
    set<ll> se;
    rep(i,0,N){
        if(se.count(tree.root(i)))continue;
        se.insert(tree.root(i));
        ll rx=tree.root(i);
        pq.push({tree.val[rx].size(),rx});
    }
    vvel ans;
    while(pq.size()>1){
        ll now=pq.top().se;
        pq.pop();
        while(pq.size()){
            if(tree.same(now,pq.top().se)){
                pq.pop();
            }else{
                pll res=tree.val[now].back();
                ans.push_back({res.fi,res.se,pq.top().se});
                tree.val[now].pop_back();
                tree.unite(pq.top().se,now);
                pq.pop();
                pq.push({tree.val[now].size(),now});
                break;
            }
        }
    }
    cout<<ans.size()<<"\n";
    for(vel v:ans){
        for(ll x:v)cout<<x+1<<" ";
        cout<<"\n";
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