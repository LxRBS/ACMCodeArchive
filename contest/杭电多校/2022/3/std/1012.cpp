#include<cstdio>
typedef unsigned long long ull;
const int N=300005,P=998244353,S=233;
int Case,n,i,j,k,x,y;
int a[N],b[N],c[N*2],pc[N][2],f[N][2],ans;
ull p[N*2],fb[N],fc[N*2];
inline void up(int&a,int b){a=a+b<P?a+b:a+b-P;}
inline ull ask(ull*f,int l,int r){return f[r]-f[l-1]*p[r-l+1];}
inline bool check(int bl,int br,int cl,int cr){
  if(bl>br)return 1;
  if(bl<1||br>n||cl<1||cr>n+n)return 0;
  return ask(fb,bl,br)==ask(fc,cl,cr);
}
int main(){
  for(p[0]=i=1;i<N*2;i++)p[i]=p[i-1]*S;
  scanf("%d",&Case);
  while(Case--){
    scanf("%d",&n);
    for(i=1;i<=n;i++)pc[i][0]=pc[i][1]=0;
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    for(i=1;i<=n;i++)scanf("%d",&b[i]),fb[i]=fb[i-1]*S+b[i];
    for(i=1;i<=n+n;i++){
      scanf("%d",&x);
      c[i]=x;
      fc[i]=fc[i-1]*S+x;
      if(!pc[x][0])pc[x][0]=i;else pc[x][1]=i;
    }
    for(i=1;i<=n;i++)if(!pc[i][0]||!pc[i][1])break;
    if(i<=n){
      puts("0");
      continue;
    }
    for(i=1;i<=n;i++)for(j=0;j<2;j++)f[i][j]=0;
    for(j=0;j<2;j++){
      x=pc[a[1]][j];
      if(check(1,x-1,1,x-1))f[1][j]=1;
    }
    for(i=1;i<n;i++)for(j=0;j<2;j++)if(f[i][j]){
      x=pc[a[i]][j];
      for(k=0;k<2;k++){
        y=pc[a[i+1]][k];
        if(y<=x)continue;
        if(check(x-i+1,y-i-1,x+1,y-1))up(f[i+1][k],f[i][j]);
      }
    }
    ans=0;
    for(j=0;j<2;j++)if(f[n][j]){
      x=pc[a[n]][j];
      if(check(x-n+1,n,x+1,n+n))up(ans,f[n][j]);
    }
    printf("%d\n",ans);
  }
}