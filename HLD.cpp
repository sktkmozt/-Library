#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define bl __int128_t
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
#define pmm pair<mint,mint>
#define bl __int128_t
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
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
// LLONG_MAX

mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

//[x^M]1/(1-x)^N=comb(N-1+M,M)


struct HLD{
    vvel G;
    vel size,head,in,parent,depth,out,et;
    ll N,root;
    void dfs1(ll now,ll par){
        if(G[now].size()&&G[now][0]==par)swap(G[now][0],G[now].back());
        for(auto &y:G[now]){
            if(y==par)continue;
            depth[y]=depth[now]+1;
            parent[y]=now;
            dfs1(y,now);
            size[now]+=size[y];
            if(size[y]>size[G[now][0]])swap(G[now][0],y);
        }
        size[now]++;
    }
    void dfs2(ll now,ll par,ll hd){
        head[now]=hd;
        in[now]=et.size();
        et.push_back(now);
        rep(i,0,G[now].size()){
            ll y=G[now][i];
            if(y==par)continue;
            if(i==0){
                dfs2(y,now,hd);
            }else{
                dfs2(y,now,y);
            }
        }
        out[now]=et.size();
    }
    HLD(vvel &_G,ll _root):G(_G),root(_root){
        N=G.size();
        size.assign(N,0);
        head.assign(N,0);
        in.assign(N,0);
        parent.assign(N,root);
        depth.assign(N,0);
        out.assign(N,0);
        dfs1(root,root);
        dfs2(root,root,root);
    }
    ll lca(ll u,ll v){
        while(head[u]!=head[v]){
            if(depth[head[u]]>depth[head[v]])u=parent[head[u]];
            else v=parent[head[v]];
        }
        return (depth[u]>depth[v])?v:u;
    }
    ll dist(ll u,ll v){
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }
    vepll query_path(ll u,ll v,bool is_edge=false){//is_lca:lcaを入れた一つのパスにしますか?
        vepll res;
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]])swap(u,v);
            res.push_back({in[head[u]],in[u]+1});
            u=parent[head[u]];
        }
        if(depth[u]>depth[v])swap(u,v);
        res.push_back({in[u]+is_edge,in[v]+1});
        return res;
    }
    vepll query_path_non_commutative(ll u,ll v,bool is_edge=false){//u->vのクエリを返す。[l,r)(l>rになることもある)
        vepll up,down;
        while(head[u]!=head[v]){
            if(depth[head[u]]>depth[head[v]]){
                up.push_back({in[u]+1,in[head[u]]});
                u=parent[head[u]];
            }else{
                down.push_back({in[head[v]],in[v]+1});
                v=parent[head[v]];
            }
        }
        if(depth[u]>depth[v]){
            up.push_back({in[u]+1,in[v]+is_edge});
        }else{
            down.push_back({in[u]+is_edge,in[v]+1});
        }
        up.insert(up.end(), down.rbegin(), down.rend());
        return up;
    }
    pll query_subtree(ll u){
        return {in[u],out[u]};
    }
    ll up(ll u,ll K){
        if(depth[u]<K)return -1;
        while(K){
            if(depth[u]-depth[head[u]]+1<=K){
                K-=depth[u]-depth[head[u]]+1;
                u=parent[head[u]];
            }else{
                u=et[in[u]-K];
                K=0;
            }
        }
        return u;
    }
    ll kth(ll u,ll v,ll K){//u->vでK番目
        ll d=dist(u,v);
        ll l=lca(u,v);
        if(d<K)return -1;
        if(depth[u]-depth[l]<K){
            K=d-K;
            swap(u,v);
        }
        return up(u,K);
    }
    bool subtree(ll u,ll root){
        return in[root]<=in[u]&&out[u]<=out[root];
    }
    ll median(ll u,ll v,ll w){//この3つにすべて一直線で到達できる頂点(Y字の交差点)
        return lca(u,v)^lca(v,w)^lca(w,u);
    }
    ll heavy_child(ll u){
        if(G[u].empty()||G[u][0]==parent[u])return -1;
        return G[u][0];
    }
};

void _solve(){
    cin>>N>>K;
    vvel a(N,vel(N));
    ll t=0;
    rep(i,0,N){
        rep(j,0,N){
            cin>>a[i][j];
            if(a[i][j]%(K+1)){
                t+=(i+j)%2;
            }
        }
    }
    if(t%2){
        cout<<"Alice\n";
    }else cout<<"Bob\n";
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