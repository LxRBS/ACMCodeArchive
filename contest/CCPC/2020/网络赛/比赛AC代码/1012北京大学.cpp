#include<bits/stdc++.h>
using namespace std;

long long f[31][3][2][2][2][2],ans;
int T,A,B,K,W,ta[31],tb[31],tw[41];

long long solve()
{
    for (int i=0; i<30; i++) ta[i]=(A>>i&1),tb[i]=(B>>i&1),tw[i]=(W>>i&1);
    memset(f,0,sizeof(f));
    f[30][1][1][1][1][1]=1;
    for (int i=30; i; i--)
        for (int j=0; j<3; j++)
            for (int k=0; k<2; k++)
                for (int l=0; l<2; l++)
                    for (int o=0; o<2; o++) 
                    for (int m=0; m<2; m++)if (f[i][j][k][l][o][m])
                    {
                        long long nw=f[i][j][k][l][o][m];
                        for (int x=0; x<((k==1&&(!ta[i-1]))?1:2); x++)
                            for (int y=0; y<((l==1&&(!tb[i-1]))?1:2); y++)
                            {
                                if (x<y&&m||(x^y)&&tw[i-1]==0&&o) continue;
                                int kt=(x<ta[i-1]?0:k),lt=(y<tb[i-1]?0:l),ot=((x^y)<tw[i-1]?0:o),mt=((x>y)?0:m);
                                if (j==2)
                                {
                                    if (x==0&&y==1) f[i-1][(K>>(i-1)&1)?1:2][kt][lt][ot][mt]+=nw; else
                                    if ((K>>(i-1)&1)&&x==y) f[i-1][2][kt][lt][ot][mt]+=nw;
                                } else
                                {
                                    if (x>y&&!(K>>(i-1)&1))
                                    {
                                        if (j==0) f[i-1][0][kt][lt][ot][mt]+=nw; else
                                        f[i-1][2][kt][lt][ot][mt]+=nw;
                                    } else
                                    {
                                        if (x<y||x==y&&(K>>(i-1)&1)) f[i-1][0][kt][lt][ot][mt]+=nw;
                                        else f[i-1][j][kt][lt][ot][mt]+=nw;
                                    }
                                }
                            }
                    }
    long long ans=0;
    for (int j=0; j<2; j++)
        for (int k=0; k<2; k++)
            for (int l=0; l<2; l++)
                for (int o=0; o<2; o++)
                    ans+=f[0][j][k][l][o][0]+f[0][j][k][l][o][1];
    return ans;
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d%d%d%d",&A,&B,&K,&W);
        ans=solve(),swap(A,B),ans+=solve(),ans-=(1+min(A,B));
        printf("%lld\n",ans);
    }
    return 0;
}