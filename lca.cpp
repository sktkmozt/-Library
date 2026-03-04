#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
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
#define mint Mint<998244353>
//#define mint Mint<1000000007>
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



template<typename T, typename Combine>
struct seg{
    int N;
    Combine combine;
    T id;
    vector<T> node;
    int sz;

    seg(vector<T> &a,Combine com,T ident):combine(com),id(ident){
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
    seg(ll n,Combine com,T ident):combine(com),id(ident){
        sz=n;
        ll m=1;
        while(m<sz) m*=2;
        node.assign(2*m,id);
        N=m;
    }
    inline void chan(int i,T x){//i番目をxに変える
        i+=N;
        node[i]=x;
        while(i>0){
            i/=2;
            node[i]=combine(node[2*i],node[2*i+1]);
        }
    }

    inline void add(int i,T x){//i番目をxに変える
        i+=N;
        node[i]+=x;
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

    bool check(T node,ll x){//noed.fi<xを満たす最小を返す
        return node.fi<x;
    }

    inline int upper(ll x){
        int now=1;
        T res=id;
        if(!check(node[now],x)){
            return sz;
        }
        while(now<N){
            if(!check(combine(res,node[2*now]),x)){
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

struct LCA{
    vvel G;
    vel ord;
    vel in;
    vel out;
    vel deep;
    vel P;
    vvel binary_P;
    vvepll sp;//[j,j+2^i)のmin
    ll N;

    void e_dfs(ll now,ll par){//オイラーツアー
        P[now]=par;
        in[now]=ord.size();
        ord.push_back(now);
        for(auto y:G[now]){
            if(y==par)continue;
            deep[y]=deep[now]+1;
            e_dfs(y,now);
            ord.push_back(now);
        }
        out[now]=ord.size();
    }

    LCA(vvel &Graph,ll root=0){
        G=Graph;
        N=G.size();
        in.assign(N,-1);
        out.assign(N,-1);
        deep.assign(N,0);
        P.assign(N,-1);
        e_dfs(root,root);
        ll size=0;
        while((1ll<<(size+1))<=ord.size())size++;
        size++;
        sp.assign(size,vepll(ord.size(),{inf,-1}));
        rep(i,0,ord.size()){
            sp[0][i]={deep[ord[i]],ord[i]};
        }
        rep(i,1,size){
            rep(j,0,ord.size()){
                pll r={inf,-1};
                if(j+(1ll<<(i-1))<ord.size()){
                    r=sp[i-1][j+(1ll<<(i-1))];
                }
                sp[i][j]=min(sp[i-1][j],r);
            }
        }
    }

    ll lca(ll l,ll r){
        ll L=in[l];
        ll R=in[r];
        if(L>R)swap(L,R);
        ll d=bit_width((ull)(R-L+1))-1;
        return min(sp[d][L],sp[d][R-(1ll<<d)+1]).se;
    }

    ll dist(ll l,ll r){
        return deep[l]+deep[r]-2*deep[lca(l,r)];
    }

    bool on_path(ll l,ll r,ll x){
        return dist(l,x)+dist(x,r)==dist(l,r);
    }

    void build_binary(){
        ll size=25;
        binary_P.assign(size,vel(N));
        binary_P[0]=P;
        rep(i,1,size){
            rep(j,0,N)binary_P[i][j]=binary_P[i-1][binary_P[i-1][j]];
        }
    }

    ll up(ll now,ll K){//build_binaryを使わないとダメ
        rep(i,0,25){
            if((1ll<<i)&K){
                now=binary_P[i][now];
            }
            if((1ll<<i)>K)break;
        }
        return now;
    }

    bool subtree(ll u,ll root){
        return in[root]<=in[u]&&out[u]<=out[root];
    }

    void solve(ll Q){
        ///セグ木初期化パート
        pll id={-1,-1};
        auto combine=[&](pll l,pll r)->pll {
            pll ret={-1,-1};
            ll d=-1;
            vel v={l.fi,l.se,r.fi,r.se};
            rep(i,0,4){
                rep(j,i+1,4){
                    if(v[i]==-1||v[j]==-1)continue;
                    if(dist(v[i],v[j])>d){
                        d=dist(v[i],v[j]);
                        ret={v[i],v[j]};
                    }
                }
            }
            return ret;
        };
        seg<pll,decltype(combine)> st(ord.size(),combine,id);
        rep(i,0,N){
            st.chan(in[i],{i,i});
        }
        build_binary();
        rep(_,0,Q){
            ll x;
            cin>>x;
            x--;
            cin>>K;
            vel v(K);
            rep(i,0,K)cin>>v[i];
            rep(i,0,K)v[i]--;
            vel p;
            vel q;
            rep(i,0,K){
                if(subtree(x,v[i])){
                    p.push_back(v[i]);
                }else{
                    q.push_back(v[i]);
                }
            }
            pll lr={0,ord.size()};
            ll now=0;
            rep(i,0,p.size()){
                if(deep[now]<=deep[p[i]]){
                    now=p[i];
                    now=up(x,dist(now,x)-1);
                }
                lr.fi=max(lr.fi,in[now]);
                lr.se=min(lr.se,out[now]);
            }
            vepll od;
            rep(i,0,q.size()){
                if(subtree(q[i],now)){
                    od.push_back({in[q[i]],1});
                    od.push_back({out[q[i]],-1});
                }
            }
            sort(od.begin(),od.end());
            ll ok=0;
            pll d={-1,-1};
            ll l=lr.fi;
            for(auto[now,c]:od){
                if(ok==0){
                    pll ret=st.Ique(l,now);
                    d=combine(ret,d);
                }
                ok+=c;
                l=now;
            }
            if(l<lr.se)d=combine(st.Ique(l,lr.se),d);
            cout<<max(dist(x,d.fi),dist(x,d.se))<<"\n";
        }
    }
};


void _solve(){
    cin>>N>>Q;
    vvel G(N);
    rep(i,0,N-1){
        cin>>x>>y;
        x--;
        y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    LCA lca(G);
    lca.solve(Q);
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