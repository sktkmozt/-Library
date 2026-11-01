//abc436-g
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

mint get(ll k,vem& f,vem &g){
    if(k==0){
        return f[0]/g[0];
    }else{
        vem mg=g;
        rep(i,1,g.size()){
            mg[i]*=-1;
            i++;
        }
        cnv<mint> CNV(f,mg);
        vem nf=CNV.conv();
        cnv<mint> CNV1(g,mg);
        vem ng=CNV1.conv();
        if(k%2){
            vem nnf;
            rep(i,1,nf.size()){
                nnf.push_back(nf[i]);
                i++;
            }
            vem nng(g.size());
            rep(i,0,g.size())nng[i]=ng[i*2];
            return get(k/2,nnf,nng);
        }else{
            vem nnf;
            rep(i,0,nf.size()){
                nnf.push_back(nf[i]);
                i++;
            }
            vem nng(g.size());
            rep(i,0,g.size())nng[i]=ng[i*2];
            return get(k/2,nnf,nng);
        }
    }
}

int main(){
    cin>>N>>M;
    vem ans={1};
    rep(i,0,N){
        cin>>x;
        vem f(x+1,0);
        f[0]=1;
        f[x]=-1;
        cnv<mint> CNV(ans,f);
        ans=CNV.conv();
    }
    vem f(2);
    f[0]=1;
    f[1]=-1;
    cnv<mint> CNV(ans,f);
    ans=CNV.conv();
    f={1};
    cout<<get(M,f,ans);
}
