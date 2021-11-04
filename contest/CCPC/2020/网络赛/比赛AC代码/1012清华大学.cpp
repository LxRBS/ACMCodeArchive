#include<bits/stdc++.h>
#define L long long
using namespace std;
int t,n,m,k,w;
L dp[35][2][2][2][2][2][2];
inline L calc(int n,int m,int k,int w)
{
    int i,a,b,c,d,e,f,x,y,z;
    int aa,bb,cc,dd,ee,ff;
    L p;
    memset(dp,0,sizeof(dp));
    dp[30][0][0][0][0][0][0]=1;
    for(i=29;i>=0;i--)
        for(a=0;a<2;a++)
        for(b=0;b<2;b++)
        for(c=0;c<2;c++)
        for(d=0;d<2;d++)
        for(e=0;e<2;e++)
        for(f=0;f<2;f++)
        if(p=dp[i+1][a][b][c][d][e][f])
            for(x=0;x<2;x++)
            for(y=0;y<2;y++)
            for(z=0;z<2;z++)
            if(!(!a && x && !(n&(1<<i)) || !b && y && !(m&(1<<i)) || !c && z && !(k&(1<<i)) || !d && x!=y && !(w&(1<<i)) || !e && y>x || x+f+f-y-z<0 || x+f+f-y-z>1))
            {
                aa=a,bb=b,cc=c,dd=d,ee=e;
                if(!x && (n&(1<<i)))
                    aa=1;
                if(!y && (m&(1<<i)))
                    bb=1;
                if(!z && (k&(1<<i)))
                    cc=1;
                if(x==y && (w&(1<<i)))
                    dd=1;
                if(y<x)
                    ee=1;
                ff=x+f+f-y-z;
                dp[i][aa][bb][cc][dd][ee][ff]+=p;
            }
    p=0;
    for(a=0;a<2;a++)
    for(b=0;b<2;b++)
    for(c=0;c<2;c++)
    for(d=0;d<2;d++)
    for(e=0;e<2;e++)
        p+=dp[0][a][b][c][d][e][0];
    return p;
    
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d",&n,&m,&k,&w);
        cout<<calc(n,m,k,w)+calc(m,n,k,w)-min(n,m)-1<<"\n";
    }
    return 0;
}