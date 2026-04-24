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


void induced_sort(vector<int> &S,vector<bool> &l,vector<int> &lms,ll size,vel &ans){//lmsが完成してるときにl,s型を伸ばして全体に波及させる
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

vel make_sa(vector<int> &S){//S+$をいれられてSのsaを返す
    vector<bool> l(S.size());//S[i]>S[i+1]ですか？
    vector<bool> is_lms(S.size());
    rrep(i,(ll)S.size()-1,0){
        if(S[i]==S[i+1]){
            l[i]=l[i+1];
        }else{
            l[i]=S[i]>S[i+1];
        }
    }
    vector<int> lms;//極小なindexたち
    int size=S[0];
    rep(i,1,S.size()){
        size=max(size,S[i]);
        if(l[i-1]&&l[i]==0){
            is_lms[i]=1;
            lms.push_back(i);
        }
    }
    vel pre(S.size(),-1);
    induced_sort(S,l,lms,size+1,pre);//これでlms単体の順序が正しく並んでるので隣り合ったやつたちを見ることで新しいlmsかを判定できる
    vector<int> new_S(lms.size(),1);
    vector<int> comp_lms(S.size());//S->new_Sのindex(lmsしか見ない)
    vector<int> sorted_lms;//lmsがsortされてはいってる
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
    for(int &c:new_S)c++;
    new_S.push_back(0);
    vel res=make_sa(new_S);
    vector<int> ordered_lms;
    rrep(i,res.size(),0){
        ordered_lms.push_back(lms[res[i]]);
    }
    induced_sort(S,l,ordered_lms,size+1,pre);
    pre.erase(pre.begin());
    return pre;
}

vel suffix_array(string &s){
    vector<int> S(s.size()+1);
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
    cin>>N;
    vel a(N);
    rep(i,0,N)cin>>a[i];
    vepll v={{a[0],1}};
    string S="0";
    if(a[0]==1)S+="1";
    rep(i,1,N){
        if(a[i]==v.back().fi){
            v.back().se++;
            if(v.back().fi==v.back().se)S+=to_string(a[i]);
        }else{
            if(v.back().fi<v.back().se)S+="0"+to_string(v.back().fi);
            if(v.back().fi>v.back().se)S+="0";
            v.push_back({a[i],1});
            if(a[i]==1)S+=to_string(a[i]);
        }
    }
    vel sa=suffix_array(S);
    vel ord(sa.size());
    rep(i,0,sa.size())ord[sa[i]]=i;
    vel lcp=lcp_array(S,sa,ord);
    N=S.size();
    ll ans=0;
    vel n(N);
    ll now=N;
    rrep(i,S.size(),0){
        if(S[i]=='0')now=i;
        else n[i]=now;
    }
    //cout<<S<<"\n";
    rep(i,0,N){
        if(S[sa[i]]=='0')continue;
        else{
            if(i+1<N){
                ll m=lcp[i];
                //cout<<sa[i]<<" "<<n[sa[i]]<<" "<<m<<" "<<min(n[sa[i]]-sa[i],(N-sa[i]))-m<<"\n";
                ans+=max(0ll,min(n[sa[i]]-sa[i],(N-sa[i]))-m);
            }else{
                //cout<<sa[i]<<" "<<n[sa[i]]<<" "<<min(n[sa[i]]-sa[i],N-sa[i])<<"\n";
                ans+=min(n[sa[i]]-sa[i],N-sa[i]);
            }
        }
    }
    cout<<ans<<"\n";
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