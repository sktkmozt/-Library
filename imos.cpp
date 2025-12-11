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
vector<int> dy={ 0, -1, 0, 1};

ll N,K,M,L,R,T,Q,H,W,i,j,k,l;
ll x,y,z;
string S,SS;
vel mod={998244353,1000000007,1000000009,1000000021,1000000033};//(1<<61)-1も素数
//ll p=998244353;
ll p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(a.begin(),a.end(),A.at(i))-a.begin();
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

    inline void add(int i,T x){//i番目をxに変える
        i+=N;
        node[i]+=x;
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

void acc(vel &a,ll l,ll r,ll plus){//[l,r]
    if(l>r)return ;
    a.at(l)+=plus;
    if(r+1<a.size())a.at(r+1)-=plus*(r-l+2);
    if(r+2<a.size())a.at(r+2)+=plus*(r-l+1);
}

void racc(vel &a,ll l,ll r,ll plus){//[l,r]
    if(l>r)return ;
    a.at(r)+=plus;
    if(l-1>=0)a.at(l-1)-=plus*(r-l+2);
    if(l-2>=0)a.at(l-2)+=plus*(r-l+1);
}

void imos(vel &a,ll l,ll r,ll plus){//[l,r]
    if(l>r)return ;
    a.at(l)+=plus;
    a.at(r+1)-=plus;
}

void do_acc(vel &a){
    rep(i,0,a.size()-1)a.at(i+1)+=a.at(i);
}

void do_racc(vel &a){
    rrep(i,a.size(),1)a.at(i-1)+=a.at(i);
}

int main(){
    cin>>N;
    vel a(N);
    rep(i,0,N)cin>>a.at(i);
    vel ra(N);
    rep(i,0,N)ra.at(a.at(i))=i;
    vel sum0(2*N,0),sum1(2*N,0);
    rep(i,0,N){
        ll l,r;
        if(i!=j)//このデバッグとてもいい
        if(i>=ra.at(i)){
            l=i-ra.at(i);
            r=l+N/2;
        }else{
            l=i-ra.at(i)+N;
            r=l+N/2;
        }
        acc(sum0,l+1,r,1);
        r=l;
        if(r-(N-1)/2>=0){
            l=r-(N-1)/2;
        }else{
            r+=N;
            l=r-(N-1)/2;
        }
        racc(sum1,l,r-1,1);
    }
    do_acc(sum0);do_acc(sum0);
    do_racc(sum1);do_racc(sum1);
    ll ans=inf;
    rep(i,0,N)ans=min(ans,sum0.at(i)+sum1.at(i)+sum0.at(i+N)+sum1.at(i+N));
    cout<<ans;
}