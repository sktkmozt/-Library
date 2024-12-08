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

struct ES{
    vel isprime,mobius,prime,minprime;
    //vvel primes;////////////////////////////////////////////////////////////
    ES(int N){
        isprime.assign(N+1,0);
        mobius.assign(N+1,1);
        minprime.assign(N+1,-1);
        //primes.assign(N+1,{});////300msぐらいかかるのであまり使わない方がいいかも
        rep(i,2,N+1){
            ll now=1;
            bool c=false;
            if(isprime.at(i)==0) c=true;
            while(now*i<N+1){
                if(c){
                    //primes.at(now*i).push_back(i);///////////////////////////
                    if(minprime.at(now*i)==-1){
                        minprime.at(now*i)=i;
                    }
                }
                isprime.at(now*i)++;
                now++;
            }
        }
        rep(i,0,N+1){
            if(isprime.at(i)!=1) isprime.at(i)=0;
            if(isprime.at(i)==1){
                prime.push_back(i);
            }
        }
        mobius.at(1)=1;
        rep(i,2,N+1){
            ll x=i;
            while(minprime.at(x)!=-1){
                if(x%(minprime.at(x)*minprime.at(x))==0){
                    mobius.at(i)=0;
                    break;
                }
                mobius.at(i)=-mobius.at(i);
                x/=minprime.at(x);
            }
        }
    }
};



int main(){
    cin>>N;
    ES es((ll)1e6);
}