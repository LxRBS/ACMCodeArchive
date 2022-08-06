#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005,inf=2100000000;
int Case,n,m,i,x,y,a[N],b[N],c[N],d[N];
struct E{int x,y,w;}e[N];
inline bool cmp(const E&a,const E&b){return a.w<b.w;}
inline void up(int&a,int b){a<b?(a=b):0;}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
    sort(e+1,e+n+1,cmp);
    a[n+1]=b[n+1]=c[n+1]=d[n+1]=-inf;
    for(i=n;i;i--){
      a[i]=max(a[i+1],-e[i].x-e[i].y);
      b[i]=max(b[i+1],-e[i].x+e[i].y);
      c[i]=max(c[i+1],e[i].x-e[i].y);
      d[i]=max(d[i+1],e[i].x+e[i].y);
    }
    while(m--){
      scanf("%d%d",&x,&y);
      int l=1,r=n,mid,tmp,ans=0;
      while(l<=r){
        mid=(l+r)>>1;
        tmp=x+y+a[mid];
        up(tmp,x-y+b[mid]);
        up(tmp,-x+y+c[mid]);
        up(tmp,-x-y+d[mid]);
        if(e[mid].w<tmp){
          l=mid+1;
          up(ans,e[mid].w);
        }else{
          r=mid-1;
          up(ans,tmp);
        }
      }
      printf("%d\n",ans);
    }
  }
}