#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define all(a,i,j) a.begin()+i,a.begin()+j
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
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

ll N, K, M, L, R, Q, H, W, i, j, k, l;
ll x, y, z;
string S,T;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};//(1<<61)-1も素数
ll p=998244353;
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
// LLONG_MAX

/*座圧
    vel A=a;
    sort(all(a,0,a.size()));
    a.erase(unique(all(a,0,a.size())),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(all(a,0,a.size()),A.at(i))-a.begin();
    swap(A,a);
*/

vel SA(string &S){
    ll N=S.size();
    vel index(N+1,0);
    {
        vel c_sum(257,0);
        rep(i,0,N){
            c_sum.at(S.at(i)+1)++;
        }
        c_sum.at(0)++;
        rep(i,0,256) c_sum.at(i+1)+=c_sum.at(i);
        vel c_cnt(257,0);
        char c=0;
        rep(i,0,N){
            index.at(c_sum.at(S.at(i))+c_cnt.at(S.at(i)))=i;
            c_cnt.at(S.at(i))++;
        }
        index.at(0)=N;
    }
    vel c(N+1);
    {
        pair<ll,char> val={1,S.at(index.at(1))};
        rep(i,1,N+1){
            if(val.se!=S.at(index.at(i))){
                val.fi++;
                val.se=S.at(index.at(i));
            }
            c.at(index.at(i))=val.fi;
        }
        c.at(N)=0;
    }
    ll now=1;
    while(now<N+1){
        vel nindex(N+1),nc(N+1);
        rep(i,0,N+1){
            nindex.at(i)=index.at(i)-now;
            if(nindex.at(i)<0)nindex.at(i)+=N+1;
        }
        ll base=c.size();
        vel c_sum(base,0);
        rep(i,0,N+1){
            c_sum.at(c.at(i))++;
        }
        rep(i,1,base){
            c_sum.at(i)+=c_sum.at(i-1);
        }
        vel c_cnt(base,0);
        rep(i,0,N+1){
            ll ni=nindex.at(i);
            index.at((c.at(ni)==0?0:c_sum.at(c.at(ni)-1))+c_cnt.at(c.at(ni)))=ni;
            c_cnt.at(c.at(ni))++;
        }
        {
            pll val={0,c.at(index.at(0))*base+c.at(now-1)};
            rep(i,0,N+1){
                ll ni=index.at(i)+now;
                if(ni>=N+1) ni-=N+1;
                if(val.se!=c.at(index.at(i))*base+c.at(ni)){
                    val.fi++;
                    val.se=c.at(index.at(i))*base+c.at(ni);
                }
                nc.at(index.at(i))=val.fi;
            }
        }
        swap(c,nc);
        now*=2;
    }
    return index;
}

int main(){
    cin>>N>>S>>T;
    char a='a';
    char z='z';
    a--;
    z++;
    string ans=S+S+a+T+T+z;
    //string ans=S;
    vel sa=SA(ans);
    ll plus=N;
    ll res=0;
    rep(i,0,sa.size()){
        if(0<=sa.at(i)&&sa.at(i)<N){
            res+=plus;
        }
        if(2*N<sa.at(i)&&sa.at(i)<=3*N) plus--;
    }
    cout<<res;
}
/*
g++ a.cpp -std=c++20
*/