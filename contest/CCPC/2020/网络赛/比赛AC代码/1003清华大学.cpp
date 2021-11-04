#include<bits/stdc++.h>
#define L long long
using namespace std;
int t,n,m,k,a[1000010];
L p;
int main()
{
    int i,j;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(i=1;i<=m;i++)
            scanf("%d",&a[i]);
        p=2*(k-1);
        for(i=1,j=0;i<=m;i++)
        {
            p+=2*abs(a[i]-k);
            if(a[i]<k)
                j=max(j,2*(k-a[i]));
        }
        p-=j;
        cout<<p<<"\n";
    } 
    return 0;
}