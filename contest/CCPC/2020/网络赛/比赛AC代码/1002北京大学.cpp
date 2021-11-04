#include<bits/stdc++.h>
using namespace std;

int T,mod,m,sq;
long long n,w[200010],x,s0[200010],s1[200010];

int pos(const long long &x)
{
    return x<=sq?x:m-n/x+1;
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%lld%d",&n,&mod),n++;
        sq=sqrtl(n),m=0;
        for (long long i=1; i<=n; i=w[m]+1)
        {
            w[++m]=n/(n/i);
            x=w[m]%mod;
            s0[m]=(x+mod-1)%mod;
            s1[m]=(x*(x+1)/2-1+mod)%mod;
        }
        for (int i=2; i<=sq; i++)
        {
            if (s0[i]==s0[i-1]) continue;
            long long si=1ll*i*i;
            for (int j=m; w[j]>=si; --j)
                s0[j]=(1ll*s0[j]-s0[pos(w[j]/i)]+s0[i-1])%mod,
                s1[j]=(s1[j]-1ll*(s1[pos(w[j]/i)]-s1[i-1])*i)%mod;
        }
        long long ans=(1ll*(n%mod)*((n-1)%mod)/2+n-1+(s1[pos(n)]%mod))%mod;
        ans=(ans-4+2ll*mod)%mod;
        printf("%lld\n",ans);
    }
}