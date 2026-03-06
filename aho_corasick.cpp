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
#define vvvel vector<vvel>
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
#define mint Mint<998244353>
//#define mint Mint<1000000007>
#define cleout(i) cout<<fixed<<setprecision(i)
template<class T>using PQ=priority_queue<T,vector<T>,greater<T>>;
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

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

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

struct hoge{
    vel next;//aho_corasickの遷移先
    ll failure;//遷移先がない時にどこまで戻るか(trie木に含まれる文字列=suffixとなる最長の場所のindex)
    ll output;//自分未満で初めてヒットするやつ
    ll deep;//この頂点の深さ
    ll P;//親のindex
    vel ids;
    ll cnt;
    hoge(ll dp,ll var){
        next.assign(var,-1);
        deep=dp;
        P=0;
        failure=0;
        output=0;
        cnt=0;
    }
};


struct trie{
    vector<hoge> node;
    char base='a';
    ll var;
    vel id;
    trie(ll v=26):var(v){//この頂点の子供の数
        hoge x(0,var);
        node.push_back(x);
    }
    ll insert(string &S,ll num){
        ll now=0;
        rep(i,0,S.size()){
            if(node[now].next[S[i]-base]==-1){
                hoge x(i+1,var);
                node[now].next[S[i]-base]=node.size();
                node.push_back(x);
            }
            ll next=node[now].next[S[i]-base];
            node[next].P=now;
            now=node[now].next[S[i]-base];
            if(i==S.size()-1){
                node[now].ids.push_back(num);
                id.push_back(now);
                //node[now].ids|=(1ll<<num);//bit用
            }
        }
        return now;
    }

    void build(){
        queue<ll> qu;
        rep(i,0,var){
            if(node[0].next[i]!=-1){
                ll child=node[0].next[i];
                node[child].failure=0;
                qu.push(node[0].next[i]);
            }else{
                node[0].next[i]=0;
            }
        }
        while(!qu.empty()){
            ll now=qu.front();
            qu.pop();
            rep(i,0,var){
                if(node[now].next[i]!=-1){
                    ll next=node[now].next[i];
                    node[next].failure=node[node[now].failure].next[i];//子供の行き先がないなら自分のところの行き先にする
                    ll f=node[next].failure;
                    //node[next].ids|=node[f].ids;//bit用
                    if(node[f].ids.size()){//子供のoutputは行き先が終端ならそこに、そうじゃないなら行き先に合わせる
                        node[next].output=f;
                    }else{
                        node[next].output=node[f].output;
                    }
                    qu.push(next);
                }else{
                    node[now].next[i]=node[node[now].failure].next[i];
                }
            }
        }
    }

    ll f(ll now,ll c){
        return node[now].next[c];
    }

    void s_list(ll now,vel &v){
        for(auto x:node[now].ids)v.push_back(x);
        while(node[now].output!=0){
            now=node[now].output;
            for(auto x:node[now].ids)v.push_back(x);
        }
        return ;
    }
    

    vel cnt(string &S){
        ll now=0;
        rep(i,0,S.size()){
            ll n=S[i]-base;
            now=f(now,n);
            node[now].cnt++;
        }
        rrep(i,node.size(),1){
            ll now=node[i].failure;
            node[now].cnt+=node[i].cnt;
        }
        vel res(id.size());
        rep(i,0,id.size())res[i]=node[id[i]].cnt;
        return res;
    }

    vvel failure_tree(){//id[i],id[j]のlcaがiとjの共通最長suffix
        ll n=node.size();
        vvel G(n);
        rep(i,1,n) {
            G[node[i].failure].push_back(i);
        }
        return G;
    }

    void solve(ll L){
        ll n=node.size();
        vvem dp(n,vem(1ll<<N));
        dp[0][0]=1;
        rep(q,0,L){
            vvem ndp(n,vem(1ll<<N));
            rep(i,0,n){
                rep(j,0,26){
                    ll m=f(i,j);
                    vel v;
                    s_list(m,v);
                    ll bit=0;
                    rep(k,0,v.size())bit|=(1ll<<v[k]);
                    rep(k,0,(1ll<<N)){
                        ndp[m][k|bit]+=dp[i][k];
                    }
                }
            }
            swap(dp,ndp);
        }
        mint ans=0;
        rep(i,0,n)ans+=dp[i].back();
        cout<<ans<<"\n";
    }
};

trie make_aho_corasick(vector<string> &a){
    trie tree;
    rep(i,0,a.size()){
        tree.insert(a[i],i);
    }
    tree.build();
    return tree;
}


void _solve(){
    cin>>N>>L;
    vector<string> a(N);
    rep(i,0,N)cin>>a[i];
    auto tree=make_aho_corasick(a);
    tree.solve(L);
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