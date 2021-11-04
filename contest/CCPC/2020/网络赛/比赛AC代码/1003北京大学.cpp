#include<bits/stdc++.h>
using namespace std;

int main()
{
    int tt;
    cin>>tt;
    while(tt--)
    {
        int n,m,k;
        cin>>n>>m>>k;
        long long sum=abs(k-1);
        int mn=2e9;
        for(int i=1;i<=m;++i)
        {
            int x;
            scanf("%d",&x);    
            sum+=2*abs(k-x);
            mn=min(mn,abs(x-1)-abs(x-k));
        }
        cout<<sum+mn<<endl;
    }
}