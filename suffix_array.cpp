#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define bl __int128_t
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define vem vector<mint>
#define vvem vector<vector<mint>>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define vvepll vector<vepll>
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, -1, 0, 1};

ll N,K,M,L,R,T,Q,H,W,i,j,k,l;
ll x,y,z;
string S,SS;
vel mod={998244353,1000000007,1000000009,1000000021,1000000033};//(1<<61)-1も素数
ll p=998244353;
// p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(a.begin(),a.end(),A.at(i))-a.begin();
    swap(A,a);
*/

struct SA{
    ll N;
    vel sa;
    vel rsa;
    string S;
    SA(string &s){
        S=s;
        N=S.size();
        sa.assign(N+1,0);
        rsa.assign(N+1,0);
        {
            vel c_sum(257,0);
            rep(i,0,N){
                c_sum.at(S.at(i)+1)++;
            }
            c_sum.at(0)++;
            rep(i,0,256) c_sum.at(i+1)+=c_sum.at(i);
            vel c_cnt(257,0);
            char c=0;
            rep(i,0,N){
                sa.at(c_sum.at(S.at(i))+c_cnt.at(S.at(i)))=i;
                c_cnt.at(S.at(i))++;
            }
            sa.at(0)=N;
        }
        vel c(N+1);
        {
            pair<ll,char> val={1,S.at(sa.at(1))};
            rep(i,1,N+1){
                if(val.se!=S.at(sa.at(i))){
                    val.fi++;
                    val.se=S.at(sa.at(i));
                }
                c.at(sa.at(i))=val.fi;
            }
            c.at(N)=0;
        }
        ll now=1;
        while(now<N+1){
            vel nindex(N+1),nc(N+1);
            rep(i,0,N+1){
                nindex.at(i)=sa.at(i)-now;
                if(nindex.at(i)<0)nindex.at(i)+=N+1;
            }
            ll base=c.size();
            vel c_sum(base,0);
            rep(i,0,N+1){
                c_sum.at(c.at(i))++;
            }
            rep(i,1,base){
                c_sum.at(i)+=c_sum.at(i-1);
            }
            vel c_cnt(base,0);
            rep(i,0,N+1){
                ll ni=nindex.at(i);
                sa.at((c.at(ni)==0?0:c_sum.at(c.at(ni)-1))+c_cnt.at(c.at(ni)))=ni;
                c_cnt.at(c.at(ni))++;
            }
            {
                pll val={0,c.at(sa.at(0))*base+c.at(now-1)};
                rep(i,0,N+1){
                    ll ni=sa.at(i)+now;
                    if(ni>=N+1) ni-=N+1;
                    if(val.se!=c.at(sa.at(i))*base+c.at(ni)){
                        val.fi++;
                        val.se=c.at(sa.at(i))*base+c.at(ni);
                    }
                    nc.at(sa.at(i))=val.fi;
                }
            }
            swap(c,nc);
            now*=2;
        }
        rep(i,1,N+1)sa.at(i)++;
        rep(i,1,N+1)rsa.at(sa.at(i))=i;
    }

    vel LCP(){
        vel lcp(N+1,0);//saで昇順に並べた後の隣接の距離
        ll h=0;
        rep(i,1,N+1){//stringを前から見ていくとbana/ban->ana/anの存在からh-1以上にはなる
            ll r=rsa.at(i);
            if(r==1){
                lcp.at(r)=0;
            }else{
                ll j=sa.at(r-1);
                while(max(i,j)+h-1<S.size()){
                    if(S.at(j+h-1)==S.at(i+h-1))h++;
                    else break;
                }
                lcp.at(r)=h;
            }
            h=max(h-1,0ll);
        }
        return lcp;
    }
};

int main(){
    cin>>N>>S;
    SA s(S);
    vel lcp=s.LCP();
    vel rsa=s.rsa;
    vel sa=s.sa;
    vel ans(N,0);
    priority_queue<ll> pq;
    map<ll,ll> ma;
    ll sum=0;
    rep(i,2,N+1){
        while(ma.upper_bound(lcp.at(i))!=ma.end()){
            auto it=ma.upper_bound(lcp.at(i));
            ma[lcp.at(i)]+=it->se;
            sum-=it->se*(it->fi-lcp.at(i));
            ma.erase(it->fi);
        }
        sum+=lcp.at(i);
        ma[lcp.at(i)]++;
        ans.at(sa.at(i)-1)+=sum;
    }
    ma.clear();
    sum=0;
    rrep(i,N+1,2){
        while(ma.upper_bound(lcp.at(i))!=ma.end()){
            auto it=ma.upper_bound(lcp.at(i));
            ma[lcp.at(i)]+=it->se;
            sum-=it->se*(it->fi-lcp.at(i));
            ma.erase(it->fi);
        }
        sum+=lcp.at(i);
        ma[lcp.at(i)]++;
        ans.at(sa.at(i-1)-1)+=sum;
    }
    rep(i,0,ans.size())cout<<ans.at(i)+N-i<<endl;
}