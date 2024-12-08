#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define all(a,i,j) a.begin()+i,a.begin()+j
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};



vector<int> ddx={ 1, 1,  1,  0, -1, -1, -1, 0};
vector<int> ddy={ 1, 0, -1, -1, -1,  0,  1, 1};

ll N, K, M, L, R, Q, H, W, i, j, k, l;
ll x, y, z;
string S,T;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};//(1<<61)-1も素数
ll inf=998244353;
// inf=1e9+7;
// LLONG_MAX

/*座圧
    vel A=a;
    sort(all(a,0,a.size()));
    a.erase(unique(all(a,0,a.size())),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(all(a,0,a.size()),A.at(i))-a.begin();
    swap(A,a);
*/


template<typename T>
struct seg{
    int N;
    using F=function<T(T,T)>;//多分これが関数の型ってやつ
    F combine;
    T id;
    vector<T> node;

    seg(vector<T> &a,F com,T ident){
        int sz=a.size();
        combine=com;
        id=ident;
        ll m=1;
        while(m<sz) m*=2;
        node.resize(2*m-1,id);
        rep(i,0,sz){
            node[i+m-1]=a[i];
        }
        for(ll i=m-2;i>=0;i--){
            node[i]=combine(node[2*i+1],node[2*i+2]);
        }
        N=m;
    }
    void chan(int i,T x){//i番目をxに変える
        i+=N-1;
        node[i]=x;
        while(i>0){
            i--;
            i/=2;
            node[i]=combine(node[2*i+1],node[2*i+2]);
        }
    }
    T  Ique(int a,int b,int now=0,int l=0,int r=-1){//[a,b)のmin
        if(r==-1) r=N;//aのsixeからn出すの無水から
        if(r<=a||b<=l) return id;//かすりなし
        if(a<=l&&r<=b) return node[now];//おおわれてるとき
        T al=Ique(a,b,2*now+1,l,(l+r)/2); 
        T ar=Ique(a,b,2*now+2,(l+r)/2,r);
        return combine(al,ar);
    }
    T  Ique(ll a,ll b){
        return Ique(a,b,0,0,-1);
    }
};



struct Etour{//lcaを求める、使う頂点の出入りのタイミングind,oind,使う辺の出入りのタイミングin,outを見れる
    vel in,out,ind,oind,dp;//in->辺を使う前 out->辺を出る前 ind->最初に頂点に来た oind->最後に頂点を出たとき　dp->頂点の順番
    vepll deep;//dpに対応する深さ
    vepll RMQ;
    ll size;
    void dfs(vector<vepll> &G,ll now,ll par,ll d){
        if(ind.at(now)==-1) ind.at(now)=dp.size();
        deep.push_back({d,now});
        dp.push_back(now);
        for(auto y:G.at(now)){
            if(y.fi==par) continue;
            in.at(y.se)=dp.size()-1;
            dfs(G,y.fi,now,d+1);
            out.at(y.se)=dp.size()-1;
            dp.push_back(now);
            deep.push_back({d,now});
        }
        oind.at(now)=dp.size()-1;
    }

    Etour(vector<vepll> &G){//(頂点,辺の番号)を持ったグラフ
        ind.assign(G.size(),-1);
        oind.assign(G.size(),-1);
        in.assign(G.size()-1,-1);
        out.assign(G.size()-1,-1);
        dfs(G,0,0,0);
        ll now=1;
        while(now<deep.size()+1){
            now*=2;
        }
        RMQ.assign(2*now,{1e18,-1});
        rep(i,0,deep.size()){
            RMQ.at(now+i)=deep.at(i);
        }
        rrep(i,now,1){
            RMQ.at(i)=min(RMQ.at(2*i),RMQ.at(2*i+1));
        }
        size=now;
    }
    
    pll Ique(ll now,ll l,ll r,ll u,ll v){
        if(u<=l&&r<=v) return RMQ.at(now);
        if(r<=u||v<=l) return {1e18,-1};
        return min(Ique(2*now,l,(l+r)/2,u,v),Ique(2*now+1,(l+r)/2,r,u,v));
    }

    ll lca(ll U,ll V){
        pll now={0,size};
        ll u=min(ind.at(U),ind.at(V));
        ll v=max(ind.at(U),ind.at(V))+1;
        return Ique(1,0ll,size,u,v).se;
    }
};



int main(){
    cin>>N;
    vector<vepll> G(N);
    vel edge(N-1); 
    rep(i,0,N-1){
        cin>>x>>y>>z;
        x--;
        y--;
        edge.at(i)={z};
        G.at(x).push_back({y,i});
        G.at(y).push_back({x,i});
    } 
    Etour et(G);
    cin>>Q;

    vel dp(et.dp.size(),0);
    rep(i,0,N-1){
        dp.at(et.in.at(i))+=edge.at(i);
        dp.at(et.out.at(i))-=edge.at(i);
    }
    ///セグ木初期化パート
    auto combine=[](ll a,ll b){return a+b;};
    ll id=0;
    seg<ll> st(dp,combine,id);
    ///
    vel ans;
    rep(i,0,Q){
        cin>>x;
        if(x==1){
            cin>>x>>y;
            x--;
            st.chan(et.in.at(x),y);
            st.chan(et.out.at(x),-y);
        }else{
            cin>>x>>y;
            x--;
            y--;
            ll res=0;
            ll lca=et.lca(x,y);
            res+=abs(st.Ique(0ll,et.ind.at(x)));
            res+=abs(st.Ique(0ll,et.ind.at(y)));
            res-=2*abs(st.Ique(0ll,et.ind.at(lca)));
            ans.push_back(res);
        }
    }
    rep(i,0,ans.size()){
        cout<<ans.at(i)<<endl;
    }
}
/*
g++ a.cpp -std=c++20
*/