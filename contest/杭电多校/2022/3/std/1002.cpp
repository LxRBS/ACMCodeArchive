#include<cstdio>
typedef long long ll;
const int N=18,M=100005;
int Case,n,i,j,S,t[N],d[N],l,r,ans,mid,sum[(1<<N)+1];
ll hp,f[(1<<N)+1],dmg[N][M];
inline void up(ll&a,ll b){a<b?(a=b):0;}
bool check(int T){
  int S,i;
  for(S=0;S<1<<n;S++)f[S]=-1;
  f[0]=0;
  for(S=0;S<1<<n;S++){
    ll w=f[S];
    if(w<0)continue;
    if(w>=hp)return 1;
    int cur=sum[S];
    if(cur>T)continue;
    for(i=0;i<n;i++)if(!(S>>i&1)){
      if(cur+d[i]-1<=T)up(f[S|(1<<i)],w+dmg[i][d[i]-1]);
      else up(f[S|(1<<i)],w+dmg[i][T-cur]);
    }
  }
  return 0;
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%lld",&n,&hp);
    ans=-1,l=r=0;
    for(i=0;i<n;i++){
      scanf("%d%d",&t[i],&d[i]);
      r+=t[i]+d[i]-1;
      for(j=0;j<d[i];j++)scanf("%lld",&dmg[i][j]);
      for(j=1;j<d[i];j++)dmg[i][j]+=dmg[i][j-1];
    }
    for(S=1;S<1<<n;S++)sum[S]=sum[S-(S&-S)]+t[__builtin_ctz(S&-S)];
    while(l<=r){
      mid=(l+r)>>1;
      if(check(mid))r=(ans=mid)-1;else l=mid+1;
    }
    printf("%d\n",ans);
  }
}