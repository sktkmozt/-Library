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
#define vvvel vector<vvel>
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
//#define mint Mint<1000000007>
#define cleout(i) cout<<fixed<<setprecision(i)
#define ppcnt __builtin_popcount
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
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
// LLONG_MAX

struct info{
    ll min_val;
    ll min_cnt;
    ll sum;
    info(){
        min_val=inf;
        min_cnt=0;
        sum=0;
    }
};

struct Combine {
    inline info operator()(info a,info b){
        info res;
        if(a.min_val==a.sum+b.min_val){
            res=a;
            res.min_cnt+=b.min_cnt;
            res.sum+=b.sum;
        }else{
            if(a.min_val>a.sum+b.min_val){
                res=b;
                res.min_val=a.sum+b.min_val;
                res.sum+=a.sum;
            }else{
                res=a;
                res.sum+=b.sum;
            }
        }
        return res;
    }
};

template<typename T, typename Combine>
struct compseg{
    int N;
    Combine combine;
    T id;
    vector<T> node;
    vel dic;
    int sz;

    compseg(map<ll,T> &ma,Combine com,T ident){
        sz=ma.size();
        combine=com;
        id=ident;
        ll m=1;
        while(m<sz) m*=2;
        node.resize(2*m,id);
        for(auto it=ma.begin();it!=ma.end();it++){
            node[dic.size()+m]=it->se;
            dic.push_back(it->fi);
        }
        rrep(i,m,1){
            node[i]=combine(node[2*i],node[2*i+1]);
        }
        N=m;
    }

    inline void _chan(int i,T x){//i番目をxに変える
        i+=N;
        node[i]=x;
        while(i>0){
            i/=2;
            node[i]=combine(node[2*i],node[2*i+1]);
        }
    }

    inline void chan(ll i,T x){
        ll _i=lower_bound(dic.begin(),dic.end(),i)-dic.begin();
        _chan(_i,x);
    }

    inline T  _Ique(int l,int r){//[a,b)のmin
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

    inline T  Ique(ll l,ll r){
        ll _l=lower_bound(dic.begin(),dic.end(),l)-dic.begin();
        ll _r=lower_bound(dic.begin(),dic.end(),r)-dic.begin();
        return _Ique(_l,_r);
    }

    inline T get(ll i){
        ll _i=lower_bound(dic.begin(),dic.end(),i)-dic.begin();
        return node[_i+N];
    }

    inline T all(){
        return node[1];
    }

    inline int _upper(int l,ll x){//check(node[now],x)=1の最小のindex(l以上で)
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
        return inf;
    }

    inline int upper(ll l,ll x){
        ll _l=lower_bound(dic.begin(),dic.end(),l)-dic.begin();
        return _upper(_l,x);
    }


    inline int _lower(int r,ll x){//check(node[now],x)=1の最大のindex(r未満で)
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
        return -inf;
    }

    inline int lower(ll r,ll x){
        ll _r=lower_bound(dic.begin(),dic.end(),r)-dic.begin();
        return _lower(_r,x);
    }

    bool check(T node,ll x){
        return node.fi>x;
    }
};

void _solve(){
    ll h,w;
    cin>>H>>W>>h>>w>>N;
    map<ll,info> R;
    map<ll,vepll> C;
    R[0];R[H-h+1];
    C[0];C[W-w+1];
    vel r(N);
    vel c(N);
    rep(i,0,N)cin>>r[i]>>c[i];
    rep(i,0,N){
        R[max(0ll,r[i]-h)];
        R[min(r[i],H-h+1)];
        C[max(0ll,c[i]-w)].push_back({i,1});
        C[min(c[i],W-w+1)].push_back({i,-1});
    }
    ll last=0;
    for(auto it=R.begin();it!=R.end();it++){
        R[last].min_cnt=it->fi-last;
        R[last].min_val=0;
        R[last].sum=0;
        last=it->fi;
    }
    info id;
    compseg<info,Combine> st(R,Combine(),id);
    last=0;
    ll len=0;
    ll ans=0;
    for(auto it=C.begin();it!=C.end();it++){
        vepll v=it->se;
        for(auto[i,b]:v){
            ll id=max(0ll,r[i]-h);
            info x=st.get(id);
            x.min_val+=b;x.sum+=b;
            st.chan(id,x);
            id=min(r[i],H-h+1);
            x=st.get(id);
            x.min_val-=b;x.sum-=b;
            st.chan(id,x);
        }
        info res=st.all();
        cout<<it->fi<<" "<<res.min_val<<" "<<res.min_cnt<<" "<<res.sum<<endl;
        ans+=(it->fi-last)*len;
        if(res.min_val==0)len=res.min_cnt;
        else len=0;
        last=it->fi;
    }
    cout<<ans<<"\n";
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