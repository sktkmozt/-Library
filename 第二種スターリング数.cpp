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
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
#define PI 3.141592653589793
#define cleout(i) cout << fixed << setprecision(i)
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

template<ll P>
struct Mint{
    ll num;
    static constexpr ll MOD=P;
    Mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=P;
            x=P-x;
        }
        x%=P;
        num=x;
    }
    Mint operator+(const Mint &other)const{
        return Mint(num+other.num);
    }
    Mint operator-(const Mint &other)const{
        return Mint(num-other.num);
    }
    Mint operator*(const Mint &other)const{
        return Mint(num*other.num);
    }
    Mint &operator+=(const Mint &other){
        num+=other.num;
        if(num>=P) num-=P;
        return *this;
    }
    Mint &operator-=(const Mint &other){
        num-=other.num;
        if(num<0) num+=P;
        return *this;
    }
    Mint &operator*=(const Mint &other){
        num=(num*other.num)%P;
        return *this;
    }
    Mint beki(const ll &x)const{
        Mint res=1;
        Mint now=num;
        rep(i,0,60){
            if(x&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    Mint inv()const{
        Mint res=1;
        Mint now=num;
        rep(i,0,30){
            if((P-2)&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    Mint operator/(const Mint &other)const{
        return *this*other.inv();
    }
    Mint &operator/=(const Mint &other){
        num=(num*other.inv())%P;
        return *this;
    }
    operator ll()const{
        return (ll)(num);
    }
    friend ostream& operator<<(ostream& os, const Mint& m) {
        os << m.num;
        return os;
    }
    friend istream& operator>>(istream& is, Mint& m) {
        ll x;
        is>>x;
        m=Mint(x);
        return is;
    }
};



struct CB{
    vem n,r;
    CB(ll N){//N以下のものをmod INFで返す
        n.assign(N+1,1);
        r.assign(N+1,1);
        rep(i,2,N+1){
            n.at(i)=n.at(i-1)*mint(i);
        }
        r.back()=n.back().inv();
        rrep(i,N,0) r.at(i)=r.at(i+1)*(mint)(i+1);
    }
    mint comb(ll N,ll R){//NCR
        if(N<R) return 0;
        return n.at(N)*r.at(R)*r.at(N-R);
    }
    mint P(ll N,ll R){//NPR
        return n.at(N)*r.at(N-R);
    }
};



template<typename T>
struct cnv{
    vector<T> A,B,C,D;
    ll now,cnt,ind;
    ll n,m;


    cnv(vector<T> &a,vector<T> &b){
        now=1;
        cnt=0;
        while(now<a.size()+b.size()){
            cnt++;
            now*=2;
        }
        n=a.size();m=b.size();
        A.assign(now,0);
        B.assign(now,0);
        rep(i,0,a.size()) A[i]=a[i];
        rep(i,0,b.size()) B[i]=b[i];
        ind=max(a.size(),b.size());
    }

    vector<T> DFT(vector<T> &a,T iv,ll cnt){
        ll size=a.size()/2;
        vector<T> INV(a.size(),1);
        INV[1]=iv;
        rep(i,2,a.size()){
            INV[i]=INV[i-1]*iv;
        }
        vector<T> ra=a;
        ll SIZE=1;
        while(size!=0){
            rep(i,0,SIZE){
                T IV=1;
                ll I=i*2*size;
                rep(j,0,size){
                    ra[I+j]=ra[I+j]+ra[I+size+j];
                    ra[I+size+j]=(ra[I+j]-(T)2*ra[I+size+j])*INV[cnt*j];
                }
            }
            cnt*=2;
            size>>=1;
            SIZE*=2;
        }
        return ra;
    }

    vector<T> rev(vector<T> &a,ll cnt){
        vector<T> res(a.size(),0);
        rep(i,0,a.size()){
            ll j=i;
            if(i==0){
                res[i]=a[i];
            }else{
                ll r=0;
                if(cnt%2==1) r|=((i>>(cnt/2))&1)<<(cnt/2);
                rep(j,0,cnt/2){
                    r|=((i>>(j))&1)<<(cnt-j-1);
                    r|=((i>>(cnt-1-j))&1)<<(j);
                }
                res[i]=a[r];
            }
        }
        return res;
    }

    vector<T> conv(){
        T iv0=3;
        iv0=iv0.beki((iv0.MOD-1)/now);
        vector<T> fa0=DFT(A,iv0,1);
        vector<T> fb0=DFT(B,iv0,1);
        vector<T> fc0(fa0.size());
        rep(i,0,fc0.size()) fc0[i]=fa0[i]*fb0[i];
        iv0=(T)1/iv0;
        fc0=rev(fc0,cnt);
        C=DFT(fc0,iv0,1);
        C=rev(C,cnt);
        T iv=T(1)/T(now);
        rep(i,0,C.size())C[i]=C[i]*iv;
        vector<T> res(n+m-1);
        rep(i,0,n+m-1)res[i]=C[i];
        return res;
    }
};







//sum_{i=0^k}(-1)^(k-i)*comb(k,i)*i^n
mint str(ll N,ll K,CB &cb){//Klong(N)
    mint k=K;
    k.beki(N);
    mint res=0;
    rep(i,0,K+1){
        mint I=i;
        if((K-i)%2){
            res-=cb.comb(K,i)*I.beki(N);
        }else{
            res+=cb.comb(K,i)*I.beki(N);
        }
    }
    return res*cb.r[K];
}

vem Str(ll K){//klogk
    vem f(K+1,0);
    vem g(K+1,0);
    mint dv=1;
    rep(i,1,K+1)dv*=(mint)i;
    dv=(mint)1/dv;
    rrep(i,K+1,1){
        f[i]=dv;
        if(i%2)f[i]*=(mint)(-1);
        mint I=i;
        g[i]=I.beki(K)*dv;
        dv*=(mint)i;
    }
    f[0]=1;
    cnv<mint> CNV(f,g);
    vem ret=CNV.conv();
    ret.resize(K+1);
    return ret;
}

int main(){
    N=2e3;
    vvem stir(2e3+1,vem(2e3+1));
    rep(i,1,N+1)stir[i][1]=1;
    rep(i,2,N+1){
        rep(j,1,N+1){
            if(j==1||j==i)stir[i][j]=1;
            else{
                stir[i][j]=stir[i-1][j-1]+(mint)j*stir[i-1][j];
            }
        }
    }
    cin>>Q;
    vem ans;
    rep(q,0,Q){
        cin>>N>>M>>K;
        mint E=M/2;
        mint O=(mint)M-E;
        mint res=0;
        mint frac=1;
        mint o=1;
        mint m=(mint)M;
        m=m.beki(N);
        mint dv=(mint)1/(mint)M;
        rep(j,0,K+1){
            res+=stir[K][j]*m*o*frac;
            frac*=(mint)(N-j);
            o*=O;
            m*=dv;
        }
        ans.push_back(res);
    }
    rep(i,0,ans.size())cout<<ans[i]<<endl;
}
//https://codeforces.com/contest/1716/problem/F