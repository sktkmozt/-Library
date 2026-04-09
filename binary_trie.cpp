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
#define mint Mint<998244353>
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

struct UF{
    vel par;
    vvel siz;
    vepll val;
    int grp_size;
    UF(int N){
        par.assign(N,0);
        siz.assign(N,{});
        val.assign(N,{0,1});
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
    void unite(int x,int y){
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
        val[rx].fi+=val[ry].fi;
        val[rx].se+=val[ry].se;
    }
    void chan(int i,pll x){
        val[root(i)]=x;
    }
    pll get(ll x){
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

void dfs(vvepll &G,vel &a,ll now,ll par,ll cnt){
    a[now]=cnt;
    for(auto[c,y]:G[now]){
        if(y==par)continue;
        dfs(G,a,y,now,cnt^c);
    }
}

struct hoge{
    ll next[2];//次のindexを持つやつ
    vel check;//ここが終点なindex
    ll cnt;//この頂点を何回通ったか
    hoge(){
        next[0]=next[1]=-1;
        cnt=0;
    }
};


struct binary_trie{
    vector<hoge> node;
    ll max_bit;
    ll lazy_xor;
    binary_trie(ll mb){
        lazy_xor=0;
        max_bit=mb;
        hoge x;
        node.push_back(x);
    }

    ll size(){
        return node[0].cnt;
    }

    void all_xor(ll X){
        lazy_xor^=X;
    }

    void set_xor(ll X){
        lazy_xor=X;
    }

    ll insert(ll num,ll id){
        ll now=0;
        rrep(i,max_bit,0){
            node[now].cnt++;
            ll n=((num^lazy_xor)>>i)&1;
            if(node[now].next[n]==-1){
                hoge x;
                node[now].next[n]=node.size();
                node.push_back(x);
            }
            now=node[now].next[n];
        }
        node[now].check.push_back(id);
        node[now].cnt++;
        return now;
    }

    ll less_count(ll X,ll is_bound=0){//X未満の数(is_boundで以下)
        ll sum=0;
        ll now=0;
        rrep(i,max_bit,0){
            ll n=((X^lazy_xor)>>i)&1;
            if(X&(1ll<<i)){
                if(node[now].next[1^n]!=-1){
                    sum+=node[node[now].next[1^n]].cnt;
                }
            }
            if(node[now].next[n]==-1)return sum;
            now=node[now].next[n];
        }
        if(is_bound)sum+=node[now].cnt;
        return sum;
    }

    ll get(ll K){//0-indexでK番目
        if(size()<=K)return -1;
        ll sum=0;
        ll now=0;
        ll ret=0;
        rrep(i,max_bit,0){
            ll n=(lazy_xor>>i)&1;
            ll left=node[now].next[n];
            ll left_cnt=left==-1?0:node[left].cnt;
            if(sum+left_cnt<=K){
                sum+=left_cnt;
                ret+=(1ll<<i);
                now=node[now].next[n^1];
            }else{
                now=node[now].next[n];
            }
        }
        return ret;
    }

    ll min(){
        return get(0);
    }

    ll max(){
        return get(size()-1);
    }

    ll lower_bound(ll X){
        return get(less_count(X));
    }

    ll upper_bound(ll X){
        return get(less_count(X,1));
    }

    ll min_xor(ll X){//Xとxorしてminになるbinary_trie内の数
        all_xor(X);
        ll ret=min();
        all_xor(X);
        return ret;
    }

    ll max_xor(ll X){//Xとxorしてmaxになるbinary_trie内の数
        all_xor(X);
        ll ret=max();
        all_xor(X);
        return ret;
    }

    void solve(){
    }
};

void _solve(){
    cin>>N>>M>>K;
    UF tree(N);
    vvepll G(N);
    vel base;
    vvel c;
    rep(i,0,M){
        cin>>x>>y>>z;
        x--;
        y--;
        if(tree.same(x,y)){
            c.push_back({x,y,z});
        }else{
            tree.unite(x,y);
            G[x].push_back({z,y});
            G[y].push_back({z,x});
        }
    }
    vel a(N);
    dfs(G,a,0,0,0); 
    rep(i,0,c.size()){
        ll now=a[c[i][0]]^a[c[i][1]]^c[i][2];
        for(ll e:base){
            if((now^e)<now)now^=e;
        }
        if(now)base.push_back(now);
    }
    rep(i,0,N){
        for(ll e:base){
            if((a[i]^e)<a[i])a[i]^=e;
        }
    }
    binary_trie trie(60);
    ll ans=0;
    rep(i,0,N){
        trie.insert(a[i],i);
    }
    rep(i,0,N){
        trie.set_xor(a[i]);
        ans+=trie.less_count(K+1);
    }
    cout<<(ans-N)/2<<"\n";
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