#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define bl __int128_t
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

struct Combine {
    inline ll operator()(ll a,ll b){
        return min(a,b);
    }
};

template<typename T, typename Combine>
struct seg{
    int N;
    Combine combine;
    T id;
    vector<T> node;
    int sz;

    seg(vector<T> &a,Combine com,T ident){
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

    seg(ll n,Combine com,T ident){
        sz=n;
        combine=com;
        id=ident;
        ll m=1;
        while(m<sz) m*=2;
        node.resize(2*m,id);
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

    inline T get(int i){
        return node[i+N];
    }

    inline T all(){
        return node[1];
    }

    template<typename F>
    int upper(int l,T x,F check){//check(node[now],x)=1の最小のindex
        if(l>=sz)return sz;
        l+=N;
        T now=id;
        do{
            while(l%2==0)l>>=1;//左にいるなら区間を大きくする
            if(check(combine(now,node[l]),x)){//この区間でhitしてる
                while(l<N){//降りていく
                    l=2*l;
                    if(!check(combine(now,node[l]),x)){//hitしないなら右に降りる
                        now=combine(now,node[l]);
                        l++;
                    }
                }
                return l-N;
            }
            now=combine(now,node[l]);//hitしなかったから右に行く
            l++;
        }while((l&-l)!=l);//2冪なら終わる(各層の右端が1,2,4,8,...なので)
        return sz;
    }


    template<typename F>
    inline int lower(int r,T x,F check){//check(node[now],x)=1の最大のindex
        if(r<=0)return -1;
        r+=N;
        T now=id;
        do{
            r--;
            while(r>1&&(r%2))r>>=1;//右側にいるなら区間を大きくする
            if(check(combine(node[r],now),x)){
                while(r<N){
                    r=2*r+1;
                    if(!check(combine(node[r],now),x)){//hitしないなら左に降りる
                        now=combine(node[r],now);
                        r--;
                    }
                }
                return r-N;
            }
            now=combine(node[r],now);
        }while((r&-r)!=r);//2冪なら場外(r+1が右端になってるので)
        return -1;
    }
};

void _solve(){
    cin>>N>>Q;
    vel a(N);
    rep(i,0,N)cin>>a[i];
    vel dp(N+1);
    rep(i,0,N){
        if(a[i]<=N)dp[a[i]]++;
    }
    seg<ll,Combine> st(dp,Combine(),inf);
    rep(q,0,Q){
        cin>>x>>y;
        x--;
        ll now;
        if(a[x]<=N){
            now=st.Ique(a[x],a[x]+1);
            st.chan(a[x],now-1);
        }
        a[x]=y;
        if(a[x]<=N){
            now=st.Ique(a[x],a[x]+1);
            st.chan(a[x],now+1);
        }
        auto check=[&](ll val,ll x){
            return val<=x;
        };
        cout<<st.upper(0,0,check)<<"\n";
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
