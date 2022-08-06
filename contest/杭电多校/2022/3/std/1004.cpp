#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=20,M=1<<N,K=1<<(N/2),P=998244353;
const ll inf=1LL<<60;
int Case,n,m,fir,sec,cq,i,j,S,T,A,B,a[N],cnt[M+1],sum[M+1],ans[N+1],q[K+1];
ll pre[M+1],cur[M+1],base[M+1];
int st[K+1],en[K+1],head,tail;
struct E{int k;ll b;E(){}E(int _k,ll _b){k=_k,b=_b;}}h[120005];
inline bool cmp(int x,int y){return sum[x]<sum[y];}
inline void up(ll&a,ll b){a>b?(a=b):0;}
inline void insert(const E&e){
  while(head<tail&&(h[tail-1].b-h[tail].b)*(e.k-h[tail].k)<=(h[tail].b-e.b)*(h[tail].k-h[tail-1].k))tail--;
  h[++tail]=e;
}
inline void merge(int A,int B,int C,int D){
  head=tail+1;
  while(A<=B&&C<=D){
    if(h[A].k==h[C].k){
      insert(h[A].b<h[C].b?h[A]:h[C]);
      A++,C++;
      continue;
    }
    insert(h[A].k<h[C].k?h[A++]:h[C++]);
  }
  while(A<=B)insert(h[A++]);
  while(C<=D)insert(h[C++]);
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)scanf("%d",&a[i]);
    for(S=1;S<1<<n;S++){
      T=S&-S;
      cnt[S]=cnt[S-T]+1;
      i=__builtin_ctz(T);
      sum[S]=sum[S-T]+a[i];
      base[S]=base[S-T]+1LL*a[i]*a[i];
    }
    for(i=1;i<=n;i++)ans[i]=0;
    cur[0]=inf;
    for(S=1;S<1<<n;S++){
      cur[S]=1LL*sum[S]*sum[S];
      ans[1]=(ans[1]+cur[S])%P;
    }
    fir=n/2;
    sec=n-fir;
    for(i=2;i<=m;i++){
      for(S=1;S<1<<n;S++){
        pre[S]=cur[S];
        cur[S]=cnt[S]<=i?base[S]:inf;
      }
      for(A=0;A<1<<fir;A++){
        cq=0;
        for(T=A;;T=(T+1)|A){
          q[cq++]=T<<sec;
          if(T==(1<<fir)-1)break;
        }
        sort(q,q+cq,cmp);
        tail=0;
        for(B=0;B<1<<sec;B++){
          st[B]=tail+1;
          S=A<<sec|B;
          if(cnt[S]>=i-1)h[++tail]=E(sum[S],pre[S]+1LL*sum[S]*sum[S]);
          en[B]=tail;
        }
        for(j=0;j<sec;j++)for(B=0;B<1<<sec;B++)if(B>>j&1){
          int l=tail+1;
          merge(st[B],en[B],st[B^(1<<j)],en[B^(1<<j)]);
          st[B]=l;
          en[B]=tail;
        }
        for(B=0;B<1<<sec;B++){
          int l=st[B],r=en[B];
          if(l>r)continue;
          for(j=0;j<cq;j++){
            S=q[j]|B;
            if(cnt[S]<=i)continue;
            ll x=-2*sum[S];
            while(l<r&&h[l].k*x+h[l].b>h[l+1].k*x+h[l+1].b)l++;
            up(cur[S],h[l].k*x+h[l].b);
          }
        }
      }
      for(S=1;S<1<<n;S++){
        if(cnt[S]>i)cur[S]+=1LL*sum[S]*sum[S];
        ans[i]=(ans[i]+cur[S])%P;
      }
    }
    for(i=1;i<=m;i++)printf("%d\n",ans[i]);
  }
}