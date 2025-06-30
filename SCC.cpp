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
//ll p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(a.begin(),a.end(),A.at(i))-a.begin();
    swap(A,a);
*/

struct SCC{
    vvel G;
    vvel NG;
    vvel DAG;//0のindegが0とは限らない
    vvel eq;//DAGの各頂点に何があるのか
    vel Id;//各頂点はDAGのどこにあるのか
    vepll rev;
    ll N;

    void dfs0(vel &seen,ll now,ll &cnt){
        seen.at(now)=1;
        for(auto y:G.at(now)){
            if(seen.at(y)==-1)dfs0(seen,y,cnt);
        }
        rev.at(now)={cnt,now};
        cnt++;
        return ;
    }

    void dfs1(vvel &G,vel &v,vel &seen,ll now){
        seen.at(now)=1;
        v.push_back(now);
        for(auto y:G.at(now)){
            if(seen.at(y)==-1)dfs1(G,v,seen,y);
        }
        return ;
    }

    SCC(vvel &g){
        N=g.size();
        G=g;
        NG.assign(N,{});
        rep(i,0,N){
            for(auto y:G.at(i)){
                NG.at(y).push_back(i);
            }
        }
        Id.assign(N,-1);
        rev.assign(N,{0,0});
        ll cnt=0;
        vel seen(N,-1);
        rep(i,0,N){
            if(seen.at(i)==-1){
                dfs0(seen,i,cnt);
            }
        }
        seen.assign(N,-1);
        sort(rev.rbegin(),rev.rend());
        rep(i,0,N){
            x=rev.at(i).se;
            if(seen.at(x)==-1){
                vel v;
                dfs1(NG,v,seen,x);
                rep(j,0,v.size())Id.at(v.at(j))=eq.size();
                eq.push_back(v);
            }
        }
        ll n=eq.size();
        DAG.assign(n,{});
        rep(i,0,N){
            for(auto y:G.at(i)){
                if(Id.at(i)==Id.at(y))continue;
                DAG.at(Id.at(i)).push_back(Id.at(y));
            }
        }
        rep(i,0,n){
            sort(DAG.at(i).begin(),DAG.at(i).end());
            DAG.at(i).erase(unique(DAG.at(i).begin(),DAG.at(i).end()),DAG.at(i).end());
        }
        return ;
    }
};

int main(){
    cin>>N>>M;
    vvel G(N);
    rep(i,0,M){
        cin>>x>>y;
        G.at(x).push_back(y);
    }
    SCC scc(G);
    vvel dag=scc.DAG;
    vvel eq=scc.eq;
    queue<ll> qu;
    N=dag.size();
    vel indeg(N,0);
    rep(i,0,N){
        for(auto y:dag.at(i)){
            indeg.at(y)++;
        }
    }
    rep(i,0,N){
        if(indeg.at(i)==0)qu.push(i);
    }
    cout<<N<<endl;
    while(!qu.empty()){
        x=qu.front();
        qu.pop();
        cout<<eq.at(x).size()<<" ";
        rep(i,0,eq.at(x).size())cout<<eq.at(x).at(i)<<" ";
        cout<<endl;
        for(auto y:dag.at(x)){
            indeg.at(y)--;
            if(indeg.at(y)==0)qu.push(y);
        }
    }
}