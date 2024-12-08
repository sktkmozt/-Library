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
Graph P(N);

vvel SCC(vvel &G){
    ll now=0;
    ll last=0;
    stack<pll> st;//dfs用
    stack<ll> s;
    vel sccid(N,-1);
    vel order(N,-1);//いきがけ
    vel seen(N,-1);
    vel lowlink(N,1e9);
    rep(i,0,N){
        if(seen.at(i)==-1){
            //seen.at(i)=0;
            s.push(i);
            st.push({i,0});
        }
        while(!st.empty()){
            pll x=st.top();
            st.pop();
            if(x.se==1){
                for(auto y:G.at(x.fi)){
                    if(sccid.at(y)!=-1) continue;
                    if(order.at(x.fi)<order.at(y)) lowlink.at(x.fi)=min(lowlink.at(y),lowlink.at(x.fi));
                    else{
                        lowlink.at(x.fi)=min(lowlink.at(x.fi),order.at(y));
                    }
                }
                if(lowlink.at(x.fi)==order.at(x.fi)){
                    while(1){
                        z=s.top();
                        sccid.at(z)=last;
                        s.pop();
                        order.at(z)=1e9;
                        if(z==x.fi)break;
                    }
                    last++;
                }
            }else{
                if(seen.at(x.fi)==0) continue;
                seen.at(x.fi)=0;
                s.push(x.fi);
                st.push({x.fi,1});
                order.at(x.fi)=now;
                lowlink.at(x.fi)=now;
                now++;
                for(auto y:G.at(x.fi)){
                    st.push({y,0});
                }
            }
        }
    }
    ll size=0;
    rep(i,0,N){
        size=max(size,sccid.at(i));
    }
    vvel ans(size+1);
    rep(i,0,N){
        //sccid.at(i)==-1の可能性があるみたいなことを昔の自分がやっていて謎
        ans.at(sccid.at(i)).push_back(i);
    }
    return ans;
}

int main() {
    cin>>N>>M;
    Graph G(N);
    rep(i,0,M){
        cin>>x>>y;
        x--;
        y--;
        G.at(x).push_back(y);
    }
    ll now=0;
    ll last=0;
    stack<pll> st;//dfs用
    stack<ll> s;
    vel sccid(N,-1);
    vel order(N,-1);//いきがけ
    vel seen(N,-1);
    vel lowlink(N,1e9);
    rep(i,0,N){
        if(seen.at(i)==-1){
            //seen.at(i)=0;
            s.push(i);
            st.push({i,0});
        }
        while(!st.empty()){
            pll x=st.top();
            st.pop();
            if(x.se==1){
                for(auto y:G.at(x.fi)){
                    if(sccid.at(y)!=-1) continue;
                    if(order.at(x.fi)<order.at(y)) lowlink.at(x.fi)=min(lowlink.at(y),lowlink.at(x.fi));
                    else{
                        lowlink.at(x.fi)=min(lowlink.at(x.fi),order.at(y));
                    }
                }
                if(lowlink.at(x.fi)==order.at(x.fi)){
                    while(1){
                        z=s.top();
                        sccid.at(z)=last;
                        s.pop();
                        order.at(z)=1e9;
                        if(z==x.fi)break;
                    }
                    last++;
                }
            }else{
                if(seen.at(x.fi)==0) continue;
                seen.at(x.fi)=0;
                s.push(x.fi);
                st.push({x.fi,1});
                order.at(x.fi)=now;
                lowlink.at(x.fi)=now;
                now++;
                for(auto y:G.at(x.fi)){
                    st.push({y,0});
                }
            }
        }
    }
    vvel ans(N);
    rep(i,0,N){
        //sccid.at(i)==-1の可能性があるみたいなことを昔の自分がやっていて謎
        ans.at(sccid.at(i)).push_back(i);
    }
    ll cnt=0;
    rep(i,0,N){
        if(ans.at(i).size()==1&&G.at(i).at(0)!=i){
            cnt++;
            //cout<<i<<" ";
        }
    }
    //ansは同値類な奴がおなじindexのvelに入ってるやつを返してる
}