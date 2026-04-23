#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,a,b) for(ll i=a-1;i>=b;i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define bl __int128_t
#define fi first
#define se second
#define vel vector<long long>
#define vvel vector<vector<long long>>
#define vvepll vector<vepll>
#define pll pair<ll,ll>
#define vepll vector<pll>
#define ves vector<string>
#define vem vector<mint>
#define vvem vector<vem>
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
ll inf=1000000000000000000;//1e18
// inf=1e9+7;
// LLONG_MAX

//mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());

//[x^M]1/(1-x)^N=comb(N-1+M,M)


struct Combine {
    inline ll operator()(ll a,ll b){
        return min(a,b);
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

void induced_sort(vel &S,vel &l,vel &lms,ll size,vel &ans){//lmsが完成してるときにl,s型を伸ばして全体に波及させる
    vel head(size);
    vel tail(size);
    for(ll &i:ans)i=-1;
    for(ll c:S){
        tail[c]++;
    }
    ll sum=0;
    rep(i,0,size){
        head[i]+=sum;
        tail[i]+=sum;
        sum=tail[i];
    }
    //s型は右隣がでかいから同じ文字なら大きい側になる(lmsはs型)(l型<s型)
    vel now_tail=tail;
    for(ll i:lms){
        ans[--now_tail[S[i]]]=i;
    }
    //l型のindexを決めるS[i:]>S[i+1:]よりS[i]>S[i+n[j]]となっていてsaの大きいほうは埋まってると思える
    rep(j,0,ans.size()){
        if(ans[j]>0){//ans[j]を次に持つ奴がl型ならそいつはS[ans[j]-1]のなかで現在最小
            ll i=ans[j]-1;
            if(l[i])ans[head[S[i]]++]=i;
        }
    }
    //s型
    rrep(j,ans.size(),0){
        if(ans[j]>0){//ans[j]を次に持つ奴がs型ならそいつはS[ans[j]-1]のなかで現在最大
            ll i=ans[j]-1;
            if(l[i]==0)ans[--tail[S[i]]]=i;
        }
    }
    return ;
}


vel make_sa(vel &S){//S+$をいれられてSのsaを返す
    vel ans(S.size(),-1);
    vel l(S.size());//S[i]>S[i+1]ですか？
    vel is_lms(S.size());
    rrep(i,(ll)S.size()-1,0){
        if(S[i]==S[i+1]){
            l[i]=l[i+1];
        }else{
            l[i]=S[i]>S[i+1];
        }
    }
    vel lms;//極小なindexたち
    ll size=S[0];
    rep(i,1,S.size()){
        size=max(size,S[i]);
        if(l[i-1]&&l[i]==0){
            is_lms[i]=1;
            lms.push_back(i);
        }
    }
    vel pre(S.size(),-1);
    induced_sort(S,l,lms,size+1,pre);//これでlms単体の順序が正しく並んでるので隣り合ったやつたちを見ることで新しいlmsかを判定できる
    vel new_S(lms.size(),1);
    vel comp_lms(S.size());//S->new_Sのindex(lmsしか見ない)
    vel sorted_lms;//lmsがsortされてはいってる
    ll cnt=0;
    for(ll i:pre){
        if(i>=0&&is_lms[i]){
            sorted_lms.push_back(i);
        }
    }
    cnt=0;
    for(ll i:lms){
        comp_lms[i]=cnt++;
    }
    ll now=0;
    if(lms.size()>0)new_S[comp_lms[sorted_lms[0]]]=0;
    rep(i,1,(ll)sorted_lms.size()){
        ll x=sorted_lms[i-1];
        ll y=sorted_lms[i];
        ll p=0;
        while(1){
            if(S[x+p]!=S[y+p]||is_lms[x+p]!=is_lms[y+p]){
                now++;
                break;
            }
            if(p>0&&is_lms[x+p])break;
            p++;
        }
        new_S[comp_lms[sorted_lms[i]]]=now;
    }
    if(now+1==lms.size()){
        reverse(sorted_lms.begin(),sorted_lms.end());
        induced_sort(S,l,sorted_lms,size+1,pre);
        pre.erase(pre.begin());
        return pre;
    }
    for(ll &c:new_S)c++;
    new_S.push_back(0);
    vel res=make_sa(new_S);
    vel ordered_lms;
    rrep(i,res.size(),0){
        ordered_lms.push_back(lms[res[i]]);
    }
    induced_sort(S,l,ordered_lms,size+1,pre);
    pre.erase(pre.begin());
    return pre;
}

vel suffix_array(string &s){
    vel S(s.size()+1);
    rep(i,0,s.size())S[i]=(unsigned char)s[i]+1;
    return make_sa(S);
}


vel lcp_array(string &S,vel &sa,vel &ord){
    ll N=S.size();
    vel lcp(N-1);
    ll h=0;
    rep(i,0,N){//S[i:i+h]=S[j:j+h]なときにS[i+1:i+1+(h-1)]=S[j+1:j+1+(h-1)]
        if(ord[i]<N-1){
            ll j=sa[ord[i]+1];
            if(h>0)h--;
            while(i+h<N&&j+h<N&&S[i+h]==S[j+h])h++;
            lcp[ord[i]]=h;
        }
    }
    return lcp;
}

void _solve(){
    cin>>N>>L>>K;
    cin>>S;
    if(L*K>N){
        cout<<"NO\n";
        return ;
    }
    vel R(N);
    rep(i,0,N){
        ll cnt=1;
        if(i!=0){
            ll l=i;
            if(l<L){
                R[i]=-1;
                continue;
            }
            cnt=min(K-1,l/L);
            if(cnt==0){
                R[i]=-1;
                continue;
            }
            cnt++;
        }
        ll X=K-cnt;
        X*=L;
        R[i]=N-X-i;
    }
    vel sa=suffix_array(S);
    vel rsa(sa.size());
    rep(i,0,sa.size())rsa[sa[i]]=i;
    vel lcp=lcp_array(S,sa,rsa);
    seg<ll,Combine> st(lcp,Combine(),1e8);
    ll ans=0;
    rep(i,1,N){
        ll ai=rsa[ans];
        ll ni=rsa[i];
        if(R[i]<L)continue;
        ll comon=st.Ique(min(ai,ni),max(ai,ni));
        if(comon<min(R[i],R[ans])){
            if(ai<=ni)ans=i;
        }else{
            if(R[ans]<=R[i])ans=i;
        }
    }
    cout<<"YES\n";
    cout<<S.substr(ans,R[ans])<<"\n";
}




int main(){
    cin.tie(nullptr);
 	ios_base::sync_with_stdio(false);

    
    ll _;
    bool multitest=1;
    if(multitest)cin>>_;
    else _=1;
    rep(__,0,_){
        _solve();
    }
}