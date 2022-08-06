#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long double ld;
const int N=100010,M=262150,K=35;
const ld eps=1e-10;
int Case,n,m,i,op,x,y,q[N],h[N],vf[M][K],vg[M][K],F[K],G[K];
struct P{int x,y;}a[N];
struct E{ld x,y;E(){}E(ld _x,ld _y){x=_x,y=_y;}};
inline ld dis(const E&a,const E&b){return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
inline E center(const E&x,const E&y,const E&z){
  ld a1=y.x-x.x,b1=y.y-x.y,
     c1=(a1*a1+b1*b1)/2,a2=z.x-x.x,
     b2=z.y-x.y,c2=(a2*a2+b2*b2)/2,
     d=a1*b2-a2*b1;
  return E(x.x+(c1*b2-c2*b1)/d,x.y+(a1*c2-a2*c1)/d);
}
inline bool cmp0(int x,int y){
  if(a[x].x!=a[y].x)return a[x].x<a[y].x;
  return a[x].y>a[y].y;
}
inline bool cmp1(int x,int y){
  if(a[x].x!=a[y].x)return a[x].x<a[y].x;
  return a[x].y<a[y].y;
}
inline void merge0(int*A,int*B,int*C){
  int cnt=0,i=0,j=0,t=0;
  while(A[i]&&B[j])q[cnt++]=cmp0(A[i],B[j])?A[i++]:B[j++];
  while(A[i])q[cnt++]=A[i++];
  while(B[j])q[cnt++]=B[j++];
  for(i=0;i<cnt;i++){
    j=q[i];
    if(i&&a[j].x==a[q[i-1]].x)continue;
    while(t>1&&1LL*(a[h[t]].y-a[h[t-1]].y)*(a[j].x-a[h[t]].x)<=1LL*(a[j].y-a[h[t]].y)*(a[h[t]].x-a[h[t-1]].x))t--;
    h[++t]=j;
  }
  for(i=1;i<=t;i++)C[i-1]=h[i];
  C[t]=0;
}
inline void merge1(int*A,int*B,int*C){
  int cnt=0,i=0,j=0,t=0;
  while(A[i]&&B[j])q[cnt++]=cmp1(A[i],B[j])?A[i++]:B[j++];
  while(A[i])q[cnt++]=A[i++];
  while(B[j])q[cnt++]=B[j++];
  for(i=0;i<cnt;i++){
    j=q[i];
    if(i&&a[j].x==a[q[i-1]].x)continue;
    while(t>1&&1LL*(a[h[t]].y-a[h[t-1]].y)*(a[j].x-a[h[t]].x)>=1LL*(a[j].y-a[h[t]].y)*(a[h[t]].x-a[h[t-1]].x))t--;
    h[++t]=j;
  }
  for(i=1;i<=t;i++)C[i-1]=h[i];
  C[t]=0;
}
inline void up(int x){
  merge0(vf[x<<1],vf[x<<1|1],vf[x]);
  merge1(vg[x<<1],vg[x<<1|1],vg[x]);
}
void build(int x,int a,int b){
  if(a==b){
    vf[x][0]=vg[x][0]=a;
    vf[x][1]=vg[x][1]=0;
    return;
  }
  int mid=(a+b)>>1;
  build(x<<1,a,mid),build(x<<1|1,mid+1,b);
  up(x);
}
void change(int x,int a,int b,int c){
  if(a==b)return;
  int mid=(a+b)>>1;
  if(c<=mid)change(x<<1,a,mid,c);else change(x<<1|1,mid+1,b,c);
  up(x);
}
void ask(int x,int a,int b,int c,int d){
  if(c<=a&&b<=d){
    merge0(F,vf[x],F);
    merge1(G,vg[x],G);
    return;
  }
  int mid=(a+b)>>1;
  if(c<=mid)ask(x<<1,a,mid,c,d);
  if(d>mid)ask(x<<1|1,mid+1,b,c,d);
}
inline int cal(){
  int n=0,i,j,k;
  static E b[K*2];
  for(i=0;F[i];i++)b[n++]=E(a[F[i]].x,a[F[i]].y);
  for(i=0;G[i];i++)b[n++]=E(a[G[i]].x,a[G[i]].y);
  random_shuffle(b,b+n);
  E O=b[0];
  ld R=0;
  for(i=1;i<n;i++)if(dis(b[i],O)>R+eps)
    for(O=b[i],R=0,j=0;j<i;j++)if(dis(b[j],O)>R+eps){
      O=E((b[i].x+b[j].x)/2,(b[i].y+b[j].y)/2);
      R=dis(O,b[i]);
      for(k=0;k<j;k++)if(dis(b[k],O)>R+eps)O=center(b[k],b[j],b[i]),R=dis(O,b[i]);
    }
  return ceil(R);
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
    build(1,1,n);
    while(m--){
      scanf("%d",&op);
      if(op==1){
        scanf("%d",&x);
        scanf("%d%d",&a[x].x,&a[x].y);
        change(1,1,n,x);
      }else{
        scanf("%d%d",&x,&y);
        F[0]=G[0]=0;
        ask(1,1,n,x,y);
        printf("%d\n",cal());
      }
    }
  }
}