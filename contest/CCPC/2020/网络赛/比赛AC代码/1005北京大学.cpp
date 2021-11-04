#include<bits/stdc++.h>
using namespace std;

const int N=sqrt(1e9)+5;
bool mark[N];
int pr[N],pcnt;

int F(int n)
{
    if(n==1)return 0;
int c=n%2==0;
    while(n%2==0)n/=2;
    int g=sqrt(n);
    for(int i=1;pr[i]<=g;++i)
    if(n%pr[i]==0)
    {
        ++c;
        while((n/=pr[i])%pr[i]==0)++c;
        g=sqrt(n);
    }
    return c+(n>1);
}

int main()
{
    for(int i=2;i<N;++i)
    if(!mark[i])
    {
        pr[++pcnt]=i;
        for(int j=i+i;j<N;j+=i)mark[j]=1;
    }
    pr[pcnt+1]=1e6;
    //cerr<<pcnt<<endl;
    
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int ans=0;
        int n;
        scanf("%d",&n);
        while(n--)
        {
            int x;
            scanf("%d",&x);
            ans^=F(x);
        }
        puts(ans?"W":"L");
    }
}