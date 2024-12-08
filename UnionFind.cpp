#include <bits/stdc++.h>
using namespace std;
using Graph=vector<vector<int>>;
#define rep(i,a,b) for(int i=a;i<b;i++)
#define ll long long
#include <vector>

long long N, K, M, L, Q, a, b, c, i, j;
string S;

struct UF{
    vector<int> par;
    vector<int> siz;
    //vector<int> rank;
    UF(int N){
        par.assign(N,0);
        siz.assign(N,0);
        rep(i,0,N){
            siz.at(i)=1;
            par.at(i)=i;
        }
    }
    int root(int x){
        if(par.at(x)==x)return x;
        par.at(x)=root(par.at(x));
        return par.at(x);
    }
    void unite(int x,int y){
        int rx=root(x);
        int ry=root(y);
        if(rx==ry) return ;
        siz.at(min(rx,ry))+=siz.at(max(rx,ry));
        par.at(rx)=min(rx,ry);
        par.at(ry)=min(rx,ry);
    }
    int size(int x){
        return siz.at(root(x));
    }
    bool same(int x,int y){
        return root(x)==root(y);
    }
};

int main() {
    cin>>N>>Q;
    UF tree(N);
    deque<bool> d; 
    rep(i,0,Q){
        cin>>a>>b>>c;
        if(a==0){
            tree.unite(b,c);
        }
        else d.push_back(tree.same(b,c));
    }
    while(!d.empty()){
        if(d.front()) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
        d.pop_front();
    }
}