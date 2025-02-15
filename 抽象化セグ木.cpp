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
        node.resize(2*m-1,id);
        rep(i,0,sz){
            node[i+m-1]=a[i];
        }
        for(ll i=m-2;i>=0;i--){
            node[i]=combine(node[2*i+1],node[2*i+2]);
        }
        N=m;
    }
    inline void chan(int i,T x){//i番目をxに変える
        i+=N-1;
        node[i]=x;
        while(i>0){
            i--;
            i/=2;
            node[i]=combine(node[2*i+1],node[2*i+2]);
        }
    }
    inline T  Ique(int l,int r){//[a,b)のmin
        T resl=id,resr=id;
        l+=N-1;
        r+=N-1;
        while(l<r){
            if(!(l&1)){//左のほうの右側なので
                resl=combine(resl,node[l]);
                l--;
            }
            if(!(r&1)){//半開区間なのでrが右だといい
                r--;
                resr=combine(node[r],resr);
            }
            l/=2;
            r/=2;
        }
        return combine(resl,resr);
    }

    inline int upper(T x){
        int now=0;
        T res=id;
        if(node.at(now)<=x){
            return sz;
        }
        while(now<N-1){
            if(combine(res,node[2*now+1])<=x){
                res=combine(res,node[2*now+1]);
                now++;
                now*=2;
            }else{
                now*=2;
                now++;
            }
        }
        return now-(N-1);
    }
};

int main(){
    cin>>N>>Q;
    vel a(N);
    rep(i,0,N) cin>>a.at(i);
    vel dp(N,1e18);

    ///セグ木初期化パート
    ll id=-1e18;
    seg<ll,Combine> st(dp,Combine(),id);

    map<ll,ll> ma;
    vvel q(Q,vel(3));
    rep(i,0,Q){
        cin>>q.at(i).at(0)>>q.at(i).at(1);
        q.at(i).at(2)=i;
    }
    sort(all(q,0,q.size()));
    ll ind=0;
    rep(i,0,N){
        if(ind>=q.size()) break;
        x=st.upper(a.at(i)-1);
        st.chan(x,a.at(i));
        while(ind<q.size()&&q.at(ind).at(0)-1<=i){
            ma[q.at(ind).at(2)]=st.upper(q.at(ind).at(1));
            ind++;
        }
    }
    for(auto it=ma.begin();it!=ma.end();it++){
        cout<<it->se<<endl;
    }
}

/*
g++ a.cpp -std=c++20
*/