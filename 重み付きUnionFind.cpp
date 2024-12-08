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
// inf=1e9+7;
// LLONG_MAX


struct UF{
    vector<int> par;
    vel difwei;//rootとのdif
    UF(int N){
        par.resize(N);
        difwei.resize(N);
        rep(i,0,N){
            par.at(i)=i;
            difwei.at(i)=0;
        }
    }
    int root(int x){
        if(par.at(x)==x)return x;
        int r=root(par.at(x));
        difwei.at(x)+=difwei.at(par.at(x));
        par.at(x)=r;
        return root(par.at(x));
    }
    void unite(int x,int y,ll w){//yの親をxにする(sameなときにやるとバグる)
        int rx,ry;
        rx=root(x);
        ry=root(y);
        w+=difwei.at(x);
        w-=difwei.at(y);
        difwei.at(ry)=w;
        par.at(ry)=rx;
    }
    ll dif(int x,int y){//yからxまでの距離(sameでないときに気を付けよう)
        int rx,ry;
        rx=root(x);
        ry=root(y);
        return difwei.at(y)-difwei.at(x);
    }
    bool same(int x,int y){
        return root(x)==root(y);
    }
};

int main(){
    cin>>N>>Q;
    vvel a(Q,vel(3));
    rep(i,0,Q){
        rep(j,0,3) cin>>a.at(i).at(j);
    }
    set<ll> se;
    UF tree(N);
    rep(i,0,Q){
        x=a.at(i).at(0);
        y=a.at(i).at(1);
        z=a.at(i).at(2);
        x--;
        y--;
        if(tree.same(x,y)){
            ll d=tree.dif(x,y);
            if(d==z){
                se.insert(i);
                tree.unite(x,y,z);
            }
        }else{
            se.insert(i);
            tree.unite(x,y,z);
        }
    }
    while(!se.empty()){
        cout<<*se.begin()+1<<" ";
        se.erase(se.begin());
    }
}