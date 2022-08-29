#include<bits/stdc++.h>
using namespace std;
int T,n,a[1000010],b[1000010];
long long solve(){
    bool tag=1;
    long long ans=0;
    for(int i=2,t;i<=n;i++){
        if(tag){
            t=max(b[i-1]+1-b[i],0);
            ans+=t;b[i]+=t;
        }else{
            t=max(b[i]+1-b[i-1],0);
            ans+=t;b[i]-=t;
        }
        tag^=1;
    }
    return ans;
}
int main(){
    // freopen("1003.in","r",stdin);
    // freopen("1003.out","w",stdout);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
        long long ans=solve();
        for(int i=1;i<=n;i++) b[i]=-a[i];
        printf("%lld\n",min(ans,solve()));
    }
    return 0;
}