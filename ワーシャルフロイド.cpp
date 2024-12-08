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
//vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};
ll inf=998244353;
// inf=1e9+7;
// LLONG_MAX



int main(){
    cin>>N;
    vel a(N);
    rep(i,0,N) cin>>a.at(i);
    vvel dist(N,vel(N,1e18));
    vvel dp(N,vel(N,0));
    rep(i,0,N){
        cin>>S;
        rep(j,0,N){
            if(S.at(j)=='Y'){
                dist.at(i).at(j)=1;
                dp.at(i).at(j)=a.at(i)+a.at(j);
            }
        }
    }
    rep(i,0,N){
        rep(j,0,N){
            rep(k,0,N){
                if(dist.at(j).at(k)==dist.at(j).at(i)+dist.at(i).at(k)){
                    dp.at(j).at(k)=max(dp.at(j).at(k),dp.at(j).at(i)+dp.at(i).at(k)-a.at(i));
                }else if(dist.at(j).at(k)>dist.at(j).at(i)+dist.at(i).at(k)){
                    dist.at(j).at(k)=dist.at(j).at(i)+dist.at(i).at(k);
                    dp.at(j).at(k)=dp.at(j).at(i)+dp.at(i).at(k)-a.at(i);
                }
            }
        }
    }
    cin>>Q;
    vepll ans;
    rep(q,0,Q){
        cin>>x>>y;
        x--;
        y--;
        if(dist.at(x).at(y)==1e18){
            ans.push_back({1e18,1e18});
            continue;
        }
        ans.push_back({dist.at(x).at(y),dp.at(x).at(y)});
    }
    rep(i,0,Q){
        if(ans.at(i).fi==1e18) cout<<"Impossible"<<endl;
        else cout<<ans.at(i).fi<<" "<<ans.at(i).se<<endl;
    }
}