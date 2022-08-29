#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int ans=1;
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]); ans=1LL*ans*(a[i]+1)%MOD;
        }
        dec(ans,1);
        printf("%d\n",ans);
    }
    return 0;
}

