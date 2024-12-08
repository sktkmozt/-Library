#include <bits/stdc++.h>
using namespace std;
using Graph=vector<vector<int>>;
#define rep(i,a,b) for(int i=a;i<b;i++)
#define ll long long
#define ull unsigned long long
#define f cout<<"a"
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
#include <vector>

ll N, K, M, L, T, Q, a, b, c, j;
unsigned long long i;
string S;
long double k;
int main() {
    cin>>N;
    vector<vector<int>> A(N,vector<int>(N));
    rep(i,0,N){
        rep(j,0,N){
            cin>>A.at(i).at(j);
        }
    }
    vector<int> v(N);
    rep(i,0,N){
        v.at(i)=i;
    }
    cin>>M;
    vector<pair<int,int>> a(M);
    rep(i,0,M){
        cin>>a.at(i).first>>a.at(i).second;
        a.at(i).first--;
        a.at(i).second--;
    } 
    int ans=1000000;
    do{
        int sum=0;
        bool che=true;
        rep(i,0,N){
            sum+=A.at(v.at(i)).at(i);
            //cout<<v.at(i);
            if(i<N-1){
                rep(j,0,M){
                if((a.at(j).first==v.at(i)&&a.at(j).second==v.at(i+1))||(a.at(j).first==v.at(i+1)&&a.at(j).second==v.at(i))) che=false;
                }
            }
        }
        if(che){
        ans=min(ans,sum);
        //cout<<"sum="<<sum;
        }
       //rep(i,0,N) cout<<v.at(i);
       //cout<<endl;
    }while(next_permutation(v.begin(),v.end()));
    if(ans==1000000)cout<<"-1";
    else cout<<ans;
}