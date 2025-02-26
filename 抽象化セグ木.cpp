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
#define vem vector<mint>
#define vvem vector<vector<mint>>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

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

struct Combine {
    inline ll operator()(ll a,ll b){
        return max(a,b);
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

    inline int upper(T x){
        int now=1;
        T res=id;
        if(node[now]<=x){
            return sz;
        }
        while(now<N){
            if(combine(res,node[2*now])<=x){
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


int main(){
    cin>>N>>Q;
    vel a(N);
    rep(i,0,N) cin>>a.at(i);
    ///セグ木初期化パート
    ll id=-1e18;
    seg<ll,Combine> st(a,Combine(),id);
    vel ans;
    rep(i,0,Q){
        cin>>x;
        if(x==1){
            cin>>y>>z;
            st.chan(y-1,z);
        }else if(x==2){
            ll l,r;
            cin>>l>>r;
            ans.push_back(st.Ique(l-1,r));
        }else{
            cin>>x>>y;
            if(st.Ique(x-1,N)<y){
                ans.push_back(N+1);
                continue;
            }
            if(st.Ique(x-1,x)>=y){
                ans.push_back(x);
                continue;
            }
            ll ng=x-1,ok=N;
            while(ok-ng>1){
                ll mid=(ng+ok)/2;
                if(st.Ique(x-1,mid)<y)ng=mid;
                else ok=mid; 
            }
            ans.push_back(ok);
        }
    }
    rep(i,0,ans.size()) cout<<ans.at(i)<<endl;
}

/*
g++ a.cpp -std=c++20
*/