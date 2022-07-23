#include<bits/stdc++.h>
using namespace std;
struct mat
{
    double dis[2010][2010];
    int len;
}F,G,H,tmp;
double x[2010],y[2010];
int split[2010][2010];
int n,k;
void p(mat &a)
{
    cout << a.len << endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout << a.dis[i][j] << ' ';
        cout << endl;
    }
}
void mul(mat &a,mat &b,mat &c)
{
    if(b.len==0)
    {
        c=a;
        return ;
    }
    int len1=a.len;
    int len2=b.len;
    int len3=len1+len2;
    for(int l=len3;l<n;l++)
    {
        if(l==len3)
        {
            for(int L=1;L+l<=n;L++)
            {
                tmp.dis[L][L+l]=a.dis[L][L+len1]+b.dis[L+len1][L+l];
                split[L][L+l]=L+len1;
            }
            continue;
        }
        for(int L=1;L+l<=n;L++)
        {
            int R=L+l;
            tmp.dis[L][R]=0;
            for(int s=split[L][R-1];s<=split[L+1][R];s++)
                if(a.dis[L][s]+b.dis[s][R]>tmp.dis[L][R])
                {
                    tmp.dis[L][R]=a.dis[L][s]+b.dis[s][R];
                    split[L][R]=s;
                }
        }
    }
    c.len=len3;
    for(int i=1;i<=n;i++)
        for(int j=i+c.len;j<=n;j++)
            c.dis[i][j]=tmp.dis[i][j];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",x+i,y+i);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            F.dis[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
            H.dis[i][j]=F.dis[i][j];
        }
    F.len=1;
    int b=k-1;
    while(b)
    {
        if(b&1)
            mul(F,G,G);
        mul(F,F,F);
        b>>=1;
    }
    double ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+k-1;j<=n;j++)
            ans=max(ans,G.dis[i][j]+H.dis[i][j]);
        
    printf("%.9lf\n",ans);
    return 0;
}
/*
4 3
1 1
1 -1
-1 -1
-1 1

8 3
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
*/
