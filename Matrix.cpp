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
#define vem vector<mint>
#define vvem vector<vem>
#define pmm pair<mint,mint>
#define cleout(i) cout<<fixed<<setprecision(i)
#define mat Matrix<SemiRing>
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

struct SemiRing{
    using T=ll;
    T val=-inf;
    SemiRing(){}
    SemiRing(T v):val(v){}
    static SemiRing mul_id(){return SemiRing(0);}

    SemiRing& operator+=(const SemiRing& other){val=max(val,other.val);return *this;}
    SemiRing operator+(const SemiRing& other)const{return SemiRing(*this)+=other;}

    SemiRing& operator*=(const SemiRing& other){val+=other.val;return *this;}
    SemiRing operator*(const SemiRing& other)const{return SemiRing(*this)*=other;}
};

template<class T>
struct Matrix{
    int N,M;
    vector<vector<T>> Mat;
    Matrix():N(0),M(0){}
    Matrix(int N,int M,T val=T()):N(N),M(M),Mat(N,vector<T>(M,val)){}
    Matrix(const vector<vector<T>>& v):N(v.size()),M(v[0].size()),Mat(v){}

    static Matrix I(int N){
        Matrix res(N,N);
        rep(i,0,N)res[i][i]=T::mul_id();
        return res;
    }

    inline vector<T>& operator[](int i){return Mat[i];}
    inline const vector<T>& operator[](int i)const{return Mat[i];}

    Matrix& operator+=(const Matrix& other){
        assert(N==other.N&&M==other.M);
        rep(i,0,N){
            rep(j,0,M){
                Mat[i][j]+=other[i][j];
            }
        }
        return *this;
    }
    Matrix operator+(const Matrix& other)const{return Matrix(*this)+=other;}

    Matrix operator*(const Matrix& other)const{
        assert(M==other.N);
        Matrix res(N,other.M);
        rep(i,0,N){
            rep(k,0,M){
                rep(j,0,other.M){
                    res[i][j]+=Mat[i][k]*other[k][j];
                }
            }
        }
        return res;
    }
    Matrix& operator*=(const Matrix& other){return *this=*this*other;}

    Matrix pow(ll K)const{
        assert(N==M);
        assert(K>=0);
        Matrix res=I(N);
        Matrix now=*this;
        while(K){
            if(K&1)res*=now;
            now*=now;
            K>>=1;
        }
        return res;
    }
};

struct Combine {
    inline mat operator()(const mat &a,const mat &b)const{
        return a*b;
    }
};

template<typename T, typename Combine>
struct seg{
    int N;
    Combine combine;
    T id;
    vector<T> node;
    int sz;

    seg(vector<T> &a,Combine com,T ident){
        sz=a.size();
        combine=com;
        id=ident;
        ll m=1;
        while(m<sz) m*=2;
        node.resize(2*m,id);
        rep(i,0,sz){
            node[i+m]=a[i];
        }
        rrep(i,m,1){
            node[i]=combine(node[2*i],node[2*i+1]);
        }
        N=m;
    }

    seg(ll n,Combine com,T ident){
        sz=n;
        combine=com;
        id=ident;
        ll m=1;
        while(m<sz) m*=2;
        node.resize(2*m,id);
        N=m;
    }

    inline void chan(int i,T x){//i番目をxに変える
        i+=N;
        node[i]=x;
        while(i>0){
            i/=2;
            node[i]=combine(node[2*i],node[2*i+1]);
        }
    }

    inline T  Ique(int l,int r){//[a,b)のmin
        T resl=id,resr=id;
        l+=N;
        r+=N;
        while(l<r){
            if(l&1){//左のほうの右側なので
                resl=combine(resl,node[l]);
                l++;
            }
            if(r&1){//半開区間なのでrが右だといい
                r--;
                resr=combine(node[r],resr);
            }
            l/=2;
            r/=2;
        }
        return combine(resl,resr);
    }

    inline T get(int i){
        return node[i+N];
    }

    inline T all(){
        return node[1];
    }

    template<typename F>
    int upper(int l,T x,F check){//check(node[now],x)=1の最小のindex
        if(l>=sz)return sz;
        l+=N;
        T now=id;
        do{
            while(l%2==0)l>>=1;//左にいるなら区間を大きくする
            if(check(combine(now,node[l]),x)){//この区間でhitしてる
                while(l<N){//降りていく
                    l=2*l;
                    if(!check(combine(now,node[l]),x)){//hitしないなら右に降りる
                        now=combine(now,node[l]);
                        l++;
                    }
                }
                return l-N;
            }
            now=combine(now,node[l]);//hitしなかったから右に行く
            l++;
        }while((l&-l)!=l);//2冪なら終わる(各層の右端が1,2,4,8,...なので)
        return sz;
    }


    template<typename F>
    inline int lower(int r,T x,F check){//check(node[now],x)=1の最大のindex
        if(r<=0)return -1;
        r+=N;
        T now=id;
        do{
            r--;
            while(r>1&&(r%2))r>>=1;//右側にいるなら区間を大きくする
            if(check(combine(node[r],now),x)){
                while(r<N){
                    r=2*r+1;
                    if(!check(combine(node[r],now),x)){//hitしないなら左に降りる
                        now=combine(node[r],now);
                        r--;
                    }
                }
                return r-N;
            }
            now=combine(node[r],now);
        }while((r&-r)!=r);//2冪なら場外(r+1が右端になってるので)
        return -1;
    }
};

void _solve(){
    ll N,Q;
    cin>>N>>Q;
    auto f=[](ll N){
        mat res=mat::I(5);
        res[0][1]=N;
        res[1][1]=N;
        res[1][2]=0;
        res[2][3]=N;
        res[3][3]=N;
        res[3][4]=0;
        return res;
    };
    seg<mat,Combine> st(N,Combine(),mat::I(5));
    rep(i,0,N){
        ll x;
        cin>>x;
        st.chan(i,f(x));
    }
    rep(q,0,Q){
        ll op;
        cin>>op;
        if(op==1){
            ll i,x;
            cin>>i>>x;
            i--;
            st.chan(i,f(x));
        }else{
            ll l,r;
            cin>>l>>r;
            l--;
            mat res(1,5,0);
            res*=st.Ique(l,r);
            ll ans=-inf;
            rep(i,0,5)ans=max(ans,res[0][i].val);
            cout<<ans<<"\n";
        }
    }
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