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

//座圧
//sort(a.begin(),a.end());
//a.erase(unique(a.begin(),a.end()),a.end());

struct hoge{
    vel next;//次のindexを持つやつ
    vel check;//これは何？
    ll cnt;//この頂点を何回通ったか
    ll deep;//個の頂点の深さ
    hoge(ll dp,ll var){
        next.assign(var,-1);
        deep=dp;
        cnt=0;
    }
};


struct trie{
    vector<hoge> node;
    char base='a';
    trie(ll var){//この頂点の子供の数
        hoge x(0,var);
        node.push_back(x);
    }
    void insert(string &S,ll num){
        ll now=0;
        rep(i,0,S.size()){
            node.at(now).cnt++;
            if(node.at(now).next.at(S.at(i)-'a')==-1){
                hoge x(i+1,26);
                node.at(now).next.at(S.at(i)-'a')=node.size();
                node.push_back(x);
            }
            now=node.at(now).next.at(S.at(i)-'a');
            if(i==S.size()-1){
                node.at(now).check.push_back(num);
            }
        }
        node.at(now).cnt++;
    }
};

void solve(trie &tree,ll now,ll &ans){
    if(now!=0){
        ll x=tree.node.at(now).cnt;
        //cout<<now<<" "<<x<<endl;
        ans+=((x-1)*x)/2;
    }
    rep(i,0,26){
        if(tree.node.at(now).next.at(i)!=-1){
            solve(tree,tree.node.at(now).next.at(i),ans);
        }
    }
}

int main(){
    cin>>N;
    trie tree(26);
    rep(i,0,N){
        cin>>S;
        tree.insert(S,i);
    }
    ll ans=0;
    solve(tree,0,ans);
    cout<<ans;
}