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

struct graph{
    struct edge{
        ll to,cap,rev;
        edge(ll t,ll c,ll r):to(t),cap(c),rev(r){
        }
    };

    ll size;
    vector<vector<edge>> G;
    vel level;//cap>0の辺でのsからの距離
    vel iter;//G[now]のiter[now]以下の辺はすべてgまでいけない

    graph(ll N):size(N),level(N),iter(N),G(N){
    }

    void add_flow(ll from,ll to,ll cap=1){
        G[from].push_back({to,cap,(ll)G[to].size()});
        G[to].push_back({from,0,(ll)G[from].size()-1});
    }

    void bfs(ll s){
        fill(level.begin(),level.end(),inf);
        level[s]=0;
        queue<ll> qu;
        qu.push(s);
        while(qu.size()){
            ll now=qu.front();
            qu.pop();
            for(auto &e:G[now]){
                if(e.cap>0&&level[e.to]>level[now]+1){
                    level[e.to]=level[now]+1;
                    qu.push(e.to);
                }
            }
        }
    }

    ll dfs(ll now,ll g,ll f){
        if(now==g)return f;
        for(ll &i=iter[now];i<G[now].size();i++){
            edge &e=G[now][i];
            if(level[e.to]!=level[now]+1)continue;
            if(e.cap==0)continue;
            ll d=dfs(e.to,g,min(e.cap,f));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;//最後まで行かないからiterは足されない
            }
        }
        return 0;
    }

    ll flow(ll s,ll g){//2回以上呼ぶと追加分しか流れない
        ll res=0;
        while(1){
            level.assign(size,inf);
            bfs(s);
            if(level[g]==inf)return res;
            fill(iter.begin(),iter.end(),0);
            while(1){
                ll f=dfs(s,g,inf);
                res+=f;
                if(f==0)break;
            }
        }
    }
};

ll f(pll now){
    return now.fi*N+now.se;
}

void _solve(){
    ll A,B;
    cin>>N>>A>>B;
    vvel seen(N,vel(N,-1));
    vvel a(N,vel(N));
    rep(i,0,N){
        cin>>S;
        rep(j,0,N){
            if(S[j]=='#')a[i][j]=1;
        }
    }
    vel DX={A,A,-A,-A,B,B,-B,-B};
    vel DY={B,-B,B,-B,A,-A,A,-A};
    rep(i,0,N){
        rep(j,0,N){
            if(a[i][j])continue;
            if(seen[i][j]==-1){
                queue<pll> qu;
                qu.push({i,j});
                seen[i][j]=0;
                while(!qu.empty()){
                    pll now=qu.front();
                    qu.pop();
                    rep(k,0,8){
                        pll nnow={now.fi+DX[k],now.se+DY[k]};
                        if(0<=nnow.fi&&nnow.fi<N&&0<=nnow.se&&nnow.se<N){
                            if(a[nnow.fi][nnow.se]==0){
                                if(seen[nnow.fi][nnow.se]==-1){
                                    seen[nnow.fi][nnow.se]=seen[now.fi][now.se]^1;
                                    qu.push(nnow);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    graph G(N*N+2);
    vepll u,v;
    rep(i,0,N){
        rep(j,0,N){
            if(seen[i][j]==0)u.push_back({i,j});
            if(seen[i][j]==1)v.push_back({i,j});
        }
    }
    rep(i,0,u.size()){
        G.add_flow(0,f(u[i])+1);
        pll now=u[i];
        rep(k,0,8){
            pll nnow={now.fi+DX[k],now.se+DY[k]};
            if(0<=nnow.fi&&nnow.fi<N&&0<=nnow.se&&nnow.se<N){
                if(a[nnow.fi][nnow.se])continue;
                G.add_flow(f(now)+1,f(nnow)+1,inf);
            }
        }
    }
    rep(i,0,v.size()){
        G.add_flow(f(v[i])+1,N*N+1);
    }
    G.flow(0,N*N+1);
    G.bfs(0);
    vel d=G.level;
    rep(i,0,N){
        rep(j,0,N){
            if(a[i][j]){
                cout<<"#";
            }else{
                if(seen[i][j])cout<<(d[i*N+j+1]==inf?"o":".");
                else cout<<(d[i*N+j+1]==inf?".":"o");
            }
        }
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
