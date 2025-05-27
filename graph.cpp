#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
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
#define vvepll vector<vepll>
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

ll N,K,M,L,R,T,Q,H,W,i,j,k,l;
ll x,y,z;
string S,SS;
vel mod={998244353,1000000007,1000000009,1000000021,1000000033};//(1<<61)-1も素数
ll p=998244353;
// p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(a.begin(),a.end(),A.at(i))-a.begin();
    swap(A,a);
*/

struct graph{
    ll size;
    vvel vertex;
    vepll edge;
    vel cost;
    vepll mergin;
    graph(ll n){
        size=n;
        vertex.assign(size,{});
    }
    void add(ll x,ll y,ll to=1){//有向辺
        vertex.at(x).push_back(edge.size());
        edge.push_back({x,y});
        cost.push_back(to);
    }
    void add_flow(ll x,ll y,ll to=1){//有向辺
        vertex.at(x).push_back(edge.size());
        edge.push_back({x,y});
        vertex.at(y).push_back(edge.size());
        edge.push_back({y,x});
        mergin.push_back({to,0});
    }
    vel bfs(ll s,bool is_flow=false){
        queue<ll> qu;
        qu.push(s);
        vel ret(size,inf);
        ret.at(s)=0;
        while(!qu.empty()){
            ll now=qu.front();
            qu.pop();
            for(auto y:vertex.at(now)){
                ll nnow=edge.at(y).se;
                if(is_flow){
                    if(y%2==0&&mergin.at(y/2).fi==0)continue;
                    if(y%2==1&&mergin.at(y/2).se==0)continue;
                }
                if(ret.at(nnow)>ret.at(now)+1){
                    ret.at(nnow)=ret.at(now)+1;
                    qu.push(nnow);
                }
            }
        }
        return ret;
    }
    vel bfs01(ll s){
        deque<ll> qu;
        qu.push_back(s);
        vel ret(size,inf);
        ret.at(s)=0;
        while(!qu.empty()){
            ll now=qu.front();
            qu.pop_front();
            for(auto y:vertex.at(now)){
                ll nnow=edge.at(y).se;
                ll cst=cost.at(y);
                if(ret.at(nnow)>ret.at(now)+cst){
                    ret.at(nnow)=ret.at(now)+cst;
                    if(cst==1)qu.push_back(nnow);
                    else qu.push_front(nnow);
                }
            }
        }
        return ret;
    }
    vel djk(ll s){
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({0,s});
        vel ret(size,inf);
        ret.at(s)=0;
        while(!pq.empty()){
            pll now=pq.top();
            pq.pop();
            if(ret.at(now.se)!=now.fi)continue;
            for(auto y:vertex.at(now.se)){
                ll nnow=edge.at(y).se;
                ll cst=cost.at(y);
                if(ret.at(nnow)>ret.at(now.se)+cst){
                    ret.at(nnow)=ret.at(now.se)+cst;
                    pq.push({ret.at(nnow),nnow});
                }
            }
        }
        return ret;
    }
    ll dfs_flow(vel &dist,ll now,ll g,ll &f){
        if(f==0)return 0;
        if(now==g){
            return f;
        }
        ll cnt=0;
        for(auto y:vertex.at(now)){
            ll nnow=edge.at(y).se;
            if(dist.at(nnow)>dist.at(now)){
                ll mgn=(y%2==0?mergin.at(y/2).fi:mergin.at(y/2).se);
                if(mgn==0)continue;
                ll f_mgn=min(f,mgn);
                ll flow=dfs_flow(dist,nnow,g,f_mgn);
                f-=flow;
                if(y%2==0){
                    mergin.at(y/2).fi-=flow;
                    mergin.at(y/2).se+=flow;
                }else{
                    mergin.at(y/2).fi+=flow;
                    mergin.at(y/2).se-=flow;
                }
                cnt+=flow;
            }
        }
        return cnt;
    }
    ll flow(ll s,ll g){
        ll flow=0;
        while(1){
            vel dist=bfs(s,true);
            if(dist.at(g)==inf)break;
            ll f=dfs_flow(dist,s,g,inf);
            flow+=f;
        }
        return flow;
    }
};

int main(){
    cin>>H>>W>>N;
    graph G(H+W+2*N+2);//0=s
                       //1~H
                       //H+1~H+N
                       //H+N+1~H+2*N
                       //H+2*N+1~H+W+2*N
                       //H+W+2*N+1
    rep(i,1,H+1){
        G.add_flow(0,i);
    }
    rep(i,1,W+1){
        G.add_flow(H+2*N+i,H+W+2*N+1);
    }
    rep(i,0,N){
        ll w;
        cin>>x>>y>>z>>w;
        rep(j,x,z+1){
            G.add_flow(j,H+i+1);
        }
        G.add_flow(i+H+1,i+H+N+1);
        rep(j,y,w+1){
            G.add_flow(i+H+N+1,H+2*N+j);
        }
    }
    cout<<G.flow(0,H+W+2*N+1);
}