#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=15,M=35,K=21155;
int Case,n,m,cnt,ce,base,i,j,k,f[N],v[N],pre[K][M],cur[K][M];
ull pool[K];
map<ull,int>T;
struct E{int x,y,w,t;E(){}E(int _x,int _y,int _w,int _t){x=_x,y=_y,w=_w,t=_t;}}e[M*2];
inline bool cmp(const E&a,const E&b){
  if(a.w!=b.w)return a.w<b.w;
  return (!a.t)<(!b.t);
}
void dfs(int x,int y){
  if(x>n){
    ull S=0;
    for(int i=1;i<=n;i++)S=S<<4|f[i];
    T[S]=++cnt;
    pool[cnt]=S;
    return;
  }
  for(int i=1;i<=y+1;i++){
    f[x]=i;
    dfs(x+1,i>y?i:y);
  }
}
inline void up(int&a,int b){a<b?(a=b):0;}
inline void clr(){for(int i=1;i<=cnt;i++)for(int j=0;j<=m;j++)cur[i][j]=-1;}
inline void nxt(){for(int i=1;i<=cnt;i++)for(int j=0;j<=m;j++)pre[i][j]=cur[i][j];}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    ce=cnt=base=0;
    T.clear();
    for(i=1;i<=m;i++){
      int x,y,a,b;
      scanf("%d%d%d%d",&x,&y,&a,&b);
      if(a<b){
        e[++ce]=E(x,y,a,1);
        e[++ce]=E(x,y,b,0);
      }else{
        base++;
        e[++ce]=E(x,y,b,-1);
        e[++ce]=E(x,y,a,0);
      }
    }
    sort(e+1,e+ce+1,cmp);
    dfs(1,0);
    clr();
    cur[cnt][base]=0;
    for(i=1;i<=ce;i++){
      int x,y,w,t;
      x=e[i].x,y=e[i].y,w=e[i].w,t=e[i].t;
      nxt();
      clr();
      for(j=1;j<=cnt;j++){
        ull S=pool[j];
        for(k=n;k;k--){
          f[k]=S&15;
          S>>=4;
        }
        int o=j,A=f[x],B=f[y],tmp=A==B?0:w;
        if(A!=B){
          int A=f[x],B=f[y];
          for(k=1;k<=n;k++)if(f[k]==A)f[k]=B;
          int now=0;
          for(k=1;k<=n;k++)v[k]=0;
          for(k=1;k<=n;k++)if(!v[f[k]])v[f[k]]=++now;
          S=0;
          for(k=1;k<=n;k++)S=S<<4|v[f[k]];
          o=T[S];
        }
        if(t==0){
          for(k=0;k<=m;k++)if(~pre[j][k])up(cur[o][k],pre[j][k]+tmp);
        }else{
          for(k=0;k<=m;k++)if(~pre[j][k])up(cur[j][k],pre[j][k]);
          if(t>0){
            for(k=0;k<m;k++)if(~pre[j][k])up(cur[o][k+1],pre[j][k]+tmp);
          }else{
            for(k=1;k<=m;k++)if(~pre[j][k])up(cur[o][k-1],pre[j][k]+tmp);
          }
        }
      }
    }
    for(i=0;i<=m;i++)printf("%d\n",cur[1][i]);
  }
}