#include <bits/stdc++.h>
using namespace std;
using Graph=vector<vector<int>>;
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
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)

vector<int> dx= { 1, 0, -1, 0 };
vector<int> dy={ 0, 1, 0, -1 };

vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll N, K, M, L, T, Q, H, W, i, j, l;
ll x, y, z;
unsigned long long q;
string S;
long double k;

ull gcd(ull a, ull b) {
    if (b==0) return a;
    else return gcd(b, a%b);
}

ll lcm(ll a,ll b){
    ll x=gcd(a,b);
    return x*(a/x)*(b/x);
}

pll f(pll x){//遅い定数倍で10倍だと思った方がいい
    ll a,b;
    a=x.fi;
    b=x.se;
    if(a<0){
        a*=-1;
        b*=-1;
    }
    if(a==0){
        return {0,1};
    }
    if(b==0){
        return {a/(abs(a)),0};
    }
    ll g=gcd(abs(a),abs(b));
    return {a/g,b/g};
}

vel euclid(ll x,ll y){
    tuple<ll,ll,ll> a={x,1,0},b={y,0,1};
    if(x<0){
        a={-x,-1,0};
    }
    if(y<0){
        b={-y,0,-1};
    }
    if(get<0>(a)<get<0>(b)) swap(a,b);
    while(get<0>(b)!=0){
        ll cnt=get<0>(a)/get<0>(b);
        a={get<0>(a)-cnt*get<0>(b),get<1>(a)-cnt*get<1>(b),get<2>(a)-cnt*get<2>(b)};
        swap(a,b);
    }////////gcd(x,y)  xの係数   yの係数
    vel res={get<0>(a),get<1>(a),get<2>(a)};
    return res;
}

ll euclidsolver(pll a,pll b){//a=(a_1,p_a) b=(b_1,p_b)でmod p_a*p_bでのやつ返す
    vel res=euclid(a.se,b.se);
    ll inf=a.se*b.se;
    ll ans=(res.at(2)+inf)%inf;ans*=b.se;ans%=inf;ans*=a.fi;ans%=inf;
    ll ANS=(res.at(1)+inf)%inf;ANS*=a.se;ANS%=inf;ANS*=b.fi;ANS%=inf;
    ans+=ANS;ans%=inf;
    return ans;
}