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
#define vvvel vector<vvel>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
#define cleout(i) cout<<fixed<<setprecision(i)
template<class T>using pq=priority_queue<T,vector<T>,greater<T>>;
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
// LLONG_MAX

/*座圧
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
*/

/*
g++ a.cpp -std=c++17
*/

struct Combine {
    inline vel operator()(vel L,vel R){
        return {max(L[0],L[2]+R[0]),max(R[1],L[1]+R[2]),L[2]+R[2],max(max(L[3],R[3]),L[1]+R[0])};//l,r,sum,max
    }
};

template<typename T,typename Combine>
struct xor_segment_tree{
    int N;
    vector<vector<T>> node;
    Combine combine;
    T id;

    xor_segment_tree(vector<T> &A,Combine com,T ident):combine(com),id(ident){
        int n=A.size();
        N=1;
        while(N<n)N*=2;
        node.resize(2*N-1);
        rep(i,0,N){
            if(i<n)node[N-1+i].push_back(A[i]);
            else node[N-1+i].push_back(id);
        }
        // 下から順にマージしてテーブルを構築
        rrep(i,N-1,0){
            int size=node[2*i+1].size();
            node[i].reserve(size*2);

            // 前半：XORのその桁のビットが0の場合 (左+右)
            rep(j,0,size){
                node[i].push_back(combine(node[2*i+1][j],node[2*i+2][j]));
            }
            // 後半：XORのその桁のビットが1の場合 (右+左)
            rep(j,0,size){
                node[i].push_back(combine(node[2*i+2][j],node[2*i+1][j]));
            }
        }
    }
    T range_fold(int L,int R,int x,int i,int l,int r){
        if(r<=L||R<=l){
            return id;
        }else if(L<=l&&r<=R){
            return node[i][x];
        }else{
            int p=(r-l)/2;
            int m=(l+r)/2;
            if((x&p)==0){
                T resL=range_fold(L,R,x,i*2+1,l,m);
                T resR=range_fold(L,R,x,i*2+2,m,r);
                return combine(resL,resR);
            }else{
                T resL=id;
                if(R>=m){
                    resL=range_fold(max(L,m)-p,R-p,x^p,i*2+1,l,m);
                }
                T resR=id;
                if(L<m){
                    resR=range_fold(L+p,min(R,m)+p,x^p,i*2+2,m,r);
                }
                return combine(resR,resL);
            }
        }
    }
    T range_fold(int L,int R,int x){
        return range_fold(L,R,x,0,0,N);
    }
};

int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);


    cin>>N;
    vvel dp(1ll<<N);
    rep(i,0,(1ll<<N)){
        cin>>x;
        dp[i]={max(0ll,x),max(0ll,x),x,max(0ll,x)};
    }
    xor_segment_tree<vel,Combine> st(dp,Combine(),(vel){0,0,0,0});
    cin>>Q;
    vel ans;
    int X=0;
    rep(q,0,Q){
        cin>>x;
        X^=(1<<x);
        ans.push_back(st.range_fold(0,(1ll<<N),X)[3]);
    }
    rep(i,0,ans.size())cout<<ans[i]<<"\n";
}
//https://codeforces.com/contest/1716/problem/E