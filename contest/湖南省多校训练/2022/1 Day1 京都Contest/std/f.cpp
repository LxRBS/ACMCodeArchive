#include <bits/stdc++.h>
using namespace std;

using ll=long long;
#define rng(i,l,r) for(int i=int(l);i<int(r);i++)
#define rep(i,r) rng(i,0,r)
#define MAX_N 100005

ll n,x,ans,b[5];
vector<ll>a[5];
ll solve(){
    ll s=0,res=x;
    rng(i,1,5){
        rep(j,min(ll(a[i].size()),b[i])){
            s+=i;
            res-=a[i][j];
        }
    }
    if(res<0)return 0;
    vector<ll>q;
    rng(i,1,5){
        ll ss=0,cnt=0;
        rng(j,b[i],a[i].size()){
            cnt+=i;
            ss+=a[i][j];
            if(cnt==12){
                cnt=0;
                q.push_back(ss);
                ss=0;
            }
        }
    }
    sort(q.begin(),q.end());
    rep(i,q.size()){
        if(res>=q[i]){
            res-=q[i];
            s+=12;
        }
    }
    return s;
}
int main(){
    cin>>n>>x;
    ans=x%5LL;
    x=x-x%5LL;
    rep(i,n){
        ll p;
        cin>>p;
        if(p%5==0)continue;
        a[5-p%5].push_back(p+5-p%5);
    }
    rng(i,1,5)sort(a[i].begin(),a[i].end());
    ll ma=0;
    for(int i=0;i<12;i++){
        for(int j=0;j*2<12;j++){
            for(int k=0;k*3<12;k++){
                for(int l=0;l*4<12;l++){
                    b[1]=i,b[2]=j,b[3]=k,b[4]=l;
                    ma=max(ma,solve());
                }
            }
        }
    }
    ans+=ma;
    cout<<ans<<endl;
}
