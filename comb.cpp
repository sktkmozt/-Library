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

//座圧
//sort(a.begin(),a.end());
//a.erase(unique(a.begin(),a.end()),a.end());

ll inv(ll a,ll inf){
    bitset<60> s(inf-2);
    vel b(60);
    b.at(0)=a;
    b.at(0)%=inf;
    rep(i,1,60){
        b.at(i)=b.at(i-1)*b.at(i-1);
        b.at(i)%=inf;
    }
    ll ans=1;
    rep(i,0,60){
        if(s.test(i)){
            ans*=b.at(i);
            ans%=inf;
        }
    }
    return ans;
}

struct CB{
    vel n,r;
    ll inf;
    CB(int N,ll INF){//N以下のものをmod INFで返す
        inf=INF;
        n.assign(N+1,1);
        r.assign(N+1,1);
        rep(i,2,N+1){
            n.at(i)=n.at(i-1)*i;
            n.at(i)%=inf;
        }
        rep(i,1,N+1) r.at(i)=inv(n.at(i),inf);
        n.at(0)=1;
        r.at(0)=1;
    }
    ll comb(ll N,ll R){//NCR
        ll res=n.at(N);
        res*=r.at(N-R);
        res%=inf;
        res*=r.at(R);
        res%=inf;
        return res;
    }
    ll P(ll N,ll R){//NPR
        ll res=n.at(N);
        res*=r.at(N-R);
        res%=inf;
        return res;
    }
};



int main(){
    inf=1e9+7;
    cin>>N>>M;
    CB cb(M,inf);
    ll ans=0;
    rep(i,0,N+1){
        if(i%2==0) ans+=(cb.P(M-i,N-i)*cb.comb(N,i))%inf;
        else{
            ans+=inf-(cb.P(M-i,N-i)*cb.comb(N,i))%inf;
        }
        ans%=inf;
    }
    ans*=cb.P(M,N);
    cout<<ans%inf;
}