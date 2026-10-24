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

struct mint{
    ll num;
    static ll P;
    static void set_mod(ll MOD){
        P=MOD;
    }
    mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=P;
            x=P-x;
        }
        x%=P;
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
        ll pos=x;
        mint res=1;
        mint now=num;
        while(pos){
            if(pos&1){
                res*=now;
            }
            now*=now;
            pos/=2;
        }
        return res;
    }
    mint inv()const{
        mint res=1;
        mint now=num;
        rep(i,0,30){
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
    friend ostream& operator<<(ostream& os, const mint& m){
        os << m.num;
        return os;
    }
    friend istream& operator>>(istream& is,mint& m){
        ll x;
        is>>x;
        m=mint(x);
        return is;
    }
};
ll mint::P=998244353;
//ll mint::P=1000000007;

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
    HLD(vvel &_G,ll _root=0):G(_G),root(_root){
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
    vel light_childs(ll u){
        vel res;
        if (G[u].empty())return res;
        rep(i,1,G[u].size()){
            ll y=G[u][i];
            if(y==parent[u])continue;
            res.push_back(y);
        }
        return res;
    }
};

template<typename DP>
struct StaticTopTree{
    using Point=typename DP::Point;
    using Path=typename DP::Path;
    using Vertex=typename DP::Vertex;
    enum NodeType{VERTEX,COMPRESS,RAKE};//頂点,heavyをまとめてる,lightをまとめてる
    struct STTNode{
        ll p=-1;
        ll l=-1;
        ll r=-1;
        NodeType type;
        ll size=0;
        Point point_val;
        Path path_val;
        ll v_id=-1;
    };

    vector<STTNode> nodes;
    ll root_stt;
    HLD* hld;
    vel vertex_node;
    vector<Vertex> vertex_data;
    StaticTopTree(HLD &_hld,vector<Vertex> &_vertex_data){
        hld=&_hld;
        nodes.reserve(hld->N*4);
        vertex_node.assign(hld->N,-1);
        vertex_data=_vertex_data;
        root_stt=build_path(hld->root);
        rep(i,0,nodes.size()){
            update_node(i);
        }
    }
    ll make_node(NodeType type,ll left,ll right,ll sz=0,ll v_id=-1){
        ll id=nodes.size();
        nodes.push_back({-1,left,right,type,sz,Point(),Path(),v_id});
        if(left!=-1)nodes[left].p=id;
        if(right!=-1)nodes[right].p=id;
        return id;
    }
    void update(ll u,Vertex val){
        vertex_data[u]=val;
        ll id=vertex_node[u];
        while(id!=-1){
            update_node(id);
            id=nodes[id].p;
        }
    }
    Point get_subtree(ll u){
        ll id=vertex_node[u];
        Path res=nodes[id].path_val;
        while(nodes[id].p!=-1&&nodes[nodes[id].p].type==COMPRESS){
            ll p=nodes[id].p;
            if(nodes[p].l==id){
                res=res*nodes[nodes[p].r].path_val;
            }
            id=p;
        }
        return Point(res);
    }
private:
    ll build_path(ll u){//uの部分木たちを組み込んで自分を組み込む(自分のindexを返す)
        vel path_nodes;
        ll now=u;
        while(now!=-1){
            vel lights=hld->light_childs(now);
            vel rake_nodes;
            for(ll v:lights){
                rake_nodes.push_back(build_path(v));
            }
            ll raked_child=build_rake(rake_nodes);
            ll sz=1;
            if(raked_child!=-1)sz+=nodes[raked_child].size;
            ll v_node=make_node(VERTEX,raked_child,-1,sz,now);
            vertex_node[now]=v_node;
            path_nodes.push_back(v_node);
            now=hld->heavy_child(now);
        }
        return build_compress(path_nodes);
    }
    ll build_compress(vel &list){
        if(list.empty())return -1;
        return build_balanced(list,0,list.size(),COMPRESS);
    }
    ll build_rake(vel &nodes_list){
        if(nodes_list.empty())return -1;
        return build_balanced(nodes_list,0,nodes_list.size(),RAKE);
    }
    ll build_balanced(vel &list,ll L,ll R,NodeType type){//まとまったのを半分につぶしていく
        if(L+1==R)return list[L];
        ll total_size=0;
        rep(i,L,R){
            total_size+=nodes[list[i]].size;
        }
        ll now_size=nodes[list[L]].size;
        ll mid=L+1;
        while(mid<R-1){
            if((now_size+nodes[list[mid]].size)*2>=total_size){
                break;
            }
            now_size+=nodes[list[mid]].size;
            mid++;
        }
        ll left_child=build_balanced(list,L,mid,type);
        ll right_child=build_balanced(list,mid,R,type);
        return make_node(type,left_child,right_child,nodes[left_child].size+nodes[right_child].size);
    }
    Point get_point(ll id){//path->point
        if(id==-1)return Point();
        if(nodes[id].type==COMPRESS||nodes[id].type==VERTEX){
            return Point(nodes[id].path_val);
        }
        return nodes[id].point_val;
    }
    void update_node(ll id){
        STTNode &node=nodes[id];
        ll l=node.l,r=node.r;
        if(node.type==RAKE){
            Point left_p=get_point(l);
            Point right_p=get_point(r);
            node.point_val=left_p+right_p;
        }else if(node.type==VERTEX){
            Point child_p=get_point(l);
            Vertex v_val=vertex_data[node.v_id];
            node.path_val=Path(v_val,child_p);
        }else if(node.type==COMPRESS){
            Path left_path=(l!=-1)?nodes[l].path_val:Path();
            Path right_path=(r!=-1)?nodes[r].path_val:Path();
            node.path_val=left_path*right_path;
        }
    }
};
struct DP{
    struct Vertex{
        ll d=-inf;
        ll q=1;
        Vertex()=default;
    };
    struct Path;
    struct Point{//上にだけくっつける
        ll ans=0;
        ll m=-inf;
        Point()=default;
        Point(const Path&p);
        Point operator+(const Point &b)const{
            Point res;
            res.ans=max(m+b.m+2,max(ans,b.ans));
            res.m=max(m,b.m);
            return res;
        }
    };
    struct Path{//上下にくっつける
        ll ans=0;
        ll u=-inf;
        ll d=-inf;
        ll len=0;
        Path()=default;
        Path operator*(const Path &b)const{//bが下
            Path res;
            res.ans=max(b.u+d+1,max(ans,b.ans));
            res.u=max(len+1+b.u,u);
            res.d=max(b.len+1+d,b.d);
            res.len=len+b.len+1;
            return res;
        }
        Path(const Vertex &val,const Point &p){//val<-pでくっつける
            this->ans=p.ans;
            this->d=p.m+1;
            this->u=p.m+1;
            this->len=0;
            if(val.q){
                this->u=max(this->u,0ll);
                this->d=max(this->d,0ll);
                this->ans=max(this->ans,this->d);
            }
        }
    };
};
inline DP::Point::Point(const DP::Path &p){
    this->ans=p.ans;
    this->m=p.u;
}

void _solve(){
    ll N;
    cin>>N;
    vvel G(N);
    rep(i,1,N){
        ll u,v;
        cin>>u>>v;
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    HLD hld(G);
    vector<DP::Vertex> v(N);
    rep(i,0,N)v[i].d=hld.depth[i];
    StaticTopTree<DP> tree(hld,v);
    vel b(N,1);
    ll Q;
    cin>>Q;
    rep(i,0,Q){
        ll v;
        cin>>v;
        v--;
        b[v]^=1;
        DP::Vertex res;
        res.d=hld.depth[v];
        res.q=b[v];
        tree.update(v,res);
        cout<<tree.get_subtree(0).ans<<"\n";
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