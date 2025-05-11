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

struct combineT {
    // combineT:nodeをcombineする
    inline ll operator()(ll s, ll t, pll rng) const { return min(s,t); }
};

struct op {
    // op:nodeにlazyを作用させる
    inline ll operator()(ll l, ll s, pll rng) const {
        return l+s;
    }
};

struct combineE {
    // combineE:lazyをcombineする
    inline ll operator()(ll l1, ll l2, pll rng) const {
        return l1+l2;
    }
};

template<typename T, typename E, typename F, typename G, typename H>
struct lsg {
    int N;
    F combineT;
    H combineE;
    G op;
    T idT; // 単位元（区間合成用）
    E idE; // 単位元（lazy用）
    
    vector<T> node;
    vector<E> lazy;
    vector<pll> range;  // 各ノードが担当する区間 [first, second)
    
    // コンストラクタ
    lsg(const vector<T> &a,F combineT,H combineE,G op,T idT,E idE)
        : combineT(combineT),op(op),combineE(combineE),idT(idT),idE(idE)
    {
        int sz=a.size();
        N=1;
        while(N<sz)N*=2;
        node.assign(2*N-1,idT);
        lazy.assign(2*N-1,idE);
        range.assign(2*N-1,{0,N});
        
        rep(i,0,sz){
            node[i+N-1]=a[i];
        }
        rrep(i,N-2,0){
            node[i]=combineT(node[2*i+1],node[2*i+2],range[2*i+1]);
        }
        for (int i=0;i<N-1;i++) {
            pll r=range[i];
            int mid=(r.first+r.second)/2;
            range[2*i+1]={r.first,mid};
            range[2*i+2]={mid,r.second};
        }
    }
    
    inline void val(int idx) {
        if (lazy[idx]!=idE){
            if (idx<N-1) {
                lazy[2*idx+1]=combineE(lazy[idx],lazy[2*idx+1],range[2*idx+1]);
                lazy[2*idx+2]=combineE(lazy[idx],lazy[2*idx+2],range[2*idx+2]);
            }
            node[idx]=op(node[idx],lazy[idx],range[idx]);
            lazy[idx]=idE;
        }
    }
    
    inline void Ichan(int l,int r,E x,int idx,int L,int R) {
        val(idx);
        if (R<=l||r<=L)return;
        if (l<=L&&R<=r) {
            lazy[idx]=combineE(x,lazy[idx],{L,R});
            val(idx);
        } else {
            int mid=(L+R)/2;
            Ichan(l,r,x,2*idx+1,L,mid);
            Ichan(l,r,x,2*idx+2,mid,R);
            node[idx]=combineT(node[2*idx+1],node[2*idx+2],range[2*idx+1]);
        }
    }
    inline void Ichan(int l,int r,E x){
        Ichan(l,r,x,0,0,N);
    }
    
    inline T Ique(int l,int r,int idx,int L,int R){
        val(idx);
        if (R<=l||r<=L)return idT;
        if (l<=L&&R<=r)return node[idx];
        int mid=(L+R)/2;
        T leftVal=Ique(l,r,2*idx+1,L,mid);
        T rightVal=Ique(l,r,2*idx+2,mid,R);
        return combineT(leftVal,rightVal,range[2*idx+1]);
    }

    inline T Ique(int l, int r) {
        return Ique(l, r, 0, 0, N);
    }
};

int main(){
    cin>>N>>Q;
    cin>>S;
    vel w(N+1);
    rep(i,0,N){
        w.at(i+1)=2*(S.at(i)=='(')-1;
    }
    rep(i,0,N)w.at(i+1)+=w.at(i);

    ll idT=inf;
    ll idE=0;
    lsg<ll, ll, combineT, op, combineE> st(w, combineT(),combineE(),op(),idT,idE);
    vel ans;
    rep(q,0,Q){
        ll l,r;
        cin>>x>>l>>r;
        if(x==1){
            if(S.at(l-1)==S.at(r-1))continue;
            if(S.at(l-1)=='('){
                st.Ichan(l,N,-2);
                st.Ichan(r,N,2);
                S.at(l-1)=')';
                S.at(r-1)='(';
            }else{
                S.at(l-1)='(';
                S.at(r-1)=')';
                st.Ichan(l,N,2);
                st.Ichan(r,N,-2);
            }
        }else{
            ans.push_back(st.Ique(l-1,l)==st.Ique(r,r+1)&&st.Ique(l-1,l)<=st.Ique(l-1,r+1));
        }
    }
    rep(i,0,ans.size())cout<<(ans.at(i)==1?"Yes":"No")<<endl;
}