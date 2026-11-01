#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<ll>
#define vvel vector<vector<ll>>
#define vvvel vector<vvel>
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
//#define mint Mint<1000000007>
#define cleout(i) cout<<fixed<<setprecision(i)
#define ppcnt __builtin_popcount
template<class T>using PQ=priority_queue<T,vector<T>,greater<T>>;
//               上  右 下 左
vector<int> dx={ -1, 0, 1, 0 };
vector<int> dy={ 0, 1, 0, -1 };


vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll N, K, M, L, R, T, Q, H, W, i, j, l, r;
ll x, y, z;
unsigned long long q;
string S;
long double k;
vel mod={998244353,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21,(ll)1e9+33};
ll p=998244353;
//ll p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
//ll inf=LLONG_MAX;

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

//[x^M]1/(1-x)^N=comb(N-1+M,M)

vel make_kmp(string &S){
    vel kmp(S.size()+1,0);//S[0:i)での接頭辞と接尾辞のmax(帰納法なので図を書いてから遷移考えたほうがいい)
    kmp[0]=-1;
    ll last=-1;
    rep(i,0,S.size()){
        while(last>=0&&S[i]!=S[last]){
            last=kmp[last];
        }
        last++;
        kmp[i+1]=last;
    }
    return kmp;
}

void _solve(){
    cin>>S;
    vel kmp=make_kmp(S);
    vvel ans(S.size()+1,vel(26,0));//ans[i][j]:[0,i)にjをつけ足したときの答え
    rep(i,1,S.size()+1){
        rep(j,0,26){
            ll Id=kmp[i];//ll Id=ans[i-1][S[i-1]-'a'];とすることでkmp配列はいらない
            if(S[Id]-'a'==j){
                ans[i][j]=Id+1;
            }else{
                Id=ans[Id][j];
                ans[i][j]=Id;
            }
        }
    }
    cin>>Q;
    vel v(26,0);
    rep(q,0,Q){
        string t;
        cin>>t;
        rep(i,0,t.size()){
            ans.push_back(v);
            S+=t[i];
            rep(j,0,26){
                ll Id=ans[S.size()-1][t[i]-'a'];
                if(S[Id]-'a'!=j){
                    ans.back()[j]=ans[Id][j];
                }else{
                    ans.back()[j]=Id+1;
                }
            }
        }
        rep(i,S.size()-t.size(),S.size()){
            cout<<ans[i][S[i]-'a']<<" ";
        }
        cout<<"\n";
        rep(i,0,t.size()){
            S.pop_back();
            ans.pop_back();
        }
    }
}


int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);


    ll _;
    
    bool multitest=0;

    if(multitest)cin>>_;
    else _=1;
    rep(__,0,_){
        _solve();
    }
}
//https://codeforces.com/contest/1721/submission/361713525