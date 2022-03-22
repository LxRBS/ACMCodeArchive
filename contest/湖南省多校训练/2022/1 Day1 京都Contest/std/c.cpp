#include <bits/stdc++.h>
using namespace std;

using ll=long long;
#define rng(i,l,r) for(int i=int(l);i<int(r);i++)
#define rep(i,r) rng(i,0,r)
#define MAX_N 100005

ll n;
vector<pair<ll,ll>>x;
int main(){
    cin>>n;
    rep(i,n){
        ll a;
        cin>>a;
        x.push_back(make_pair(a,-1));
    }
    rep(i,n){
        ll b;
        cin>>b;
        x.push_back(make_pair(b,1));
    }
    x.push_back(make_pair(0,0));
    sort(x.begin(),x.end());
    ll s=0;
    rng(i,1,x.size()){
        x[i].second+=x[i-1].second;
        if(x[i-1].second<0)s+=(x[i].first-x[i-1].first)*2LL;
    }
    ll ans=s;
    ll ss=0;
    for(int i=x.size()-1;i>0;i--){
        if(x[i-1].second<0)ss-=(x[i].first-x[i-1].first)*2LL;
        ans=min(ans,s+ss+x.back().first-x[i-1].first);
    }
    cout<<ans+x.back().first<<endl;
}
