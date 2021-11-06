#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        int ans=0;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            int x,sg;
            scanf("%d",&x);
            if(x%8!=0&&x%8!=7)
                sg=x;
            else
                if(x%8==0) sg=x-1;else sg=x+1;
            ans^=sg;
        }
        if(ans) printf("First player wins.\n");else printf("Second player wins.\n");
    }
    return 0;
}
