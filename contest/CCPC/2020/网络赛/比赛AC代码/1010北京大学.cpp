#include<bits/stdc++.h>
using namespace std;

int T,n,a[110];

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n); bool bo=1;
        for (int i=1; i<=n; i++)
        {
            scanf("%d",&a[i]);
            if (i!=1&&a[i]==a[i-1]) bo=0;
        }
        puts(bo?"YES":"NO");
    }
    return 0;
}