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
#define pll pair<ll,ll>
#define vepll vector<pll>
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

ll N, K, M, L, R, Q, H, W, i, j, k, l;
ll x, y, z;
string S,T;
vel mod={998244353,897581057,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21};//(1<<61)-1も素数
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

struct UF{
    vector<int> par;
    vector<int> siz;
    //vector<int> rank;
    UF(int N){
        par.assign(N,0);
        siz.assign(N,0);
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
    }
    int size(int x){
        return siz.at(root(x));
    }
    bool same(int x,int y){
        return root(x)==root(y);
    }
};



int main(){
    cin>>N>>M>>K;
    vvel a(M,vel(3));
    rep(i,0,M){
        rep(j,0,3) cin>>a.at(i).at(2-j);
    }
    sort(all(a,0,a.size()));
    UF tree(N);
    vector<vepll> G(N);
    vel a0(N,0);
    vel a1(N,0);
    rep(i,0,K){
        cin>>x;
        x--;
        a0.at(x)++;
    }
    rep(i,0,K){
        cin>>x;
        x--;
        a1.at(x)++;
    }
    ll ans=0;
    rep(i,0,M){
        pll now={a.at(i).at(1)-1,a.at(i).at(2)-1};
        //cout<<now.fi<<" "<<now.se<<endl;
        if(tree.same(now.fi,now.se)) continue;
        x=tree.root(now.fi);
        y=tree.root(now.se);
        tree.unite(x,y);
        if(x<y){
            a0.at(x)+=a0.at(y);
            a1.at(x)+=a1.at(y);
        }else{
            a0.at(y)+=a0.at(x);
            a1.at(y)+=a1.at(x);
        }
        //cout<<a0.at(min(x,y))<<" "<<a1.at(min(x,y))<<endl;
        ans+=min(a0.at(min(x,y)),a1.at(min(x,y)))*a.at(i).at(0);
        ll z=min(a0.at(min(x,y)),a1.at(min(x,y)));
        a0.at(min(x,y))-=z;
        a1.at(min(x,y))-=z;
        //cout<<a0.at(min(x,y))<<" "<<a1.at(min(x,y))<<endl;
        //cout<<endl;
    }
    cout<<ans;

}


/*
g++ a.cpp -std=c++20
*/