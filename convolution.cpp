#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define all(a,i,j) a.begin()+i,a.begin()+j
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define cleout(i) cout << fixed << setprecision(i)
//                上 右 下 左
vector<int> dx={ -1, 0, 1, 0};
vector<int> dy={ 0, 1, 0, -1};

ll N, K, M, L, R, Q, H, W, i, j, k, l;
ll x, y, z;
string S,T;
vel mod={998244353,897581057,(ll)1e9+7,(ll)1e9+9,(ll)1e9+21};//(1<<61)-1も素数
ll inf=998244353;
// inf=1e9+7;
// LLONG_MAX

/*座圧
    vel A=a;
    sort(all(a,0,a.size()));
    a.erase(unique(all(a,0,a.size())),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(all(a,0,a.size()),A.at(i))-a.begin();
    swap(A,a);
*/

ll beki(ll a,ll b,ll inf){
    ll ans=1;
    ll now=a%inf;
    rep(i,0,60){
        if(b&(1ll<<i)){
            ans*=now;
            ans%=inf;
        }
        now*=now;
        now%=inf;
    }
    return ans;
}

struct cnv{
    vel A,B,C,D;
    ll now,cnt,ind;

    vel euclid(ll x,ll y){
        tuple<ll,ll,ll> a={x,1,0},b={y,0,1};
        if(x<0){
            a={-x,-1,0};
        }
        if(y<0){
            b={-y,0,-1};
        }
        if(get<0>(a)<get<0>(b)) swap(a,b);
        while(get<0>(b)!=0){
            ll cnt=get<0>(a)/get<0>(b);
            a={get<0>(a)-cnt*get<0>(b),get<1>(a)-cnt*get<1>(b),get<2>(a)-cnt*get<2>(b)};
            swap(a,b);
        }////////gcd(x,y)  xの係数   yの係数
        vel res={get<0>(a),get<1>(a),get<2>(a)};
        return res;
    }

    ll euclidsolver(pll a,pll b){//a=(a_1,p_a) b=(b_1,p_b)でmod p_a*p_bでのやつ返す
        vel res=euclid(a.se,b.se);
        __int128_t inf=a.se*b.se;
        __int128_t ans=(res.at(2)+inf)%inf;
        ans*=b.se;ans%=inf;ans*=a.fi;ans%=inf;
        __int128_t ANS=(res.at(1)+inf)%inf;
        ANS*=a.se;ANS%=inf;ANS*=b.fi;ANS%=inf;
        ans+=ANS;
        ans%=inf;
        return ans;
    }

    void set(vel &a,vel &b){
        now=1;
        cnt=0;
        while(now<a.size()+b.size()){
            cnt++;
            now*=2;
        }
        A.assign(now,0);
        B.assign(now,0);
        rep(i,0,a.size()) A.at(i)=a.at(i);
        rep(i,0,b.size()) B.at(i)=b.at(i);
        ind=max(a.size(),b.size());
    }

    vel DFT(vel &a,ll inf,ll iv,ll cnt){
        ll size=a.size()/2;
        vel INV(a.size(),1);
        INV.at(1)=iv;
        rep(i,2,a.size()){
            INV.at(i)=(INV.at(i-1)*iv)%inf;
        }
        vel ra=a;
        ll SIZE=1;
        while(size!=0){
            rep(i,0,SIZE){
                ll IV=1;
                ll I=i*2*size;
                rep(j,0,size){
                    ra.at(I+j)=ra.at(I+j)+ra.at(I+size+j);
                    if(ra.at(I+j)>=inf) ra.at(I+j)-=inf;
                    ra.at(I+size+j)=((2*inf+ra.at(I+j)-2*ra.at(I+size+j))*INV.at(cnt*j))%inf;
                }
            }
            cnt*=2;
            size>>=1;
            SIZE*=2;
        }
        return ra;
    }

    vel rev(vel &a,ll cnt){
        vel res(a.size(),0);
        rep(i,0,a.size()){
            ll j=i;
            if(i==0){
                res.at(i)=a.at(i);
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

    vel SUM(bool c){
        ll iv0=beki(3,(mod.at(0)-1)/now,mod.at(0));
        ll iv1=beki(3,(mod.at(1)-1)/now,mod.at(1));
        vel fa0=DFT(A,mod.at(0),iv0,1);
        vel fb0=DFT(B,mod.at(0),iv0,1);
        vel fc0(fa0.size());
        rep(i,0,fc0.size()) fc0.at(i)=(fa0.at(i)*fb0.at(i))%mod.at(0);
        iv0=beki(iv0,mod.at(0)-2,mod.at(0));
        iv1=beki(iv1,mod.at(1)-2,mod.at(1));
        fc0=rev(fc0,cnt);
        C=DFT(fc0,mod.at(0),iv0,1);
        C=rev(C,cnt);
        ll iv=beki(now,mod.at(0)-2,mod.at(0));
        rep(i,0,C.size())C.at(i)=(C.at(i)*iv)%mod.at(0);
        if(c){
            ll iv1=beki(3,(mod.at(1)-1)/now,mod.at(1));
            vel fa1=DFT(A,mod.at(1),iv1,1);
            vel fb1=DFT(B,mod.at(1),iv1,1);
            vel fc1(fa1.size());
            rep(i,0,fc1.size()) fc1.at(i)=(fa1.at(i)*fb1.at(i))%mod.at(1);
            iv1=beki(iv1,mod.at(1)-2,mod.at(1));
            fc1=rev(fc1,cnt);
            D=DFT(fc1,mod.at(1),iv1,1);
            D=rev(D,cnt);
            iv=beki(now,mod.at(1)-2,mod.at(1));
            rep(i,0,D.size())D.at(i)=(D.at(i)*iv)%mod.at(1);
            C.at(i)=euclidsolver({C.at(i),mod.at(0)},{D.at(i),mod.at(1)});
            return C;
        }
        return C;
    }

    vel MAX(){
        rep(i,0,now-1){
            A.at(i+1)+=A.at(i);
            A.at(i+1)%=mod.at(0);
        }
        rep(i,0,now-1){
            B.at(i+1)+=B.at(i);
            B.at(i+1)%=mod.at(0);
        }
        vel C(A.size(),0);
        rep(i,0,C.size())C.at(i)=(A.at(i)*B.at(i))%mod.at(0);
        rrep(i,now-1,0){
            C.at(i+1)+=mod.at(0)-C.at(i);
            C.at(i+1)%=mod.at(0);
        }
        return C;
    }

    vel MIN(){
        rrep(i,now-1,0){
            A.at(i)+=A.at(i+1);
            A.at(i)%=mod.at(0);
        }
        rrep(i,now-1,0){
            B.at(i)+=B.at(i+1);
            B.at(i)%=mod.at(0);
        }
        vel C(A.size(),0);
        rep(i,0,C.size())C.at(i)=(A.at(i)*B.at(i))%mod.at(0);
        rep(i,0,now-1){
            C.at(i)+=mod.at(0)-C.at(i+1);
            C.at(i)%=mod.at(0);
        }
        return C;
    }

    vel GCD(){//faが与えられていると思っている
        vel C(now,0);
        rep(i,0,now) C.at(i)=(A.at(i)*B.at(i));
        rrep(i,now,1){
            ll j=2;
            while(j*i<now){
                C.at(i)-=C.at(i*j);
                j++;
            }
        }
        return C;
    }
};

int main(){
    cin>>N>>M;
    vel a(N),b(M);
    rep(i,0,N) cin>>a.at(i);
    rep(i,0,M) cin>>b.at(i);
    rep(i,0,N) a.at(i)%=inf;
    rep(i,0,M) b.at(i)%=inf;
    cnv cnv;
    cnv.set(a,b);
    vel A=cnv.SUM(false);
    rep(i,0,a.size()+b.size()-1){
        cout<<A.at(i)<<" ";
    }
}

/*
g++ a.cpp -std=c++20
*/