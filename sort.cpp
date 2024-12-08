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

ll N, K, M, L, R, T, Q, H, W, i, j, l;
ll x, y, z;
unsigned long long q;
string S;
long double k;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};
ll inf=998244353;
// inf=1e9+7;
// LLONG_MAX

/*座圧
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
*/

/*
g++ a.cpp -std=c++20
*/




int main(){
    cin>>N>>K;
    vepll a(N);
    rep(i,0,N)cin>>a.at(i).fi>>a.at(i).se;
    sort(a.begin(),a.end(),[&](pll x,pll y){
        return x.fi*(y.fi+y.se)+x.se<y.fi*(x.fi+x.se)+y.se;
    });
    vvel dp(N,vel(K+1,0));
    dp.at(0).at(0)=1;
    dp.at(0).at(1)=a.at(0).fi+a.at(0).se;
    rep(i,0,N) dp.at(i).at(0)=1;
    rep(i,1,N){
        rep(j,0,K){
            dp.at(i).at(j+1)=max(dp.at(i-1).at(j+1),a.at(i).fi*dp.at(i-1).at(j)+a.at(i).se);
        }
    }
    cout<<dp.at(N-1).at(K);
}