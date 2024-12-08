#include <bits/stdc++.h>
using namespace std;
using Graph=vector<vector<int>>;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define veb vector<bool>
#define vveb vector<vector<bool>>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
#include <vector>

vector<int> dx= { 1, 0, -1, 0 };
vector<int> dy={ 0, 1, 0, -1 };

vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll N, K, M, L, T, Q, H, W, i, j, l;
ll x, y, z;
unsigned long long q;
string S;
long double k;

ll inf=998244353;

ll beki(ll a,ll b,ll inf){
    ll ans=1;
    ll now=a%inf;
    rep(i,0,60){
        if(b&(1ll<<i)){
            ans*=now;
            ans%=inf;
        }
        now*=now;
        now%=inf;
    }
    return ans;
}

int main() {
}