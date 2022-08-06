#include<stdio.h>
#include<string.h>
#include<random>

#define U unsigned
#define LL long long
#define UL U LL


int t[10];
int g[10][5];
char w[3000000];

void dfs(int n,int c,int idx)
{
    int m=9999999;
    if(n)
    for(int a=1;a<=7;a++)
    for(int b=1;b<=7;b++)
    {
        int p[5]={0,a,b,b,a};
        memset(g,1,sizeof g);
        for(int i=0;i<=4;i++)
            g[0][i]=i;
        for(int i=0;i<=7;i++)
            g[i][0]=i;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=4;j++)
                g[i][j]=std::min(std::min(g[i-1][j]+1,g[i-1][j-1]+(t[i]!=p[j])),g[i][j-1]+1);
        if(g[n][4]<m)m=g[n][4];
    }
    if(n)w[idx]=m;
    if(n==7)return;
    n++;
    for(int i=1;i<=c;i++)
    {
        t[n]=i;
        dfs(n,c,idx*8+i);
    }
    t[n]=c+1;
    dfs(n,c+1,idx*8+c+1);
}

char s[1000001];
int dp[1000001];
int last[26];
int pre[1000001];
void sol()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    memset(dp+1,10,n*4);
    memset(last,-1,sizeof last);

    for(int i=1;i<=n;i++)
    {
        pre[i]=last[s[i]-'a'];
        last[s[i]-'a']=i;
    }

    for(int i=0;i<n;i++)
    {
        dp[i+1]=std::min(dp[i+1],dp[i]+1);
        int cnt=0;
        int idx=0;
        int tmp[8];

        for(int j=1;j<=7&&i+j<=n;j++)
        {
            int c=s[i+j]-'a';
            if(pre[i+j]<=i)
                idx=idx*8+ (tmp[j]=++cnt);
            else
                idx=idx*8+ (tmp[j]=tmp[pre[i+j]-i]);
            dp[i+j]=std::min(dp[i+j],dp[i]+w[idx]);
        }
    }
    printf("%d\n",dp[n]);
}

int main()
{
    dfs(0,0,0);
    int t;
    scanf("%d",&t);
    while(t--)sol();
}
