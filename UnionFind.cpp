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
//ll inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(a.begin(),a.end(),A.at(i))-a.begin();
    swap(A,a);
*/

struct UF{
    vel par;
    vel siz;
    vel sum;
    UF(int N){
        par.assign(N,0);
        siz.assign(N,0);
        sum.assign(N,0);
        rep(i,0,N){
            siz.at(i)=1;
            par.at(i)=i;
        }
    }
    int root(int x){
        if(par.at(x)==x)return x;
        par.at(x)=root(par.at(x));
        return par.at(x);
    }
    void unite(int x,int y){
        int rx=root(x);
        int ry=root(y);
        if(rx==ry) return ;
        siz.at(min(rx,ry))+=siz.at(max(rx,ry));
        par.at(rx)=min(rx,ry);
        par.at(ry)=min(rx,ry);
        sum.at(min(rx,ry))=sum.at(rx)+sum.at(ry);
    }
    void chan(vel &a){
        rep(i,0,N)sum.at(i)=a.at(i);
    }
    ll get(ll x){
        return sum.at(root(x));
    }
    int size(int x){
        return siz.at(root(x));
    }
    bool same(int x,int y){
        return root(x)==root(y);
    }
};

int main() {
    cin>>N>>Q;
    UF tree(N);
    deque<bool> d; 
    rep(i,0,Q){
        ll a,b,c;
        cin>>a>>b>>c;
        if(a==0){
            tree.unite(b,c);
        }
        else d.push_back(tree.same(b,c));
    }
    while(!d.empty()){
        if(d.front()) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
        d.pop_front();
    }
}