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

struct Interval{
    using T=ll;
    ll l,r;
    T val;
    Interval(ll L,ll R, ll v=1):l(L),r(R),val(v){}
    bool operator<(const Interval& other)const{
        if(l!=other.l) {
            return l<other.l;
        }
        return r<other.r; 
    }
    bool operator>(const Interval& other)const{
        if(l!=other.l) {
            return l>other.l;
        }
        return r>other.r; 
    }
    bool is_valid(){
        return l<r;
    }
};

struct Intervalset{
    ll Inf=1ll<<60;
    ll sum=0;
    set<Interval> se;

    Intervalset(){
        Interval L(-Inf,-Inf,1);
        Interval R(Inf,Inf,1);
        se.insert(L);
        se.insert(R);
    }

    void insert(Interval &lr){
        ll l=lr.l;
        Interval ivl(l,l,0);
        auto itl=se.lower_bound(ivl);
        itl--;
        if(itl->r<l)itl++;
        //lrのlよりも右の区間があり得る最小
        ll r=lr.r;
        ivl={r,Inf,1};
        auto itr=se.upper_bound(ivl);
        itr--;
        //lrのr以下がある最大
        if(*itl>*itr){
            se.insert(lr);
            sum+=(lr.r-lr.l)*lr.val;
            return ;
        }
        Interval add_L(itl->l,min(itl->r,l),itl->val);
        Interval add_R(max(itr->l,r),itr->r,itr->val);
        itr++;
        for(auto it=itl;it!=itr;){
            sum-=(it->r-it->l)*it->val;
            it=se.erase(it);
        }
        if(lr.val==add_L.val){
            add_L={min(lr.l,add_L.l),max(lr.r,add_L.r),add_L.val};
        }
        if(lr.val==add_R.val){
            add_R={min(lr.l,add_R.l),max(lr.r,add_R.r),add_R.val};
        }
        if(lr.val==add_L.val&&lr.val==add_R.val){
            add_L={add_L.l,add_R.r,add_L.val};
            if(add_L.is_valid())sum+=(add_L.r-add_L.l)*add_L.val;
            se.insert(add_L);
        }else{
            if(add_L.is_valid()){
                sum+=(add_L.r-add_L.l)*add_L.val;
                se.insert(add_L);
            }
            if(add_R.is_valid()){
                sum+=(add_R.r-add_R.l)*add_R.val;
                se.insert(add_R);
            }
            if(add_L.val!=lr.val&&add_R.val!=lr.val){
                sum+=(lr.r-lr.l)*lr.val;
                se.insert(lr);
            }
        }
    }

    void erase(Interval lr){
        ll l=lr.l;
        Interval ivl(l,l,0);
        auto itl=se.lower_bound(ivl);
        itl--;
        if(itl->r<l)itl++;
        //lrのlよりも右の区間があり得る最小
        ll r=lr.r;
        ivl={r,Inf,1};
        auto itr=se.upper_bound(ivl);
        itr--;
        if(*itl>*itr){
            return ;
        }
        Interval add_L(itl->l,min(itl->r,l),itl->val);
        Interval add_R(max(itr->l,r),itr->r,itr->val);
        itr++;
        for(auto it=itl;it!=itr;){
            sum-=(it->r-it->l)*it->val;
            it=se.erase(it);
        }
        if(add_L.r>add_L.l){
            sum+=(add_L.r-add_L.l)*add_L.val;
            se.insert(add_L);
        }
        if(add_R.r>add_R.l){
            sum+=(add_R.r-add_R.l)*add_R.val;
            se.insert(add_R);
        }
    }

    void debug(){
        cout<<"debug"<<endl;
        for(auto it=se.begin();it!=se.end();it++){
            cout<<it->l<<" "<<it->r<<" "<<it->val<<endl;
        }
        cout<<endl;
    }

    ll mex(){
        auto it=se.upper_bound({0,Inf});
        it--;
        return max(0ll,it->r);
    }
};


int main(){
    cin>>N>>Q;
    Intervalset se;
    Interval s(1,N+1,1);
    se.insert(s);
    vel ans;
    rep(q,0,Q){
        ll r;
        cin>>l>>r;
        Interval s(l,r+1,0);
        se.erase(s);
        ans.push_back(se.sum);
    }
    rep(i,0,ans.size())cout<<ans[i]<<endl;
}