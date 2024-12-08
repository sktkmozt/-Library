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

ll inf=998244353;
// inf=1e9+7;
// LLONG_MAX

ld f(pll x,pll y){
    return sqrt((x.fi-y.fi)*(x.fi-y.fi)+(x.se-y.se)*(x.se-y.se));
}

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


int main() {
    cin>>N>>K;
    pll s;
    cin>>s.fi>>s.se;
    vepll a(N);
    rep(i,0,N) cin>>a.at(i).fi>>a.at(i).se;
    vector<ll> dp(N,0);
    dp.at(0)=0;


    ///セグ木初期化パート
    auto combine=[](ll a,ll b){return a+b;};
    ll id=0;
    seg<ll> st(dp,combine,id);
    ///

    rep(i,1,N){
        dp.at(i)=st.Ique(max((ll)0,i-K),i,0,0,-1)+f(s,a.at(i-1))+f(s,a.at(i))-f(a.at(i-1),a.at(i));
        st.chan(i,dp.at(i));
    }
    ld ans=f(s,a.at(0));
    rep(i,0,N-1){
        ans+=f(a.at(i),a.at(i+1));
    }
    ans+=f(a.at(N-1),s);
    cleout(16);
    cout<<ans+st.Ique(N-K,N);
}
