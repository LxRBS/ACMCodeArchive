#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;

long long powt(long long a,long long b)
{
    long long r = 1;
    while(b)
    {
        if(b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

int main()
{
    long long t,n,m;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&m);
        printf("%lld\n",((powt(m,n + 1) - 1) * powt(m - 1,mod - 2) % mod + mod) % mod);
    }
    return 0;
}
