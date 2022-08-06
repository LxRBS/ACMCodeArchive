#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=50005,M=100005,Q=50005,K=785,B=325;
int Case,n,m,q,all,ce,i,j,k,x,y,l,r,g[N],v[M],nxt[M],que[Q][2],en[M];
ull f[N][K],h[Q*2/B+3][K],cur[K];
struct E{int x,y;E(){}E(int _x,int _y){x=_x,y=_y;}}e[Q*2];
inline bool cmp(const E&a,const E&b){return a.x<b.x;}
inline void flip(ull*f,int x){f[x>>6]^=1ULL<<(x&63);}
inline void clr(ull*f){for(int i=0;i<=all;i++)f[i]=0;}
inline void copy(ull*f,ull*g){for(int i=0;i<=all;i++)f[i]=g[i];}
inline void trans(ull*f,ull*g,ull*h){for(int i=0;i<=all;i++)f[i]|=g[i]&h[i];}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d%d",&n,&m,&q);
    for(i=1;i<=m;i++){
      scanf("%d%d",&x,&y);
      v[i]=y;
      nxt[i]=g[x];
      g[x]=i;
    }
    all=(q-1)>>6;
    for(i=1;i<=n;i++)clr(f[i]);
    for(i=0;i<q;i++){
      scanf("%d%d%d%d",&x,&y,&l,&r);
      que[i][0]=x;
      que[i][1]=y;
      flip(f[y],i);
      e[++ce]=E(l,i);
      e[++ce]=E(r+1,i);
    }
    sort(e+1,e+ce+1,cmp);
    for(i=1,j=0;i<=m;i++){
      while(j<ce&&e[j+1].x<=i)j++;
      en[i]=j;
    }
    clr(cur);
    for(i=1;i<=ce;i++){
      flip(cur,e[i].y);
      if(i%B==0)copy(h[i/B],cur);
    }
    for(i=n;i;i--)for(j=g[i];j;j=nxt[j]){
      x=en[j];
      copy(cur,h[x/B]);
      for(k=x/B*B+1;k<=x;k++)flip(cur,e[k].y);
      trans(f[i],f[v[j]],cur);
    }
    for(i=0;i<q;i++)puts(f[que[i][0]][i>>6]>>(i&63)&1?"YES":"NO");
    for(i=1;i<=n;i++)g[i]=0;
    ce=0;
  }
}