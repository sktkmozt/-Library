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
vector<int> dy={ 0, 1, 0, -1};

ll N,K,M,L,R,T,Q,H,W,i,j,k,l;
ll x,y,z;
string S,SS;
vel mod={998244353,1000000007,1000000009,1000000021,1000000033};//(1<<61)-1も素数
//ll p=998244353;
ll p=1000000007;
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
    vector<int> sa;
    vector<int> rsa;
    string S;
    SA(string &s){
        S=s;
        N=S.size();
        sa.resize(N+1,0);//i->i番目にS[i~N]が小さいindexを返す(1-index)
        rsa.resize(N+1,0);//i->S[i~N]の順位を返す(1-index)
        {
            vector<int> c_sum(257,0);
            rep(i,0,N){
                c_sum[S.at(i)+1]++;
            }
            c_sum[0]++;
            rep(i,0,256) c_sum[i+1]+=c_sum[i];
            vector<int> c_cnt(257,0);
            char c=0;
            rep(i,0,N){
                sa[c_sum[S.at(i)]+c_cnt[S.at(i)]]=i;
                c_cnt[S.at(i)]++;
            }
            sa[0]=N;
        }
        vector<int> c(N+1);
        {
            pair<int,char> val={1,S[sa.at(1)]};
            rep(i,1,N+1){
                if(val.se!=S.at(sa[i])){
                    val.fi++;
                    val.se=S.at(sa[i]);
                }
                c[sa[i]]=val.fi;
            }
            c[N]=0;
        }
        ll now=1;
        vector<int> nindex(N+1),nc(N+1);
        while(now<N+1){
            rep(i,0,N+1){
                nindex[i]=sa[i]-now;
                if(nindex[i]<0)nindex[i]+=N+1;
            }
            ll base=c.size();
            vector<int> c_sum(base,0);
            rep(i,0,N+1){
                c_sum[c.at(i)]++;
            }
            rep(i,1,base){
                c_sum[i]+=c_sum[i-1];
            }
            vector<int> c_cnt(base,0);
            rep(i,0,N+1){
                ll ni=nindex[i];
                sa[(c[ni]==0?0:c_sum[c[ni]-1])+c_cnt[c[ni]]]=ni;
                c_cnt[c[ni]]++;
            }
            {
                pll val={0,c[sa[0]]*base+c[now-1]};
                rep(i,0,N+1){
                    ll ni=sa[i]+now;
                    if(ni>=N+1) ni-=N+1;
                    if(val.se!=c[sa[i]]*base+c[ni]){
                        val.fi++;
                        val.se=c[sa[i]]*base+c[ni];
                    }
                    nc[sa[i]]=val.fi;
                }
            }
            swap(c,nc);
            now*=2;
        }
        rep(i,1,N+1)sa[i]++;
        rep(i,1,N+1)rsa[sa[i]]=i;
    }

    vel LCP(){
        vel lcp(N+1,0);//saで昇順に並べた後のS[i~N]とその隣のS[j~N]の距離(1-index)
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
    string T;
    cin>>S>>T;
    ll n=S.size();
    string t=S;
    N=S.size();
    M=T.size();
    if(N<M){
        string s((M/N+1)*N,'a');
        rep(i,0,s.size())s.at(i)=S.at(i%N);
        swap(s,S);
    }
    string s=S+t+"`"+T+"{";
    SA sa(s);
    vel lcp=sa.LCP();
    ll id=sa.rsa.at(t.size()+S.size()+2);
    vel v;
    rrep(i,id+1,2){
        if(lcp.at(i)<M)break;
        if(sa.sa.at(i-1)<=n&&sa.sa.at(i-1)>0)v.push_back(sa.sa.at(i-1));
    }
    //rep(i,0,v.size())cout<<i<<" "<<v.at(i)<<endl;
    if(v.size()==0){
        cout<<0;
        return 0;
    }
    //rep(i,0,v.size())cout<<v.at(i)<<endl;
    vel indeg(n,0);
    vel next(n,-1);
    rep(i,0,v.size()){
        next.at(v.at(i)-1)=(v.at(i)+T.size()-1)%n;
        indeg.at((v.at(i)+T.size()-1)%n)++;
    }
    vel seen(n,0);
    queue<ll> qu;
    rep(i,0,n){
        if(indeg.at(i)==0&&next.at(i)!=-1){
            seen.at(next.at(i))=1;
            qu.push(i);
            //cout<<i<<endl;
        }
    }
    if(qu.empty()){
        cout<<-1;
        return 0;
    }
    //rep(i,0,n)cout<<i<<" "<<indeg.at(i)<<endl;
    while(!qu.empty()){
        ll x=qu.front();
        qu.pop();
        if(next.at(x)!=-1){
            indeg.at(next.at(x))=0;
            qu.push(next.at(x));
            seen.at(next.at(x))=seen.at(x)+1;
        }
    }
    //rep(i,0,n)cout<<i<<" "<<indeg.at(i)<<endl;
    rep(i,0,n){
        if(indeg.at(i)==1){
            cout<<-1;
            return 0;
        }
    }
    ll ans=0;
    rep(i,0,n)ans=max(ans,seen.at(i));
    cout<<ans;
}