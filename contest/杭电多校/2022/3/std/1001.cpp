#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=262144,K=17,P=998244353,G=3;
int Case,n,i,x;
int pos[N+5],A[N+5],B[N+5],W[N+5],g[K+5],ng[K+5],inv[N+5],inv2;
int p[N+5],invp[N+5],cost[N+5],w[N+5],pre[N+5];
int ea[N+5],eb[N+5],fa[N+5],fb[N+5];
inline int po(int a,int b){int t=1;for(;b;b>>=1,a=1LL*a*a%P)if(b&1)t=1LL*t*a%P;return t;}
inline void NTT(int*a,int n,int t){
  for(int i=1;i<n;i++)if(i<pos[i])swap(a[i],a[pos[i]]);
  for(int d=0;(1<<d)<n;d++){
    int m=1<<d,m2=m<<1,_w=t==1?g[d]:ng[d];
    for(int i=0;i<n;i+=m2)for(int w=1,j=0;j<m;j++){
      int&A=a[i+j+m],&B=a[i+j],t=1LL*w*A%P;
      A=B-t;if(A<0)A+=P;
      B=B+t;if(B>=P)B-=P;
      w=1LL*w*_w%P;
    }
  }
  if(t==-1)for(int i=0,j=inv[n];i<n;i++)a[i]=1LL*a[i]*j%P;
}
void solve(int l,int r){
  if(l==r){
    if(l){
      ea[l+1]=((ea[l]-(1LL-p[l])*fa[l]%P*pre[l])%P+P)*invp[l]%P;
      eb[l+1]=((eb[l]-cost[l]-(1LL-p[l])*fb[l]%P*pre[l])%P+P)*invp[l]%P;
    }
    return;
  }
  int mid=(l+r)>>1;
  solve(l,mid);
  int k=1;
  while(k<r-l+1)k<<=1;
  for(int i=0;i<k;i++)A[i]=B[i]=W[i]=0;
  for(int i=l;i<=mid;i++)A[i-l]=ea[i],B[i-l]=eb[i];
  for(int i=1;i<=r-l;i++)W[i]=w[i];
  int j=__builtin_ctz(k)-1;
  for(int i=0;i<k;i++)pos[i]=pos[i>>1]>>1|((i&1)<<j);
  NTT(A,k,1);
  NTT(B,k,1);
  NTT(W,k,1);
  for(int i=0;i<k;i++)A[i]=1LL*A[i]*W[i]%P,B[i]=1LL*B[i]*W[i]%P;
  NTT(A,k,-1);
  NTT(B,k,-1);
  for(int i=mid+1;i<=r;i++){
    fa[i]=(fa[i]+A[i-l])%P;
    fb[i]=(fb[i]+B[i-l])%P;
  }
  solve(mid+1,r);
}
int main(){
  for(g[K]=po(G,(P-1)/N),ng[K]=po(g[K],P-2),i=K-1;~i;i--)g[i]=1LL*g[i+1]*g[i+1]%P,ng[i]=1LL*ng[i+1]*ng[i+1]%P;
  for(inv[1]=1,i=2;i<=N;i++)inv[i]=1LL*(P-inv[P%i])*(P/i)%P;inv2=inv[2];
  scanf("%d",&Case);
  while(Case--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
      scanf("%d%d",&x,&cost[i]);
      p[i]=1LL*x*inv[100]%P;
      invp[i]=100LL*inv[x]%P;
    }
    for(i=1;i<n;i++){
      scanf("%d",&w[i]);
      pre[i]=(pre[i-1]+w[i])%P;
    }
    for(i=1;i<n;i++)pre[i]=po(pre[i],P-2);
    for(i=0;i<=n;i++)fa[i]=fb[i]=0;
    ea[0]=1,eb[0]=0;
    ea[1]=1,eb[1]=(P-cost[0])%P;
    solve(0,n-1);
    int ans=1LL*(P-eb[n])*po(ea[n],P-2)%P;
    printf("%d\n",(ans+P)%P);
  }
}