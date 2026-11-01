#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned ll
#define ld long double
#define bl __int128_t
#define fi first
#define se second
#define vel vector<ll>
#define vvel vector<vel>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define vvepll vector<vepll>
#define ves vector<string>
#define mint Mint<998244353>
#define vem vector<mint>
#define vvem vector<vem>
#define pmm pair<mint,mint>
#define cleout(i) cout<<fixed<<setprecision(i)
template<class T>using PQ=priority_queue<T,vector<T>,greater<T>>;
//               上  右 下 左
vector<int> di={-1, 0, 1, 0};
vector<int> dj={ 0, 1, 0,-1};

vector<int> dx={ 0, 1, 0,-1};
vector<int> dy={ 1, 0,-1, 0};


vector<int> ddx={ 1, 1, 1, 0, -1, -1, -1, 0 };
vector<int> ddy={ 1, 0, -1, -1, -1, 0, 1, 1 };

ll inf=1000000000000000000;//1e18
// LLONG_MAX

mt19937_64 rng((ull)chrono::steady_clock::now().time_since_epoch().count());

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

struct fps:std::vem{
    using vem::vector;

    static fps DFT(fps &f,mint iv){
        ll cnt=1;
        ll size=f.size()/2;
        fps INV(f.size(),1);
        INV[1]=iv;
        rep(i,2,f.size()){
            INV[i]=INV[i-1]*iv;
        }
        ll SIZE=1;
        while(size!=0){
            rep(i,0,SIZE){
                mint IV=1;
                ll I=i*(mint)2*size;
                rep(j,0,size){
                    f[I+j]=f[I+j]+f[I+size+j];
                    f[I+size+j]=(f[I+j]-(mint)2*f[I+size+j])*INV[cnt*j];
                }
            }
            cnt<<=1;
            size>>=1;
            SIZE<<=1;
        }
        int n=f.size();
        int j=0;
        for(int i=1;i<n-1;i++){
            int bit=n>>1;
            while(j>=bit){
                j-=bit;
                bit>>=1;
            }
            j+=bit;
            if(i<j)std::swap(f[i],f[j]);
        }
        return f;
    }
    fps &operator*=(const mint &c){
        rep(i,0,this->size()){
            (*this)[i]*=c;
        }
        return *this;
    }
    fps operator*(const mint &c)const{
        return (fps(*this)*=c);
    }
    fps &operator/=(const mint &c){
        mint c_inv=(mint)1/c;
        rep(i,0,this->size()){
            (*this)[i]*=c_inv;
        }
        return *this;
    }
    fps operator/(const mint &c)const{
        return (fps(*this)/=c);
    }
    fps pre(ll d){
        fps res(this->begin(),this->begin()+min((ll)this->size(),d));
        if(this->size()<d)res.resize(d,0);
        return res;
    }
    void shrink(){
        while(this->size()&&this->back()==0)this->pop_back();
    }
    fps &operator+=(const fps &other){
        if(other.size()>this->size()){
            this->resize(other.size(),0);
        }
        rep(i,0,other.size()){
            (*this)[i]+=other[i];
        }
        return *this;
    }
    fps operator+(const fps &other)const{
        return (fps(*this)+=other);
    }
    fps &operator-=(const fps &other){
        if(other.size()>this->size()){
            this->resize(other.size(),0);
        }
        rep(i,0,other.size()){
            (*this)[i]-=other[i];
        }
        return *this;
    }
    fps operator-(const fps &other)const{
        return (fps(*this)-=other);
    }
    fps operator*(const fps &other)const{
        if(this->empty()||other.empty())return{};
        int rsz=this->size()+other.size()-1;
        int sz=bit_ceil((ull)this->size()+other.size()-1);

        mint w=mint(3).beki(998244352/sz);

        fps Fthis(this->begin(),this->end());
        Fthis.resize(sz);
        Fthis=DFT(Fthis,w);

        fps Fother=other;
        Fother.resize(sz);
        Fother=DFT(Fother,w);

        rep(i,0,Fthis.size())Fthis[i]*=Fother[i];
        fps res=DFT(Fthis,(mint)1/w);
        res.resize(rsz);
        return res/(mint)sz;
    }
    fps &operator*=(const fps &other){
        *this=(*this)*other;
        return *this;
    }
    fps &operator<<=(int d){
        this->insert(this->begin(),d,(mint)0);
        return *this;
    }
    fps operator<<(int d)const{
        return(fps(*this)<<=d);
    }
    fps &operator>>=(int d){
        if((ll)this->size()<=d){
            this->clear();
        }else{
            this->erase(this->begin(),this->begin()+d);
        }
        return *this;
    }
    fps operator>>(int d)const{
        return(fps(*this)>>=d);
    }
    void show(){
        for(auto it=this->begin();it!=this->end();it++){
            cout<<*it<<" ";
        }
        cout<<"\n";
    }
};
mint bostan_mori(fps f,fps g,ll K){//[x^k]f/g
    fps og;
    while(K){
        og=g;
        for(ll i=1;i<og.size();i+=2){
            og[i]=-og[i];
        }
        f*=og;
        g*=og;
        ll f_size=0;
        ll g_size=0;
        for(ll i=0;2*i<g.size();i++){
            g[i]=g[2*i];
            g_size++;
        }
        g.resize(g_size);
        for(ll i=0;2*i+(K%2)<f.size();i++){
            f[i]=f[2*i+(K%2)];
            f_size++;
        }
        f.resize(f_size);
        K/=2;
    }
    return f.size()?f[0]/g[0]:(mint)0;
}
pair<ll,fps> Berlekamp_Massey(fps &S){
    ll N=S.size();
    fps Q={1};
    ll L=0;
    fps B={1};
    ll n0=-1;
    mint b=1;
    rep(n,0,N){
        mint d=0;
        rep(j,0,min((ll)Q.size(),n+1))d+=Q[j]*S[n-j];
        if(d==0)continue;
        fps Q_new=Q-(B<<(n-n0))*(d/b);
        ll L_new;
        if(2*L<=n){
            L_new=n+1-L;
            B=Q;
            n0=n;
            b=d;
        }else L_new=L;
        Q=Q_new;
        L=L_new;
    }
    return {L,Q};
}
mint BMBM(fps &f,ll K,bool debug=false){
    auto[L,Q]=Berlekamp_Massey(f);
    if(debug)cout<<f.size()<<" "<<2*L<<"\n";
    assert((ll)f.size()>=2*L);
    fps P=(f*Q).pre(Q.size()-1);
    P.shrink();
    return bostan_mori(P,Q,K);
}

void _solve(){
    ll N,M;
    cin>>N>>M;
    vel a(N);
    rep(i,0,N)cin>>a[i];
    ll K=N*200+1;
    vvem dp(N,vem(K+1));
    for(ll i=0;i<=K;i+=a[0]){
        dp[0][i]=1;
    }
    rep(i,1,N){
        for(ll j=0;j<a[i];j++){
            ll id=j;
            mint sum=0;
            while(id<=K){
                sum+=dp[i-1][id];
                dp[i][id]+=sum;
                id+=a[i];
            }
        }
    }
    fps f(K+1);
    rep(i,0,K+1){
        f[i]=dp.back()[i];
        if(i>0)f[i]+=f[i-1];
    }
    cout<<BMBM(f,M)<<"\n";
}


int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);


    ll _;
    bool multitest=0;
    if(multitest)cin>>_;
    else _=1;
    rep(__,0,_){
        _solve();
    }
}