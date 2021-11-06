#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
struct segment
{
    int a[3];
}t[N<<2];
int n,cnt,x,T;
inline void build(int x,int l,int r)
{
    if(l==r)return;
    if(r==l+1)
     {
         build(t[x].a[0]=++cnt,l,l);
         build(t[x].a[1]=++cnt,r,r);
         return;
     }
    int len=(r-l)/3+1;
    int a=l+len-1,b=a+r>>1;
    build(t[x].a[0]=++cnt,l,a);
    build(t[x].a[1]=++cnt,a+1,b);
    build(t[x].a[2]=++cnt,b+1,r);
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--){
    cnt=1;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&x);
    build(1,1,n);
    printf("%d\n",cnt);
    }
}
 