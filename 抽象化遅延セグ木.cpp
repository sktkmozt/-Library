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
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
//               上  右 下 左
vector<int> dx={ -1, 0, 1, 0 };
vector<int> dy={ 0, 1, 0, -1 };

vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll N, K, M, L, T, Q, H, W, i, j, l;
ll x, y, z;
unsigned long long q;
string S;
long double k;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};
ll inf=998244353;

template<typename T,typename E>
struct lsg{
    int N;
    using F=function<T(T,T,pll)>;//queで上に送る
    using G=function<T(T,E,pll)>;//nodeをlazyを使って更新
    using H=function<E(E,E,pll)>;//区間が合うように調整しながらlazyを下に渡す
    F combineT;
    G op;
    H combineE;
    T idT;
    E idE;
    vector<T> node;
    vector<E> lazy;
    vepll range;
    lsg(vector<T> &a,F comt,H come,G o,T idt,E ide){
        ll sz=a.size();
        combineT=comt;
        op=o;
        combineE=come;
        idT=idt;
        idE=ide;
        N=1;
        while(N<sz){
            N*=2;
        }
        node.assign(2*N-1,idT);
        lazy.assign(2*N-1,idE);
        range.assign(2*N-1,{0,N});
        rep(i,0,sz){
            node[i+N-1]=a[i];
        }
        rrep(i,N-1,0){
            node[i]=combineT(node[2*i+1],node[2*i+2],range[2*i+1]);
        }
        rep(i,0,N-1){
            pll x=range[i];
            range[2*i+1]={x.fi,(x.fi+x.se)/2};
            range[2*i+2]={(x.fi+x.se)/2,x.se};
        }
    }
    void val(int now){//lazyを初期化(伝播)
        if(lazy[now]!=idE){
            if(now<N-1){
                lazy[2*now+1]=combineE(lazy[now],lazy[2*now+1],range[2*now+1]);
                lazy[2*now+2]=combineE(lazy[now],lazy[2*now+2],range[2*now+2]);
            }
            node[now]=op(node[now],lazy[now],range[now]);
        }
        lazy[now]=idE;
    }
    void Ichan(ll l,ll r,ll nowl,ll nowr,ll now,E x){//下に降りて上に上がる
        if(nowr<0) nowr=N;
        stack<tuple<int,int,int>> st;
        st.push({0,N,0});
        stack<ll> s;
        while(!st.empty()){
            tuple<int,int,int> X=st.top();
            st.pop();
            val(get<2>(X));
            if(l>=get<1>(X)||get<0>(X)>=r){
                
            }else if(l<=get<0>(X)&&get<1>(X)<=r){
                lazy[get<2>(X)]=x;
                val(get<2>(X));
            }else{
                st.push({get<0>(X),(get<0>(X)+get<1>(X))/2,2*get<2>(X)+1});
                st.push({(get<0>(X)+get<1>(X))/2,get<1>(X),2*get<2>(X)+2});
                s.push(get<2>(X));
            }
        }
        while(!s.empty()){
            node[s.top()]=combineT(node[2*s.top()+1],node[2*s.top()+2],range[2*s.top()+1]);
            s.pop();
        }
    }
    void Ichan(ll l,ll r,E x){
        Ichan(l,r,(ll)0,(ll)-1,(ll)0,x);
    }
    T Ique(ll l,ll r,ll nowl,ll nowr,ll now){
        if(nowr<0) nowr=N;
        val(now);
        if(nowr<=l||r<=nowl){
            return idT;
        }else if(l<=nowl&&nowr<=r){
            return node[now];
        }else{
            return combineT(Ique(l,r,nowl,(nowl+nowr)/2,2*now+1),Ique(l,r,(nowl+nowr)/2,nowr,2*now+2),range[2*now+1]);
        }
    }
    T Ique(ll l,ll r){
        return Ique(l,r,0,-1,0);
    }
};

int main() {
    cin>>W>>N;
    vepll a(N);
    rep(i,0,N) cin>>a.at(i).fi>>a.at(i).se;
    vel w(W,0);

    ll idT=0;//ノードの単位元
    ll idE=0;//lazyの単位元
    auto combineT=[&](ll s,ll t,pll x){
        return max(s,t);
    };//Iqueで上に送る
    auto combineE=[&](ll a,ll b,pll x){//lazyの合成a(b(T))で区間はxが持ってる
        return max(a,b);
    }; 
    auto op=[&](ll s,ll a,pll x){//lazyを使ってnodeを更新(node,lazy,pll)
        return max(s,a);
    };
    lsg<ll,ll> st(w,combineT,combineE,op,idT,idE);//node,lazyの型
    
    vel ans;
    rep(i,0,N){
        x=st.Ique(a.at(i).fi-1,a.at(i).se);
        st.Ichan(a.at(i).fi-1,a.at(i).se,x+1);
        ans.push_back(x+1);
    }
    rep(i,0,N) cout<<ans.at(i)<<endl;
}