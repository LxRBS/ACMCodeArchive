#include<bits/stdc++.h>
using namespace std;

const int N=50+5;
int a[N][N],K[4][4];

int main()
{
    int tt;
    cin>>tt;
    while(tt--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)scanf("%d",a[i]+j);
        int sum=0;
        for(int i=1;i<=3;++i)
        for(int j=1;j<=3;++j)
        {
            scanf("%d",K[i]+j);
            sum+=K[i][j];
        }
        for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)printf("%d%c",a[i][j]*(sum==K[1][1])," \n"[j==n]);
    }
}