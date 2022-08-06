#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=100000+105;
int Case,n,M,W,H,i,j,k,x,y;
int cp,pool[N*2];
int ce,cb,cnt;
struct Block{
  int l,r,bl,br,st,en;
  Block(){}
  Block(int _l,int _r){l=_l;r=_r;bl=l/W;br=r/W;}
}block[N*4];
struct E{
  int b,x,y,t;
  E(){}
  E(int _b,int _x,int _y,int _t){b=_b;x=_x;y=_y;t=_t;}
}e[N*2];
struct Area{
  int yl,yr,xl,xr;
  Area(){}
  Area(int _yl,int _yr,int _xl,int _xr){yl=_yl,yr=_yr,xl=_xl,xr=_xr;}
  ull cal(){return 1ULL*(yr-yl+1)*(xr-xl+1);}
}area[N*8];
int f[N*8];
ull sz[N*8],ans;
inline bool cmpe(const E&a,const E&b){return a.b==b.b?a.y<b.y:a.b<b.b;}
inline void ext(int x,int y){
  pool[++cp]=x/W;
  e[++ce]=E(x/W,x,y,0);
  if(x%W==0)return;
  x+=W-1;
  pool[++cp]=x/W;
  e[++ce]=E(x/W,x,y,1);
}
int F(int x){return f[x]==x?x:f[x]=F(f[x]);}
inline void merge(int x,int y){
  x=F(x),y=F(y);
  if(x==y)return;
  sz[y]+=sz[x];
  f[x]=y;
}
inline bool check(int al,int ar,int bl,int br){return al<=br&&bl<=ar;}
inline void analyze(int o,int l,int r){
  int i,j,k,m,_;
  static int py[N*4],q0[N*2],q1[N*2];
  int L=block[o].l,R=block[o].r;
  py[_=1]=M;
  for(i=l;i<=r;i++){
    py[++_]=e[i].y-1;
    py[++_]=e[i].y+H-1;
  }
  sort(py+1,py+_+1);
  for(m=0,i=1;i<=_;i++)if(py[i]>py[m])py[++m]=py[i];
  int h0=1,t0=0,h1=1,t1=0;
  block[o].st=cnt+1;
  for(i=1,j=l;i<=m;i++){
    while(j<=r&&e[j].y<=py[i-1]+1){
      if(e[j].t==0){
        while(h0<=t0&&e[q0[t0]].x>=e[j].x)t0--;
        q0[++t0]=j;
      }else{
        while(h1<=t1&&e[q1[t1]].x<=e[j].x)t1--;
        q1[++t1]=j;
      }
      j++;
    }
    int up=L,down=R;
    while(h0<=t0&&e[q0[h0]].y+H-1<py[i])h0++;
    if(h0<=t0)down=min(down,e[q0[h0]].x-1);
    while(h1<=t1&&e[q1[h1]].y+H-1<py[i])h1++;
    if(h1<=t1)up=max(up,e[q1[h1]].x+1);
    if(up<=down){
      area[++cnt]=Area(py[i-1]+1,py[i],up,down);
      sz[cnt]=area[cnt].cal();
      f[cnt]=cnt;
    }
  }
  int nowl=block[o].st,nowr=block[o].en=cnt;
  for(i=nowl;i<nowr;i++)
    if(area[i].yr+1==area[i+1].yl&&check(area[i].xl,area[i].xr,area[i+1].xl,area[i+1].xr))
      merge(i,i+1);
  if(o==1)return;
  int prel=block[o-1].st,prer=block[o-1].en;
  for(i=nowl,j=prel,k=prel-1;i<=nowr;i++){
    if(area[i].xl!=L)continue;
    while(j<=prer&&area[j].yr<area[i].yl)j++;
    while(k<prer&&area[k+1].yl<=area[i].yr)k++;
    for(_=j;_<=k;_++)if(area[_].xr+1==L)merge(i,_);
  }
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d%d%d",&n,&M,&W,&H);
    pool[1]=0;
    pool[cp=2]=(M-1)/W;
    ce=cb=cnt=0;
    while(n--){
      scanf("%d%d",&x,&y);
      x--;
      ext(x,y);
    }
    sort(pool+1,pool+cp+1);
    for(i=1;i<=cp;i++){
      if(i>1&&pool[i]==pool[i-1])continue;
      int l=pool[i]*W;
      if(cb&&l>block[cb].r+1){
        cb++;
        block[cb]=Block(block[cb-1].r+1,l-1);
      }
      block[++cb]=Block(l,min(l+W-1,M-1));
    }
    sort(e+1,e+ce+1,cmpe);
    for(i=j=1;i<=cb;i++){
      for(k=j;k<=ce&&e[k].b<=block[i].br;k++);
      analyze(i,j,k-1);
      j=k;
    }
    ans=0;
    for(i=1;i<=cnt;i++)if(F(i)==i)ans+=sz[i]*sz[i];
    printf("%llu\n",ans);
  }
}