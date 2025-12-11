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
ll p=998244353;
//ll p=1000000007;
ll inf=1000000000000000000;//1e18
// inf=LLONG_MAX

/*座圧
    vel A=a;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    rep(i,0,A.size()) A.at(i)=lower_bound(a.begin(),a.end(),A.at(i))-a.begin();
    swap(A,a);
*/

struct mint{
    ll num;
    static ll P;
    mint(ll x=0){
        if(x<0){
            x*=-1;
            x%=P;
            x=P-x;
        }
        x%=P;
        num=x;
    }
    static void set_mod(ll PP) {
        P=PP;
    }
    mint operator+(const mint &other)const{
        return mint(num+other.num);
    }
    mint operator-(const mint &other)const{
        return mint(num-other.num);
    }
    mint operator*(const mint &other)const{
        return mint(num*other.num);
    }
    mint &operator+=(const mint &other){
        num+=other.num;
        if(num>=P) num-=P;
        return *this;
    }
    mint &operator-=(const mint &other){
        num-=other.num;
        if(num<0) num+=P;
        return *this;
    }
    mint &operator*=(const mint &other){
        num=(num*other.num)%P;
        return *this;
    }
    mint beki(const ll &x)const{
        mint res=1;
        mint now=num;
        rep(i,0,60){
            if(x&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    mint inv()const{
        mint res=1;
        mint now=num;
        rep(i,0,60){
            if((P-2)&(1ll<<i)){
                res*=now;
            } 
            now*=now;
        }
        return res;
    }
    mint operator/(const mint &other)const{
        return *this*other.inv();
    }
    mint &operator/=(const mint &other){
        num=(num*other.inv())%P;
        return *this;
    }
    operator ll()const{
        return (ll)(num);
    }
    friend ostream& operator<<(ostream& os, const mint& m) {
        os << m.num;
        return os;
    }
    friend istream& operator>>(istream& is, mint& m) {
        ll x;
        is>>x;
        m=mint(x);
        return is;
    }
};
ll mint::P=p;



struct hoge{
    vel next;//次のindexを持つやつ
    vel check;//これは何？
    ll cnt;//この頂点を何回通ったか
    ll deep;//個の頂点の深さ
    ll back;
    hoge(ll dp,ll var){
        next.assign(var,-1);
        deep=dp;
        cnt=0;
        back=-1;
    }
};


struct trie{
    vector<hoge> node;
    char base='a';
    trie(ll var){//この頂点の子供の数
        hoge x(0,var);
        node.push_back(x);
    }
    ll insert(string &S,ll num){
        ll now=0;
        rep(i,0,S.size()){
            node.at(now).cnt++;
            if(node.at(now).next.at(S.at(i)-base)==-1){
                hoge x(i+1,26);
                node.at(now).next.at(S.at(i)-base)=node.size();
                node.push_back(x);
            }
            ll next=node.at(now).next.at(S.at(i)-base);
            node.at(next).back=now;
            now=node.at(now).next.at(S.at(i)-base);
            if(i==S.size()-1){
                node.at(now).check.push_back(num);
            }
        }
        node.at(now).cnt++;
        return now;
    }

    void solve(ll now){
    }
};

int main(){
    cin>>T;
    vel ans;
    trie tree(26);
    rep(i,0,ans.size())cout<<ans.at(i)<<endl;
}