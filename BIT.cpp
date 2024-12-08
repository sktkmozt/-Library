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

struct BIT{
    vel node; 
    ll n;
    BIT(vel &a){
        n=a.size()+2;
        node.assign(a.size()+2,0);
        rep(i,0,a.size()){
            ll ind=i+1;
            while(ind<a.size()+1){
                node.at(ind)+=a.at(i);
                ind=ind+(ind&(-ind));
            }
        }
    }
    ll sum(ll i,ll j){//[i,j)
        ll res=0;
        if(i!=0){
            while(i!=0){
                res-=node.at(i);
                i-=i&(-i);
            }
        }
        j++;
        while(j!=0){
            res+=node.at(j);
            j-=j&(-j);
        }
        return res;
    }
    void add(ll i,ll x){
        i++;
        while(i<n){
            node.at(i)+=x;
            i+=i&(-i);
        }
    }
};




int main(){
    cin>>N>>M>>Q;
    vvel a(Q);
    rep(i,0,Q){
        cin>>x;
        if(x==1){
            a.at(i).assign(4,1);
            rep(j,0,3) cin>>a.at(i).at(j+1);
        }else if(x==2){
            a.at(i).assign(3,2);
            rep(j,0,2) cin>>a.at(i).at(j+1);
        }else{
            a.at(i).assign(3,3);
            rep(j,0,2) cin>>a.at(i).at(j+1);
        }
    }
    vepll last(N+1,{-1,0});
    map<ll,vel> ma;
    vel ans(Q,1e18);
    vel dp(M,0);
    BIT bit(dp);
    rep(i,0,Q){
        if(a.at(i).at(0)==2){
            last.at(a.at(i).at(1))={i,a.at(i).at(2)};
        }else if(a.at(i).at(0)==3){
            ans.at(i)=last.at(a.at(i).at(1)).se;
            if(!ma.count(last.at(a.at(i).at(1)).fi)){
                ma[last.at(a.at(i).at(1)).fi]={i};
            }else{
                ma[last.at(a.at(i).at(1)).fi].push_back(i);
            }
        }
    }
    rep(i,0,Q){
        if(a.at(i).at(0)==1){
            bit.add(a.at(i).at(1)-1,a.at(i).at(3));
            bit.add(a.at(i).at(2),-a.at(i).at(3));
        }else if(a.at(i).at(0)==3){
            ans.at(i)+=bit.sum(0,a.at(i).at(2)-1);
        }
        if(ma.count(i)){
            rep(j,0,ma[i].size()){
                ans.at(ma[i].at(j))-=bit.sum(0,a.at(ma[i].at(j)).at(2)-1);
            }
        }
    }
    rep(i,0,ans.size()){
        if(ans.at(i)!=1e18) cout<<ans.at(i)<<endl;
    }
}