#include<cstdio>
const int N=55;
int Case,n,i,j,k,o,now,ans;
struct P{
  int x,y,z;
  P(){}
  P(int _x,int _y,int _z){x=_x,y=_y,z=_z;}
  P operator-(const P&p)const{return P(x-p.x,y-p.y,z-p.z);}
  P operator*(const P&p)const{return P(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
  int operator^(const P&p)const{return x*p.x+y*p.y+z*p.z;}
  bool operator==(const P&p)const{return x==p.x&&y==p.y&&z==p.z;}
}p[N*2];
inline int ptoplane(const P&a,const P&b,const P&c,const P&p){return((b-a)*(c-a))^(p-a);}
inline bool colinear(const P&a,const P&b,const P&p){
  P t=(a-b)*(b-p);
  return !t.x&&!t.y&&!t.z;
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d",&n);
    for(i=0;i<n+n;i++)scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
    ans=1;
    for(i=0;i<n+n;i++)for(j=0;j<i;j++){
      if(p[i]==p[j])continue;
      for(k=0;k<j;k++){
        if(p[i]==p[k])continue;
        if(p[j]==p[k])continue;
        if(colinear(p[i],p[j],p[k]))continue;
        now=0;
        for(o=0;o<n;o++){
          int x=ptoplane(p[i],p[j],p[k],p[o<<1]);
          int y=ptoplane(p[i],p[j],p[k],p[o<<1|1]);
          if(!x||!y||(x<0&&y>0)||(x>0&&y<0))now++;
        }
        if(now>ans)ans=now;
      }
      now=0;
      for(o=0;o<n;o++)
        if(colinear(p[i],p[j],p[o<<1])||colinear(p[i],p[j],p[o<<1|1]))
          now++;
      if(now>ans)ans=now;
    }
    printf("%d\n",ans);
  }
}